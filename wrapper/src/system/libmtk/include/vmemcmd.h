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
 * vmemcmd_sdk.h
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
 * diangang.qin(mtk81217)
 *
*==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *------------------------------------------------------------------------------
* *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *============================================================================== 
*******************************************************************************/
#ifndef VM_EMCMD_SDK_H
#define VM_EMCMD_SDK_H
#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/

#include "vmsys.h"

/*vm_emcmd_enum*/
typedef enum
{
    VM_EMCMD_NO_ERROR                          = 0,//operator suceed
    VM_EMCMD_GET_MEM_FAIL                      = -1,//memory is not enough
    VM_EMCMD_ERR_OTHERS                      = -65535,// other errors
    VM_EMCMD_ERR_END                        = -65536//end mark
}vm_emcmd_enum;

/* callback function at_cmd */
typedef VMINT (*VM_EM_CMD_CB)(void *data);

/*****************************************************************************
 * FUNCTION
 *  vm_em_send_command
 * DESCRIPTION
 *  this is for send em cmd
 * PARAMETERS
 *  atCmdStr:  [IN]the cmd string                     
 *  atcmd_cb:[IN]the cmd cb
 * RETURNS
 *  vm_emcmd_enum:return VM_EMCMD_NO_ERROR, success, othersize, fail
 *****************************************************************************/
extern vm_emcmd_enum vm_em_send_command(VMCHAR *atCmdStr, VM_EM_CMD_CB atcmd_cb);

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*VM_EMCMD_SDK_H*/