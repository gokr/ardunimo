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

#ifndef VMUART_SDK_H_
#define VMUART_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* Enum values of uart port */
typedef enum {
      vm_uart_port1=0,
      vm_uart_port2,
      vm_uart_port3,
      vm_uart_port_swdbg,
      vm_uart_port_irda,
      vm_uart_port_usb,
      vm_uart_port_usb2,
      vm_uart_port_usb3,
      vm_uart_port_bluetooth,
      vm_uart_max_port,    
      vm_uart_port_null = 99
} vm_port;


/*******************************************************************************
* FUNCTION
*  vm_uart_open
* DESCRIPTION
*  open uart port
* PARAMETERS
*  port:    [IN]    uart port
* RETURNS
*  uart port handle
* GLOBALS AFFECTED
* 
*******************************************************************************/
VMINT32 vm_uart_open(vm_port port);

/*******************************************************************************
* FUNCTION
*  vm_read_from_uart
* DESCRIPTION
*  read data from specific uart port handle
* PARAMETERS
*  handle:    [IN]    return value of vm_uart_open
*  buffer:    [OUT]    memory space of read data
*  length:    [IN]    the expected length of read data
* RETURNS
*  real length of read data
* GLOBALS AFFECTED
* 
*******************************************************************************/
VMUINT16 vm_read_from_uart(VMINT32 handle, VMUINT8 *buffer, VMUINT16 length);

/*******************************************************************************
* FUNCTION
*  vm_write_to_uart
* DESCRIPTION
*  write data using uart port
* PARAMETERS
*  handle:    [IN]    return value of vm_uart_open
*  buffer:    [IN]    write data space
*  length:    [IN]    the expected length of write data
* RETURNS
*  real length of write data
* GLOBALS AFFECTED
* 
*******************************************************************************/
VMUINT16 vm_write_to_uart(VMINT32 handle, VMUINT8 *buffer, VMUINT16 length);

/*******************************************************************************
* FUNCTION
*  vm_uart_close
* DESCRIPTION
*  close uart port
* PARAMETERS
*  hanle:    [IN]    return value of vm_uart_open
* RETURNS
*  VMINT32    0 is success, other fail
* GLOBALS AFFECTED
* 
*******************************************************************************/
VMINT32 vm_uart_close(VMINT32 handle);


/*
using sample code

VMINT32 handle;
VMUINT16  length;
VMUINT8   buffer[7];
handle = vm_uart_open(vm_uart_port1);
if(handle != 0)
{
    length = vm_write_to_uart(result, buffer, 7);
    
    (or length = vm_read_from_uart(result, buffer, 7);)
}
if(handle != 0)
{
    vm_uart_close(handle);
}
*/


#ifdef __cplusplus
}
#endif

#endif /* VMUART_SDK_H_ */