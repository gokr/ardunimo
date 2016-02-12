/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2006
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

/*******************************************************************************
 * Filename:
 * ---------
 * vmbridge_sdk.h
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  driver bridge header file
 *
 * Author:
 * -------
 * jianying.li(mtk81091)
 *
*==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *------------------------------------------------------------------------------
* *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *============================================================================== 
*******************************************************************************/
#ifndef VM_BRIDGE_SDK_H
#define VM_BRIDGE_SDK_H
#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/
#include "vmsys.h"

/*vm_pipe_type*/
typedef enum
{
    VM_SOCKET_PIPE_TYPE = 0x01,//VM_SOCKET_PIPE_TYPE
    VM_UART_PIPE_TYPE,//VM_UART_PIPE_TYPE
    VM_USB_PIPE_TYPE,// VM_USB_PIPE_TYPE
    VM_UNDEFINED_TYPE//VM_UNDEFINED_TYPE
}vm_pipe_type;

/*vm_socket_info*/
typedef struct
{
    VMINT socket_accpet_fd;//socket_accpet_fd
}vm_socket_info;

typedef struct 
{
    VMUINT8 usb_port;//usb_port
}vm_usb_info;

/*vm_uart_info*/
typedef struct
{
    VMUINT32 uart_band;//uart_band
    VMUINT8 uart_port;//uart_port
    VMUINT8 flowControl;//flowControl  
}vm_uart_info;

/*vm_bridge_info*/
typedef struct
{
    VMINT type;//type
    union//type_info
        {
            vm_socket_info sock_info;//sock_info
            vm_uart_info uart_info;//uart_info
            vm_usb_info  usb_info;//usb_info
        }type_info;//type_info
}vm_bridge_info;



/*****************************************************************************
 * FUNCTION
 *	vm_bridge_create
 * DESCRIPTION
 *	create bridge and connect firPeer and secPeer
 * PARAMETERS
 *	firPeer: the first peer to create
 *  secPeer: the second peer to create
 * RETURNS
 *	if create success, return 0, else return non_zero val
 * USE CASE
 * <code>
 *  //accept sockect fd should obtain when socket accpet() return
 *  VMINT accpet_id;
 *  VMINT uart_port_id;
 *  vm_bridge_info firBridgeInfo,  secBridgeInfo;
 *  VMINT ret;
 *  // accpet fd should create by your socket listen() action
 *  firBridgeInfo.type = VM_SOCKET_PIPE_TYPE;
 *  firBridgeInfo.type_info.sock_info.socket_accpet_fd = accpet_id;
 *  
 *  secBridgeInfo.type = VM_UART_PIPE_TYPE;
 *  secBridgeInfo.type_info.uart_info.uart_port = uart_port_id;
 *  secBridgeInfo.type_info.uart_info.uart_band = UART_BAUD_9600;
 *  secBridgeInfo.type_info.uart_info.flowControl = 0;
 *  
 *  ret = vm_bridge_create(&firBridgeInfo, &secBridgeInfo);
 *  if(0 != ret)
 *  {
 *     //create bridge fail and can record trace
 *  }
 *
 *  // run bridge...
 * 
 * //close bridge(optional)
 *  ret = vm_bridge_close(&firBridgeInfo, &secBridgeInfo);
 * </code>
 *****************************************************************************/
extern VMINT vm_bridge_create(vm_bridge_info *firPeer, vm_bridge_info *secPeer);
/*****************************************************************************
 * FUNCTION
 *	vm_bridge_close
 * DESCRIPTION
 *	close bridge and disconnect firPeer and secPeer
 * PARAMETERS
 *	firPeer: the first peer to create
 *  secPeer: the second peer to create
 * RETURNS
 *	if close success, return 0, else return non_zero val
 * USE CASE like vm_bridge_create.
 *  <code>  
 *  //accept sockect fd should obtain when socket accpet() return
 *  VMINT accpet_id;
 *  VMINT uart_port_id;
 *  vm_bridge_info firBridgeInfo,  secBridgeInfo;
 *  VMINT ret;
 *  // accpet fd should create by your socket listen() action
 *  firBridgeInfo.type = VM_SOCKET_PIPE_TYPE;
 *  firBridgeInfo.type_info.sock_info.socket_accpet_fd = accpet_id;
 *  
 *  secBridgeInfo.type = VM_UART_PIPE_TYPE;
 *  secBridgeInfo.type_info.uart_info.uart_port = uart_port_id;
 *  secBridgeInfo.type_info.uart_info.uart_band = UART_BAUD_9600;
 *  secBridgeInfo.type_info.uart_info.flowControl = 0;
 *  
 *  ret = vm_bridge_create(&firBridgeInfo, &secBridgeInfo);
 *  if(0 != ret)
 *  {
 *     //create bridge fail and can record trace
 *  }
 *
 *  // run bridge...
 * 
 * //close bridge(optional)
 *  ret = vm_bridge_close(&firBridgeInfo, &secBridgeInfo);
 * </code>
 *****************************************************************************/
extern VMINT vm_bridge_close(vm_bridge_info *firPeer, vm_bridge_info *secPeer);
#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*VM_BRIDGE_SDK_H*/