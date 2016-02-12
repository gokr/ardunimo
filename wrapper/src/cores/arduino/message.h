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


#ifndef _MESSAGE_
#define _MESSAGE_
#include "Arduino.h"
#include "vmsys.h"
#include "vmthread.h"
#ifdef C2NIM
#include "wiring_constants.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define VM_MSG_ARDUINO_CALL  3000

typedef boolean (*remote_call_ptr)(void* user_data);

typedef struct _msg_struct
{
	VM_SIGNAL_ID signal;
	remote_call_ptr remote_func;
	void* userdata;
}msg_struct;

#ifdef __cplusplus
}
#endif

#endif /* _MESSAGE_ */

