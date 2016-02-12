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
 * vmfota_sdk.h
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  fota header file
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
#ifndef VM_FOTA_SDK_H
#define VM_FOTA_SDK_H
#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/
#include "vmsys.h"

/*vm_srv_funet_flag_enum*/
typedef enum
{
    VM_SRV_FUNET_FLAG_SUCCESS,//VM_SRV_FUNET_FLAG_SUCCESS
    VM_SRV_FUNET_FLAG_FAIL_DEL_CBR_UPDATING_INFO,//VM_SRV_FUNET_FLAG_FAIL_DEL_CBR_UPDATING_INFO
    VM_SRV_FUNET_FLAG_ERASE_MARKER_BLOCK,//VM_SRV_FUNET_FLAG_ERASE_MARKER_BLOCK
    VM_SRV_FUNET_FLAG_WRITE_MARKER_BLOCK,//VM_SRV_FUNET_FLAG_WRITE_MARKER_BLOCK
    VM_SRV_FUNET_FLAG_NO_DL_PACKAGE_FOUND,//VM_SRV_FUNET_FLAG_NO_DL_PACKAGE_FOUND
    VM_SRV_FUNET_FLAG_FLASH_INIT_FAIL//VM_SRV_FUNET_FLAG_FLASH_INIT_FAIL
} vm_srv_funet_flag_enum;

/*vm_srv_funet_update_type_enum*/
typedef enum
{
    VM_SRV_FUNET_UPDATE_FULL,//VM_SRV_FUNET_UPDATE_FULL
    VM_SRV_FUNET_UPDATE_PARTIAL//VM_SRV_FUNET_UPDATE_PARTIAL
} vm_srv_funet_update_type_enum;

/*vm_fudiffnet_update_type_enum*/
typedef enum
{
	  VM_FUDIFFNET_UPDATE_FULL,//VM_FUDIFFNET_UPDATE_FULL
    VM_FUDIFFNET_UPDATE_PARTIAL//VM_FUDIFFNET_UPDATE_PARTIAL
}vm_fudiffnet_update_type_enum;

/*vm_fudiffnet_flag_enum*/
typedef enum
{
    VM_FUDIFFNET_FLAG_SUCCESS,//VM_FUDIFFNET_FLAG_SUCCESS
    VM_FUDIFFNET_FLAG_FAIL_DEL_CBR_UPDATING_INFO,//VM_FUDIFFNET_FLAG_FAIL_DEL_CBR_UPDATING_INFO
    VM_FUDIFFNET_FLAG_ERASE_MARKER_BLOCK,//VM_FUDIFFNET_FLAG_ERASE_MARKER_BLOCK
    VM_FUDIFFNET_FLAG_WRITE_MARKER_BLOCK,//VM_FUDIFFNET_FLAG_WRITE_MARKER_BLOCK
    VM_FUDIFFNET_FLAG_NO_DL_PACKAGE_FOUND,//VM_FUDIFFNET_FLAG_NO_DL_PACKAGE_FOUND
    VM_FUDIFFNET_FLAG_FLASH_INIT_FAIL//VM_FUDIFFNET_FLAG_FLASH_INIT_FAIL
} vm_fudiffnet_flag_enum;
/*vm_fudiffnet_update_ret_enum*/
typedef enum
{
    VM_FUDIFFNET_NO_UPDATE,//VM_FUDIFFNET_NO_UPDATE
    VM_FUDIFFNET_UPDATE_SUCCESS,//VM_FUDIFFNET_UPDATE_SUCCESS
    VM_FUDIFFNET_UPDATE_FAIL//VM_FUDIFFNET_UPDATE_FAIL
}vm_fudiffnet_update_ret_enum;

/* srv_fudiffnet_fota_pre_info_struct */
typedef struct
{
    VMUINT8 brand[50]; //brand
    VMUINT8 model[50]; //model
    VMUINT8 domain[30]; //domain
    VMUINT8 pin_code[30]; //pin_code
}vm_fudiffnet_fota_pre_info_struct;

/*****************************************************************************
 * FUNCTION
 *	vm_srv_funet_trigger
 * DESCRIPTION
 *  Trigger bootloader to update. 
 * PARAMETERS
 *	file_name            [IN] FOTA update package
 *  update_type        [IN] Full update or partial update
 * RETURNS
 *	vm_srv_funet_flag_enum: update flag return
 *****************************************************************************/
extern vm_srv_funet_flag_enum vm_srv_funet_trigger(VMWCHAR * file_name, vm_srv_funet_update_type_enum update_type);

/*****************************************************************************
 * FUNCTION
 *	vm_fudiffnet_trigger
 * DESCRIPTION
 *  Trigger bootloader to update differential package.
 * PARAMETERS
 *	update_type        [IN] Full update or partial update 
 * RETURNS
 *	vm_fudiffnet_flag_enum: update flag return
 * EXAMPLE
 * <code>
 *if (VM_FUDIFFNET_FLAG_SUCCESS == vm_fudiffnet_trigger(VM_FUDIFFNET_UPDATE_PARTIAL))
 *{
 *	 ...
 *}
 *else
 *{
 *	...
 *}
 *
 * </code>
 *****************************************************************************/
extern vm_fudiffnet_flag_enum vm_fudiffnet_trigger(vm_fudiffnet_update_type_enum update_type);

/*****************************************************************************
 * FUNCTION
 *	vm_fudiffnet_get_fota_result
 * DESCRIPTION
 *  get update result from update_info file. 
 * PARAMETERS
 *	N/A
 * RETURNS
 *	vm_fudiffnet_update_ret_enum
 * EXAMPLE
 * <code>
 * vm_fudiffnet_update_ret_enum ret = VM_FUDIFFNET_NO_UPDATE;	
 * 
 * ret = vm_fudiffnet_get_fota_result();
 * if (VM_FUDIFFNET_UPDATE_SUCCESS == ret)
 * {
 *     ...
 * }
 * else if(VM_FUDIFFNET_UPDATE_FAIL == ret)
 * {
 *     vm_log_info( "fota update failed.");
 * }
 * else if(VM_FUDIFFNET_NO_UPDATE == ret)
 * {
 *     vm_log_info( "fota no update.");
 * }
 * </code>
 *****************************************************************************/
extern vm_fudiffnet_update_ret_enum vm_fudiffnet_get_fota_result(void);

/*****************************************************************************
 * FUNCTION
 *	vm_fudiffnet_get_firmware_path
 * DESCRIPTION
 *  get firmware path
 * PARAMETERS
 *	N/A
 * RETURNS
 *	VMWCHAR*
 * EXAMPLE
 * <code>
 * VMWCHAR* firmware_path = NULL;
 * firmware_path = vm_fudiffnet_get_firmware_path();	
 * </code>
 *****************************************************************************/
extern VMWCHAR* vm_fudiffnet_get_firmware_path(void);

/*****************************************************************************
 * FUNCTION
 *  vm_fudiffnet_get_fota_pre_info
 * DESCRIPTION
 *  get some pre info which need to be used to check new version in fota process.
 * PARAMETERS
 * pre_info        [OUT] fota pre info structure  
 * RETURNS
 *  void
 *****************************************************************************/
extern void vm_fudiffnet_get_fota_pre_info(vm_fudiffnet_fota_pre_info_struct* pre_info);


#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*VM_FOTA_SDK_H*/





