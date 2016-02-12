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

#ifndef _VM_DES_SDK_H_
#define _VM_DES_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"


/* DOM-NOT_FOR_SDK-BEGIN */

#define	VMDESHANDLE			VMINT

#define	DES_INVALID_HANDLE		-1
#define	DES_OK					0

#define DES_BLOCK_SIZE		8

/*****************************************************************************
 * FUNCTION
 *  vm_des_set_key (old usage, please use new interface of CHE, refer in vmche.h)
 * DESCRIPTION
 *  set des key.
 * PARAMETERS
 *  key : [IN] key.
 * RETURNS
 *  des handle
 *****************************************************************************/
VMDESHANDLE vm_des_set_key( VMUINT8 key[8] );

/*****************************************************************************
 * FUNCTION
 *  vm_des_encrypt  (old usage, please use new interface of CHE, refer in vmche.h)
 * DESCRIPTION
 *  encrypt the data.
 * PARAMETERS
 *  handle : [IN] des handle from vm_des_set_key .
 *  input : [IN] input data.
 *  input_len : [IN] input data length.
 *  output_len : [OUT] output data length.
 * RETURNS
 *  encrypt output data
 *****************************************************************************/
VMUINT8 * vm_des_encrypt( VMDESHANDLE handle, VMUINT8 * input, VMINT input_len, VMINT * output_len );

/*****************************************************************************
 * FUNCTION
 *  vm_des_decrypt  (old usage, please use new interface of CHE, refer in vmche.h)
 * DESCRIPTION
 *  decrypt the data.
 * PARAMETERS
 *  handle : [IN] des handle from vm_des_set_key .
 *  input : [IN] input data.
 *  input_len : [IN] input data length.
 *  output_len : [OUT] output data length.
 * RETURNS
 *  decrypt output data
 *****************************************************************************/
VMUINT8 * vm_des_decrypt( VMDESHANDLE handle, VMUINT8 * input, VMINT input_len, VMINT * output_len );

/*****************************************************************************
 * FUNCTION
 *  vm_des_reset_key  (old usage, please use new interface of CHE, refer in vmche.h)
 * DESCRIPTION
 *  This function is document type start handler.
 * PARAMETERS
 *  handle : [IN] des handle from vm_des_set_key .
 * RETURNS
 *  DES_INVALID_HANDLE : error
 *  DES_OK : ok
 *****************************************************************************/
VMINT vm_des_reset_key( VMDESHANDLE handle );

/* DOM-NOT_FOR_SDK-END */

#ifdef __cplusplus
}
#endif

#endif /* _VM_DES_SDK_H_ */
