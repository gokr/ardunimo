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

#ifndef _LTaskClass_h
#define _LTaskClass_h

#include "vmsys.h"
#include "vmthread.h"
#include "message.h"

class _LTaskClass
{
private:
	vm_thread_mutex_struct m_mutex;
	msg_struct m_msg;
	VM_THREAD_HANDLE m_handle;
    VM_SIGNAL_ID m_signal;
	void sendMsg(VMUINT32 msg_id, void* user_data);

public:
	_LTaskClass();
	
	void begin(void);
	void mutexLock();
	void mutexUnlock();
	void stop(void);
	void remoteCall(remote_call_ptr func,  void* userdata);

public:
	void post_signal();

};

extern _LTaskClass LTask;

#endif

