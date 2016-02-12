/*
 GPRS Web Server

 A simple web server that shows a updating counter

 created 8 Mar 2012
 by Tom Igoe
Modified 20 Aug 2014
 by MediaTek Inc.
 */
#include <LGPRS.h>
#include <LGPRSClient.h>
#include <LGPRSServer.h>

LGPRSServer server(80); // port 80 (http)

void setup()
{
  // setup Serial port
  Serial.begin(115200);

  // detect APN
  while(!LGPRS.attachGPRS())
  {
    delay(500);
  }
  
  Serial.println("Connected to GPRS network");

  // start server
  server.begin();

  //Get IP.
  for(int i = 0; i < 5; ++i)
  {
    IPAddress localIP = server.serverIP();
    Serial.println("Server IP address=");
    Serial.println(localIP);
    delay(1000);
  }
}

void loop() {
  delay(50);
  // checking incoming clients
  LGPRSClient client = server.available();

  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        Serial.println("Receiving request!");
        bool sendResponse = false;
        while (int i = client.read()) {
          if ((char)i == '\n')
          {
            sendResponse = true;
            break;
          }
          if(i!=-1)
            Serial.print((char)i);
        }

        // if you've gotten to the end of the line (received a newline
        // character)
        if (sendResponse)
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(analogRead(analogChannel));
            client.println("<br />");
          }
          client.println("</html>");
          //necessary delay
          delay(1000);
          client.stop();
        }
      }
    }
  }
}


