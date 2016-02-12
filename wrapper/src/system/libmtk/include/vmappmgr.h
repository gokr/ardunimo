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
 * vmappmgr_sdk.h
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  application manager header file
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
#ifndef VM_APPMGR_SDK_H
#define VM_APPMGR_SDK_H
#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/
#include "vmsys.h"
#include "vmdatetime.h"

#define VM_INSTALL_ID_LEN 60
#define VM_APPMGR_DEVELOPER_NAME_LEN    30
#define VM_APPMGR_TEL_NUM_LEN   20
#define VM_APPMGR_APP_NAME_LEN  15
#define VM_APPMGR_FILEPATH_LEN  260

#define VM_APPMGR_MRE_ALL_FLAG              0x0001
#define VM_APPMGR_MRE_INSTALLED_FLAG        0x0002
#define VM_APPMGR_MRE_SHORTCUT_FLAG         0x0004

#define VM_APPMGR_WIDGET_PACKAGE_FLAG       (0x8001) /* mre widget app */
#define VM_APPMGR_WALLPAPER_PACKAGE_FLAG       (0x8002) /* mre wallpaper app */
#define VM_APPMGR_LAUNCHER_PACKAGE_FLAG       (0x8004) /* mre launcher app */
#define VM_APPMGR_SCRLOCK_PACKAGE_FLAG       (0x8008) /* mre screen lock app */

#define VM_APPMGR_VPP_PACKAGE_FLAG \
                (VM_APPMGR_WIDGET_PACKAGE_FLAG |\
                 VM_APPMGR_WALLPAPER_PACKAGE_FLAG |\
                 VM_APPMGR_LAUNCHER_PACKAGE_FLAG |\
                 VM_APPMGR_SCRLOCK_PACKAGE_FLAG)


typedef VMCHAR vm_install_id[VM_INSTALL_ID_LEN];




typedef enum
{
    VM_APPMGR_INSTALL_TYPE_UNKNOWN = 0,    /* UNKNOWN */
    VM_APPMGR_INSTALL_TYPE_DOWNLOAD,       /* dwonload from server */
    VM_APPMGR_INSTALL_TYPE_ROM,            /* build-in app */
    VM_APPMGR_INSTALL_TYPE_LOCAL_INSTALL,  /* install from local */
    VM_APPMGR_INSTALL_TYPE_SHORTCUT,       /* shortcut app */
    VM_APPMGR_INSTALL_TYPE_END_OF_ENUM
}vm_appmgr_install_type;

/* Application storage position type */
typedef enum
{
    VM_APPMGR_APP_POSITION_UNKNOWN = 0,    /* UNKNOWN */
    VM_APPMGR_APP_POSITION_PHONE,          /* Phone */
    VM_APPMGR_APP_POSITION_CARD,           /* Memory card */
    VM_APPMGR_APP_POSITION_ROM,            /* build-in app */
    VM_APPMGR_APP_POSITION_END_OF_ENUM
} vm_appmgr_app_storage_position;

/* Application authotization infomation */
typedef enum
{
    VM_APPMGR_APP_AUTH_CALLOUT = 0x00000001, /* call out */
    VM_APPMGR_APP_AUTH_SMS_SEND = 0x00000002, /* send sms */
    VM_APPMGR_APP_AUTH_MMS_SEND = 0x00000004, /* send mms */
    VM_APPMGR_APP_AUTH_GPRS_CONNECT = 0x00000010, /* GPRS connect */
    VM_APPMGR_APP_AUTH_WLAN_CONNECT = 0x00000040, /* WLAN connect */
    VM_APPMGR_APP_AUTH_GPS = 0x00000080, /* GPS */
    VM_APPMGR_APP_AUTH_RECORDER = 0x00000200, /* recorder */
    VM_APPMGR_APP_AUTH_CAMERA = 0x00000400, /* camera */
    VM_APPMGR_APP_AUTH_CALLLOG_READ = 0x00001000, /* read calllog */
    VM_APPMGR_APP_AUTH_SMS_READ = 0x00002000, /* read sms */
    VM_APPMGR_APP_AUTH_MMS_READ = 0x00004000, /* read mms */
    VM_APPMGR_APP_AUTH_BT_SWITCH = 0x00008000, /* BT */
    VM_APPMGR_APP_AUTH_ALL  = 0x80000000, /* full authorization */
} vm_appmgr_app_authorization_enum;

typedef struct
{
    VMUINT app_id;
    VMUINT app_size;
    vm_appmgr_install_type install_type; 
    vm_appmgr_app_storage_position store_pos;
    vm_time_t installed_time; 
    VMUINT16 developer[VM_APPMGR_DEVELOPER_NAME_LEN];  
    VMUINT16 tel[VM_APPMGR_TEL_NUM_LEN]; 
    VMUINT16 app_name[VM_APPMGR_APP_NAME_LEN]; 
    VMUINT16 app_path[VM_APPMGR_FILEPATH_LEN]; 
    VMUINT32 app_auth;
    VMUINT32 user_auth;
}vm_install_info;

typedef enum 
{
   VM_WALLPAPER_SRC_HOME_SCREEN,
   VM_WALLPAPER_SRC_LOCK_SCREEN
} vm_app_mgr_wallpaper_src_enum;


/*****************************************************************************
 * FUNCTION
 *  vm_appmgr_install
 * DESCRIPTION
 *  install mre app 
 * PARAMETERS
 *  path : [IN] path of app
 *  flag : [IN] reserved, please fill 0
 *  install_id : [OUT] identification of installed app
 * RETURNS
 *  error code 0 means success
 *****************************************************************************/
VMINT vm_appmgr_install(VMWSTR path, VMINT flag, vm_install_id install_id);

/*****************************************************************************
 * FUNCTION
 *  vm_appmgr_uninstall
 * DESCRIPTION
 *  uninstall mre app 
 * PARAMETERS
 *  install_id : [IN] identification of installed app, can get 
 *                            by using vm_appmgr_get_installed_list or vm_appmgr_is_installed
 * RETURNS
 *  error code 0 means success
 *****************************************************************************/
VMINT vm_appmgr_uninstall(vm_install_id install_id);


/*****************************************************************************
 * FUNCTION
 *  vm_appmgr_is_installed
 * DESCRIPTION
 *  check the mre app is intalled or not
 * PARAMETERS
 *  path : [IN] path of app
 *  install_id : [OUT] identification of installed app
 * RETURNS
 *  error code 0 means success
 *****************************************************************************/
VMBOOL vm_appmgr_is_installed(VMWSTR path, vm_install_id install_id);

/*****************************************************************************
 * FUNCTION
 *  vm_appmgr_get_installed_list
 * DESCRIPTION
 *  get installed app list. set install_id_list to NULL to get number of installed app.
 * PARAMETERS
 *  flag : [IN] 
 *  install_id_list : [OUT] identifications of installed app
 *  num :[IN/OUT] number of installed app
 * RETURNS
 *  error code 0 means success
 *****************************************************************************/
VMINT vm_appmgr_get_installed_list(VMINT flag ,vm_install_id* install_id_list, VMUINT* num);

/*****************************************************************************
 * FUNCTION
 *  vm_appmgr_get_install_info
 * DESCRIPTION
 *  get installed app detail information
 * PARAMETERS
 *  vm_install_id : [IN] identification of installed app
 *  vm_install_info : [OUT] detail information
 * RETURNS
 *  error code 0 means success
 *****************************************************************************/
VMINT vm_appmgr_get_install_info(vm_install_id install_id, vm_install_info* install_info);
/*****************************************************************************
 * FUNCTION
 *  vm_appmgr_activate_launcher
 * DESCRIPTION
 *  Active launcher plug-in
 * PARAMETERS
 *  install_id : [IN] identification of installed app, can get 
 *                            by using vm_appmgr_get_installed_list or vm_appmgr_is_installed
 * RETURNS
 *  error code 0 means success
 *****************************************************************************/
VMINT vm_appmgr_activate_launcher(vm_install_id install_id);

/*****************************************************************************
 * FUNCTION
 *  vm_appmgr_activate_screen_lock
 * DESCRIPTION
 *  Active Screen-Lock plug-in 
 * PARAMETERS
 *  install_id : [IN] identification of installed app, can get 
 *                            by using vm_appmgr_get_installed_list or vm_appmgr_is_installed
 * RETURNS
 *  error code 0 means success
 *****************************************************************************/
VMINT vm_appmgr_activate_screen_lock(vm_install_id install_id);

/*****************************************************************************
 * FUNCTION
 *  vm_appmgr_activate_wallpaper
 * DESCRIPTION
 *  Active wallpaper plug-in
 * PARAMETERS
 *  install_id : [IN] identification of installed app, can get 
 *                            by using vm_appmgr_get_installed_list or vm_appmgr_is_installed
 * RETURNS
 *  error code 0 means success
 *****************************************************************************/
VMINT vm_appmgr_activate_wallpaper(vm_install_id install_id, vm_app_mgr_wallpaper_src_enum src);

/******************************************************************************
 * FUNCTION
 *  vm_appmgr_get_mem_size
 * DESCRIPTION
 *  Get Memory size of DLUI components
 * PARAMETERS
 *  Package  :   [IN]       VM_APPMGR_WIDGET_PACKAGE_FLAG
 *                          VM_APPMGR_LAUNCHER_PACKAGE_FLAG
 *                          VM_APPMGR_WALLPAPER_PACKAGE_FLAG
 *                          VM_APPMGR_SCRLOCK_PACKAGE_FLAG
 * RETURNS
 *  Memory Size requirement, -1 means not support.
 ******************************************************************************/
VMINT vm_appmgr_get_mem_size(VMUINT32 package);
/******************************************************************************
 * FUNCTION
 *  vm_is_support_downloadable_app_icon
 * DESCRIPTION
 *  check whether downloadable app icon is supported.
 * PARAMETERS
 *  void
 * RETURNS
 *  TRUE means support, FALSE means NOT support.
 ******************************************************************************/
VMINT vm_is_support_downloadable_app_icon(void);


/******************************************************************************
 * FUNCTION
 *  vm_appmgr_is_launcher_activated
 * DESCRIPTION
 *  check whether launcher is activated.
 * PARAMETERS
 *  install_id  :   [IN]    identification of installed app, can get by using
 *                          vm_appmgr_get_installed_list or vm_appmgr_is_installed.
 * RETURNS
 *  TRUE means activated, FALSE means NOT activated.
 ******************************************************************************/
VMINT vm_appmgr_is_launcher_activated(vm_install_id install_id);


/******************************************************************************
 * FUNCTION
 *  vm_appmgr_is_wallpaper_activated
 * DESCRIPTION
 *  check whether wallpaper is activated.
 * PARAMETERS
 *  install_id  :   [IN]    identification of installed app, can get by using
 *                          vm_appmgr_get_installed_list or vm_appmgr_is_installed.
 *  src :   [IN]    wallpaper src.
 * RETURNS
 *  TRUE means activated, FALSE means NOT activated.
 ******************************************************************************/
VMINT vm_appmgr_is_wallpaper_activated(
            vm_install_id install_id,
            VMINT src);

/******************************************************************************
 * FUNCTION
 *  vm_appmgr_is_screen_lock_activated
 * DESCRIPTION
 *  check whether screen lock is activated.
 * PARAMETERS
 *  install_id  :   [IN]    identification of installed app, can get by using
 *                          vm_appmgr_get_installed_list or vm_appmgr_is_installed.
 * RETURNS
 *  TRUE means activated, FALSE means NOT activated.
 ******************************************************************************/
VMINT vm_appmgr_is_screen_lock_activated(vm_install_id install_id);

/******************************************************************************
 * FUNCTION
 *	vm_appmgr_is_support_launcher
 * DESCRIPTION
 *	check whether launcher is supported.
 * PARAMETERS
 *	void.
 * RETURNS
 *	TRUE means support, FALSE means NOT support.
 ******************************************************************************/
VMINT vm_appmgr_is_support_launcher(void);


/******************************************************************************
 * FUNCTION
 *	vm_appmgr_is_support_wallpaper
 * DESCRIPTION
 *	check whether wallpaper is supported.
 * PARAMETERS
 *	void.
 * RETURNS
 *	TRUE means support, FALSE means NOT support.
 ******************************************************************************/
VMINT vm_appmgr_is_support_wallpaper(void);

/******************************************************************************
 * FUNCTION
 *	vm_appmgr_is_support_screen_lock
 * DESCRIPTION
 *	check whether screen_lock is supported.
 * PARAMETERS
 *	void.
 * RETURNS
 *	TRUE means support, FALSE means NOT support.
 ******************************************************************************/
VMINT vm_appmgr_is_support_screen_lock(void);

/******************************************************************************
 * FUNCTION
 *	vm_appmgr_is_support_widget
 * DESCRIPTION
 *	check whether widget is supported.
 * PARAMETERS
 *	void.
 * RETURNS
 *	TRUE means support, FALSE means NOT support.
 ******************************************************************************/
VMINT vm_appmgr_is_support_widget(void);

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*VM_APPMGR_SDK_H*/