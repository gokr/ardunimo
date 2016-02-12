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
#ifndef LGPRSClient_h
#define LGPRSClient_h
#include "Arduino.h"
#include <LTcpClient.h>
#include <vmconn.h>
#include <vmtcp.h>

//LGPRSClient Class
// 
// See the method description of LTcpClient class
//
// EXAMPLE:
// <code>
//     LGPRS.attachGPRS();
//     LGPRSClient c;
//     c.connect("www.website.com", 80);
// </code>
class LGPRSClient : public LTcpClient {
public:
  LGPRSClient();
  
  /* DOM-NOT_FOR_SDK-BEGIN */
  LGPRSClient(const LTcpClient &rhs);
  LGPRSClient(VMINT handle);
  LGPRSClient(VMINT handle, VMINT serverHandle);
  virtual VMINT getAPN() const;
  /* DOM-NOT_FOR_SDK-END */
};

#endif  // LGPRSClient_h