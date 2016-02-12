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
#include "vmio.h"
#include "vmlog.h"
#include "sysfile.h"
#include "LEEPROM.h"

#if defined(__LINKIT_ONE_DEBUG__)
#define APP_LOG(...) vm_log_info(__VA_ARGS__); \
    Serial.printf(__VA_ARGS__)
#else
#define APP_LOG(...)
#endif

fs_data_t g_fs_data;


boolean onRead(void* user_data)
{
    VMINT hdl, ret;
    fs_data_t *tmp_fs_data = (fs_data_t*)&g_fs_data;
    VMUINT read = 0;

    APP_LOG((char*)"EEPROM onRead -s");
    if (0 > tmp_fs_data->addr)
    {
        setReadData(0);
        APP_LOG((char*)"EEPROM fs_data->addr[%d] -e1", tmp_fs_data->addr);
        return true;
    }
    
    hdl = vm_sys_file_open(MODE_READ, 1);
    if (0 > hdl)
    {
        setReadData(0);
        APP_LOG((char*)"EEPROM hdl[%d] -e2", hdl);
        return true;
    }

    ret = vm_sys_file_seek(hdl, tmp_fs_data->addr, BASE_BEGIN);
    APP_LOG((char*)"EEPROM vm_sys_file_seek [%d][%d]", tmp_fs_data->addr, ret);

    ret = vm_sys_file_read(hdl, &(tmp_fs_data->value), 1, &read);
    APP_LOG((char*)"EEPROM vm_sys_file_read [%d][%d] v[%d]", read, ret, tmp_fs_data->value);
    
    setReadData(tmp_fs_data->value);

    vm_sys_file_close(hdl);
    
    APP_LOG((char*)"EEPROM onRead -e");
    return true;   
}
boolean onWrite(void* user_data)
{
    VMINT hdl, ret;
    VMINT init_data[1024] = {0};
    fs_data_t *tmp_fs_data = (fs_data_t*)&g_fs_data;
    VMUINT written = 0;
    
    APP_LOG((char*)"EEPROM onWrite -s");
    if (0 > tmp_fs_data->addr)
    {
        setReadData(0);
        APP_LOG((char*)"EEPROM fs_data->addr[%d] -e1", tmp_fs_data->addr);
        return true;
    }
    
    hdl = vm_sys_file_open(MODE_WRITE, 1);
    if (0 > hdl)
    {
        hdl = vm_sys_file_open(MODE_CREATE_ALWAYS_WRITE, 1);
        if (0 > hdl)
        {
            APP_LOG((char*)"EEPROM MODE_CREATE_ALWAYS_WRITE FAILED");
            return true;
        }
        else
      	{
            ret = vm_sys_file_seek(hdl, 0, BASE_BEGIN);
            ret = vm_sys_file_write(hdl, init_data, 1024, &written);
            APP_LOG((char*)"initialize data size: %d \n", written);
      	}
        APP_LOG((char*)"EEPROM MODE_CREATE_ALWAYS_WRITE OK");
    }

    APP_LOG((char*)"EEPROM vm_sys_file_open [%d]", hdl);

    ret = vm_sys_file_seek(hdl, tmp_fs_data->addr, BASE_BEGIN);
    APP_LOG((char*)"EEPROM vm_sys_file_seek [%d][%d]", tmp_fs_data->addr, ret);

    ret = vm_sys_file_write(hdl, &(tmp_fs_data->value), 1, &written);
    APP_LOG((char*)"EEPROM vm_sys_file_write [%d][%d] v[%d]", written, ret, tmp_fs_data->value);
    
    setReadData(tmp_fs_data->value);

    vm_sys_file_close(hdl);
    
    APP_LOG((char*)"EEPROM onWrite -e");
    return true;   
}

// be called in arduino task.
VMUINT8 getReadData()
{
    APP_LOG((char*)"getReadData [%d]", g_fs_data.value);
    return g_fs_data.value;
}

// mmi task set data
void setReadData(VMUINT8 data_read)
{
    g_fs_data.value = data_read;
    APP_LOG((char*)"setReadData [%d]", data_read);
}


