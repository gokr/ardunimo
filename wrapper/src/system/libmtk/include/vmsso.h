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
 * vmpromng.c
 *
 * Project:
 * --------
 *   MAUI
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
 * $Log$
 *
 * 07 05 2012 feng.lin
 * [MAUI_03211419] It allways shows invalid username or password error notice while logging in yahoo services.
 * .
 *
 * 06 14 2012 feng.lin
 * [MAUI_03202717] update sso srv callback prototype
 * .
 *
 * 06 07 2012 feng.lin
 * [MAUI_03159675] MRE of SSO
 * .
 *
 * 06 04 2012 feng.lin
 * [MAUI_03159675] MRE of SSO
 * .
 *
 * 05 14 2012 feng.lin
 * [MAUI_03159675] MRE of SSO
 * sso sdk.
 *
 * 05 14 2012 feng.lin
 * [MAUI_03159675] MRE of SSO
 * sso sdk.
 *
 * 04 25 2012 feng.lin
 * [MAUI_03159675] MRE of SSO
 * .
 *
 * 04 19 2012 feng.lin
 * [MAUI_03159675] MRE of SSO
 * .
 *
 * 04 18 2012 feng.lin
 * [MAUI_03159675] MRE of SSO
 * .
 *
 * 03 30 2012 feng.lin
 * [MAUI_03159675] MRE of SSO
 * .
 *
 * *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *============================================================================== 
 *******************************************************************************/

#ifndef VM_SSO_SDK_H
#define VM_SSO_SDK_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vmsys.h"

#define VM_SSO_NAME_SIZE                            64
#define VM_SSO_ACCESS_TOKEN                         256
#define VM_SSO_REFRESH_TOKEN                        256
#define VM_SSO_SCOPE                                128
#define VM_SSO_EXTENSION                            256

#define VM_SSO_EXT_YAHOO_COOKIE                     300
#define VM_SSO_EXT_YAHOO_CRUMB                      256


typedef enum
{
    VM_SSO_ICON_LARGE,
    VM_SSO_ICON_SMALL,
    VM_SSO_ICON_TOTAL,
}vm_sso_icon_enum;

typedef enum
{
    VM_SSO_LOGIN_DONT_CARE,
    VM_SSO_LOGIN_TRUE,
    VM_SSO_LOGIN_FALSE,
    VM_SSO_LOGIN_TOTAL
}vm_sso_login_state;

typedef enum
{
   VM_SSO_CREDENTIAL_OAUTH,
   VM_SSO_CREDENTIAL_USERPASS,
   VM_SSO_CREDENTIAL_YAHOO,
   VM_SSO_CREDENTIAL_TOTAL
}vm_sso_credential_enum;

typedef enum
{
    VM_SSO_OK,
    VM_SRV_SSO_UNKNOWN_ERROR      = -999,
    VM_SRV_SSO_CARD_PLUG_OUT,
    VM_SRV_SSO_USB_MS_MODE, 
    VM_SRV_SSO_PROVIDER_NOT_FOUND,
    VM_SRV_SSO_ACCOUNT_NOT_FOUND,
    VM_SRV_SSO_BUSY,
    VM_SRV_SSO_CONNECTION_FAIL,
    VM_SRV_SSO_INCORRECT_ID_PW,
    VM_SRV_SSO_NOT_FULL_EMAIL,
    VM_SRV_SSO_CANCELLED,
    VM_SRV_SSO_UPGRADING,
    VM_SRV_SSO_FAIL_TO_LOAD_PLUGIN
}vm_sso_result;


typedef struct
{
    VMUINT32 provider;
    VMUINT8 accounts_total;    // number of total accounts
    VMUINT8 accounts_loggedin; // number of accounts which are logged-in
}vm_sso_provider_struct;

typedef struct
{
    VMUINT32 provider;
    VMUINT8 account;
    VMUINT8 is_login;
} vm_sso_account_struct;

typedef struct
{
    vm_sso_credential_enum type;
    union 
    {
       struct 
       {
          VMCHAR access_token[VM_SSO_ACCESS_TOKEN];
          VMCHAR refresh_token[VM_SSO_REFRESH_TOKEN];
          VMCHAR scope[VM_SSO_SCOPE];
          VMCHAR extension[VM_SSO_EXTENSION];
       } oauth;
       struct 
       {
          VMCHAR username[VM_SSO_NAME_SIZE];
          VMCHAR password[VM_SSO_NAME_SIZE];
       } userpass;       
       struct 
       {
          VMCHAR security_token[VM_SSO_ACCESS_TOKEN];
          VMCHAR ycookie[VM_SSO_EXT_YAHOO_COOKIE];
          VMCHAR tcookie[VM_SSO_EXT_YAHOO_COOKIE];
          VMCHAR crumb[VM_SSO_EXT_YAHOO_CRUMB];
       } yahoo;
    } value;
}vm_sso_credential_struct;

typedef void (*vm_sso_account_callback)(VMINT req_id, vm_sso_result result, VMUINT32 provider, VMUINT8 account, void * user_data);

typedef void (*vm_sso_result_callback)(VMINT req_id, vm_sso_result result, void * user_data);


/******************************************************************************
 * FUNCTION
 *    vm_sso_get_provider_count
 * DESCRIPTION
 *    get the number of providers
 * RETURNS
 *    return the nubmer of providers if positive number, else failure 
 ******************************************************************************/
VMINT vm_sso_get_provider_count(void);

/******************************************************************************
 * FUNCTION
 *    vm_sso_get_providers
 * DESCRIPTION
 *    get info for all providers
 * PARAMETERS
 *    buffer:       [OUT] memory allocated by caller to hold the provider structure
 *    buffer_items: [IN]  number of items the buffer can hold
 * RETURNS
 *    return the nubmer of available providers if positive number, else failure 
 ******************************************************************************/
VMINT vm_sso_get_providers(vm_sso_provider_struct * buffer, VMUINT8 buffer_items);

/******************************************************************************
 * FUNCTION
 *    vm_sso_get_provider
 * DESCRIPTION
 *    get info for specific providers
 * PARAMETERS
 *    provider: [IN]  the provider id as in vm_sso_provider_struct.provider
 *    buffer: [OUT]  refer to vm_sso_provider_struct
 * RETURNS
 *    success if 0, else failure.
 ******************************************************************************/
VMINT vm_sso_get_provider(VMUINT32 provider, vm_sso_provider_struct * buffer);

/******************************************************************************
 * FUNCTION
 *    vm_sso_get_provider_icon
 * DESCRIPTION
 *    get the name of a provider by its id
 * PARAMETERS
 *    provider: [IN] the provider id as in vm_sso_provider_struct.provider
 *    type:     [IN] the size of icon to get
 *    icon_path [OUT] icon_path
 * RETURNS
 *    success if 0, else failure.
 ******************************************************************************/
VMINT vm_sso_get_provider_icon(VMUINT32 provider, vm_sso_icon_enum type, VMWCHAR ** icon_path);

/******************************************************************************
 * FUNCTION
 *    vm_sso_get_provider_name
 * DESCRIPTION
 *    get the name of a provider by its id
 * PARAMETERS
 *    provider: [IN]  the provider id as in vm_sso_provider_struct.provider
 *    buffer:   [OUT] memory allocated by caller to hold the name of the provider
 *                    must be at least VM_SSO_NAME_SIZE bytes
 * RETURNS
 *    success if 0, else failure.
 ******************************************************************************/
VMINT vm_sso_get_provider_name(VMUINT32 provider, VMWCHAR * buffer);

/******************************************************************************
 * FUNCTION
 *    vm_sso_get_account_count
 * DESCRIPTION
 *    get the number of accounts for a provider according the login state
 * PARAMETERS
 *    provider:    [IN] the provider id as in vm_sso_provider_struct.provider
 *    login_state: [IN] login state to filter accounts
 * RETURNS
 *    return the nubmer of accounts if positive number, else failure 
 ******************************************************************************/
VMINT vm_sso_get_account_count(VMUINT32 provider, vm_sso_login_state login_state);

/******************************************************************************
 * FUNCTION
 *    vm_sso_get_accounts
 * DESCRIPTION
 *    get the info of accounts for a provider according the login state
 * PARAMETERS
 *    provider:     [IN]  the provider id as in vm_sso_provider_struct.provider
 *    login_state:  [IN]  login state to filter accounts
 *    buffer:       [OUT] memory allocated by caller to hold the vm_sso_account_struct
 *    buffer_items: [IN]  number of items the buffer can hold
 * RETURNS
 *    return the nubmer of accounts if positive number, else failure 
 ******************************************************************************/
VMINT vm_sso_get_accounts(VMUINT32 provider, vm_sso_login_state login_state, vm_sso_account_struct * buffer, VMUINT8 buffer_items);

/******************************************************************************
 * FUNCTION
 *    vm_sso_get_account
 * DESCRIPTION
 *    get the info of accounts for a provider according the login state
 * PARAMETERS
 *    provider:     [IN]  the provider id as in vm_sso_provider_struct.provider
 *    account:  [IN]  the account as in vm_sso_account_struct.account
 *    buffer: [OUT]  refer to vm_sso_account_struct
 * RETURNS
 *    return the nubmer of accounts if positive number, else failure 
 ******************************************************************************/
VMINT vm_sso_get_account(VMUINT32 provider, VMUINT8 account, vm_sso_account_struct * buffer);

/******************************************************************************
 * FUNCTION
 *    vm_sso_get_account_name
 * DESCRIPTION
 *    get the username of an account by its provider and account
 * PARAMETERS
 *    provider:    [IN]  the provider id as in vm_sso_account_struct.provider
 *    account:  [IN]  the account as in vm_sso_account_struct.account
 *    buffer:      [OUT] memory allocated by caller to hold the username of the account
 *                       must be at least VM_SSO_NAME_SIZE bytes
 * RETURNS
 *    success if 0, else failure.
 ******************************************************************************/
VMINT vm_sso_get_account_name(VMUINT32 provider, VMUINT8 account, VMWCHAR * buffer);

/******************************************************************************
 * FUNCTION
 *    vm_sso_get_credentials
 * DESCRIPTION
 *    get the credentials of an account by its provider and account
 * PARAMETERS
 *    provider:    [IN]  the provider id as in vm_sso_provider_struct.provider
 *    account:  [IN]  the account as in vm_sso_provider_struct.account
 *    buffer:      [OUT] memory allocated by caller to hold the credentials of the account
 *                       must be at least sizeof(vm_sso_credential_struct) bytes
 * RETURNS
 *    success if 0, else failure.
 ******************************************************************************/
VMINT vm_sso_get_credentials(VMUINT32 provider, VMUINT8 account, vm_sso_credential_struct * buffer);

/******************************************************************************
 * FUNCTION
 *    vm_sso_add_account
 * DESCRIPTION
 *    launch plugin to prompt user for username/password in exchange for credentials
 * PARAMETERS
 *    provider:  [IN] the provider id as in vm_sso_provider_struct.provider
 *    username: [IN] username of account
 *    password: [IN] password of account
 *    callback:  [IN] will be called when the operation is done, no matter success or failure
 *    user_data: [IN] user data to be pass along by the callback function
 * RETURNS
 *    success if >= 0, else failure.
 ******************************************************************************/
VMINT vm_sso_add_account(VMUINT32 provider, const VMWCHAR * username, const VMWCHAR * password, vm_sso_account_callback callback, void * user_data);

/******************************************************************************
 * FUNCTION
 *    vm_sso_login_account
 * DESCRIPTION
 *    log in to an existing account which has been logged out
 * PARAMETERS
 *    provider:   [IN] the provider id as in vm_sso_provider_struct.provider
 *    account: [IN] the account as in vm_sso_provider_struct.account
 *    password: [IN] password of account, user needs to enter again
 *    callback:   [IN] will be called when the operation is done, no matter success or failure
 *    user_data:  [IN] user data to be pass along by the callback function
 * RETURNS
 *    success if >= 0, else failure.
 ******************************************************************************/
VMINT vm_sso_login_account(VMUINT32 provider, VMUINT8 account, const VMWCHAR * password, vm_sso_account_callback callback, void * user_data);

/******************************************************************************
 * FUNCTION
 *    vm_sso_logout_account
 * DESCRIPTION
 *    logout account but still keep it for log-in later
 * PARAMETERS
 *    provider:  [IN] the provider id as in vm_sso_provider_struct.provider
 *    account: [IN] the account as in vm_sso_provider_struct.account
 *    callback:  [IN] will be called when the operation is done, no matter success or failure
 *    user_data: [IN] user data to be pass along by the callback function
 * RETURNS
 *    success if >= 0, else failure.
 ******************************************************************************/
VMINT vm_sso_logout_account(VMUINT32 provider, VMUINT8 account, vm_sso_result_callback callback, void * user_data);

/******************************************************************************
 * FUNCTION
 *    vm_sso_del_account
 * DESCRIPTION
 *    delete account and do the necessary clean-ups
 * PARAMETERS
 *    provider:   [IN] the provider id as in srv_sso_account_struct.provider
 *    account: [IN] the account as in srv_sso_account_struct.account
 *    callback:   [IN] will be called when the operation is done, no matter success or failure
 *    user_data:  [IN] user data to be pass along by the callback function
 * RETURNS
 *    success if >= 0, else failure.
 ******************************************************************************/
VMINT vm_sso_del_account(VMUINT32 provider, VMUINT8 account, vm_sso_result_callback callback, void * user_data);

/******************************************************************************
 * FUNCTION
 *    vm_sso_refresh_credentials
 * DESCRIPTION
 *    ask plugin to refresh access token by using refresh token or extension
 * PARAMETERS
 *    provider:   [IN] the provider id as in srv_sso_account_struct.provider
 *    account: [IN] the account as in srv_sso_account_struct.account
 *    callback:   [IN] will be called when the operation is done, no matter success or failure
 *    user_data:  [IN] user data to be pass along by the callback function
 * RETURNS
 *    success if >= 0, else failure.
 ******************************************************************************/
VMINT vm_sso_refresh_credentials(VMUINT32 provider, VMUINT8 account, vm_sso_result_callback callback, void * user_data);

/******************************************************************************
 * FUNCTION
 *    vm_sso_cancel
 * DESCRIPTION
 *    cancel an running operation
 * PARAMETERS
 *    req_id: [IN] request id
 * RETURNS
 *    success if 0, else failure.
 ******************************************************************************/
VMINT vm_sso_cancel(VMINT req_id);



#ifdef __cplusplus
}
#endif /* __cplusplus */




#endif /* VM_SSO_SDK_H */

