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
#ifndef LGPRS_h
#define LGPRS_h

#include "Arduino.h"
#include "IPAddress.h"
#include "vmnwsetting.h"
#include "vmconn.h"

class LGPRSConnectContext;

//LGPRS Class
class LGPRSClass
{
public:

	/* DOM-NOT_FOR_SDK-BEGIN */
    LGPRSClass();
    /* DOM-NOT_FOR_SDK-END */	

    // DESCRIPTION
    //  Sets up the Access Point Name (APN) information used to connect to GPRS network. Use the data provided by your telecom operator to set it up
    // 
    // PARAMETERS
    //  apn: char string, Access Point Name (APN) provided by the telecom operator
    //  username: char string, username provided by the telecom operator. Pass NULL if the telecom operator does not provide the username information.
    //  password: char string, password provided by the telecom operator. Pass NULL if the telecom operator does not provide the password information.
    //
    // RETURN
    //  1: APN setup succeeded
    //  0: Otherwise
    int attachGPRS(const char *apn, const char *username, const char *password);

    // DESCRIPTION
    //  Automatically detect Access Point Name (APN) information from SIM card and use it to connect to GPRS network.
    // 
    // RETURN
    //  1: APN setup succeeded
    //  0: Otherwise
    int attachGPRS();

    // DESCRIPTION
    //  Resolve the given hostname to an IP address.
    // 
    // PARAMETERS
    //  aHostname: a string, URL Name to be resolved
    //  aResult: IPAddress structure to store the returned IP address
    // 
    // RETURNS
    //  1 if aIPAddrString was successfully converted to an IP address, 
    //  else error code
    int hostByName(const char* aHostname, IPAddress& aResult); 

    VMINT getAPN() const;
    friend class LGPRSServer;
    friend class LGPRSClient;
    
private:
    boolean m_simCardReady;
    boolean m_customAPN;
    static boolean gprsCheckSIM(void *userData);
};

extern LGPRSClass LGPRS;

#endif // #ifndef LGPRS_h