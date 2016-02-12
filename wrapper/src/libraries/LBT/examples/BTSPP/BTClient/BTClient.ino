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
#include <LBT.h>
#include <LBTClient.h>


static LBTDeviceInfo info = {0};
boolean find = 0;
#define SPP_SVR "ARD_SPP" // it should be the prefer server's name,  customize it yourself.
#define ard_log Serial.printf
int read_size = 0;
void setup()  
{
  Serial.begin(9600);
  ard_log("LBT start\n");
  // begin BT
  bool success = LBTClient.begin();
  if( !success )
  {
      ard_log("Cannot begin Bluetooth Client successfully\n");
      delay(0xffffffff);
  }
  else
  {
      ard_log("Bluetooth Client begin successfully\n");
      // scan the devices around
      int num = LBTClient.scan(30);
      ard_log("scanned device number [%d]", num);
      for (int i = 0; i < num; i++)
      {
        memset(&info, 0, sizeof(info));
        // to check the prefer master(server)'s name
        if (!LBTClient.getDeviceInfo(i, &info))
        {
            continue;
        }
        ard_log("getDeviceInfo [%02x:%02x:%02x:%02x:%02x:%02x][%s]", 
            info.address.nap[1], info.address.nap[0], info.address.uap, info.address.lap[2], info.address.lap[1], info.address.lap[0],
            info.name);
        if (0 == strcmp(info.name, SPP_SVR))
        {
            find = 1;
            ard_log("found\n");
            break;
        }
      }
      
  }
}
 
void loop()
{

    // to check if the connection is ready
    if(find && !LBTClient.connected())
    {
        ard_log("Diconnected, try to connect\n");
        // do connect
        bool conn_result = LBTClient.connect(info.address);
        ard_log("connect result [%d]", conn_result);
 
        if( !conn_result )
        {
            ard_log("Cannot connect to SPP Server successfully\n");
            delay(0xffffffff);
        }
        else
        {
            ard_log("Connect to SPP Server successfully\n");
        }

        char buffer[32] = {0};
        int write_size = LBTClient.write((uint8_t*)"123456789012", 12);
        ard_log("client first spec write_size [%d]", write_size);

        // to read the data from master(server)
        while(1)
        {
           if(LBTClient.available())
           {
           read_size = LBTClient.readBytes(buffer,32);
           break;
           }
           delay(100);
        }
        ard_log("read size [%d][%s]", read_size, buffer);
        

        write_size = LBTClient.write((uint8_t*)"LinkIt BT Client", 16);
        ard_log("write_size [%d]", write_size);
        
        
        find = 0;
    }
    ard_log("loop client\n");
    delay(2000);

}
