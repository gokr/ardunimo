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

#include "vmsys.h"


/*****************************************************************************
 * DESCRIPTION
 *   VM_DCL_DEV is the type used to represent a special device such as UART,I2C,GPIO and so on.
 *   The value for every device group is defined in VM_DCL_DEV_T. 
 *   The value of a special device is defined in the header file of the device.
 *****************************************************************************/
typedef VMUINT16 VM_DCL_DEV;
/*****************************************************************************
 * DESCRIPTION
 *   VM_DCL_FLAGS is the type used to represent the flag that pass to the vm_dcl_open.
 *   The value depend on each special device.
 *****************************************************************************/
typedef VMUINT32 VM_DCL_FLAGS;



/*****************************************************************************
 * DESCRIPTION
 *   VM_DCL_OPTIONS is the type used to pass some special option to the read/write API.
 *   The value depend on each special device.
 *****************************************************************************/
typedef VMUINT32 VM_DCL_OPTIONS;

/*****************************************************************************
 * DESCRIPTION
 *   VM_DCL_HANDLE is the type used to record a specific device that opened by vm_dcl_open.
 *   This value will be pass to other API to tell the driver which device will response to the corresponding operation. 
 *****************************************************************************/
typedef VMINT32 VM_DCL_HANDLE;
/*Represent invalid handle, returned by vm_dcl_open.*/
#define VM_DCL_HANDLE_INVALID    (-1)


/* VM_DCL_BUFF is the type of the buffer*/
typedef VMUCHAR   VM_DCL_BUFF;
/* VM_DCL_BUFF_LEN is the type of the buffer length*/
typedef VMUINT32  VM_DCL_BUFF_LEN;


/*****************************************************************************
 * DESCRIPTION
 *   VM_DCL_EVENT is the type used to represent event.
 *   The event usually represent a specific hardware condition changed, such as data transfer finished. 
 *   This type value is used in asynchronous operations, please reference VM_DCL_EVENT_T
 *****************************************************************************/
typedef VMUINT32  VM_DCL_EVENT;

/*****************************************************************************
 * DESCRIPTION
 *   VM_DCL_CALLBACK is the prototype of the call back function.
 * PARAMETERS
 * parameter:    [IN]  This pointer is the data structure pointer that driver pass to user.
 *                     The real type of this value should be VM_DCL_CB_ILM_DATA_T. 
 *                     The detail of this structure will be given by the driver.
 * event:        [IN]  The event identify which condition that this call back triggered by.
 *device_handle: [IN]  This handle represent the device that trigger this callback.
 * RETURNS
 *  The return value is void. 
 *  
 * RETURN VALUES                                    
 *  None
 * EXAMPLE		                            
 * <code>
 * //This example explain how to implement the callback.
 *  void uart_callback(void* parameter, VM_DCL_EVENT event, VM_DCL_HANDLE device_handle){
 *	VM_DCL_CB_ILM_DATA_T* uart_para = (VM_DCL_CB_ILM_DATA_T*)parameter;
 *	if(VM_UART_READY_TO_READ==event){
 *		vm_sio_ctrl_get_bytes_t* get_byte=(vm_sio_ctrl_get_bytes_t*)(uart_para->vm_local_para_ptr);
 *		vm_log_info("UART read callback!!!");
 *	}else if(VM_UART_READY_TO_WRITE==event){
 *		vm_sio_ctrl_put_bytes_t* put_byte = (vm_sio_ctrl_put_bytes_t*)(uart_para->vm_local_para_ptr);
 *		vm_log_info("UART write callback!!!");
 *	}else{
 *		vm_log_info("Wrong callback event!!!");
 *	}
 *	}
 * </code>
 *****************************************************************************/
typedef void (*VM_DCL_CALLBACK)(void* parameter, VM_DCL_EVENT event, VM_DCL_HANDLE device_handle);


/*****************************************************************************
 * DESCRIPTION
 *  VM_DCL_CTRL_CMD is the type used to represent the operation the driver need to do.
 *  The value of the type variable is depend on specific device driver.
 *  The detail please reference to  the command enum of driver.
 *	Please find different command for difference driver:
 *		SIO:	VM_DCL_SIO_CTRL_CMD
 *		I2C:	VM_DCL_I2C_CTRL_CMD_T
 *		SPI:	VM_SPI_IOCTL_CODE
 *		ADC:	VM_DCL_ADC_CTRL_CMD_T
 *		GPIO:	VM_DCL_GPIO_CTRL_CMD_T
 *		PMU:	VM_DCL_PMU_CTRL_CMD_T
 *		EINT:	VM_DCL_EINT_CMD_T
 *****************************************************************************/
typedef VMUINT32  VM_DCL_CTRL_CMD;

/*****************************************************************************
 * DESCRIPTION
 *   VM_DCL_STATUS is the type used to represent the status the driver returned.
 *    The meaning of the value please reference to VM_DCL_STATUS_T.
 *****************************************************************************/
typedef VMINT32 VM_DCL_STATUS;

/*****************************************************************************
*This is the type used for callback transfer data from driver.
*The callback's parameter is always this type.
*Most of the time, the data send back by driver was wrapped in the vm_local_para_ptr, sometimes in vm_peer_buff_ptr.
*Different device driver has different specific type for these two parameter.
*****************************************************************************/
typedef struct{
   void *vm_local_para_ptr; /* local_para pointer */
   void *vm_peer_buff_ptr;  /* peer_buff pointer */
}VM_DCL_CB_ILM_DATA_T;

/* This used to represent the status of dcl operations.*/
typedef enum
{
   VM_DCL_STATUS_OK = 0, /*Operation success*/
   VM_DCL_STATUS_FAIL = -1, /*Operation failed*/
   VM_DCL_STATUS_INVALID_CMD = -2, /*The command send to device is invalid*/
   VM_DCL_STATUS_UNSUPPORTED = -3, /*The device do not support the operation*/
   VM_DCL_STATUS_NOT_OPENED = -4, /*The device isn't open*/
   VM_DCL_STATUS_INVALID_EVENT = -5, /*The event is invalid*/
   VM_DCL_STATUS_INVALID_DCL_HANDLE = -6, /*The handle used to operate the device is invalid. The invalid handle returned by vm_dcl_open is another value.*/
   VM_DCL_STATUS_INVALID_CTRL_DATA = -7, /*The data used to control the device is invalid.*/
   VM_DCL_STATUS_INVALID_ARGUMENT = -9, /*The data used to control the device is invalid.*/
   VM_DCL_STATUS_ERROR_TIMEOUT = -10, /*Operation timeout.*/
   VM_DCL_STATUS_ERROR_CRCERROR = -11, /*CRC error.*/
   VM_DCL_STATUS_ERROR_READONLY = -12, /*device is readonly.*/
   VM_DCL_STATUS_ERROR_WRONG_STATE = -13, /*wrong state.*/
   VM_DCL_STATUS_INVALID_DEVICE = -14, /*invalid device.*/
   VM_DCL_STATUS_ALREADY_OPENED = -15, /*device is already opened.*/
   VM_DCL_STATUS_INVALID_OPERATION = -17, /*operation is invalid.*/
   VM_DCL_STATUS_DEVICE_NOT_EXIST = -18,/*device is not exist.*/
   VM_DCL_STATUS_DEVICE_NOT_SUPPORT_DMA = -19, /* device not support DMA */
   VM_DCL_STATUS_DEVICE_IS_BUSY = -20,   /*device is busy.*/
   VM_DCL_STATUS_ACKERR = -21,           /* I2C ACK error */
   VM_DCL_STATUS_HS_NACKERR = -22,       /* I2C HighSpeed NACK error */
   
} VM_DCL_STATUS_T;

/*****************************************************************************
*This is the type used for vm_dcl_get_ownerid.
*This value may be have different meaning for the same value.
*So MUST use the vm_dcl_get_ownerid to get the correct value at runtime.
*****************************************************************************/
typedef enum{
	VM_MODULE_START = 0,/*give the start number*/
	VM_MODULE_END = 0x1FF/*set the end number*/
}VM_DCL_MODULE_TYPE_T;



/*****************************************************************************
*This is the device number group enum.
*Each group device may have several devices.
*The specific device number please reference to the device driver.
*****************************************************************************/
typedef enum
{
   VM_DCL_SIO_GROUP_START = 0, /*SIO(Uart,USB) device number starts. Please reference VM_DCL_SIO_DEV_T*/
   VM_DCL_I2C_GROUP_START = 0x100,/*I2C device number starts. Please reference VM_DCL_I2C_DEV_T*/
   VM_DCL_SPI_GROUP_START = 0x200, /*SPI device number starts. Please reference VM_DCL_SPI_DEV_T*/
   VM_DCL_ADC_GROUP_START = 0x300, /*ADC device number starts. Please reference VM_DCL_ADC_DEV_T*/
   VM_DCL_GPIO_GROUP_START = 0x400, /*GPIO device number starts. Please reference VM_DCL_GPIO_DEV_T*/   
   VM_DCL_PWM_GROUP_START = 0x500, /*PWM device number starts. Please reference VM_DCL_PWM_DEV_T*/      
   VM_DCL_PMU_GROUP_START = 0xB00, /*PMU device number starts. Please reference VM_DCL_PMU_DEV_T*/
   VM_DCL_EINT_GROUP_START = 0x1C00 /* EINT device number starts.  Please reference VM_DCL_EINT_DEV_T*/
} VM_DCL_DEV_T;

/*****************************************************************************
*This is the event number group enum.
*Each group device may have several events. Some device may not need the event.
*The specific event number and the meaning please reference to the device driver.
*****************************************************************************/
typedef enum
{
   VM_EVENT_NULL = 0, 
   VM_GPIO_EVENTS_START = 0x100,   /*for GPIO*/
   VM_ADC_EVENTS_START = 0x600,  /*for ADC, please reference VM_DCL_ADC_EVENT_T*/
   VM_I2C_EVENTS_START = 0x700, /*for I2C*/
   VM_SERIPORT_EVENTS_START = 0x1400,  	/*For SIO(include UART and USB), please reference VM_DCL_SIO_EVENT_T*/
   VM_SPI_EVENTS_START = 0x1500 , /*for SPI*/
   VM_EINT_EVENTS_START = 0x1600 /* for EINT , please reference VM_DCL_EINT_EVENT_T*/
} VM_DCL_EVENT_T;

/*****************************************************************************
* FUNCTION
 *    vm_dcl_open
 * DESCRIPTION
 *  Open the device. Every device must be opened with this function before use it.
 *  The device number passed to this function was defined in device driver's header file.
 *  The returned handle is the device's identify which will be passed to the other functions at runtime.
 * PARAMETERS
 * device: [IN]  The number of device, given by device driver. It's a 16 bits integer.
 * flags:  [IN]  The parameter needed for the device. It's a 32 bits unsigned integer. Some driver may not need this.
 * RETURNS
 *  The return value is the handle which record the information of corresponding device. 
 *  
 * RETURN VALUES                                    
 *  DCL_HANDLE  :  The handle record the information of corresponding device. 
 *  If the value of returned handle equal to VM_DCL_HANDLE_INVALID, the open operation failed.
 *
 * EXAMPLE		                            
 * <code>
 * DCL_HANDLE uart_handle;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * usr_id = vm_dcl_get_ownerid();
 * //some device may not need the second parameter.
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * if(VM_DCL_HANDLE_INVALID==uart_handle) return;
 * //Do something with the handle.
 * </code>
*****************************************************************************/
VM_DCL_HANDLE vm_dcl_open(VM_DCL_DEV dev, VM_DCL_FLAGS flags);
/*****************************************************************************
* FUNCTION
 *    vm_dcl_control
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
 * device_handle: [IN]  The device handle which returned by vm_dcl_open.
 * cmd:  [IN]  The command used to control the device.  The detail reference to the device document.
 * arg:  [IN]  The argument used by the command. The detail reference to the device document.
 * RETURNS
 *  The return value is status. The meaning reference to VM_DCL_STATUS_T;  
 *  
 * RETURN VALUES                                    
 *  DCL_STATUS  :  The return value is status.The meaning reference to VM_DCL_STATUS_T;  
 *
 * EXAMPLE		                            
 * <code>
 * DCL_STATUS status;
 *	vm_sio_ctrl_dcb_t config;
 *	VM_DCL_MODULE_TYPE_T usr_id;
 *	VM_DCL_HANDLE uart_handle;
 *	
 * 	usr_id=vm_dcl_get_ownerid();
 *	uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 *	config.u4OwenrId = usr_id;
 *	config.rUARTConfig.fgDSRCheck = 0;
 *	config.rUARTConfig.u1DataBits = 8;
 *	config.rUARTConfig.u1FlowControl = VM_FC_NONE;
 *	config.rUARTConfig.u1Parity = VM_PA_NONE;
 *	config.rUARTConfig.u1StopBits = VM_SB_1;
 *	config.rUARTConfig.u4Baud = 115200;
 *	config.rUARTConfig.ucXoffChar = 0x13;
 *	config.rUARTConfig.ucXonChar = 0x11;
 *	status=vm_dcl_control(uart_handle,VM_SIO_CMD_SET_DCB_CONFIG,&config);
 * </code>
*****************************************************************************/
VM_DCL_STATUS vm_dcl_control(VM_DCL_HANDLE device_handle,VM_DCL_CTRL_CMD cmd,  void* arg);

	
/*****************************************************************************
* FUNCTION
 *    vm_dcl_close
 * DESCRIPTION
 *   Close the device. After the device finished the operation, user should close the device.
 *   Pay attention to the device operation with callback. The device should not be closed before the callback finished.
 * PARAMETERS
 * device_handle: [IN]  The device handle which returned by vm_dcl_open.
 * RETURNS
 *  The return value is status. The meaning reference to VM_DCL_STATUS_T;  
 *  
 * RETURN VALUES                                    
 *  VM_DCL_STATUS  :  The return value is status.The meaning reference to VM_DCL_STATUS_T;  
 *
* EXAMPLE		                            
 * <code>
 * status = vm_dcl_close(i2c_handle);
 * </code>
*****************************************************************************/
VM_DCL_STATUS vm_dcl_close(VM_DCL_HANDLE device_handle);
 /*****************************************************************************
* FUNCTION
 *    vm_dcl_read
 * DESCRIPTION
 *   Read data from the device. This function may not be provided by the devices that don't transfer data.
 *   If the device have several ways to transfer data, this function may provide some of the methods, 
 *   others can be done bye the vm_dcl_control. The details please reference to the specific device driver document.
 * PARAMETERS
 * device_handle: [IN]  The device handle which returned by vm_dcl_open.
 * buf:           [IN]  The buffer used to save data.
 * read_len:      [IN]  The number of bytes that need to be read.
 * returned_len:  [OUT]  The number of bytes that read by device after returned.
 * options:       [IN]  The special options need by the device. The detail reference to the device document.
 * RETURNS
 *  The return value is status. The meaning reference to VM_DCL_STATUS_T; 
 *  
 * RETURN VALUES                                    
 *  VM_DCL_STATUS  :  The return value is status.The meaning reference to VM_DCL_STATUS_T; 
 *
* EXAMPLE		                            
 * <code>
 * VM_DCL_STATUS status;
 * VM_DCL_BUFF  data_buffer[1024];
 * VM_DCL_BUFF_LEN returned_len;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * VM_DCL_HANDLE uart_handle;
 * usr_id=vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * status = vm_dcl_read(uart_handle,(VM_DCL_BUFF*)data_buffer,1024,&returned_len,usr_id);
 * </code>
*****************************************************************************/
VM_DCL_STATUS vm_dcl_read(VM_DCL_HANDLE device_handle, VM_DCL_BUFF* buf, VM_DCL_BUFF_LEN read_len, VM_DCL_BUFF_LEN* returned_len,VM_DCL_OPTIONS options);
/*****************************************************************************
* FUNCTION
 *    vm_dcl_write
 * DESCRIPTION
 *   Write data to the device.This function may not be provided by the devices that don't transfer data.
 *   If the device have several ways to transfer data, this function may provide some of the methods, 
 *   others can be done bye the vm_dcl_control. The details please reference to the specific device driver document.
 * PARAMETERS
 * device_handle: [IN]  The device handle which returned by vm_dcl_open.
 * buf:           [IN]  The buffer with data that to be written.
 * write_len:      [IN]  The number of bytes that need to write.
 * written_len:  [OUT]  The number of bytes that written by device after returned.
 * options:       [IN]  The special options need by the device. The detail reference to the device document.
 * RETURNS
 *  The return value is status. The meaning reference to VM_DCL_STATUS_T; 
 *  
 * RETURN VALUES                                    
 *  VM_DCL_STATUS  :  The return value is status.The meaning reference to VM_DCL_STATUS_T; 
 *
* EXAMPLE		                            
 * <code>
 * VM_DCL_STATUS status;
 * VM_DCL_BUFF  data_buffer[1024];
 * VM_DCL_BUFF_LEN written_len;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * VM_DCL_HANDLE uart_handle;
 * usr_id=vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * status = vm_dcl_write(uart_handle,(VM_DCL_BUFF*)data_buffer,1024,&written,usr_id);
 * </code>
*****************************************************************************/
VM_DCL_STATUS vm_dcl_write(VM_DCL_HANDLE device_handle,VM_DCL_BUFF* buf, VM_DCL_BUFF_LEN write_len, VM_DCL_BUFF_LEN* written_len,VM_DCL_OPTIONS options);

/*****************************************************************************
* FUNCTION
 *    vm_dcl_registercallback
 * DESCRIPTION
 *   Register event callback. Before the device to do asynchronous operations, the callback function for that operation 
 *   should be registered. The implementation of the callback please reference to the document of the callback function prototype.
 * PARAMETERS
 * device_handle: [IN]  The device handle which returned by vm_dcl_open.
 * event:           [IN]  The event that will triger the callback.
 * callback:      [IN]  callback function.
 * parameter:  [IN]  user parameter.
 * RETURNS
 *  The return value is status. 
 *  
 * RETURN VALUES                                    
 *  VM_DCL_STATUS  :  The return value is status.
 *
* EXAMPLE		                            
 * <code>
 * VM_DCL_STATUS status;
 * VM_DCL_MODULE_TYPE_T usr_id;
 * VM_DCL_HANDLE uart_handle;
 * usr_id=vm_dcl_get_ownerid();
 * uart_handle = vm_dcl_open(vm_uart_port1,usr_id);
 * status=vm_dcl_registercallback(uart_handle,VM_UART_READY_TO_WRITE ,(VM_DCL_CALLBACK)uart_callback,(void *)NULL);
 * </code>
*****************************************************************************/
VM_DCL_STATUS vm_dcl_registercallback(VM_DCL_HANDLE device_handle,VM_DCL_EVENT event, VM_DCL_CALLBACK callback,void* user_data);

/*****************************************************************************
* FUNCTION
 *    vm_dcl_addlistenevent
 * DESCRIPTION
 *   if you want listen mluti event then you can use vm_dcl_registercallback first, and use  vm_dcl_addlistenevent to add all your events
 * PARAMETERS
 * device_handle: [IN]  The device handle which returned by vm_dcl_open.
 * event:           [IN]  The event that will triger the callback.
 * callback:      [IN]  The number of bytes that need to write.
 * user_data:  [IN]  The number of bytes that written by device after returned.
 * RETURNS
 *  The return value is status. 
 *  
 * RETURN VALUES                                    
 *  VM_DCL_STATUS  :  The return value is status.
 *
* EXAMPLE		                            
 * <code>
 * status=vm_dcl_addlistenevent(uart_handle,VM_UART_READY_TO_READ,(void *)NULL);
 * </code>
*****************************************************************************/
VM_DCL_STATUS vm_dcl_addlistenevent(VM_DCL_HANDLE device_handle,VM_DCL_EVENT event, void* user_data);

/*****************************************************************************
* FUNCTION
 *    vm_dcl_get_ownerid
 * DESCRIPTION
 *   Get the runtime environment identify of the user. Some device may need this. 
 *   Most of the time  this function's returned value need to be passed to the driver when the device do asynchronous operations.
 * PARAMETERS
 *   No parameter.
 * RETURNS
 *  The return value is the owner id. 
 *  
 * RETURN VALUES                                    
 *  VM_DCL_MODULE_TYPE_T  :  the owner id.
 *
* EXAMPLE		                            
 * <code>
 * VM_DCL_MODULE_TYPE_T usr_id;
 * usr_id=vm_dcl_get_ownerid();
 * </code>
*****************************************************************************/
VM_DCL_MODULE_TYPE_T vm_dcl_get_ownerid(void);

/*****************************************************************************
 * FUNCTION
 * vm_irq_mask
 * DESCRIPTION
 *  This interface used in AP mode, Mask the I bit of the processor. Note this function must be used in pairs with vm_irq_restore.
 *  And more, the I bit mask time should not exceed 5ms.
 * PARAMETERS
 *  
 * RETURN VALUES
 * mask status of the current I bit, it should be an input parameter of vm_irq_restore
 * EXAMPLE
 * <code>
 * VMUIN32 savedMask;
 * savedMask = vm_irq_mask();
 *      ... // your code need to protect
 * vm_irq_restore(savedMask);
 * 
 * </code>
 *****************************************************************************/
VMUINT32 vm_irq_mask();

/*****************************************************************************
 * FUNCTION
 * vm_irq_restore
 * DESCRIPTION
 *  This interface used in AP mode, restore the I bit of the processor. Note, this function must be used in pairs with  vm_irq_mask.
 * PARAMETERS
 *  saved_mask:[in] the return value of  vm_irq_mask
 * RETURN VALUES
 * EXAMPLE
 * <code>
 * VMUIN32 savedMask;
 * savedMask = vm_irq_mask();
 *      ... // your code need to protect
 * vm_irq_restore(savedMask);
 * 
 * </code>
 *****************************************************************************/
void vm_irq_restore(VMUINT32 mask);

#if 0
#include "vmdcl_i2c.h"
#include "vmdcl_gpio.h"
#include "vmdcl_sio.h"
#include "vmdcl_spi.h"
#include "vmdcl_adc.h"
#include "vmdcl_pmu.h"
#include "vmdcl_eint.h"
#endif

#ifdef __cplusplus
}
#endif

#endif  /* __VM_DCL_H__ */