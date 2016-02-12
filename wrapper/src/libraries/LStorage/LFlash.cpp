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

#include "LFlash.h"

#include "vmio.h"

static boolean _get_drv_handler(void* userdata);

/*****************************************************************************
* 
* LFlash class
* 
*****************************************************************************/

LFlashClass::LFlashClass()
{

}

LFlashClass::~LFlashClass()
{

}

boolean LFlashClass::begin()
{
    int drv;
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

LFlashClass LFlash;

/*****************************************************************************
* 
* MMI part (running on MMI thread)
* 
*****************************************************************************/

static boolean _get_drv_handler(void* userdata)
{
#ifdef LINKITSTORAGE_DEBUG
    Serial.print("vm_get_system_driver()=");
    Serial.println(vm_get_system_driver());
#endif
    *((int*)userdata) = vm_get_system_driver();
    return true;
}
