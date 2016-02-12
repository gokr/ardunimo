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


#ifndef _VMAUDIO_H
#define _VMAUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "chip.h"
#include "LAudio.h"

boolean audioPlay(void* user_data);
boolean audioPause(void* user_data);
boolean audioResume(void* user_data);
boolean audioSetVolume(void* user_data);
boolean audioStop(void* user_data);

#ifdef __cplusplus
}
#endif

#endif

