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
#ifndef BT_CLIENT_H
#define BT_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

boolean btClientBegin(void *userData);
boolean btClientEnd(void *userData);
boolean btClientConnect(void *userData);
boolean btClientConnected(void *userData);
boolean btClientScan(void *userData);
boolean btClientGetDeviceInfo(void *userData);
boolean btClientRead(void *userData);
boolean btClientWrite(void *userData);

#ifdef __cplusplus
}
#endif

#endif //#ifndef BT_CLIENT_H