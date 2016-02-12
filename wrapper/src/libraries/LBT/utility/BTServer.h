
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

#ifndef BT_SERVER_H
#define BT_SERVER_H

#ifdef __cplusplus
extern "C" {
#endif


boolean btServerBegin(void *userData);
boolean btServerEnd(void *userData);
boolean btServerAccept(void *userData);
boolean btServerConnected(void *userData);
boolean btServerGetHostDeviceInfo(void *userData);
boolean btServerRead(void *userData);
boolean btServerWrite(void *userData);
 
#ifdef __cplusplus
}
#endif

#endif //#ifndef BT_SERVER_H