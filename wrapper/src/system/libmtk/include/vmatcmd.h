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

#ifndef VMATCMD_SDK_H
#define VMATCMD_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/***************************************************************************** 
* Typedef 
*****************************************************************************/
/*vm_command_type*/
typedef enum
{
	VM_CMD_AT = 0,           // receive AT command
	VM_CMD_TYPE_TOTAL       // total received command type
} vm_command_type;

/*vm_command_transmitter_type*/
typedef enum
{
	VM_UART_TYPE = 0,           // reply command resoult though UART
	VM_TRANSMITTER_TYPE_TOTAL   // reply command type
} vm_command_transmitter_type;

/*vm_command_struct*/
typedef struct
{
	VMUINT32      command_type;      // command type
	VMUINT32      command_buf_size;  // command buffer size
	char*    command_buf;            // command buffer
}vm_command_struct;

/*vm_command_callback*/
typedef void (*vm_command_callback)(vm_command_struct *param, void *user_data);


/***************************************************************************** 
* Function
*****************************************************************************/
	
/*****************************************************************************
 * FUNCTION
 *  vm_command_open_port
 * DESCRIPTION
 *  After app open one port, all the command send to the port will transfer to the app.
 *  Remember that, the port number which just in scope(500~65535) can be used by app.
 *  User can send AT command like such format: "AT+[port]commandstring",ex:AT+[5000]command1.
 * PARAMETERS
 *  port                          [IN]       the port number, only can use from 500 ~ 65535.
 *  call_back                     [IN]       callback function, will be invoked when receive at command from this port.
 *  user_data                     [IN]       user data when you want to use in callback function; if no use, give NULL value.
 * RETURNS
 *  The opened port if sucess, or 0
 * EXAMPLE
 *<code>
 *
 * #define ATCMD_PORT 5000
 *
 * void vm_atcmd_callback(vm_command_struct *param, void *user_data)
 * {
 *    int len;
 *    char ret_buf[50];
 *
 * 	if (VM_CMD_AT == param->command_type)
 * 	{
 *          // use "AT+[5000]command1" to trigger it.
 * 		if (strncmp(command_buf, "command1", param->command_buf_size))
 * 		{	
 *                // handle the command and fill the result buffer.
 * 		    hadle_command1(ret_buf, &len);
 *                vm_command_reply(ret_buf, len, VM_UART_TYPE);
 * 		}
 * 	}
 * 	return;
 * }
 *
 * void handle_sysevt(VMINT message, VMINT param)
 * {
 *	 switch (message)
 *	 {
 *		 case VM_MSG_CREATE: 
 * 			vm_command_open_port(ATCMD_PORT, vm_atcmd_callback, NULL);
 * 			break;
 *		 case VM_MSG_QUIT:
 * 			vm_command_close_port(ATCMD_PORT);
 * 			break;
 * 		}
 * 	}
 * 	return 0;
 * }
 *</code>
 *****************************************************************************/
extern VMUINT16 vm_command_open_port(VMUINT16 port, vm_command_callback call_back, void *user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_command_close_port
 * DESCRIPTION
 *  Close the command port when app stop or you don't want to use it.
 * PARAMETERS
 *  port                          [IN]       the port number which be open by vm_open_command_port().
 * RETURNS
 *  None
 * EXAMPLE
 *<code>
 *
 * #define ATCMD_PORT 5000
 *
 * void vm_atcmd_callback(vm_command_struct *param, void *user_data)
 * {
 *    int len;
 *    char ret_buf[50];
 *
 * 	if (VM_CMD_AT == param->command_type)
 * 	{
 *          // use "AT+[5000]command1" to trigger it.
 * 		if (strncmp(command_buf, "command1", param->command_buf_size))
 * 		{	
 *                // handle the command and fill the result buffer.
 * 		    hadle_command1(ret_buf, &len);
 *                vm_command_reply(ret_buf, len, VM_UART_TYPE);
 * 		}
 * 	}
 * 	return;
 * }
 *
 * void handle_sysevt(VMINT message, VMINT param)
 * {
 *	 switch (message)
 *	 {
 *		 case VM_MSG_CREATE: 
 * 			vm_command_open_port(ATCMD_PORT, vm_atcmd_callback, NULL);
 * 			break;
 *		 case VM_MSG_QUIT:
 * 			vm_command_close_port(ATCMD_PORT);
 * 			break;
 * 		}
 * 	}
 * 	return 0;
 * }
 *</code>
 *****************************************************************************/
extern void vm_command_close_port(VMUINT16 port);


/*****************************************************************************
 * FUNCTION
 *  vm_command_reply
 * DESCRIPTION
 *  Response the command resoult to remote terminal which send the AT command.
 * PARAMETERS
 *  reply_buf                 [IN]       command resoult string buffer.
 *  buf_size                  [IN]       the size of the buffer.
 *  reply_type               [IN]       default transfer 0 for AT command reply.
 * RETURNS
 *  None
 * EXAMPLE
 *<code>
 *
 * #define ATCMD_PORT 5000
 *
 * void vm_atcmd_callback(vm_command_struct *param, void *user_data)
 * {
 *    int len;
 *    char ret_buf[50];
 *
 * 	if (VM_CMD_AT == param->command_type)
 * 	{
 *          // use "AT+[5000]command1" to trigger it.
 * 		if (strncmp(command_buf, "command1", param->command_buf_size))
 * 		{	
 *                // handle the command and fill the result buffer.
 * 		    hadle_command1(ret_buf, &len);
 *                vm_command_reply(ret_buf, len, VM_UART_TYPE);
 * 		}
 * 	}
 * 	return;
 * }
 *
 * void handle_sysevt(VMINT message, VMINT param)
 * {
 *	 switch (message)
 *	 {
 *		 case VM_MSG_CREATE: 
 * 			vm_command_open_port(ATCMD_PORT, vm_atcmd_callback, NULL);
 * 			break;
 *		 case VM_MSG_QUIT:
 * 			vm_command_close_port(ATCMD_PORT);
 * 			break;
 * 		}
 * 	}
 * 	return 0;
 * }
 *</code>
 *****************************************************************************/
extern void vm_command_reply(char* reply_buf, VMUINT32 buf_size, VMUINT32 reply_type);

#ifdef __cplusplus
}
#endif

#endif /* VMATCMD_SDK_H */ 

