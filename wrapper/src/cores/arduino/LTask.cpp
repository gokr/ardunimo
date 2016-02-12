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


#include "vmsys.h"
#include "vmthread.h"
#include "LTask.h"
#include "Arduino.h"


_LTaskClass::_LTaskClass()
{
	m_handle = 0;
	m_signal = 0;
}

void _LTaskClass::begin(void)
{
	vm_mutex_create(&m_mutex);
	m_handle = vm_thread_get_main_handle();
	m_signal = vm_signal_init();
}

void _LTaskClass::sendMsg(VMUINT32 msg_id, void* user_data)
{
	if(m_handle == 0)
	{
		begin();
	}
	if(m_handle != 0)
	{
		vm_thread_send_msg(m_handle, msg_id, user_data);
	}
}

void _LTaskClass::stop(void)
{
	m_handle = 0;
	vm_signal_clean(m_signal);
	vm_signal_deinit(m_signal);
	m_signal = 0;
}

void _LTaskClass::mutexLock()
{
	if(m_handle == 0)
	{
		begin();
	}
	
	vm_mutex_lock(&m_mutex);
}

void _LTaskClass::mutexUnlock()
{
	if(m_handle == 0)
	{
		begin();
	}
	
	vm_mutex_unlock(&m_mutex);
}

void _LTaskClass::post_signal()
{
	if(m_handle == 0)
	{
		begin();
	}
	
	vm_signal_post(m_signal);
}

void _LTaskClass::remoteCall(remote_call_ptr func,  void* userdata)
{
		if(m_handle == 0)
		{
			begin();
		}
    mutexLock();
    m_msg.remote_func = (remote_call_ptr)func;
    m_msg.userdata = userdata;
    m_msg.signal = m_signal;
    sendMsg(VM_MSG_ARDUINO_CALL, &m_msg);
    vm_signal_wait(m_signal);
    mutexUnlock();
}

_LTaskClass LTask = _LTaskClass();

