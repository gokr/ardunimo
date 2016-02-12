/*
  Copyright (c) 2014 MediaTek Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License..

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU Lesser General Public License for more details.
*/

#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>
#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiClient.h>

#define WIFI_AP "your_ap_ssid"
#define WIFI_PASSWORD "your_password"
#define WIFI_AUTH LWIFI_WEP  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP according to your WiFi AP configuration

// This sample connects to HTTP server and download a file to LinkIt ONE internal storage

#define SITE_URL "www.yourwebsite.com"
#define FILE_NAME "/url_to_file.zip"
#define DOWNLOAD_FILENAME "file_downloaded.zip"

#define TEMP_BUF_SIZE (2048)
uint8_t buf[TEMP_BUF_SIZE] = {0};

void setup()
{
  LWiFi.begin();
  Serial.begin(115200);
  LFlash.begin();

  // keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    delay(1000);
  }

  LWiFiClient c;

  // keep retrying until connected to website
  Serial.println("Connecting to WebSite");
  while (0 == c.connect(SITE_URL, 80))
  {
    Serial.println("Re-Connecting to WebSite");
    delay(1000);
  }

  Serial.println("send GET request");
  c.println("GET " FILE_NAME " HTTP/1.0");
  c.println("User-Agent: Wget/1.11.4");
  c.println("Accept: */*");
  c.println("Host: " SITE_URL);
  c.println("Connection: Close");
  c.println();

  Serial.println("waiting server response");
  int peekByte = -1;
  while (peekByte == -1 && c.connected())
  {
    peekByte = c.peek();
    delay(200);
  }

  // wait for header finish (\r\n\r\n)
  Serial.println("skipping header:");
  int lineFeedCount = 0;
  while (lineFeedCount < 2)
  {
    int value = c.read();
    if (value == -1)
    {
      delay(10);
      continue;
    }

    Serial.print((char)value);

    if (value == '\r')
    {
      value = -1;
      while (value == -1)
      {
        value = c.read();
        Serial.print((char)value);
      }

      if (value == '\n')
      {
        lineFeedCount++;
      }
      else
      {
        lineFeedCount = 0;
      }
    }
    else
    {
      lineFeedCount = 0;
    }
  }

  Serial.println("start downloading file");
  LFile f = LFlash.open(DOWNLOAD_FILENAME, FILE_WRITE);
  int totalSize = 0;
  while (c.connected())
  {
    size_t bytesRead = c.read(buf, TEMP_BUF_SIZE);
    if (bytesRead)
    {
      const size_t bytesWrite = f.write((const uint8_t *)&buf[0], (size_t)bytesRead);
      if (bytesWrite > 0)
      {
        totalSize += bytesWrite;
        Serial.print("\r");
        Serial.print(totalSize);
        Serial.print(" bytes");
      }
      else
      {
        Serial.println("error writing file");
        break;
      }
    }
    else
    {
      Serial.println("server disconnected");
      break;
    }
    delay(100);
  }
  f.flush();
  f.close();
  Serial.println();
  Serial.println("download finished");
}

void loop()
{
  delay(1000);
}


