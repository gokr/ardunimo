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

#include "arduino.h"
#include "vmpwr.h"
#include "Battery.h"

boolean batteryLevel(void* user_data)
{
	int level = vm_get_battery_level();
	*(int*)user_data = level;
  return true;
}

boolean batteryIsCharging(void* user_data)
{
	VMBOOL charging = vm_charbat_is_charging();
  *(boolean*)user_data = charging;
  return true;
}
