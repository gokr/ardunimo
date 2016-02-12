/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 20 Aug 2014 by MediaTek Inc.
  
*/

#define ARDUINO_MAIN
#include "Arduino.h"
#include "vmsys.h"
#include "vmthread.h"
#include "vmpromng.h"
#include "vmlog.h"
#include "vmtel.h"

typedef VMINT (*vm_get_sym_entry_t)(char* symbol);
extern vm_get_sym_entry_t vm_get_sym_entry;

extern "C" void vm_thread_change_priority(VM_THREAD_HANDLE thread_handle, VMUINT32 new_priority);

unsigned char* spi_w_data = NULL;
unsigned char* spi_r_data= NULL;
unsigned char* spi_data_memory= NULL;
vm_call_listener_func g_call_status_callback = NULL;

void __handle_sysevt(VMINT message, VMINT param) 
{
    if(message == VM_MSG_ARDUINO_CALL)
    {
    	 msg_struct* pMsg = (msg_struct*)param;
    	 if(pMsg->remote_func(pMsg->userdata))
        {
        	vm_signal_post(pMsg->signal);
    	 }
        return ;
    }
}

void __call_listener_func(vm_call_listener_data* data)
{
	if(g_call_status_callback)
	{
		g_call_status_callback(data);
	}
}

VMINT32 __arduino_thread(VM_THREAD_HANDLE thread_handle, void* user_data)
{
	init();

	delay(1);
	
	setup();

	for (;;)
	{
		loop();
		if (serialEventRun) serialEventRun();
	}
}

/*
 * \brief Main entry point of Arduino application
 */
void vm_main( void )
{
	VM_THREAD_HANDLE handle;
	spi_w_data = (unsigned char*)vm_malloc_nc(2);
	spi_r_data = (unsigned char*)vm_malloc_nc(2);
	srand(0);
	rand();
	spi_data_memory = (unsigned char*)vm_malloc_nc(64*1024);
	memset(spi_data_memory,0, 64*1024);
	vm_reg_sysevt_callback(__handle_sysevt);
	vm_call_reg_listener(__call_listener_func);
	handle = vm_thread_create(__arduino_thread, NULL, 0);
	vm_thread_change_priority(handle, 245);
}

