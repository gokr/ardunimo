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
#include "vmgps.h"
#include "vmlog.h"
#include "GPS.h"
#include "LGPS.h"

typedef void (*vm_gps_handler_t)(vm_gps_sentence_info* info);
vm_gps_handler_t _gps_handle = NULL;

static void _gps_callback(VMINT msg, void* data)
{
     switch(msg)
     {
     case VM_GPS_OPEN_CNF:
         {
             VMINT result = (VMINT)data;
             if(result == true)
             {
                vm_log_info((char*)"open success");
             }
             else
             {
                 vm_log_warn((char*)"open failed");
             }
         }
         break;
     case VM_GPS_CLOSE_CNF:
         // app cannot receive this msg now, ignore this.
         break;
     case VM_GPS_SET_MODE_CNF:
         {
             VMINT result = (VMINT)data;
             if(result == true)
             {
             	  vm_log_info((char*)"set mode success");
             }
             else
	      {
             	  vm_log_warn((char*)"set mode failed");
             }
         }
         break;
     case VM_GPS_SENTENCE_DATA:
         {
            	LGPS.setData((gpsSentenceInfoStruct*)data);
         }
         break;
     }
 }

boolean gpsPowerOn(void* user_data)
{
  VMINT result;
  vm_gps_type_enum* type = (vm_gps_type_enum*)user_data;

  result = vm_gps_open( 1, *type, _gps_callback);
		     
  if(result == VM_GPS_OPEN_SUCCESS)
  {
      // this is first time to open GPS, need to get the message VM_GPS_OPEN_CNF
      vm_log_info((char*)"gps open success");
  }
  else if(result == VM_GPS_OPEN_ALREADY_OPEN)
  {
      // GPS had been opened before, can get data, no need to wait VM_GPS_OPEN_CNF
      // if need you can set mode
      // vm_gps_set_mode();
      vm_log_info((char*)"gps already open");

  }
  else
  {
      // open failed
      vm_log_info((char*)"gps open failed");
  }
  return true;
}

boolean gpsPowerOff(void* user_data)
{
  vm_gps_close();
  return true;
}

boolean gpsSetMode(void* user_data)
{
  vm_gps_mode_enum* mode = (vm_gps_mode_enum*)user_data;
  vm_gps_set_mode(*mode);
  return true;
}


