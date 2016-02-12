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
 * vmrtspd_sdk.h
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  
 *
 * Author:
 * -------
 * 
 *
*==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *------------------------------------------------------------------------------
* *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *============================================================================== 
*******************************************************************************/
#ifndef VM_RTSPD_SDK_H
#define VM_RTSPD_SDK_H
#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/
#include "vmsys.h"
/*vm_rtspd_error_enum*/
typedef enum
{
	VM_RTSPD_ERR_NO_ERROR                    = 0,  //operator suceed
	VM_RTSPD_ERR_STATE_ERROR                 = -1, //state of http is mess 
	VM_RTSPD_ERR_GET_MEM_FAIL                = -2, //memory is not enough
	VM_RTSPD_ERR_CONNECT_NETWORK_FAIL        = -3, //net work is not ready
	VM_RTSPD_ERR_FD_INIT_FAIL                = -4, //file disciptor init fail
	VM_RTSPD_ERR_SRV_INIT_FAIL               = -5, //server init fail
	VM_RTSPD_ERR_SAVE_CB                     = -65534,//save cb fail
	VM_RTSPD_ERR_OTHERS                      = -65535, // other errors
	VM_RTSPD_ERR_CODE                        = -65536  //end mark.
}vm_rtspd_error_enum;
/*vm_rtspd_status_enum*/
typedef enum
{
	VM_RTSPD_IND_IDLE = 0,
	VM_RTSPD_IND_RECORDING_ONLY,// in local recording and save temp file
	VM_RTSPD_IND_FILE_MERGE_ONLY,// create local video file
	VM_RTSPD_IND_STREAMING_ONLY,//rtsp send rtp data
	VM_RTSPD_IND_STREAMING_RECORDING,//rtsp send rtp & local save temp file
	VM_RTSPD_IND_STREAMING_FILE_MERGE//rtsp send rtp & local save file merge
}vm_rtspd_status_enum;

/*****************************************************************************
 * DESCRIPTION
 *   VM_RTSPD_CB is the prototype of the call back function.
 * PARAMETERS
 * status:    [IN]  vm_rtspd_status_enum
 * data:      [IN]  currently have no meaning,use for future extend
 * RETURNS
 *  The return value is void. 
 *****************************************************************************/
typedef void (*VM_RTSPD_CB)(vm_rtspd_status_enum status, void* data);
/*****************************************************************************
 * FUNCTION
 *  vm_inet_rtspd_register_cb
 * DESCRIPTION
 * register rtspd callback function
 * PARAMETERS
 *  callback: VM_RTSPD_CB
 * RETURNS
 *  vm_rtspd_error_enum: 0,success; others: fail.
 *****************************************************************************/
extern vm_rtspd_error_enum vm_inet_rtspd_register_cb(VM_RTSPD_CB callback);
/*****************************************************************************
 * FUNCTION
 *  vm_inet_rtspd_start
 * DESCRIPTION
 * this is for lauch rtsp server
 * PARAMETERS
 *  port: 
 *  root_dir:[IN] the root dir
 * RETURNS
 *  vm_rtspd_error_enum:
 *<code>
 *vm_inet_rtspd_start(554, "C:\\@rtsp");
 *</code>
 *****************************************************************************/
extern vm_rtspd_error_enum vm_inet_rtspd_start(VMUINT32 port, VMCHAR* root_dir);
/*****************************************************************************
 * FUNCTION
 *  vm_inet_httpd_stop
 * DESCRIPTION
 *  this is for stop http server
 * PARAMETERS
 *  N/A
 * RETURNS
 *  httpsrv_error_enum:return VM_HTTPSRV_ERR_NO_ERROR, success, othersize, fail
 *<code>
 *vm_inet_rtspd_stop();
 *</code>
 *****************************************************************************/
extern vm_rtspd_error_enum vm_inet_rtspd_stop(void);
/*****************************************************************************
 * FUNCTION
 *  vm_inet_rtspd_restart
 * DESCRIPTION
 * this is for restart rtsp server
 * PARAMETERS
 *  port:  [IN]the port to restart                     
 *  root_dir:[IN]the root dir
 * RETURNS
 *  vm_rtspd_error_enum
 *<code>
 *vm_inet_rtspd_restart(554, "C:\\@rtsp");
 *</code>
 *****************************************************************************/
extern vm_rtspd_error_enum vm_inet_rtspd_restart(VMUINT32 port, VMCHAR* root_dir);
/*****************************************************************************
 * FUNCTION
 *  vm_inet_rtspd_set_stream_identify
 * DESCRIPTION
 * this is for set the name of real time stream,rtsp server will check request URL with this string
 * PARAMETERS
 *  stream_name:  [IN]                  
 * RETURNS
 *  none
 *<code>
 *vm_inet_rtspd_set_stream_identify("xxx.3gp");
 *</code>
 *****************************************************************************/
extern void vm_inet_rtspd_set_stream_identify(VMCHAR* stream_name);


#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*VM_RTSPD_SDK_H*/