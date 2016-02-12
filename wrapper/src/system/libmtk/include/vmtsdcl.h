/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef __VM_DCL_H__
#define __VM_DCL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "vmtssys.h"


/*****************************************************************************
 * DESCRIPTION
 *   VM_TS_DCL_DEV is the type used to represent a special device such as UART,I2C,GPIO and so on.
 *   The value for every device group is defined in VM_TS_DCL_DEV_T. 
 *   The value of a special device is defined in the header file of the device.
 *****************************************************************************/ 
typedef VMUINT16 VM_TS_DCL_DEV;


/*****************************************************************************
* This is the device number group enum.
* Each group device may have several devices.
* The specific device number please reference to the device driver.
* DUMMY_DEV group is for other users(not driver user) to register it's callback
*****************************************************************************/
typedef enum
{
   VM_TS_DCL_UART_GROUP_START = 0, /*UART device number starts.*/
   VM_TS_DCL_I2C_GROUP_START = 0x100,/*I2C device number starts.*/
   VM_TS_DCL_SPI_GROUP_START = 0x200, /*SPI device number starts.*/
   VM_TS_DCL_ADC_GROUP_START = 0x300, /*ADC device number starts.*/
   VM_TS_DCL_GPIO_GROUP_START = 0x400, /*GPIO device number starts.*/   
   VM_TS_DCL_PWM_GROUP_START = 0x500, /*PWM device number starts.*/      
   VM_TS_DCL_RTC_GROUP_START = 0xA00, /*RTC device number starts.*/     
   VM_TS_DCL_PMU_GROUP_START = 0xB00, /*PMU device number starts.*/
   VM_TS_DCL_EINT_GROUP_START = 0x1C00, /* EINT device number starts. */
   VM_TS_DCL_DUMMY_DEV_GROUP_START = 0x8000 /*DUMMY device number starts. For other user(not user driver)register callback in tiny system*/
} VM_TS_DCL_DEV_T;

/*****************************************************************************
* This is enum define dummy device, it's for other users(not driver user) to register callback 
*****************************************************************************/
typedef enum
{
	VM_TS_DCL_DUMMY_DEV_START = VM_TS_DCL_DUMMY_DEV_GROUP_START,
	VM_TS_DCL_DUMMY_DEV
}VM_TS_DCL_DUMMY_DEV_T;

/*****************************************************************************
 * DESCRIPTION
 *   VM_TS_DCL_FLAGS is the type used to represent the flag that pass to the vm_ts_dcl_open.
 *   The value depend on each special device.
 *****************************************************************************/
typedef VMUINT32 VM_TS_DCL_FLAGS;


/*****************************************************************************
 * DESCRIPTION
 *   VM_TS_DCL_HANDLE is the type used to record a specific device that opened by vm_ts_dcl_open.
 *   This value will be pass to other API to tell the driver which device will response to the corresponding operation. 
 *****************************************************************************/
typedef VMINT32 VM_TS_DCL_HANDLE;


/*Represent invalid handle, returned by vm_ts_dcl_open.*/
#define VM_TS_DCL_HANDLE_INVALID    (-1)


/*****************************************************************************
 * DESCRIPTION
 *   VM_TS_DCL_EVENT is the type used to register three level callcbcack, VM_TS_DCL_EVENT_T show the detail.
 *   Driver(UART/I2C/EINT,etc.) user can use VM_TS_DCL_REGISTER_CALLBACK_LEVEL0 to register level0 callback, 
 *   VM_TS_DCL_REGISTER_CALLBACK_LEVEL2 to register level2 callback,and use VM_TS_DCL_REGISTER_CALLBACK_LEVEL3 to register level3 callback;
 *   But,other user(not user driver) just can  use VM_TS_DCL_REGISTER_CALLBACK_LEVEL2 to register level2 callback,
 *   and use VM_TS_DCL_REGISTER_CALLBACK_LEVEL3 to register level3 callback. 
 *****************************************************************************/
typedef VMUINT32  VM_TS_DCL_EVENT;

typedef enum
{
	VM_TS_DCL_REGISTER_CALLBACK_LEVEL0=0,/*register LISR level*/
	VM_TS_DCL_REGISTER_CALLBACK_LEVEL2, /*register HISR level1*/
	VM_TS_DCL_REGISTER_CALLBACK_LEVEL3  /*register HISR level2*/
}VM_TS_DCL_EVENT_T;


/*****************************************************************************
 * DESCRIPTION
 *   VM_TS_DCL_CALLBACK_LEVEL is the type used to active callcbcack, VM_TS_DCL_CALLBACK_LEVEL_T show the detail.
 *   user can use VM_TS_DCL_CALLBACK_LEVEL2 to active level2 callback, and use VM_TS_DCL_CALLBACK_LEVEL3 to active level3 callback
 *****************************************************************************/
typedef VMUINT32 VM_TS_DCL_CALLBACK_LEVEL;
typedef enum
{
   VM_TS_DCL_CALLBACK_LEVEL2,/* HISR level1*/
   VM_TS_DCL_CALLBACK_LEVEL3 /* HISR level2*/
}VM_TS_DCL_CALLBACK_LEVEL_T;


/*****************************************************************************
 * DESCRIPTION
 *   VM_TS_DCL_CB_LEVEL0 is the prototype of the level0 callback function,
 *   with input parameter for driver(UART/I2C/EINT,etc.)sync status with user
 *   VM_TS_DCL_CB_LEVEL2 is the prototype of the level2 callback function.
 *   VM_TS_DCL_CB_LEVEL3 is the prototype of the level3 callback function.
 *****************************************************************************/
typedef void (* VM_TS_DCL_CB_LEVEL0)(VMUINT32 para);
typedef void (* VM_TS_DCL_CB_LEVEL2)(void);
typedef void (* VM_TS_DCL_CB_LEVEL3)(void);


/*****************************************************************************
 * DESCRIPTION
 *   VM_TS_DCL_CTRL_CMD is the type used to represent the operation the driver need to do.
 *   The value of the type variable is depend on specific device driver.
 *   The detail please reference to  the command enum of driver.
 *****************************************************************************/
typedef VMUINT32  VM_TS_DCL_CTRL_CMD;

/*****************************************************************************
 * DESCRIPTION
 *   VM_TS_DCL_STATUS is the type used to represent the status the driver returned.
 *   The meaning of the value please reference to VM_TS_DCL_STATUS.
 *****************************************************************************/
typedef VMINT32 VM_TS_DCL_STATUS;


/* This used to represent the status of dcl operations.*/
typedef enum
{
   VM_TS_DCL_STATUS_OK = 0, /*Operation success*/
   VM_TS_DCL_STATUS_FAIL = -1, /*Operation failed*/
   VM_TS_DCL_STATUS_INVALID_CMD = -2, /*The command send to device is invalid*/
   VM_TS_DCL_STATUS_UNSUPPORTED = -3, /*The device do not support the operation*/
   VM_TS_DCL_STATUS_NOT_OPENED = -4, /*The device isn't open*/
   VM_TS_DCL_STATUS_INVALID_EVENT = -5, /*The event is invalid*/
   VM_TS_DCL_STATUS_INVALID_DCL_HANDLE = -6, /*The handle used to operate the device is invalid. The invalid handle returned by vm_dcl_open is another value.*/
   VM_TS_DCL_STATUS_INVALID_CTRL_DATA = -7, /*The data used to control the device is invalid.*/
   VM_TS_DCL_STATUS_INVALID_ARGUMENT = -9, /*The data used to control the device is invalid.*/
   VM_TS_DCL_STATUS_ERROR_TIMEOUT = -10, /*Operation timeout.*/
   VM_TS_DCL_STATUS_ERROR_CRCERROR = -11, /*CRC error.*/
   VM_TS_DCL_STATUS_ERROR_READONLY = -12, /*device is readonly.*/
   VM_TS_DCL_STATUS_ERROR_WRONG_STATE = -13, /*wrong state.*/
   VM_TS_DCL_STATUS_INVALID_DEVICE = -14, /*invalid device.*/
   VM_TS_DCL_STATUS_ALREADY_OPENED = -15, /*device is already opened.*/
   VM_TS_DCL_STATUS_INVALID_OPERATION = -17, /*operation is invalid.*/
   VM_TS_DCL_STATUS_DEVICE_NOT_EXIST = -18,/*device is not exist.*/
   VM_TS_DCL_STATUS_DEVICE_IS_BUSY = -20,/*device is busy.*/
} VM_TS_DCL_STATUS_T;



/*****************************************************************************
* FUNCTION
 *    vm_ts_dcl_open
 * DESCRIPTION
 *  1 Open one device. Every device must be opened with this function before use it.
 *    The device number passed to this function was defined in device driver's header file(except dummy device).
 *    The returned handle is the device's identify which will be passed to the other functions at runtime
 * PARAMETERS
 * device: [IN]  The number of device, given by device driver. It's a 16 bits integer.
 * flags:  [IN]  The parameter needed for the device. It's a 32 bits unsigned integer. Some driver may not need this.
 * RETURNS
 *  The return value is the handle which record the information of corresponding device. 
 *  
 * RETURN VALUES                                    
 *  VM_TS_DCL_HANDLE:  The handle record the information of corresponding device. 
 *  If the value of returned handle equal to VM_TS_DCL_HANDLE_INVALID, the open operation failed.
 *
 * EXAMPLE		                            
 * <code>
 * VM_TS_DCL_HANDLE uart_handle;
 * uart_handle = vm_dcl_open(vm_uart_port1,0);
 * if(VM_TS_DCL_HANDLE_INVALID==uart_handle)
 *    return;
 * else
 *    //Do something with the handle.
 * </code>
*****************************************************************************/
VM_TS_DCL_HANDLE vm_ts_dcl_open(VM_TS_DCL_DEV dev, VM_TS_DCL_FLAGS flags);


/*****************************************************************************
* FUNCTION
 *    vm_ts_dcl_control
 * DESCRIPTION
 *   Send command to control the device.
 *   This function used to control the device after open the device successfully.
 *   The command tell the driver what to do and the arg will give the information needed for the control to driver.
 *   The command is defined in device driver's header file and represent different meaning even have the same value 
 *    for different device. So the handle, command and arg must be match, otherwise the operation maybe given to wrong 
 *    device or do wrong operation.
 *   This function maybe synchronous or asynchronous operation depending on which devices' which command. 
 *   The details please reference to the command description in the specific driver's document.
 * PARAMETERS
 * handle: [IN]  The  handle which returned by vm_dcl_open.
 * cmd:  [IN]  The command used to control the device.  The detail reference to the device document.
 * arg:  [IN]  The argument used by the command. The detail reference to the device document.
 * RETURNS
 *  The return value is status. The meaning reference to VM_TS_DCL_STATUS_T;  
 *  
 * RETURN VALUES                                    
 *  VM_TS_DCL_STATUS  :  The return value is status.The meaning reference to VM_TS_DCL_STATUS_T;  
 *
 * EXAMPLE		                            
 * <code>
 * VM_TS_DCL_STATUS status;
 *	vm_ts_sio_ctrl_dcb_t config;
 *	VM_TS_DCL_MODULE_TYPE_T usr_id;
 *	VM_TS_DCL_HANDLE uart_handle;
 *	
 *	uart_handle = vm_ts_dcl_open(vm_ts_uart_port1,usr_id);
 *	config.u4OwenrId = usr_id;
 *	config.rUARTConfig.fgDSRCheck = 0;
 *	config.rUARTConfig.u1DataBits = 8;
 *	config.rUARTConfig.u1FlowControl = VM_FC_NONE;
 *	config.rUARTConfig.u1Parity = VM_PA_NONE;
 *	config.rUARTConfig.u1StopBits = VM_SB_1;
 *	config.rUARTConfig.u4Baud = 115200;
 *	config.rUARTConfig.ucXoffChar = 0x13;
 *	config.rUARTConfig.ucXonChar = 0x11;
 *	status=vm_ts_dcl_control(uart_handle,VM_TS_SIO_CMD_SET_DCB_CONFIG,&config);
 * </code>
*****************************************************************************/
VM_TS_DCL_STATUS vm_ts_dcl_control(VM_TS_DCL_HANDLE handle,VM_TS_DCL_CTRL_CMD cmd,  void* arg);

	
/*****************************************************************************
* FUNCTION
 *   vm_ts_dcl_close
 * DESCRIPTION
 *   Close the device, after the device finished the operation, user should close the device.
 * PARAMETERS
 *   handle: [IN]  The  handle which returned by vm_dcl_open.
 * RETURNS
 *   The return value is status. The meaning reference to VM_DCL_STATUS_T;  
 *  
 * RETURN VALUES                                    
 *  VM_DCL_STATUS  :  The return value is status.The meaning reference to VM_DCL_STATUS_T;  
 *
* EXAMPLE		                            
 * <code>
 * status = vm_dcl_close(i2c_handle);
 * status = vm_dcl_close(user_handle);
 * </code>
*****************************************************************************/
VM_TS_DCL_STATUS vm_ts_dcl_close(VM_TS_DCL_HANDLE handle);


/*****************************************************************************
* FUNCTION
 *    vm_ts_dcl_register_callback
 * DESCRIPTION
 *   Register user's callback. 
 *   For Driver(UART/I2C/EINT,etc.) user, the callback is for device to do asynchronous operations.
 *   For other(not driver user) user,the callback support one context to run code.
 *   In both case, it's should be register the callback, before active it.
 *   The implementation of the callback please reference to prototype of the callback function.
 * PARAMETERS
 * handle:   [IN]  The  handle which returned by vm_ts_dcl_open.
 * event:    [IN]  The event indicate register which level of callback, include: VM_TS_DCL_REGISTER_CALLBACK_LEVEL0,
 *                 VM_TS_DCL_REGISTER_CALLBACK_LEVEL2,VM_TS_DCL_REGISTER_CALLBACK_LEVEL3
 * callback: [IN]  callback function.
 *
 * RETURN VALUES                                    
 *  VM_TS_DCL_STATUS  :  The return value is status.
 *
* EXAMPLE		                            
 * <code>

 * </code>
*****************************************************************************/
VM_TS_DCL_STATUS vm_ts_dcl_register_callback(VM_TS_DCL_HANDLE handle,VM_TS_DCL_EVENT event, void* callback);


/*****************************************************************************
 * FUNCTION
 *    vm_ts_dcl_active_callback
 * DESCRIPTION
 *   Active callback,use to active just level2 or level3 callback,(not include level0 callback),if register before.
 * PARAMETERS
 * handle:   [IN]  The  handle which returned by vm_ts_dcl_open.
 * level:    [IN]  The level indicate active which level of callback, include: VM_TS_DCL_CALLBACK_LEVEL2,
 *                 VM_TS_DCL_CALLBACK_LEVEL3
 * RETURN VALUES                                    
 *  VM_TS_DCL_STATUS  :  The return value is status.
 *
 * EXAMPLE		                            
 * <code>

 * </code>
*****************************************************************************/
void vm_ts_dcl_active_callback(VM_TS_DCL_HANDLE handle, VM_TS_DCL_CALLBACK_LEVEL level);


#ifdef __cplusplus
}
#endif

#endif  /* __VM_DCL_H__ */