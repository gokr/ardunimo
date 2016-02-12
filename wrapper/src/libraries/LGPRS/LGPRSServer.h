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
#ifndef LGPRSServer_h
#define LGPRSServer_h
#include <Arduino.h>
#include <LTcpServer.h>
#include "LGPRSClient.h"

//LGPRSServer Class
// 
// See the method description of LTcpServer class
//
// 
// EXAMPLE:
// <code>
//     LGPRS.attach();
//     LGPRSServer server(80);
//     server.begin();  // start listening on port 80 via GPRS network
// </code>
class LGPRSServer : public LTcpServer {
public:
  LGPRSServer(uint16_t port);

  // DESCRIPTION
  //   Checks if there is a client connected.
  //   If there is one, an LGPRSClient object will be returned to represent the connection between this server object and the remote client. Call LGPRSClient.read()/LGPRSClient.write() to exchange data with the connected client.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   An LGPRSClient object representing the connection between this server object and the remote client.
  //   This object will turn to false if there is no incoming connection.
  LGPRSClient available();

  /* DOM-NOT_FOR_SDK-BEGIN */
  virtual VMINT getAPN() const;
  /* DOM-NOT_FOR_SDK-END */
};

#endif