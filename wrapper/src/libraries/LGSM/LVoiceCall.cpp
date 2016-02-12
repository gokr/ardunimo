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

#include "LGSM.h"

#include <vmsim.h>
#include <vmchset.h>
#include <vmstdlib.h>
#include "VoiceCall.h"
static call_info_struct callInfo;
static int ret;
static char status;

LVoiceCallClass::LVoiceCallClass()
{
	registerCallback();
}

LVoiceCallClass::~LVoiceCallClass()
{

}

int LVoiceCallClass::ready()
{
	ret = 0;
	remoteCall(callready, (void*)&ret);
	return ret;
}

int LVoiceCallClass::voiceCall(const char* to,  unsigned long timeout)
{
	strcpy(callInfo.num, to);
	remoteCall(callvoiceCall, (void*)&callInfo);
	return callInfo.result;
}

char LVoiceCallClass::getVoiceCallStatus(void)
{
    remoteCall(callgetVoiceCallStatus, (void*)&status);
    return status;
}

int LVoiceCallClass::answerCall(void)
{
	remoteCall(callanswerCall, &ret);
	return ret;
}

int LVoiceCallClass::retrieveCallingNumber(char* number, int nlength )
{

	memset(number, 0, nlength);

	remoteCall(callretrieveCallingNumber, (void*)&callInfo);
	
	if(callInfo.result == 1)
	{
		strcpy(number, callInfo.num);
		return 1;
	}
	else
	{
		return 0;
	}
}

int LVoiceCallClass::hangCall(void)
{
	remoteCall(callhangCall, (void*)&ret);
	return ret;
}

LVoiceCallClass LVoiceCall;

