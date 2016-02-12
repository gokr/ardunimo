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
#include <LEEPROM.h>

#define ard_log Serial.printf

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  ard_log("setup\n");
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  ard_log("loop\n");
  delay(2000);
  
    byte a = 1;
  

  EEPROM.write(0, a);
  ard_log("written\n");
  delay(1000);
  byte b = EEPROM.read(0);
  ard_log("read [%d]\n", b);
  if (a == b)
  {
  	// do something.
  	delay(1000);
  }
  
  
  

}
