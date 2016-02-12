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
#include "LGPRSServer.h"
#include <vmconn.h>
#include <vmtcp.h>
#include "LGPRS.h"

LGPRSServer::LGPRSServer(uint16_t port):
  LTcpServer(port)
{
}

LGPRSClient LGPRSServer::available()
{
	VMINT hClient = -1;
	VMINT hServer = -1;
	availableImpl(hClient, hServer);
	// return a special client object that has server handle
	// Note that we rely on move-constructor optimization
	// to prevent temp object destructor, which stop() the connection.
	return LGPRSClient(hClient, hServer);
}

VMINT LGPRSServer::getAPN() const
{
  return LGPRS.getAPN();
}