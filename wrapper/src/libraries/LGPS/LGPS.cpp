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


#include "Arduino.h"
#include "GPS.h"
#include "LGPS.h"

extern void handle_gps_evt(int message, int param);

void LGPSClass::powerOn(gpsTypeEnum type)
{
	begin();
	remoteCall(gpsPowerOn, (void*)&type);
}

void LGPSClass::powerOff(void){
	remoteCall(gpsPowerOff, (void*)NULL);
}

void LGPSClass::setMode(gpsModeEnum mode){
    remoteCall(gpsSetMode, (void*)&mode);  
}

void LGPSClass::getData(gpsSentenceInfoStruct* info){
    	memcpy(info, &m_info, sizeof(gpsSentenceInfoStruct));
}

void LGPSClass::setData(gpsSentenceInfoStruct* info) {
	memcpy(&m_info, info, sizeof(gpsSentenceInfoStruct));
}

LGPSClass LGPS;

