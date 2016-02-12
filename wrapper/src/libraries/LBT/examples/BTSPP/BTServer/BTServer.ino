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
#include <LBTServer.h>
#define SPP_SVR "ARD_SPP" // it is the server's visible name, customize it yourself.
#define ard_log Serial.printf

int read_size = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ard_log("start BTS\n");

  bool success = LBTServer.begin((uint8_t*)SPP_SVR);
  if( !success )
  {
      ard_log("Cannot begin Bluetooth Server successfully\n");
      // don't do anything else
      delay(0xffffffff);
  }
  else
  {
      LBTDeviceInfo info;
      if (LBTServer.getHostDeviceInfo(&info))
      {
          ard_log("LBTServer.getHostDeviceInfo [%02x:%02x:%02x:%02x:%02x:%02x]", 
            info.address.nap[1], info.address.nap[0], info.address.uap, info.address.lap[2], info.address.lap[1], info.address.lap[0]);
      }
      else
      {
          ard_log("LBTServer.getHostDeviceInfo failed\n");
      }
      ard_log("Bluetooth Server begin successfully\n");
  }
 
  // waiting for Spp Client to connect
  bool connected = LBTServer.accept(1800);
 
  if( !connected )
  {
      ard_log("No connection request yet\n");
      // don't do anything else
      delay(0xffffffff);
  }
  else
  {
      ard_log("Connected\n");
  }
}

int sent = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (!sent)
  {
      char buffer[32] = {0};
      //int read_size = LBTServer.read((uint8_t*)buffer, 32);
      //vm_log_info("spec read size [%d][%s]", read_size);
      
      char* buffer_w = "LinkIt BT Server";
      int write_size = LBTServer.write((uint8_t*)buffer_w, strlen(buffer_w));
      ard_log("write_size [%d]", write_size);
      

      memset(buffer, 0, sizeof(buffer));
      while(1)
      {
        if(LBTServer.available())
        {
          read_size = LBTServer.readBytes((uint8_t*)buffer, 32);
          break;
        }
        delay(100);
      }
      ard_log("read size [%d][%s]", read_size, buffer);

      memset(buffer, 0, sizeof(buffer));
      while(1)
      {
        if(LBTServer.available())
        {
          read_size = LBTServer.readBytes((uint8_t*)buffer, 32);
          break;
        }
        delay(100);
      }
      ard_log("read size [%d][%s]", read_size, buffer);

    
      sent = 1;
  }
  ard_log("loop server\n");
  delay(2000);
}
