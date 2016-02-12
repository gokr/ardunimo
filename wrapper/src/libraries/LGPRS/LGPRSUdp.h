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
#ifndef lgprsudp_h
#define lgprsudp_h

#include <Udp.h>
#include <LUdp.h>

//LGPRSUDP Class
// 
// Use this class to manipulate UDP datagrams after connecting to GPRS network with LGPRS
// See the method description of LUDP class
class LGPRSUDP : public LUDP {
  /* DOM-NOT_FOR_SDK-BEGIN */   
public:
  virtual int beginPacket(const char *host, uint16_t port);
  using LUDP::beginPacket;

protected:
  virtual VMINT getAPN() const;
  /* DOM-NOT_FOR_SDK-END */   
};

#endif
