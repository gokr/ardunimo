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
 * vmota_sdk.h
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  ota
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
#ifndef VM_OTA_SDK_H
#define VM_OTA_SDK_H
#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/
#include "vmsys.h"

#define VM_UPDATE_OK_ALREADY_DOWNLOADED         1
#define VM_UPDATE_OK                            0
#define VM_UPDATE_ERROR                         -2
#define VM_UPDATE_ERROR_GET_VERSION_FAIL        -3
#define VM_UPDATE_ERROR_GET_APP_ID_FAIL         -4
#define VM_UPDATE_ERROR_GET_SC_FAIL             -5
#define VM_UPDATE_ERROR_PATH_NOT_EXIST          -6
#define VM_UPDATE_ERROR_NO_MEMORY               -7
#define VM_UPDATE_ERROR_NO_UPDATE_FILE          -8
#define VM_UPDATE_ERROR_INTER                   -9

typedef void (*vm_update_app_callback)(VMINT hdl, void * para);



/*****************************************************************************
 * FUNCTION
 *  vm_update_check_version
 * DESCRIPTION
 *  check new version is avaliable or not through service.  
 * PARAMETERS
 *  
 * RETURNS
 *  error code, VM_UPDATE_OK means success, can get result from callback
 *                   VM_UPDATE_OK_ALREADY_DOWNLOADED means new version already downloaded   
 *****************************************************************************/
VMINT vm_update_check_version(VMSTR URL, VMINT port, VMINT apn, vm_update_app_callback callback, void* user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_update_download
 * DESCRIPTION
 *  after check version, can use this to download new version app
 * PARAMETERS
 *  
 * RETURNS
 *  error code, VM_UPDATE_OK means success, can get result from callback
 *****************************************************************************/
VMINT vm_update_download(VMINT handle, VMINT bOnCard, vm_update_app_callback callback, void* user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_update_update_file
 * DESCRIPTION
 *  if downloaded, can use this to update to new version app. This will exit the running app.
 * PARAMETERS
 *  
 * RETURNS
 *****************************************************************************/
VMINT vm_update_update_file(void);

/*****************************************************************************
 * FUNCTION
 *  vm_update_cancel
 * DESCRIPTION
 *  cancel the downloading process
 * PARAMETERS
 *  
 * RETURNS
 *****************************************************************************/
VMINT vm_update_cancel(VMINT handle);

VMINT vm_update_check_launch(VMWSTR path, VMWSTR new_path);

#define vm_update_mre_app_callback vm_update_app_callback

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*VM_OTA_SDK_H*/
