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

#ifndef VM_PURCHASE_SDK_H
#define VM_PURCHASE_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

typedef enum
{
    VM_BUYER_ALIPAY
}vm_payment_type_enum;

typedef enum
{
    VM_PURCHASE_RET_ERR_PARAM,
    VM_PURCHASE_RET_ERR_FAILURE,
    VM_PURCHASE_RET_ERR_SIM,
    VM_PURCHASE_RET_ERR_SUCCESS = 0,
}vm_purchase_ret_enum;

typedef VMINT VM_H_BUYER;
typedef void (*purchase_cb)(void*);


/*****************************************************************************
 * FUNCTION
 *  vm_create_buyer
 * DESCRIPTION
 *  get the payment handle.
 * PARAMETERS
 *  payment_type : [IN] 
 * RETURNS
 *  the handle of the buyer, non-negtive is successful
*****************************************************************************/
VM_H_BUYER vm_create_buyer(vm_payment_type_enum payment_type);

/*****************************************************************************
* FUNCTION
 *  vm_purchase_item
 * DESCRIPTION
 *  the operation of item-purchase.
 * PARAMETERS
 *  h : [IN] buyer handle.
 * data : [IN] user data.
 * cb : [IN] feedback of purchase
 * RETURNS
 *  the number of process that have created already.
*****************************************************************************/
VMINT vm_purchase_item(VM_H_BUYER h, void * data, purchase_cb cb);


/*****************************************************************************
 * FUNCTION
 * vm_release_buyer
 * DESCRIPTION
 *  release the handle of buyer.
 * PARAMETERS
 *  h : [IN] buyer handle.
*****************************************************************************/
void vm_release_buyer(VM_H_BUYER h);

#ifdef __cplusplus
}
#endif

#endif /* VM_PURCHASE_SDK_H */
