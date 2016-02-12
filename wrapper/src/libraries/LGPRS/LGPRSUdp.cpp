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
#include <Arduino.h>
#include "LGPRSUdp.h"
#include "LGPRS.h"
#include "vmtcp.h"

VMINT LGPRSUDP::getAPN() const
{
    return LGPRS.getAPN();
}

int LGPRSUDP::beginPacket(const char *host, uint16_t port)
{
	// DNS loopup and bypass to IP version
	int ret = LGPRS.hostByName(host, m_sendToIP);
	if(ret)
	{
		return beginPacket(m_sendToIP, port);	
	}
	else
	{
		return 0;
	}
}

