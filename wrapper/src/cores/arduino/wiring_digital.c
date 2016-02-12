/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "vmdcl.h"
#include "vmdcl_gpio.h"
#include "vmlog.h"

#ifdef __cplusplus
 extern "C" {
#endif

extern void pinMode( uint32_t ulPin, uint32_t ulMode )
{  
	VM_DCL_HANDLE gpio_handle; 
    vm_gpio_ctrl_set_pupd_r0_r1_t pupd;
    //vm_log_info("pinMode(): pin = %d , pin_internal = %d, mode = %d", ulPin, g_APinDescription[ulPin].ulGpioId, ulMode);
    
    if(!changePinType(ulPin, PIO_DIGITAL, &gpio_handle))
		return;

	if(gpio_handle == VM_DCL_HANDLE_INVALID)
		gpio_handle = vm_dcl_open(VM_DCL_GPIO, g_APinDescription[ulPin].ulGpioId);
    
    // set PIN direction
    switch ( ulMode )
    {
        case INPUT:
            vm_dcl_control(gpio_handle,VM_GPIO_CMD_SET_DIR_IN, NULL);
			
	     if( g_APinDescription[ulPin].ulPupd)
	     {
	       pupd.fgSetPupd = 0;
	       pupd.fgSetR0 = 1;
		pupd.fgSetR1 = 0;
            	vm_dcl_control(gpio_handle,VM_GPIO_CMD_SET_PUPD_R0_R1, &pupd);
	     }
	     else
	     {
            	vm_dcl_control(gpio_handle,VM_GPIO_CMD_ENABLE_PULL, NULL);
            	vm_dcl_control(gpio_handle,VM_GPIO_CMD_SET_PULL_LOW, NULL);
	     }
            break ;
        
        case INPUT_PULLUP:
            vm_dcl_control(gpio_handle,VM_GPIO_CMD_SET_DIR_IN, NULL);   
			
	     if( g_APinDescription[ulPin].ulPupd)
	     {
	       pupd.fgSetPupd = 1;
	       pupd.fgSetR0 = 1;
		pupd.fgSetR1 = 0;
            	vm_dcl_control(gpio_handle,VM_GPIO_CMD_SET_PUPD_R0_R1, &pupd);
	     }
	     else
	     {
            	vm_dcl_control(gpio_handle,VM_GPIO_CMD_ENABLE_PULL, NULL);
            	vm_dcl_control(gpio_handle,VM_GPIO_CMD_SET_PULL_HIGH, NULL);      
	     }
            break ;
        
        case OUTPUT:
            vm_dcl_control(gpio_handle,VM_GPIO_CMD_SET_DIR_OUT, NULL);
            break ;
        
        default:
            break ;
    }
    
    g_APinDescription[ulPin].ulHandle = gpio_handle;
    
}

extern void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{   
    //vm_log_info("digitalWrite(): pin = %d , value = %d", ulPin, ulVal);
    
    if (ulPin > PIO_MAX_NUM )
    {
        return;
    }
    
    if(g_APinDescription[ulPin].ulHandle == VM_DCL_HANDLE_INVALID)
    {
        g_APinDescription[ulPin].ulHandle = vm_dcl_open(VM_DCL_GPIO, g_APinDescription[ulPin].ulGpioId);
    }
    // write PIN
    switch (ulVal)
    {
        case HIGH:
            vm_dcl_control(g_APinDescription[ulPin].ulHandle,VM_GPIO_CMD_WRITE_HIGH, NULL);   
            break;
            
        case LOW:
            vm_dcl_control(g_APinDescription[ulPin].ulHandle,VM_GPIO_CMD_WRITE_LOW, NULL);  
            break;
            
        default:
            break;
    }
    
}

extern int digitalRead( uint32_t ulPin )
{
    vm_gpio_ctrl_read_t  data;

	//vm_log_info("digitalRead(): pin = %d", ulPin);

	if (ulPin > PIO_MAX_NUM )
    {
        //vm_log_info("digitalRead(): pin mapping failed, return LOW as default.");
        return LOW;
    }

    if(g_APinDescription[ulPin].ulHandle == VM_DCL_HANDLE_INVALID)
    {
        g_APinDescription[ulPin].ulHandle = vm_dcl_open(VM_DCL_GPIO, g_APinDescription[ulPin].ulGpioId);
    }
	 
    vm_dcl_control(g_APinDescription[ulPin].ulHandle, VM_GPIO_CMD_READ,(void *)&data);
   
    if ( data.u1IOData == VM_GPIO_IO_LOW )
    {
        //vm_log_info("digitalRead(): result = LOW");
        return LOW ;
    }
    else if ( data.u1IOData == VM_GPIO_IO_HIGH )
    {
        //vm_log_info("digitalRead(): result = HIGH");
        return HIGH ;
    }
    else
    {
        //vm_log_info("digitalRead(): read failed, return LOW as default.");
        return LOW ;
    }
}

#ifdef __cplusplus
}
#endif

