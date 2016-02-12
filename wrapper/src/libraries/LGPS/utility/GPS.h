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


#ifndef _GPS_H
#define _GPS_H

#ifdef __cplusplus
extern "C" {
#endif

boolean gpsPowerOn(void* user_data);
boolean gpsPowerOff(void* user_data);
boolean gpsSetMode(void* user_data);

#ifdef __cplusplus
}
#endif

#endif

