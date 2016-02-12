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

#include "LSD.h"

#include "vmio.h"

static boolean _get_drv_handler(void* userdata);

/*****************************************************************************
* 
* LSD class
* 
*****************************************************************************/

LSDClass::LSDClass()
{

}

LSDClass::~LSDClass()
{

}

boolean LSDClass::begin()
{
    int drv;
    VM_DCL_HANDLE sd_handle;
    
    if(!changePinType(11, PIO_SD, &sd_handle))
		return false;

    LTask.remoteCall(_get_drv_handler, &drv);

    if(drv > 0)
    {
        initDrv(drv);
        return true;
    }
    else
    {
        return false;
    }
}

LSDClass LSD;

/*****************************************************************************
* 
* MMI part (running on MMI thread)
* 
*****************************************************************************/

static boolean _get_drv_handler(void* userdata)
{
#ifdef LINKITSTORAGE_DEBUG
    Serial.print("vm_get_removable_driver()=");
    Serial.println(vm_get_removable_driver());
#endif
    *((int*)userdata) = vm_get_removable_driver();
    return true;
}
