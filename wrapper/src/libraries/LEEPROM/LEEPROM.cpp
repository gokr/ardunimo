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

#include "vmsys.h"
#include "LEEPROM.h"
#include "sysfile.h"
#include "vmlog.h"

#if defined(__LINKIT_ONE_DEBUG__)
#define APP_LOG(...) vm_log_info(__VA_ARGS__); \
    Serial.printf(__VA_ARGS__)
#else
#define APP_LOG(...)
#endif
//extern void app_log_file(char *fmt, ...);


LEEPROMClass::LEEPROMClass(int init) : _LTaskClass(), m_init(init)
{
    //Serial.println("LEEPROMClass::LEEPROMClass");
    //APP_LOG((char*)"LEEPROMClass::LEEPROMClass");
    //_LTaskClass::begin();
    //APP_LOG((char*)"LEEPROMClass::LEEPROMClass");
}

/*

LEEPROMClass::~LEEPROMClass()
{
    //APP_LOG((char*)"LEEPROMClass::~LEEPROMClass");
    //_LTaskClass::stop();
    //APP_LOG((char*)"LEEPROMClass::~LEEPROMClass");
}
*/
VMUINT8 LEEPROMClass::read(int addr)
{
    APP_LOG((char*)"LEEPROMClass::read [%d]", addr);
    if (!m_init)
    {
        _LTaskClass::begin();    
        m_init = 1;
    }

    if (0 > addr || 1024 <= addr)
    {
        APP_LOG((char*)"LEEPROMClass::read e1");
        return 0;
    }
    g_fs_data.addr = addr;
    APP_LOG((char*)"remoteCall onRead s");
	remoteCall(onRead, (void*)NULL);
    APP_LOG((char*)"remoteCall onRead e");
	return getReadData();
}

void LEEPROMClass::write(int addr, uint8_t value)
{
    APP_LOG((char*)"LEEPROMClass::write @[%d] value[%d]", addr, value);
    if (!m_init)
    {
        _LTaskClass::begin();    
        m_init = 1;
    }

    if (0 > addr || 1024 <= addr)
    {
        APP_LOG((char*)"LEEPROMClass::write e1");
        return;
    }
    g_fs_data.addr = addr;
    g_fs_data.value = value;
    APP_LOG((char*)"remoteCall onWrite s");
	remoteCall(onWrite, (void*)NULL);
    APP_LOG((char*)"remoteCall onWrite e");
    //return 0;
}

LEEPROMClass & getEEPROM(void)
{
    
    static LEEPROMClass EEPROM_internal(0);
    return EEPROM_internal;
}

