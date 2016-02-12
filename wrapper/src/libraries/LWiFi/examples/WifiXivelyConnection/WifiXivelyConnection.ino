/*
  Wifi Xively sensor client
 
 This sketch sends a simple time value to Xively (http://www.xively.com)
 using Wi-Fi functionality on LinkIt platform.

 Change the WIFI_AP, WIFI_PASSWORD and WIFI_AUTH accordingly.
 
 To make it work, create a feed ID with a datastream first. 
 Or change the code below to match your feed.

 created 13 Mar 2012
 modified 31 May 2012
 by Tom Igoe
 modified 8 Nov 2013
 by Scott Fitzgerald
 modified 20 Aug 2014
 by MediaTek Inc.

 This code is in the public domain.

 */

/*****************
 * This sample connectes to Xively.com API by LinkIt ONE WiFi module and keeps updating a feed in Xively.
 * You need to apply an Xively API key and create the feed first.
 */
#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiClient.h>

#define SITE_URL      "api.xively.com"  // Xively API URL
#define APIKEY         "apikey" // replace your xively api key here
#define FEEDID         0000         // replace your feed ID
#define USERAGENT      "chrome"     // user agent is the project name

#define WIFI_AP "yourssid"            // replace your WiFi AP SSID
#define WIFI_PASSWORD "yourpassword"  // replace your WiFi AP password
#define WIFI_AUTH LWIFI_WEP           // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP according to your AP

void setup()
{
  Serial.begin(115200);
  // Initializes LinkIt ONE WiFi module
  LWiFi.begin();

  Serial.print("Connecting to WiFi AP:");
  Serial.println(WIFI_AP);
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    delay(1000);
  }
}

unsigned long time = 0;

void loop()
{

  // in this sketch, we send to process time of loop()
  // to Xively server.
  // The feed is created on Xively first.
  unsigned long t1 = millis();

  Serial.print("try connect ");
  Serial.println(SITE_URL);
  LWiFiClient c;
  while (!c.connect(SITE_URL, 80))
  {
    Serial.println("retry connect");
    delay(100);
  }

  String data = "Time,"+String(time);
  Serial.println("send PUT request");
  Serial.println(data);

  // construct a HTTP PUT request
  // and set CSV data to the Xively feed.
  c.print("PUT /v2/feeds/");
  c.print(FEEDID);
  c.println(".csv HTTP/1.1");
  c.println("Host: api.xively.com");
  c.print("X-ApiKey: ");
  c.println(APIKEY);
  c.print("User-Agent: ");
  c.println(USERAGENT);
  c.print("Content-Length: ");
  int thisLength = data.length();
  c.println(thisLength);
  c.println("Content-Type: text/csv");
  c.println("Connection: close");
  c.println();
  c.println(data);

  // this is required delay, to allow server response
  delay(1000);
  // disconnect from server
  c.stop();
  // add delay to prevent connect again too fast
  delay(300);

  unsigned long t2 = millis();
  time = t2-t1;
  Serial.print("Total time spend (we will send this to server next time): ");
  Serial.println(time);
}
