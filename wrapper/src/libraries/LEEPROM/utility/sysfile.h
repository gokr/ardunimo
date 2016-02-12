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
#ifndef _SYSFILE_H
#define _SYSFILE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    VMINT addr;
    VMUINT8 value;
}fs_data_t;

extern fs_data_t g_fs_data;

boolean onRead(void* user_data);
boolean onWrite(void* user_data);

VMUINT8 getReadData();
void setReadData(VMUINT8 data_read);

#ifdef __cplusplus
}
#endif

#endif

