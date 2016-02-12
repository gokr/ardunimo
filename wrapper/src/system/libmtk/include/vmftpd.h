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
 * vmftpd_sdk.h
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
#ifndef VM_FTPD_SDK_H
#define VM_FTPD_SDK_H
#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/
#include "vmsys.h"

/* vm_ftpsrv_error_enum */
typedef enum
{
	VM_FTPSRV_ERR_NO_ERROR                    = 0,  //operator suceed
	VM_FTPSRV_ERR_STATE_ERROR                 = -1, //state of ftp is mess 
	VM_FTPSRV_ERR_GET_MEM_FAIL                = -2, //memory is not enough
	VM_FTPSRV_ERR_CONNECT_NETWORK_FAIL        = -3, //net work is not ready
	VM_FTPSRV_ERR_FD_INIT_FAIL                = -4, //file disciptor init fail
	VM_FTPSRV_ERR_GET_HOSTNAME_FAIL           = -5, //invalid host name
	VM_FTPSRV_ERR_SRV_INIT_FAIL               = -6, //server init fail
	VM_FTPSRV_ERR_ERROR_FD_NUMBER             = -7, //file diciptor abnormal
	VM_FTPSRV_ERR_OTHERS                      = -65535, // other errors
	VM_FTPSRV_ERR_CODE                        = -65536  //end mark.
}vm_ftpsrv_error_enum;


/*****************************************************************************
 * FUNCTION
 *  vm_inet_ftpd_start
 * DESCRIPTION
 *  this is for lauch ftp server
 * PARAMETERS
 * port : [IN]
 * root_dir : [IN]
 * RETURNS
 * vm_ftpsrv_error_enum
 * EXAMPLE
 * <code>
 *  if (vm_inet_ftpd_start(21, "C:\\@ftp") == VM_FTPSRV_ERR_NO_ERROR)
 *  {
 *      // do relate action
 *  }
 * </code>
 *****************************************************************************/
extern vm_ftpsrv_error_enum vm_inet_ftpd_start(VMUINT32 port, VMCHAR* root_dir);


/*****************************************************************************
 * FUNCTION
 *  vm_inet_ftpd_stop
 * DESCRIPTION
 *  this is for stop ftp server
 * PARAMETERS
 * RETURNS
 * vm_ftpsrv_error_enum
 *
 * EXAMPLE
 * <code>
 *  if (vm_inet_ftpd_stop() == VM_FTPSRV_ERR_NO_ERROR)
 *  {
 *      // do relate action
 *  }
 * </code>
 *****************************************************************************/
extern vm_ftpsrv_error_enum vm_inet_ftpd_stop(void);

/*****************************************************************************
 * FUNCTION
 *  vm_inet_ftpd_restart
 * DESCRIPTION
 * this is for restart ftp server
 * PARAMETERS
 * port : [IN]
 * root_dir : [IN]
 * RETURNS
 * vm_ftpsrv_error_enum
 *
 * EXAMPLE
 * <code>
 *  if (vm_inet_ftpd_restart(21, "C:\\@ftp") == VM_FTPSRV_ERR_NO_ERROR)
 *  {
 *      // do relate action
 *  }
 * </code>
 *****************************************************************************/
extern vm_ftpsrv_error_enum vm_inet_ftpd_restart(VMUINT32 port, VMCHAR* root_dir);


#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*VM_FTPD_SDK_H*/