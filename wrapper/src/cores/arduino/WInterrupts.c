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


#include "vmdcl.h"
#include "vmdcl_gpio.h"
#include "vmdcl_eint.h"
#include "vmlog.h"
#include "WInterrupts.h"

typedef struct _Exinterrupts_Struct
{
	VM_DCL_HANDLE handle;
	uint32_t pin;
       uint32_t eint;
       uint32_t first;
	voidFuncPtr cb;
}Exinterrupts_Struct;


static Exinterrupts_Struct gExinterruptsPio[EXTERNAL_NUM_INTERRUPTS] = {
    {VM_DCL_HANDLE_INVALID, 2, 20, 0, NULL},
    {VM_DCL_HANDLE_INVALID, 3, 11, 0, NULL}
};

#ifdef __cplusplus
extern "C" {
#endif

static void eint_callback(void* parameter, VM_DCL_EVENT event, VM_DCL_HANDLE device_handle)
{
    int i;
   
    for(i=0; i<EXTERNAL_NUM_INTERRUPTS; i++)
    {
        if(gExinterruptsPio[i].handle == device_handle)
        {
            if(noStopInterrupts())
            {
            	 gExinterruptsPio[i].cb();
            }
            break;
        }
    }
}

#ifdef __cplusplus
}
#endif


void attachInterrupt(uint32_t pin, void (*callback)(void), uint32_t mode)
{
    VM_DCL_HANDLE eint_handle;
    vm_eint_ctrl_config_t eint_config;
    vm_eint_ctrl_set_sensitivity_t sens_data;
    vm_eint_ctrl_set_hw_deounce_t deboun_time;
    VM_DCL_STATUS status;
	
    if(pin > EXTERNAL_NUM_INTERRUPTS)
		return ;

	detachInterrupt(pin);

	if(!changePinType(gExinterruptsPio[pin].pin, PIO_EINT, &eint_handle))
		return;
	
    memset(&eint_config,0, sizeof(vm_eint_ctrl_config_t));
    memset(&sens_data,0, sizeof(vm_eint_ctrl_set_sensitivity_t));
    memset(&deboun_time,0, sizeof(vm_eint_ctrl_set_hw_deounce_t));

	if(eint_handle == VM_DCL_HANDLE_INVALID)
    	eint_handle = vm_dcl_open(VM_DCL_EINT,gExinterruptsPio[pin].eint);
	
    if(VM_DCL_HANDLE_INVALID == eint_handle)
    {
        vm_log_info("open EINT error");
        return;
    }

    setPinHandle(gExinterruptsPio[pin].pin, eint_handle);
    gExinterruptsPio[pin].handle = eint_handle;
    gExinterruptsPio[pin].cb = callback;

    status = vm_dcl_control(eint_handle ,VM_EINT_CMD_MASK,NULL);  /* Usually, before we config eint, we mask it firstly. */
    if(status != VM_DCL_STATUS_OK)
    {
    	vm_log_info("VM_EINT_CMD_MASK  = %d", status);
    }
	
     status = vm_dcl_registercallback(eint_handle , VM_EVENT_EINT_TRIGGER,(VM_DCL_CALLBACK)eint_callback,(void*)NULL );
     if(status != VM_DCL_STATUS_OK)
     {
         vm_log_info("VM_EVENT_EINT_TRIGGER = %d", status);
     }	
    if(gExinterruptsPio[pin].first == 0)
    {
			
	    if (mode == CHANGE)
	    {
	    		sens_data.sensitivity = 0;
	              eint_config.act_polarity = 0;
		       eint_config.auto_unmask = 1;
	    } 
	    else 
	    {		  
		  if (mode == FALLING)
		  {
	    		sens_data.sensitivity = 0;
	              eint_config.act_polarity = 0;
		       eint_config.auto_unmask = 1;
		  }
		  else if (mode == RISING) 
		  {
	    		sens_data.sensitivity = 0;
	              eint_config.act_polarity = 1;
		       eint_config.auto_unmask = 1;
		  }
		  else
		  {
		  		vm_log_info("mode not support = %d", mode);
		  }
	    }

	    status = vm_dcl_control(eint_handle ,VM_EINT_CMD_SET_SENSITIVITY,(void *)&sens_data);  /* set eint sensitivity */
	     if(status != VM_DCL_STATUS_OK)
	    {
	        vm_log_info("VM_EINT_CMD_SET_SENSITIVITY = %d", status);
	    }

	    deboun_time.debounce_time = 1;  /* debounce time 1ms */
	    status = vm_dcl_control(eint_handle ,VM_EINT_CMD_SET_HW_DEBOUNCE,(void *)&deboun_time); /* set debounce time */
	    if(status != VM_DCL_STATUS_OK)
	    {
	        vm_log_info("VM_EINT_CMD_SET_HW_DEBOUNCE = %d", status);
	    }

	    status = vm_dcl_control(eint_handle ,VM_EINT_CMD_MASK,NULL);  /* Usually, before we config eint, we mask it firstly. */
	    if(status != VM_DCL_STATUS_OK)
	    {
	    	vm_log_info("VM_EINT_CMD_MASK  = %d", status);
	    }

	    eint_config.debounce_en = 0;    /* 1 means enable hw debounce, 0 means disable. */

	    status = vm_dcl_control(eint_handle ,VM_EINT_CMD_CONFIG,(void *)&eint_config);   /* Please call this api finally, because we will unmask eint in this command. */
	    if(status != VM_DCL_STATUS_OK)
	    {
	        vm_log_info("VM_EINT_CMD_CONFIG = %d", status);
	    }
		
	    if (mode == CHANGE)
	    {
	    	 vm_eint_ctrl_set_auto_change_pol_t auto_change;
		 auto_change.autoChangePol = 1;
	        status = vm_dcl_control(eint_handle ,VM_EINT_CMD_SET_AUTO_CHANGE_POLARTIY,(void *)&auto_change);   /* Please call this api finally, because we will unmask eint in this command. */
	        if(status != VM_DCL_STATUS_OK)
	        {
	            vm_log_info("VM_EINT_CMD_CONFIG chage= %d", status);
	        }
	    }
	    gExinterruptsPio[pin].first ++;
    }
    else
    {	
        status = vm_dcl_control(eint_handle,VM_EINT_CMD_UNMASK,NULL);  /* call this function to unmask this eint. */
        if(status != VM_DCL_STATUS_OK)
        {
             vm_log_info("VM_EINT_CMD_CONFIG = %d", status);
        }
    }
}

void detachInterrupt(uint32_t pin)
{
    if(VM_DCL_HANDLE_INVALID != gExinterruptsPio[pin].handle)
    {
    	vm_dcl_close(gExinterruptsPio[pin].handle);
    }
	gExinterruptsPio[pin].handle = VM_DCL_HANDLE_INVALID;
    gExinterruptsPio[pin].cb = NULL;
	g_APinDescription[gExinterruptsPio[pin].pin].ulHandle = VM_DCL_HANDLE_INVALID;
	g_APinDescription[gExinterruptsPio[pin].pin].ulPinType= PIO_DIGITAL;
	gExinterruptsPio[pin].first = 0;
}


