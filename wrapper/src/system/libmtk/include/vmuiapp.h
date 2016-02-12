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

#ifndef VMUIAPP_SDK_H
#define VMUIAPP_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"
/* This enumeration defines the error code of dispatching URI request or registering URI request handler by scheme or by prefix. */
typedef enum
{
    VM_SRV_URIAGENT_ERR_OK,                    /* Success to process this request. */
    VM_SRV_URIAGENT_ERR_SCHEME_IS_REGISTERED,  /* Fail to process this registration  because handler was already registered for this scheme; this error code is used for URI request handler registration only. */
    VM_SRV_URIAGENT_ERR_PREFIX_IS_REGISTERED,  /* Fail to process this registration  because handler was already registered for this prefix; this error code is used for URI request handler registration only. */
    VM_SRV_URIAGENT_ERR_PROCESSING,            /* Fail to process this URI request because the previous request from the same URA is  still in processing; this error code is used for URI request dispatch only. */
    VM_SRV_URIAGENT_ERR_UNSUPPORTED            /* Fail to process this request. */
}vm_srv_uriagent_err_enum;


/*****************************************************************************
 * FUNCTION
 *  vm_uriagent_uri_request
 * DESCRIPTION
 *  wtai
 * PARAMETERS
 *  str    [IN]    string of wati
 *  confirm    [IN]    confirm
 * RETURNS
 *  -1 : no authorization
 *  -2 : not be supported
 *  refer to vm_srv_uriagent_err_enum
 *****************************************************************************/
VMINT vm_uriagent_uri_request(const VMCHAR * str, VMINT confirm);

/*****************************************************************************
 * FUNCTION
 *  vm_start_native_browser
 * DESCRIPTION
 *  query if specified key code is supported
 * PARAMETERS
 *  url    [IN]    open native browser if there dose exist.
 * RETURNS
 *  -1 : no authorization
 *  -2 : not be supported
 *  refer to return value of vm_open_wap_url 
 *****************************************************************************/
VMINT vm_start_native_browser(const VMWSTR url);


/*****************************************************************************
 * FUNCTION
 *  vm_startup_email
 * DESCRIPTION
 *  startup email
 * PARAMETERS
 *  to_addr : [IN] email address of receiver (UCS2)
 * RETURN VALUES
 *  0 : success
 *  non-zero : failure
 *  -2 : platform not support
 *  -3 : no email account
 *****************************************************************************/
VMINT vm_startup_email(const VMWSTR to_addr);

typedef enum
{
    VM_CAM_ERR_BUSY = -4,
    VM_CAM_ERR_EXCEPTION,
    VM_CAM_ERR_NOT_SUPPORT,
    VM_CAM_ERR_NOT_AUTHORIZED,
    VM_CAM_ERR_SUCCESS = 0,
}vm_camera_startup_error_t;


/*****************************************************************************
 * FUNCTION
 *  vm_camera_startup
 * DESCRIPTION
 *  Run Camrea APP directly, In lowend project, APP maybe need to exit cause of Out of Memory.
 * PARAMETERS
 *  Void
 * RETURNS
 *  Run result
 * RETURN VALUES
 *  0 : success
 *  non-zero : failure
 *****************************************************************************/
VMINT vm_camera_startup(void);

typedef enum
{
    VM_SELECTOR_ERR_NO_RES = -7, /* no avalible resource */
    VM_SELECTOR_ERR_PARAM, /* input invalid parameter */
    VM_SELECTOR_ERR_NO_MEMORY, /* no memmory */
    VM_SELECTOR_ERR_NO_DISK, /* driver path failure */
    VM_SELECTOR_ERR_EXCEPTION, /* exception */
    VM_SELECTOR_ERR_NOT_SUPPORT, /* platform dose not support */
    VM_SELECTOR_ERR_NOT_AUTHORIZED, /* no authrization */
    VM_SELECTOR_ERR_SUCCESS = 0 /* success */
}vm_selector_error_t;

typedef enum
{ 
    VM_SELECTOR_TYPE_ALL = 0, /* all file type */
    VM_SELECTOR_TYPE_IMAGE, /* image type */
    VM_SELECTOR_TYPE_TXT /* txt type */
}vm_selector_type_t;

/*****************************************************************************
 * FUNCTION
 *  vm_selector_run
 * DESCRIPTION
 *  Start Fmgr to select a file.
 * PARAMETERS
 * type : [IN] the browse type of file, define in vm_selector_type_t
 * folder_path : [IN] witch path need to be browsed, NULL means root 
 * callback : [IN] the result callback of file selection. file_path is the path name of current selected file, 
 * it be set NULL if error. wlen is the length of path name in words.
 * RETURNS
 *  0 or error code define in vm_selector_error_t
 * RETURN VALUES
 *  vm_selector_error_t
*****************************************************************************/
VMINT vm_selector_run(VMINT type, const VMWCHAR * folder_path, VMINT (*callback)(VMWCHAR * file_path, VMINT wlen));

typedef enum
{
    VM_FOLDER_BROWSER_ERR_NO_RES = -7, /* no avalible resource */
    VM_FOLDER_BROWSER_ERR_PARAM, /* input invalid parameter */
    VM_FOLDER_BROWSER_ERR_NO_MEMORY, /* no memmory */
    VM_FOLDER_BROWSER_ERR_NO_DISK, /* driver path failure */
    VM_FOLDER_BROWSER_ERR_EXCEPTION, /* exception */
    VM_FOLDER_BROWSER_ERR_NOT_SUPPORT, /* platform dose not support */
    VM_FOLDER_BROWSER_ERR_NOT_AUTHORIZED, /* no authrization */
    VM_FOLDER_BROWSER_ERR_SUCCESS = 0 /* success */
} vm_folder_browser_error_t;

typedef enum
{ 
    VM_FOLDER_BROWSER_TYPE_ALL = 0, /* all file type */
    VM_FOLDER_BROWSER_TYPE_IMAGE, /* image type */
    VM_FOLDER_BROWSER_TYPE_TXT /* txt type */
} vm_folder_browser_type_t;

/*******************************************************************************
 * FUNCTION
 *	vm_folder_browser_run
 * DESCRIPTION
 *	launch folder browser CUI.
 * PARAMETER
 *	type		:	[IN]	which type of file should be shown in folder browser.
 *							the optional values are :
 *								VM_FOLDER_BROWSER_TYPE_ALL
 *								VM_FOLDER_BROWSER_TYPE_IMAGE
 *								VM_FOLDER_BROWSER_TYPE_TXT
 *	folder_path	:	[IN]	the folder that you want to enter.
 *							NOTE:	it can NOT be L"root" or only a Driver name 
 *									such as L"D:\\".
 * RETURNS
 *	if success, return VM_FOLDER_BROWSER_ERR_SUCCESS.
 *	otherwise, a value in type of vm_folder_browser_type_t will be returned.
 ******************************************************************************/
VMINT vm_folder_browser_run(VMINT type, const VMWCHAR *folder_path);

typedef enum
{
    VM_FOLDER_SELECTOR_ERR_NO_RES           = -7, /* no avalible resource */
    VM_FOLDER_SELECTOR_ERR_PARAM,                 /* input invalid parameter */
    VM_FOLDER_SELECTOR_ERR_NO_MEMORY,             /* no memmory */
    VM_FOLDER_SELECTOR_ERR_NO_DISK,               /* driver path failure */
    VM_FOLDER_SELECTOR_ERR_EXCEPTION,             /* exception */
    VM_FOLDER_SELECTOR_ERR_NOT_SUPPORT,           /* platform doesn't support */
    VM_FOLDER_SELECTOR_ERR_NOT_AUTHORIZED,        /* no authrization */
    VM_FOLDER_SELECTOR_ERR_SUCCESS          = 0   /* success */
} vm_folder_selector_error_t;

typedef enum
{ 
    VM_FOLDER_SELECTOR_STYLE_READ,  /* CUI_FOLDER_SELECTOR_STYLE_READ */
    VM_FOLDER_SELECTOR_STYLE_WRITE, /* CUI_FOLDER_SELECTOR_STYLE_WRITE */
    VM_FOLDER_SELECTOR_STYLE_TOTAL  /* CUI_FOLDER_SELECTOR_STYLE_TOTAL */
} vm_folder_selector_style_t;

/******************************************************************************
 * FUNCTION
 *     vm_folder_selector_run
 * DESCRIPTION
 *     Start a file manager to select a folder.
 * PARAMETERS
 *     start_folder_path     : [IN] the path of start folder. when file manager
 *                                  is opened, it will enter this folder 
 *                                  directly.
 *     folder_selector_style : [IN] if it's VM_FOLDER_SELECTOR_STYLE_READ, that
 *                                      means you can NOT create a folder, 
 *                                      rename it or delete it.
 *                                  if it's VM_FOLDER_SELECTOR_STYLE_WRITE, that
 *                                      means you can create a folder, rename it
 *                                      , or delete it. 
 *     callback              : [IN] user provided callback function. when a 
 *                                  folder is selected, this function will be
 *                                  called to handle the selection. 
 *                                  selected_folder_path indicates which folder
 *                                      is selected. if it's NULL, that means 
 *                                      an error occurs.
 *                                  wlen is the length of selected folder's path
 *                                      in words.
 * RETURNS
 *     VM_FOLDER_SELECTOR_ERR_SUCCESS : the CUI runs successfully.
 *     other values means an error occurs, please refer to 
 *     vm_folder_selector_error_t for detailed information.
******************************************************************************/
VMINT vm_folder_selector_run(
    const VMWCHAR   *start_folder_path,
    VMINT           folder_selector_style,
    VMINT           (*callback)(VMWCHAR *selected_folder_path, VMINT wlen));

/*****************************************************************************
 * FUNCTION
 *  vm_is_support_gsensor
 * DESCRIPTION
 *  Check whether the phone support G-sensor or not.
 * PARAMETERS
 *  void
 * RETURN VALUES
 *  TRUE : Supports G-sensor.
 *  FALSE : Not support.
 *****************************************************************************/
VMINT vm_is_support_gsensor(void);

/*****************************************************************************
 * FUNCTION
 *  vm_is_support_camera_sensor
 * DESCRIPTION
 *  Check whether the phone support camera sensor or not.
 * PARAMETERS
 *  void
 * RETURN VALUES
 *  TRUE : Supports camera sensor.
 *  FALSE : Not support.
 *****************************************************************************/
VMINT vm_is_support_camera_sensor(void);

#ifdef __cplusplus
}
#endif

#endif /* VMUIAPP_SDK_H */ 

