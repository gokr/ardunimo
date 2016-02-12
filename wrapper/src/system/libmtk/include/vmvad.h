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

#ifndef VMVAD_SDK_H
#define VMVAD_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"


 /*****************************************************************************
 * <GROUP  CallbackFunctions>
 *
 * FUNCTION
 *  vm_vad_msg_hdlr
 * DESCRIPTION
 *  This function is used to handle msg data.
 * PARAMETERS
 *  msg : [IN] message id.
 *  param : [IN] message parameter.
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_vad_msg_hdlr)(VMINT msg, VMINT param);

/*****************************************************************************
 * FUNCTION
 *  vm_vad_switch_on_off
 * DESCRIPTION
 *  switch on/off VAD.
 * PARAMETERS
 *  on : [IN] on/off VAD
 *  param : reserve, NULL is ok
 * RETURN VALUES
 *  TRUE : if the operation is successful.
 *  FALSE : means error illegal
 *****************************************************************************/
VMBOOL vm_vad_switch_on_off(VMBOOL on, void* param);

/*****************************************************************************
 * FUNCTION
 *  vm_vad_set_level
 * DESCRIPTION
 *  Set VAD Detect sensitivity
 * PARAMETERS
 *  level : [IN] 0¨C255, 0 is the highest level sensitivity
 * RETURN VALUES
 *  TRUE : if the operation is successful.
 *  FALSE : means error illegal
 *****************************************************************************/
VMBOOL vm_vad_set_level(VMUINT8 level);

/*****************************************************************************
 * FUNCTION
 *  vm_vad_is_on
 * DESCRIPTION
 *  check VAD on/off
 * RETURN VALUES
 *  TRUE : on.
 *  FALSE : off
 *****************************************************************************/
VMBOOL vm_vad_is_on(void);

/*****************************************************************************
 * FUNCTION
 *  vm_vad_get_level
 * DESCRIPTION
 *  get current VAD sensitivity level
 * RETURN VALUES
 *  0-255 
 *****************************************************************************/
VMUINT8 vm_vad_get_level(void);

/*****************************************************************************
 * FUNCTION
 *  vm_vad_register_callback
 * DESCRIPTION
 *  Register the callback function that deal with the detect result 
 * PARAMETERS
 *  callback : [IN] the function to deal with the detect result
 *****************************************************************************/
void vm_vad_register_callback(vm_vad_msg_hdlr callback);


#ifdef __cplusplus
}
#endif

#endif /* VMVAD_SDK_H */ 

