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
#include "vmmm.h"
#include "vmchset.h"
#include "LAudio.h"
#include "Audio.h"
#include "vmlog.h"
#include "vmio.h"
#include "vmstdlib.h"

typedef void (*call_func_ptr)(int result);
call_func_ptr g_callback = NULL;


void audio_callback(VMINT result)
{
	if(g_callback)
		g_callback(result);
	return;
}

boolean audioPlay(void* user_data)
{
  VMWCHAR path[256];
  VMCHAR path_a[256];

  VMINT drv ;
  VMCHAR driver_str[2] = {0};

  if(LAudio.getDriver() ==0)
  {
  	drv = vm_get_system_driver();
  }
  else
  {
  	VM_DCL_HANDLE sd_handle;
  	drv = vm_get_removable_driver();
  	if(drv>=0)
  	{
  		 changePinType(11, PIO_SD, &sd_handle);
  	}
  }
  
  if(drv >=0)
  {
	
	if( LAudio.getType())
	{
  	    sprintf(path_a,"%c:\\%s", drv, LAudio.getFile());
	    vm_ascii_to_ucs2(path, 256, path_a);
	}
	else
	{
		sprintf(path_a,"%c:\\", drv);
		vm_ascii_to_ucs2(path, 256, path_a);
		vm_wstrcat(path, (VMWSTR)LAudio.getFile());
	}
  }
  else
  {
  	vm_log_info("AudioPlay get driver error");
	return true;
  }
  

  
  g_callback = (call_func_ptr)user_data;
  vm_audio_play_file(path, audio_callback);
  vm_set_volume(LAudio.getVolume());
  return true;
}

boolean audioPause(void* user_data)
{
  vm_audio_pause(audio_callback);
  if(g_callback)
	{
		g_callback(AudioPause);
	}
  return true;
}

boolean audioResume(void* user_data)
{
  vm_audio_resume(audio_callback);
  if(g_callback)
	{
		g_callback(AudioResume);
	}
  return true;
}

boolean audioStop(void* user_data)
{
  vm_audio_stop(audio_callback);
  if(g_callback)
	{
		g_callback(AudioStop);
	}
  return true;
}

boolean audioSetVolume(void* user_data)
{
  vm_set_volume(LAudio.getVolume());
  return true;
}


