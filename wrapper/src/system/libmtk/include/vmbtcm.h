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

#ifndef VM_BTCM_SDK_H
#define VM_BTCM_SDK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vmsys.h"

#define VM_SRV_BT_CM_BD_FNAME_LEN 56
#define VM_SRV_BT_CM_MAX_HOST_SUPPORTED_PROFILE 10

typedef enum
{
    VM_BT_CM_ERR_LOGICAL = -5,
    VM_BT_CM_ERR_BAD_PARAM,
    VM_BT_CM_ERR_NO_RESOURCE,
    VM_BT_CM_ERR_NOT_SUPPORT,
    VM_BT_CM_ERR_NO_AUTHORIZATION,
    VM_BT_CM_ERR_SUCCESS = 0
}vm_btcm_error_t;

typedef enum
{
    VM_SRV_BT_CM_RESULT_SUCCESS                = 0,  /* success */
    VM_SRV_BT_CM_RESULT_FAILED                 = -1, /* failed */
    VM_SRV_BT_CM_RESULT_INVALID_HANDLE         = -2, /* invalid instance handler */
    VM_SRV_BT_CM_RESULT_DEV_NOT_FOUND          = -3, /* device not found */
    VM_SRV_BT_CM_RESULT_DEV_LIST_FULL          = -4, /* device list full */
    VM_SRV_BT_CM_RESULT_NO_CONNECTION          = -5, /* there is no connection */
    VM_SRV_BT_CM_RESULT_ONE_HEADSET_CONNECTED  = -6, /* there is one headset connected */
    VM_SRV_BT_CM_RESULT_ONE_A2DP_CONNECTED     = -7, /* there is one A2DP connection */
    VM_SRV_BT_CM_RESULT_SAME_HEADSET_CONNECTED = -8, /* the same headset is connected */
    VM_SRV_BT_CM_RESULT_PROFILE_NOT_SUPPORT    = -9, /* the profile is not supported */
    VM_SRV_BT_CM_RESULT_TOTAL      /* last enum for BT CM result code */
} vm_srv_bt_cm_result_codes_enum;


/* event definiation */
typedef enum 
{
    VM_SRV_BT_CM_EVENT_ACTIVATE                    = 0x00000001, /* activate */
    VM_SRV_BT_CM_EVENT_DEACTIVATE                  = 0x00000002, /* deactivate */
    VM_SRV_BT_CM_EVENT_INQUIRY_IND                 = 0x00000004, /* inquiry indication */
    VM_SRV_BT_CM_EVENT_INQUIRY_COMPLETE            = 0x00000008, /* inquiry complete */
    VM_SRV_BT_CM_EVENT_BEGIN_ACTIVATE              = 0x00000010, // begin activate
    VM_SRV_BT_CM_EVENT_BEGIN_DEACTIVATE            = 0x00800000, // begin deactivate
    VM_SRV_BT_CM_EVENT_BOND_RES                    = 0x00000020, /* bond result */
    VM_SRV_BT_CM_EVENT_PAIR_IND                    = 0x00000040, /* pair indication */
    VM_SRV_BT_CM_EVENT_PAIR_RES                    = 0x00000080, /* pair result */
    VM_SRV_BT_CM_EVENT_SECURITY_USER_CONFIRM       = 0x00000100, /* security user confirm */
    VM_SRV_BT_CM_EVENT_SECURITY_PASSKEY_NOTIFY     = 0x00000200, /* security passkey notify */
    VM_SRV_BT_CM_EVENT_SECURITY_KEYPRESS_NOTIFY    = 0x00000400, /* security keypress notify */
    VM_SRV_BT_CM_EVENT_CONNECT_REQ                 = 0x00000800, /* connect request */
    VM_SRV_BT_CM_EVENT_CONNECT_RES                 = 0x00001000, /* connect result */
    VM_SRV_BT_CM_EVENT_DISCONNECT_IND              = 0x00002000, /* disconnect indication */
    VM_SRV_BT_CM_EVENT_RELEASE_ALL_CONN            = 0x00004000, /* release all connection */
    VM_SRV_BT_CM_EVENT_REFRESH_PROFILE             = 0x00008000, /* refresh profile */
    VM_SRV_BT_CM_EVENT_SET_AUTHORIZE               = 0x00010000, /* set authorize */
    VM_SRV_BT_CM_EVENT_UNBLOCK                     = 0x00020000, /* unblock device */
    VM_SRV_BT_CM_EVENT_MYDEV_DEL                   = 0x00040000, /* mydevice delete */
    VM_SRV_BT_CM_EVENT_BLE_ACTIVATE                = 0x00080000, /*BLE active notify*/
    VM_SRV_BT_CM_EVENT_SET_VISIBILITY              = 0x00100000, /* set visibility */
    VM_SRV_BT_CM_EVENT_SET_NAME                    = 0x00200000, /* set name */
    VM_SRV_BT_CM_EVENT_SET_AUTHENTICATION          = 0x00400000, /* set authentication */
    VM_SRV_BT_CM_EVENT_SET_SIMAP                   = 0x01000000, /* set SIMAP */
    VM_SRV_BT_CM_EVENT_SCO_IND                     = 0x02000000, /* sco indication */
    VM_SRV_BT_CM_EVENT_PANIC_IND                   = 0x04000000, /* panic inidation */
    VM_SRV_BT_CM_EVENT_READ_REMOTE_DEV_NAME        = 0x08000000, /* read remote device */
    VM_SRV_BT_CM_EVENT_SET_LIMIT_DISCOVERABLE_MODE = 0x10000000, /* set limit discoverable mode */
    VM_SRV_BT_CM_EVENT_CHIP_DETECT                 = 0x20000000, /* chip auto detect */
    VM_SRV_BT_CM_EVENT_BOND_CANCEL                 = 0x40000000,  /* bond cancel */
    VM_SRV_BT_CM_EVENT_FAIL_CONN_TO				         = 0x80000000,  /* bond cancel */
    VM_SRV_BT_CM_EVENT_TOTAL                                      /* last bt srv event enum */
}vm_srv_bt_cm_event_enum;  

/* the power status of BT */
typedef enum
{
    VM_SRV_BT_CM_POWER_ON,                 /* power on */
    VM_SRV_BT_CM_POWER_OFF,                /* power off */
    VM_SRV_BT_CM_POWER_SWITCHING_ON,       /* power switching on */
    VM_SRV_BT_CM_POWER_SWITCHING_OFF,      /* power switching off */  
    VM_SRV_BT_CM_POWER_TOTAL               /* last enum for BT power status */
}vm_srv_bt_cm_power_status_enum;

/* visibility type enum */
typedef enum
{
    VM_SRV_BT_CM_VISIBILITY_ON = 1, /* visibility on, can be discovered by other bt device */
    VM_SRV_BT_CM_VISIBILITY_TEMPORARY_ON, /* visibility temporary on, can be discovered by other bt device for some time */
    VM_SRV_BT_CM_VISIBILITY_OFF,   /* visibility off, can not be discovered by other bt device */
    VM_SRV_BT_CM_VISIBILITY_TOTAL  /* last enum for visibility type */
}vm_srv_bt_cm_visibility_type;

/* Bluetooth device type */
typedef enum
{
    VM_SRV_BT_CM_DISCOVERED_DEV,   /* discovered device */
    VM_SRV_BT_CM_RECENT_USED_DEV,  /* recent used device */
    VM_SRV_BT_CM_PAIRED_DEV,       /* paired device */
    VM_SRV_BT_CM_ALL_DEV,          /* all device */
    VM_SRV_BT_CM_DEV_TYPE_TOTAL
}vm_srv_bt_cm_dev_type_enum;

/* bt addr */
struct _vm_srv_bt_cm_bt_addr
{
    VMUINT lap;    /* Lower Address Part 00..23 */
    VMUINT8  uap;    /* upper Address Part 24..31 */
    VMUINT16 nap;    /* Non-significant    32..47 */
};

#ifndef vm_bt_cm_bt_addr
#define vm_bt_cm_bt_addr
typedef struct _vm_srv_bt_cm_bt_addr vm_srv_bt_cm_bt_addr;
#endif

/* pair indication struct */
typedef struct
{
    VMINT32 srv_hd;                 /* service handle*/
    void* user_data;            /* user data */
    VMUINT8* dev_name;                 /* device name */
    VMUINT8 enable_16digits_pin_code;  /* whether enable 16 digits pin code */
    vm_srv_bt_cm_bt_addr dev_addr;   /* device address */
} vm_srv_bt_cm_pair_ind_struct;

/* dev info structure */
typedef struct 
{
    VMUINT cod;                                                /* class of device */
    VMUINT8 name[VM_SRV_BT_CM_BD_FNAME_LEN];                        /* device name */
    vm_srv_bt_cm_bt_addr bd_addr;                              /* device addres */
    vm_srv_bt_cm_bt_addr le_bd_addr;                              /*ble bt device address */
    VMUINT8 attribute;                                           /* authorized or blocked */
    VMUINT8 service_list_num;                                    /* supported service number */
    VMINT service_list[VM_SRV_BT_CM_MAX_HOST_SUPPORTED_PROFILE]; /* supported service list */
}vm_srv_bt_cm_dev_struct;



/* event struct for VM_SRV_BT_CM_EVENT_ACTIVATE & VM_SRV_BT_CM_EVENT_BLE_ACTIVATE */
typedef struct
{
    VMINT res_hd;                 /* res handle*/ 
    void * user_data;            /* user data */
    VMINT result;            /* activate result */
}vm_srv_bt_cm_activate_struct;


/* event struct for VM_SRV_BT_CM_EVENT_DEACTIVATE */
typedef struct
{
    VMINT res_hd;                 /* res handle*/ 
    void * user_data;            /* user data */
    VMINT result;            /* deactivate result */
}vm_srv_bt_cm_deactivate_struct;


/* event struct for VM_SRV_BT_CM_EVENT_INQUIRY_IND */
typedef struct
{
    VMINT res_hd;                 /* res handle*/ 
    void* user_data;            /* user data */
    VMUINT discovered_dev_num;     /* discovered device number */
} vm_srv_bt_cm_inquiry_indication_struct;

/* event struct for VM_SRV_BT_CM_EVENT_INQUIRY_COMPLETE */
typedef struct
{
    VMINT res_hd;                 /* res handle*/ 
    void * user_data;            /* user data */
    VMINT result;                 /* inquiry complete result */
    VMINT is_cancelled;      /* non zero : cancelled by user
                                 * zero : not cancelled by user */
}vm_srv_bt_cm_inquiry_complete_struct;

/* event struct for VM_SRV_BT_CM_EVENT_SET_VISIBILITY */
typedef struct
{
    VMINT res_hd;                 /* res handle*/ 
    void * user_data;            /* user data */
    VMINT result;            /* set visibility result */
    VMINT is_from_mmi;       /* to identify whether the action is initiated by MMI
                                 * or change the visibility just by CM service due to A2DP connected */
}vm_srv_bt_cm_set_visibility_struct;

/* event struct for VM_SRV_BT_CM_EVENT_SET_NAME */
typedef struct
{
    VMINT res_hd;                 /* res handle*/ 
    void * user_data;            /* user data */
    VMINT result;                 /* set name result in vm_srv_bt_cm_result_codes_enum */
}vm_srv_bt_cm_set_name_struct;


//Pairing method
typedef enum 
{
	 VM_PIN_AND_SSP = 0,							//Pairing need UI and user should confirm,normal case for product,such as phone/mid,we support both pin and ssp
	 VM_FIXED_PIN_ONLY,							//Pairing no need UI,auto accept pairing ,only adopt FIXED PIN CODE method
	 VM_FIXED_PIN_AND_SSP_JUST_WORK				//Pairing no need UI,auto accept pairing ,adopt FIXED PIN CODE and JUST WORK of SSP
}vm_bt_pairing_Type;


/****************************************************************************** 
 * FUNCTION
 *  vm_btcm_init
 * DESCRIPTION
 *  Bluetooth CM set notifier, after set successfully,
 *  notifier will receive the event notification it it happens.
 * PARAMETERS
 *  callback  :    [IN]    notifier
 *  evt_mask:    [IN]    event mask, refer to vm_srv_bt_cm_event_enum
 *  user_data :    [IN]    user data
 *  
 * RETURNS
 *  VMINT res handle, failure if less than 0, see vm_btcm_error_t
 ******************************************************************************/
VMINT vm_btcm_init(void (*callback)(VMUINT evt, void * param, void * user_data), VMUINT evt_mask, void * user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_btcm_exit
 * DESCRIPTION
 *  exit btcm,
 * PARAMETERS
 *  res_hd : [IN] res handle
 * RETURNS
 *  failure if less than 0, else successful, see vm_btcm_error_t
 *****************************************************************************/
VMINT vm_btcm_exit(VMINT res_hd);

/*****************************************************************************
 * FUNCTION
 *  vm_btcm_get_power_status
 * DESCRIPTION
 *  This function is to get current bt power status
 * PARAMETERS
 *  void
 * RETURNS
 * failure if less than 0, else
 *  vm_srv_bt_cm_power_status_enum   
 *    VM_SRV_BT_CM_POWER_ON means BT power is ON
 *    VM_SRV_BT_CM_POWER_OFF means BT power is OFF
 *    VM_SRV_BT_CM_POWER_SWITCHING_ON means switching power to be ON now
 *    VM_SRV_BT_CM_POWER_SWITCHING_OFF means switching power to be OFF now 
 *****************************************************************************/
VMINT vm_btcm_get_power_status(void);
    

/*****************************************************************************
 * FUNCTION
 *  vm_btcm_switch_on
 * DESCRIPTION
 *  This function is to switch on bt chip,
 *  and it will also help to activate bt profiles registered to CM service
 * PARAMETERS
 *  void
 * RETURNS
 *  VMINT : refer to vm_srv_bt_cm_result_codes_enum
 *****************************************************************************/
VMINT vm_btcm_switch_on(void);

/*****************************************************************************
 * FUNCTION
 *  vm_btcm_switch_off
 * DESCRIPTION
 *  This function is to switch off bt, it will also help to deactivate all the activated bt profiles,
 *  if there is live connection(s), it will disconnect the live connection(s) firstly
 * PARAMETERS
 * RETURNS
 *  VMINT : refer to vm_srv_bt_cm_result_codes_enum
 *****************************************************************************/
VMINT vm_btcm_switch_off(void);

/****************************************************************************** 
 * FUNCTION
 *  vm_btcm_srv_set_visibility
 * DESCRIPTION
 *  this function is to set bluetooth visibility
 * PARAMETERS
 *  type:    [IN]    visibility type
 * RETURNS
 *  VMINT : refer to vm_srv_bt_cm_result_codes_enum
 ******************************************************************************/
VMINT vm_btcm_srv_set_visibility(vm_srv_bt_cm_visibility_type type);

/****************************************************************************** 
 * FUNCTION
 *  vm_btcm_srv_get_visibility
 * DESCRIPTION
 *  this function is to get bluetooth visibility
 * PARAMETERS
 *  void
 * RETURNS
 *  VMINT : refer to vm_srv_bt_cm_result_codes_enum
 ******************************************************************************/
VMINT vm_btcm_srv_get_visibility(void);

/*****************************************************************************
 * FUNCTION
 *  vm_btcm_search
 * DESCRIPTION 
 *  This function is to process inquiry request,
 *  each time finding a device, it will notify notifier with event VM_SRV_BT_CM_EVENT_INQUIRY_IND ,
 *  after search procedure completed, it will notify notifier VM_SRV_BT_CM_EVENT_INQUIRY_COMPLETE.
 * PARAMETERS
 *  max_response  :    [IN]    max repsone number of device
 *  time_out       :    [IN]    inquiry timeout timer
 *  cod           :    [IN]    class of device
 *  is_name_discovery:    [IN]    whether do name discovery 
 * RETURNS
 *  VMINT : failure if less than 0, see vm_srv_bt_cm_result_codes_enum, else successful
 *****************************************************************************/
VMINT vm_btcm_search(VMUINT8 max_response, VMUINT16 time_out, VMUINT cod, VMBYTE is_name_discovery);

/*****************************************************************************
 * FUNCTION
 *  vm_btcm_search_abort
 * DESCRIPTION
 *  This function is to process inquiry cancel request
 *  and invoke srv_bt_cm_cancel_discovery_req_hdler,
 *  notifier will receive VM_SRV_BT_CM_EVENT_INQUIRY_COMPLETE after cancel inquiry procedure is completed
 * PARAMETERS
 *  void
 * RETURNS
 *  VMINT : refer to vm_srv_bt_cm_result_codes_enum
 *****************************************************************************/
VMINT vm_btcm_search_abort(void);

/*****************************************************************************
 * FUNCTION
 *  vm_btcm_set_host_name
 * DESCRIPTION
 *  This function is to set host device name, it will notify notifier VM_SRV_BT_CM_EVENT_SET_NAME
 *  after set host device name procedure is completed.
 * PARAMETERS
 *  name :    [IN]    host device name, UTF-8 coding
 * RETURNS
 *  VMINT  : refer to vm_srv_bt_cm_result_codes_enum
 *****************************************************************************/
VMINT vm_btcm_set_host_name(VMUINT8 * name);

/*****************************************************************************
 * FUNCTION
 *  vm_btcm_get_host_name
 * DESCRIPTION
 *  This function is to get host device information
 * PARAMETERS
 *  info : [IN] host device info structure in vm_srv_bt_cm_dev_struct
 * RETURNS
 *  VMINT : failure if less than 0, see vm_btcm_error_t, else successful
 *****************************************************************************/
VMINT vm_btcm_get_host_dev_info(vm_srv_bt_cm_dev_struct * info);

/****************************************************************************** 
 * FUNCTION
 *  vm_btcm_get_dev_num
 * DESCRIPTION
 *  this function is to get device number according to device type
 * PARAMETERS
 *  dev_type:    [IN]    refer to vm_srv_bt_cm_dev_type_enum 
 *  
 * RETURNS
 *  VMINT : device number of designated device type
 ******************************************************************************/
VMINT vm_btcm_get_dev_num(vm_srv_bt_cm_dev_type_enum dev_type);

/****************************************************************************** 
 * FUNCTION
 *  vm_btspp_get_dev_info_by_index
 * DESCRIPTION
 *  this function is to get device info 
 * PARAMETERS
 *  index   :    [IN]    device index
 *  dev_type:    [IN]    device type
 *  info:    [OUT]    device type
 *  
 * RETURNS
 *  if succeed to find the device, return VM_BT_CM_ERR_SUCCESS
 *  return value less than 0, if failed to find the device
 ******************************************************************************/
VMINT vm_btcm_get_dev_info_by_index(VMUINT idx, vm_srv_bt_cm_dev_type_enum dev_type, vm_srv_bt_cm_dev_struct * info);

/*****************************************************************************
 * FUNCTION
 *  vm_bt_cm_release_all_conn
 * DESCRIPTION
 *  This function is to process release the designated device's all live connection,
 *  after the procedure is completed, it will notify the notifier VM_SRV_BT_CM_EVENT_RELEASE_ALL_CONN.
 * PARAMETERS
 *  void
 * RETURNS
 *  VMINT : refer to vm_srv_bt_cm_result_codes_enum
 *****************************************************************************/
VMINT vm_bt_cm_release_all_conn(void);

/*****************************************************************************
 * FUNCTION
 *  vm_bt_cm_send_passkey
 * DESCRIPTION
 *  This function is to process pair request and send passkey
 * PARAMETERS
 *  dev_addr   :    [IN]    device address
 *  dev_passkey:    [IN]    passkey
 *  result     :    [IN]    VM_TURE: valid passkey, VM_FALSE:reject this pair
 * RETURNS
 * VMINT : refer to vm_srv_bt_cm_result_codes_enum
 *****************************************************************************/
VMINT vm_bt_cm_send_passkey(vm_srv_bt_cm_bt_addr* dev_addr, VMUINT8* dev_passkey, VMBOOL result);


/*****************************************************************************
 * FUNCTION
 *  vm_custom_set_bt_pairing_method
 * DESCRIPTION
 *  This function is to set bt pair type
 * PARAMETERS
 *  config_type   :    [IN]    pair type
 * RETURNS
 * None
 *****************************************************************************/
void vm_custom_set_bt_pairing_method(vm_bt_pairing_Type config_type);

/* BT CM connection type enum */
typedef enum
{
    VM_BT_CM_NO_CONNECTION,          
    VM_BT_CM_HFP_CONNECTION,         
    VM_BT_CM_HSP_CONNECTION,          
    VM_BT_CM_SPP_CONNECTION,         
    VM_BT_CM_DUN_CONNECTION,         
    VM_BT_CM_FTP_CONNECTION,         
    VM_BT_CM_OPP_CONNECTION,         
    VM_BT_CM_A2DP_CONNECTION,        
    VM_BT_CM_A2DP_SINK_CONNECTION,
    VM_BT_CM_AVRCP_CONNECTION,       
    VM_BT_CM_AVRCP_CT_CONNECTION,    
    VM_BT_CM_BPP_CONNECTION,         
    VM_BT_CM_SIMAP_CONNECTION,       
    VM_BT_CM_FAX_CONNECTION,         
    VM_BT_CM_HID_CONNECTION,         
    VM_BT_CM_BIP_CONNECTION,         
    VM_BT_CM_BIPC_CONNECTION,        
    VM_BT_CM_PBAP_CONNECTION,        
    VM_BT_CM_PBAPC_CONNECTION,       
    VM_BT_CM_FTPC_CONNECTION,        
    VM_BT_CM_OPPC_CONNECTION,        
    VM_BT_CM_SYNCML_CONNECTION,      
    VM_BT_CM_MAPC_CONNECTION,        
    VM_BT_CM_HF_CONNECTION,
    VM_BT_CM_CONNECTION_TOTAL        
} vm_bt_cm_connection_type;

/*****************************************************************************
 * FUNCTION
 *  vm_btcm_is_profile_connected
 * DESCRIPTION
 *  This function is to check if a profile is connected
 * PARAMETERS
 *  conn_type:    [IN]    to check if conn_type is connected, conn_type is defind in srv_bt_cm_connection_type 
 * RETURNS
 *  no-zero  : the profile is connected
 *  else : the profile is not connected
 *****************************************************************************/
VMINT vm_btcm_is_profile_connected(vm_bt_cm_connection_type conn_type);

/*****************************************************************************
 * FUNCTION
 *  vm_btcm_is_dev_busy
 * DESCRIPTION
 *  This function is to check if a dev is connecting
 * PARAMETERS
 *  dev_addr		[IN]		remote device
 * RETURNS
 *  MMI_BOOL            TRUE : there is some profile connecting
 *                      FALSE : the device is not connected or connected already.
 *****************************************************************************/
VMBOOL vm_btcm_is_dev_busy(const vm_srv_bt_cm_bt_addr* dev_addr);



/****************************************************************************** 
 * FUNCTION
 *  vm_btcm_get_dev_info
 * DESCRIPTION
 *  this function will return the device information from paird device list and searched device list according to address,
 *  if can't find the device, it will return NULL
 * PARAMETERS
 *  dev_addr:    [IN]    BT device address
 *  
 * RETURNS
 *  srv_bt_cm_dev_struct* : device information structure pointer
 ******************************************************************************/
const vm_srv_bt_cm_dev_struct* vm_btcm_get_dev_info(const vm_srv_bt_cm_bt_addr* dev_addr);


/* BLE CM current state enum */
typedef enum
{
    VM_BLE_CM_STATE_IDLE,                              /* 0*/
    VM_BLE_CM_STATE_INQUIRING,                         /* 1 */
    VM_BLE_CM_STATE_INQUIR_RES_IND,                    /* 2 */
    VM_BLE_CM_STATE_INQUIR_CANCELLING,                 /* 3 */  
    VM_BLE_CM_STATE_CONNECTING,                        /* 4 */
    VM_BLE_CM_STATE_DISCONNECTING,                     /* 5 */  
    VM_BLE_CM_STATE_VISIBILITY_SETTING,                /* 6 */
    VM_BLE_CM_STATE_TOTAL                              /* . */
} vm_ble_cm_state_enum;
/* BlE device type */
typedef enum
{
    VM_BLE_CM_DISCOVERED_DEV,   /* discovered device */
    VM_BLE_CM_CONNECTED_DEV,  /* connected device */
    VM_BLE_CM_ALL_DEV,          /* all device */
    VM_BLE_CM_DEV_TYPE_TOTAL
} vm_ble_cm_dev_type_enum;


/* event definiation */
typedef enum 
{
    VM_BLE_CM_EVENT_CONNECT_REQ                     = 0x00000001,
    VM_BLE_CM_EVENT_CONNECT_CNF                     = 0x00000002,
    VM_BLE_CM_EVENT_DISCONNECT_REQ                  = 0x00000004,
    VM_BLE_CM_EVENT_DISCONNECT_CNF                  = 0x00000008,
    VM_BLE_CM_EVENT_INQUIRY_IND                     = 0x00000020,
    VM_BLE_CM_EVENT_INQUIRY_COMPLETE                = 0x00000040,
    VM_BLE_CM_EVENT_UPDATE_NAME                     = 0x00000100,
    VM_BLE_CM_EVENT_TOTAL                                      /* last bt srv event enum */
}vm_ble_cm_event_enum;

/* structure for VM_BLE_CM_EVENT_CONNECT_REQ */ 
typedef struct
{
    VMINT res_hd;                 /* res handle*/ 
    void* user_data;            /* user data */
    vm_srv_bt_cm_bt_addr* dev_addr;
	void* reserved;
} vm_ble_cm_evt_connect_req_struct;

/* structure for VM_BLE_CM_EVENT_DISCONNECT_REQ */ 
typedef struct
{
    VMINT res_hd;                 /* res handle*/ 
    void* user_data;            /* user data */
    vm_srv_bt_cm_bt_addr* dev_addr;
	void* reserved;
} vm_ble_cm_evt_disconnect_req_struct;

/* structure for VM_BLE_CM_EVENT_CONNECT_CNF & VM_BLE_CM_EVENT_DISCONNECT_CNF*/ 
typedef struct
{
    VMINT res_hd;                 /* res handle*/ 
    void* user_data;            /* user data */
    vm_srv_bt_cm_bt_addr* dev_addr;
	VMUINT8 name[VM_SRV_BT_CM_BD_FNAME_LEN];                        /* device name */
	VMINT8 is_ind;// is indication
	VMINT8 result;// success
	VMINT8 is_conn;// connect or disconnect
	void* reserved;
} vm_ble_cm_evt_gatt_cnf_struct;

typedef void (*ble_cm_calback)(VMUINT evt, void * param, void * user_data);


/* dev info structure */
typedef struct 
{
    VMUINT cod;                                                /* class of device */
    VMUINT8 name[VM_SRV_BT_CM_BD_FNAME_LEN];                        /* device name */
    vm_srv_bt_cm_bt_addr bd_addr;                              /* device addres */
    vm_srv_bt_cm_bt_addr le_bd_addr;                              /* ble device addres */
    VMUINT8 attribute;                                           /* authorized or blocked */
    VMUINT8 service_list_num;                                    /* supported service number */
    VMINT service_list[VM_SRV_BT_CM_MAX_HOST_SUPPORTED_PROFILE]; /* supported service list */
}vm_srv_bt_cm_dev_struct_le;


/* */
/****************************************************************************** 
 * FUNCTION
 *  vm_ble_cm_init
 * DESCRIPTION
 *  Bluetooth CM set notifier, after set successfully,
 *  notifier will receive the event notification it it happens.
 * PARAMETERS
 *  callback  :    [IN]    notifier
 *  evt_mask:    [IN]    event mask, refer to vm_ble_cm_event_enum
 *  user_data :    [IN]    user data
 * RETURNS
 *  VMINT res handle, failure if less than 0
 ******************************************************************************/
VMINT vm_ble_cm_init(ble_cm_calback callback, VMUINT evt_mask, void * user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_ble_cm_exit
 * DESCRIPTION
 *  exit btcm,
 * PARAMETERS
 *  res_hd : [IN] res handle
 * RETURNS
 *  failure if less than 0, else successful
 *****************************************************************************/
VMINT vm_ble_cm_exit(VMINT res_hd);

/*****************************************************************************
 * FUNCTION
 *  vm_ble_cm_search
 * DESCRIPTION 
 *  This function is to process inquiry request. 
 * PARAMETERS
 *  max_response        [IN]            max repsone number of device
 *  timeout             [IN]                inquiry timeout timer
 *  cod                 [IN]                  class of device
 *  name_discovery      [IN]            name discovery 
 *  user_data   [IN]            user data 
 * RETURNS
 *  VMINT : 0 succeed, else failed.
 *****************************************************************************/
VMINT vm_ble_cm_search(VMUINT8 max_response, VMUINT16 timeout, VMUINT32 cod, VMBOOL name_discovery);

/****************************************************************************** 
 * FUNCTION
 *  vm_ble_cm_get_connected_dev_info
 * DESCRIPTION
 *  this function is to get the device infor in connected device by index
 * PARAMETERS
 *  U16: [IN] index
 *  dev: [OUT] device info 
 * RETURNS
 *  VMINT : 0 succeed, else failed.
 ******************************************************************************/  
VMINT vm_ble_cm_get_connected_dev_info(VMUINT16 index, vm_srv_bt_cm_dev_struct_le* dev);

/****************************************************************************** 
 * FUNCTION
 *  vm_ble_cm_get_connected_dev_num
 * DESCRIPTION
 *  this function is to get the number about connected device.
 * PARAMETERS
 *  void
 * RETURNS
 *  VMINT : failure if less than 0, else succeed
 ******************************************************************************/  
VMINT vm_ble_cm_get_connected_dev_num(void);
/****************************************************************************** 
 * FUNCTION
 *  vm_ble_cm_get_searched_dev_info
 * DESCRIPTION
 *  this function is to get device info in scan list by index.
 * PARAMETERS
 *  U16: [IN] index
 *  dev: [OUT] device info 
 * RETURNS
 *  VMINT : 0 succeed, else failed.
 ******************************************************************************/  
VMINT vm_ble_cm_get_searched_dev_info(VMUINT16 index, vm_srv_bt_cm_dev_struct_le* dev);

/****************************************************************************** 
 * FUNCTION
 *  vm_ble_cm_get_searched_dev_num
 * DESCRIPTION
 *  this function is to get total number about scan_list.
 * PARAMETERS
 *  void
 * RETURNS
 *  VMINT : failure if less than 0, else succeed
 ******************************************************************************/   
VMINT vm_ble_cm_get_searched_dev_num(void);

/****************************************************************************** 
 * FUNCTION
 *  vm_ble_cm_get_maxed_linked_num
 * DESCRIPTION
 *  this function is to get maxed linked num.
 * PARAMETERS
 *  void
 * RETURNS
 *  VMINT : failure if less than 0, else succeed
 ******************************************************************************/
VMINT vm_ble_cm_get_maxed_linked_num(void);

/****************************************************************************** 
 * FUNCTION
 *  vm_ble_cm_disconnect_req
 * DESCRIPTION
 *  this function is send event to app ,disconnect gatt.
 * PARAMETERS
 *  dev_addr:  [IN] address
 * RETURNS
 *  VMINT : 0 succeed, else failed.
 ******************************************************************************/
VMINT vm_ble_cm_disconnect_req(vm_srv_bt_cm_bt_addr* dev_addr);

/****************************************************************************** 
 * FUNCTION
 *  vm_ble_cm_connect_req
 * DESCRIPTION
 *  this function is send event to app ,connect gatt.
 * PARAMETERS
 *  dev_addr:  [IN] address
 * RETURNS
 *  VMINT : 0 succeed, else failed.
 ******************************************************************************/
VMINT vm_ble_cm_connect_req(vm_srv_bt_cm_bt_addr* dev_addr);


/*****************************************************************************
 * FUNCTION
 *  vm_ble_cm_search_abort
 * DESCRIPTION
 *  This function is to process inquiry cancel request
 * PARAMETERS
 *  void
 * RETURNS
 *  VMINT : failure if less than 0, else succeed
 *****************************************************************************/
VMINT vm_ble_cm_search_abort(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VM_BTCM_SDK_H */

