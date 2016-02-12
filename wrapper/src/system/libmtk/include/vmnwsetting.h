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

#ifndef VM_NWSETTING_SDK_H
#define VM_NWSETTING_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"



/* Maximum length of WLAN SSID attribute in WLAN profile */
#define VM_WLAN_PROF_MAX_SSID_LEN             (32)

/* Maximum length of WLAN SSID attribute in WLAN profile */
#define VM_WLAN_PROF_MAX_SSID_LEN             (32)
/* Maximum length of profile IP address length in WLAN profile */
#define VM_WLAN_PROF_MAX_IP_ADDR_LEN      (4)

#define VM_WLAN_PROF_MAX_PROXY_ADDR_LEN   (63)
/* Maximum length of proxy auth ID attribute in WLAN profile */
#define VM_WLAN_PROF_MAX_PX_AUTH_ID_LEN   (40)
/* Maximum length of proxy auth password attribute in WLAN profile */
#define VM_WLAN_PROF_MAX_PX_AUTH_PW_LEN   (40)
/* Maximum length of homepage attribute in WLAN profile */
#define VM_WLAN_PROF_MAX_HOMEPAGE_LEN     (256)
/* Maximum length of WLAN profile name attribute in WLAN profile */
#define VM_WLAN_PROF_MAX_WLAN_PROF_NAME_LEN   (VM_WLAN_PROF_MAX_SSID_LEN)
//#ifdef __WAPI_SUPPORT__
#define VM_WLAN_WAPI_PSK_STR_LEN  (32+1)			/* WAPI PSK string length */
//#endif /* __WAPI_SUPPORT__ */
/* Maximum length of password attribute in WLAN profile */
#define VM_WLAN_PROF_MAX_PW_LEN           (31)
/* Maximum length of username attribute in WLAN profile */
#define VM_WLAN_PROF_MAX_USER_LEN         (31)
/* Maximum length of WLAN profile passphrase attribute in WLAN profile */
#define VM_WLAN_PROF_MAX_PASSPHRASE_LEN       (64)
/* Maximum length of WLAN profile psk attribute in WLAN profile */
#define VM_WLAN_PROF_MAX_PSK_LEN              (34)
/* Maximum length of WLAN profile wep key attribute in WLAN profile */
#define VM_WLAN_PROF_MAX_WEP_KEY_LEN          (26)
/* MAX WLAN profile number */
#define VM_MAX_WLAN_ACCOUNT_NUM  (30)

/* --- MAC Address Length -------------------------------------------------- */
/* WNDRV_MAC_ADDRESS_LEN */
#define VM_WLAN_WNDRV_MAC_ADDRESS_LEN       (6)
/* --- SSID Length --------------------------------------------------------- */
/* WNDRV_SSID_MAX_LEN */
#define VM_WLAN_WNDRV_SSID_MAX_LEN          (32)

#define VM_WLAN_MAX_AP_LIST_NUM  (30)

/* Maximum length of password attribute of all kinds in WLAN profile */
#define VM_WLAN_PROF_PSWD_MAX_LEN          (64)

/* Profile fields */

/* Set SSID field in wlan account profile */
#define VM_WLAN_PROF_FIELD_SSID                  (0x00000002)

/* Set auth type field in wlan account profile */
#define VM_WLAN_PROF_FIELD_AUTH_TYPE             (0x00000400)

/* Set username field in wlan account profile */
#define VM_WLAN_PROF_FIELD_USER                  (0x00080000)

/* Set password field in wlan account profile */
#define VM_WLAN_PROF_FIELD_PW                    (0x00100000)

/* Set All fields */
#define VM_WLAN_PROF_FIELD_ALL                   (0xFFFFFFFF)

#define VM_WLAN_MAX_SPEC_SSID_LIST_NUM    (7)

/* wlan network type enum */
typedef enum
{
    VM_WLAN_NETWORK_TYPE_INFRA,  /* infrasturcture mode */
    VM_WLAN_NETWORK_TYPE_ADHOC,  /* ad-hoc mode */
    VM_WLAN_NETWORK_TYPE_TOTAL
} vm_wlan_network_type_enum;


/* wlan auth.mode enum */
typedef enum
{
    VM_WLAN_AUTH_MODE_OPEN,                     /* Open Network */
    VM_WLAN_AUTH_MODE_WEP,                      /* WEP */
    VM_WLAN_AUTH_MODE_IEEE8021X,                /* IEEE802.1x */
    VM_WLAN_AUTH_MODE_WPA_ONLY,                 /* WPA Enterprise */
    VM_WLAN_AUTH_MODE_WPA_ONLY_PSK,             /* WPA Only PSK */
    VM_WLAN_AUTH_MODE_WAPICERT,                 /* WAPICERT */
    VM_WLAN_AUTH_MODE_WAPIPSK,                  /* WAPIPSK */
    
    VM_WLAN_AUTH_MODE_WPA2_ONLY,                /* WPA2 Enterprise */
    VM_WLAN_AUTH_MODE_WPA_WPA2_MIX,             /* WPA WPA2 Mix Enterprise */
    VM_WLAN_AUTH_MODE_WPA2_ONLY_PSK,           /* WPA2 Only PSK */
    VM_WLAN_AUTH_MODE_WPA_WPA2_MIX_PSK,         /* WPA WPA2 Mix PSK */
    VM_WLAN_AUTH_MODE_TOTAL
} vm_wlan_auth_mode_enum;

/* wlan encrypt mode */
typedef enum
{
    VM_WLAN_ENCRYPT_MODE_NONE,   /* unencrypt mode */
    VM_WLAN_ENCRYPT_MODE_WEP,    /* WEP mode */
    VM_WLAN_ENCRYPT_MODE_TKIP,   /* TKIP mode */
    VM_WLAN_ENCRYPT_MODE_AES,    /* AES mode */
    VM_WLAN_ENCRYPT_MODE_WPI,    /* WPI mode */
    VM_WLAN_ENCRYPT_MODE_TKIP_AES, /*TKIP_CCMP */
    VM_WLAN_ENCRYPT_MODE_TOTAL
} vm_wlan_encrypt_mode_enum;

typedef enum
{
    VM_WLAN_WEP_KEY_FORMAT_HEX,  /* HEX encoded */
    VM_WLAN_WEP_KEY_FORMAT_ASCII,/* ASCII encoded */
    VM_WLAN_WEP_KEY_FORMAT_TOTAL
} vm_wlan_wep_key_format_enum;

typedef enum
{
    VM_WLAN_AP_USER_DEFINE,
    VM_WLAN_AP_DEFAULT,
    VM_WLAN_AP_UNKNOW,
    VM_WLAN_AP_BLACK_LIST,
    VM_WLAN_AP_END
}vm_wlan_ap_type_enum;

/* Connect error type */
typedef enum
{
    VM_WLAN_TIMEOUT,
    VM_WLAN_LOST_COVERAGE,
    VM_WLAN_NORMAL_REJ,
    VM_WLAN_CONNECT_FAIL,
    VM_WLAN_AUTH_FAIL,
    VM_WLAN_CAUSE_COUNT,
    VM_WLAN_UNSUPPORTED_EAP_TYPE, //add for WiFi UE enhancement
    VM_WLAN_WRONG_USER_INFO,      //add for WiFi UE enhancement
    VM_WLAN_LOW_RSSI, // when RSSI < -85dBm . indicate this cause
    VM_WLAN_INVALID_CAUSE
} vm_wlan_cause_enum; /* same as supc_abm_cause_enum */

/* Connection type */
typedef enum
{
    VM_WLAN_ALL_PROFILE_ENABLE,
    VM_WLAN_ONE_PROFILE_SELECT,
    VM_WLAN_START_WPS_PIN,
    VM_WLAN_START_WPS_PBC
} vm_wlan_connection_type_enum; /* supc_connection_type_enum */

/* WLAN request result enum */
typedef enum
{
    VM_WLAN_REQ_RES_DONE = 0,    /* request completed successfully */
    VM_WLAN_REQ_RES_TERMINATED,  /* request is terminated by newer request */
    VM_WLAN_REQ_RES_DUPLICATED,  /* request is removed by newer same request */
    VM_WLAN_REQ_RES_FAILED,      /* request is ignored due to state error */
    VM_WLAN_REQ_RES_ADD_BY_SRV,
    VM_WLAN_REQ_RES_UNKNOWN_ERROR,
    VM_WLAN_REQ_RES_CANCELLED,
    VM_WLAN_REQ_RES_BUSY,

    VM_WLAN_REQ_RES_TOTAL
} vm_wlan_req_res_enum;

/* WLAN scan result enum */
typedef enum
{
    VM_WLAN_SCAN_RESULT_SUCCESS = 0,   /* WLAN scan success */
    VM_WLAN_SCAN_RESULT_FAILED,        /* WLAN scan failed */
    VM_WLAN_SCAN_RESULT_ABORTED,       /* WLAN scan service is aborted */
    VM_WLAN_SCAN_RESULT_DELETE,        /* WLAN scan delete in CONNECT_WAIT */
    VM_WLAN_SCAN_RESULT_TOTAL
} vm_wlan_scan_result_enum;

/* WLAN services result enum */
typedef enum
{
    VM_WLAN_RESULT_SUCCESS    = 0,    /* success */
    VM_WLAN_RESULT_FAILED,            /* general failed case */
    VM_WLAN_RESULT_PROCESSING,        /* processing state implies Event notify */
    VM_WLAN_RESULT_STATE_ERROR,       /* service status error */
    VM_WLAN_RESULT_INVALID_INPUT,     /* the input parameter is invalid */
    VM_WLAN_RESULT_ABORTED,           /* the process is aborted */
    VM_WLAN_RESULT_TERMINATED,        /* the process is terminated */
    VM_WLAN_RESULT_ONE_STORE_EXISTS,  /* currently only support one store */
    VM_WLAN_RESULT_STORE_NOT_COMMIT,  /* store doesn't be config commited before */
    VM_WLAN_RESULT_INVALID_STORE,     /* store invalid */
    VM_WLAN_RESULT_STORE_FULL,        /* reach maximum profile storage */
    VM_WLAN_RESULT_READ_ONLY,         /* can't delete or update read_only profile */
    VM_WLAN_RESULT_FIRST_BOOTUP,      /* first bootup rerurn code for store open */
    VM_WLAN_RESULT_RESET_FACTORY,     /* the data base sim profiles folder is deleted */
    VM_WLAN_RESULT_FS_ERROR,          /* the database file system error */
    VM_WLAN_RESULT_IGNORE,
    VM_WLAN_RESULT_TOTAL
} vm_wlan_result_enum;

/* WLAN set mode enum */
typedef enum
{
    VM_WLAN_SET_MODE_NONE,
    VM_WLAN_SET_MODE_OFF,              /* OFF */
    VM_WLAN_SET_MODE_AP,               /* AP only*/
    VM_WLAN_SET_MODE_STA,              /* STA only */
    VM_WLAN_SET_MODE_AP_STA,           /* AP+STA */

    VM_WLAN_SET_MODE_TOTAL
}vm_wlan_set_mode_enum;



/* WLAN mode status enum */
typedef enum
{
    VM_WLAN_MODE_STATUS_OFF,              /* OFF */
    VM_WLAN_MODE_STATUS_OFF_SWITCHING,
    VM_WLAN_MODE_STATUS_AP,               /* AP only*/
    VM_WLAN_MODE_STATUS_AP_SWITCHING,
    VM_WLAN_MODE_STATUS_STA,              /* STA only */
    VM_WLAN_MODE_STATUS_STA_SWITCHING,
    VM_WLAN_MODE_STATUS_AP_STA,           /* AP+STA */
    VM_WLAN_MODE_STATUS_AP_STA_SWITCHING,
    VM_WLAN_MODE_STATUS_ERROR,

    VM_WLAN_MODE_STATUS_TOTAL
}vm_wlan_mode_status_enum;


/* WLAN mode status enum */
typedef enum
{
    VM_WLAN_STA_STATUS_INACTIVE      = 0x01, /* inactive state */
    VM_WLAN_STA_STATUS_ACTIVE        = 0x02, /* active state */
    VM_WLAN_STA_STATUS_CONNECTED     = 0x04, /* connected state */
    VM_WLAN_STA_STATUS_INVALID_MAC   = 0x08, /* current MAC address isn't valid, OR'd with ACTIVE and CONNECTED status */
    VM_WLAN_STA_STATUS_SNIFFER       = 0x10, /* sniffer status */
    VM_WLAN_STA_STATUS_BUSY          = 0x20, /* status changing */

    VM_WLAN_STA_STATUS_TOTAL         = 0xFF
} vm_wlan_sta_status_enum;



/* Sniffer ON Callback type */
typedef enum
{
    VM_WLAN_SNIFFER_ON_RES,
    VM_WLAN_SNIFFER_ON_AP_INFO,

    VM_WLAN_SNIFFER_ON_END
}vm_wlan_sniffer_on_cb_type_enum;


/* Sniffer ON/OFF callback result Enum */
typedef enum
{  
   VM_WLAN_SNIFFER_SUCCESS = 0,
   VM_WLAN_SNIFFER_FAIL_INVALID_CHANNEL,
   VM_WLAN_SNIFFER_FAIL_INVALID_SNIFFERFILTEROPTIONS,
   VM_WLAN_SNIFFER_FAIL_INVALID_ONOFFSWITCH,
   VM_WLAN_SNIFFER_FAIL_NETWORK_IS_CONNECTED,   
   VM_WLAN_SNIFFER_FAIL_UNKNOWN,
   VM_WLAN_SNIFFER_FAIL_STATE_ERROR,
   VM_WLAN_SNIFFER_FAIL_HW_ERROR
}vm_wlan_sniffer_res_enum;


/* Notification type */
typedef enum
{
    VM_WLAN_NOTI_NONE,
    VM_WLAN_NOTI_IP_AVAILABLE,		//IP available
    VM_WLAN_NOTI_PASSIVE_DISCONN,	//Passive disconnect

    VM_WLAN_NOTI_END = 0xFFFF
}vm_wlan_noti_type_enum;


/* Connected ap info type */ 
typedef enum
{
    VM_WLAN_AP_INFO_BSSID,		//Get BSSID
    VM_WLAN_AP_INFO_PROF_ID,	//Get Profile ID
    VM_WLAN_AP_INFO_RSSI,		//Get RSSI
    VM_WLAN_AP_INFO_ALL,		//Get All infomation

    VM_WLAN_AP_INFO_END = 0xFFFF
}vm_wlan_ap_info_type_enum;


/* scan param type */
typedef enum
{
    VM_WLAN_SCAN_PARAM_DWELL_TIME,			/* Get/Set dwell time */
    VM_WLAN_SCAN_PARAM_SPEC_SSID_LIST,		/* Get/Set ssid list */
    
    VM_WLAN_SCAN_PARAM_END = 0xFFFF
}vm_wlan_scan_param_type_enum;

/* Custom config apmode para enum */
typedef enum
{
    VM_WLAN_CFG_AP_PARA_AUTH_MODE = 0x00000001, /* AP mode */
    VM_WLAN_CFG_AP_PARA_SSID = 0x00000002, /* AP mode */
    VM_WLAN_CFG_AP_PARA_PWD = 0x00000004, /* AP mode */
    
    VM_WLAN_CFG_AP_PARA_ALL = VM_WLAN_CFG_AP_PARA_AUTH_MODE |
                               VM_WLAN_CFG_AP_PARA_SSID |  
                               VM_WLAN_CFG_AP_PARA_PWD, /*All parameter */

    VM_WLAN_CFG_AP_PARA_END
} vm_wlan_cfg_ap_para_enum;  

typedef struct
{
    VMUINT8 ssid[VM_WLAN_PROF_MAX_SSID_LEN+1];       /* SSID ASCII string (MAX: VM_WLAN_PROF_MAX_SSID_LEN) */         
    vm_wlan_auth_mode_enum auth_mode;				/* profile auth.mode */        
    VMUINT8 username[VM_WLAN_PROF_MAX_USER_LEN+1];   /* user name string (ASCII, MAX: VM_WLAN_PROF_MAX_USER_LEN) */
    VMUINT8 password[VM_WLAN_PROF_PSWD_MAX_LEN+1]; /* password string (ASCII, MAX: VM_WLAN_PROF_PSWD_MAX_LEN) */
    VMUINT32 profile_id;							/* Profile ID */
} vm_wlan_prof_struct;



/* Sniffer ON structure , used in callback function*/
typedef struct
{   
    vm_wlan_sniffer_on_cb_type_enum    cb_type;	// callback type, reference vm_wlan_sniffer_on_cb_type_enum
    vm_wlan_sniffer_res_enum           result;	// Result ENUM, reference vm_wlan_sniffer_res_enum
    vm_wlan_prof_struct                profile; // Get by sniffer
}vm_wlan_sniffer_on_res_struct;


/* Sniffer ON Config structure, used in paramter */
typedef struct
{
    VMUINT32 sniffer_filter_op;
    VMUINT8  channel_num;
    VMINT32 min_rssi;
    VMINT32 max_rssi;
    VMUINT16 min_pack_len;
    VMUINT16 max_pack_len;
}vm_wlan_sniffer_on_cfg_struct;


/* WLAN Notification Structure */
typedef struct
{   
    vm_wlan_noti_type_enum type;	//Notification type
    void * data;					//Notification data
}vm_wlan_noti_struct;


/* Mac addres query structure */
typedef struct
{      
    VMCHAR *dest;       /* destination buffer. */
    VMUINT16 dest_len;     /* application's dest buffer length. */
    VMUINT16 req_len;      /* if this attribute is provided by application (NOT NULL), 
                         WLAN SRV will hint application the required buffer length */
} vm_wlan_prof_str_info_qry_struct;


/* WLAN scan AP info strucutre */
typedef struct
{
    VMUINT8      bssid[ VM_WLAN_WNDRV_MAC_ADDRESS_LEN ]; /* MAC address */
    VMUINT8      ssid [ VM_WLAN_WNDRV_SSID_MAX_LEN ];	 /* SSID */
    VMUINT16     ssid_len;								/* SSID Length */
    VMINT32     rssi;                           /* receive signal, in dBm */
    VMUINT32     channel_number;					/* AP Channel number */
    VMUINT8      max_rate;							/* AP Max rate */
    VMUINT8      privacy;                        /* WEP encryption requirement */
    vm_wlan_network_type_enum  network_type;  /* profile network type */
    vm_wlan_auth_mode_enum     auth_mode;     /* profile auth.mode */    
    vm_wlan_encrypt_mode_enum  encrypt_mode;  /* profile encrypt mode */
} vm_wlan_scan_ap_info_struct;

/* this struct is designed for WLAN SRV to send the scan result to APP */
typedef struct
{
    vm_wlan_scan_result_enum                   result;      /* scan result enum */
    VMUINT8                                          ap_list_num; /* total num of searched ap list */
    vm_wlan_scan_ap_info_struct         ap_list[VM_WLAN_MAX_AP_LIST_NUM]; /* bss info array */
    VMINT32                                         scan_job_id; /* scan_job_id, 0xFFFFFF means scan result broadcasting */    
} vm_wlan_scan_result_struct;

/* This struct is designed for user to pass the specialized ssid for scaning. */
typedef struct
{
    VMUINT8 ssid_len;								//SSID length
    VMUINT8 ssid[VM_WLAN_WNDRV_SSID_MAX_LEN];		//SSID
}vm_wlan_ssid_struct;


/* this struct is designed for WLAN SRV to send the connect result to APP */
typedef struct
{
    vm_wlan_result_enum   result;     /* SUCCESS: connected, FAILD: connect failed, 
                                         * ABORTED: preemptived by new connect req 
                                         * TERMINATED: terminated by new disconnect req
                                         * STATE_ERROR: can't perform connect req
                                         */
    vm_wlan_cause_enum     cause;      /* Error cause, uses only if result = FAILD */
    VMUINT8                      bssid[VM_WLAN_WNDRV_MAC_ADDRESS_LEN];   /* MAC Address */
    VMUINT8                      ssid[VM_WLAN_WNDRV_SSID_MAX_LEN];       /* SSID */
    VMBYTE                init_by_soc;                    /* connection activated by socket flag */
    VMUINT16                     ssid_len;                       /* SSID length in array */
    VMUINT32                     channel_number;                 /* channel info from chip */
    VMUINT32                     profile_id;                     /* connected profile id */
    VMUINT32                         auth_type;
    VMUINT32                         eap_peap_auth_type;
    VMUINT32                         eap_ttls_auth_type;
    vm_wlan_connection_type_enum   conn_type;
    VMUINT16                  encry_mode; /*defaultly, it is WPS_ENCR_TYPES, 
                                              and now we don't to parse encry_mode in M2 */
    VMUINT8                   passphase[32];
    VMUINT8                   passphase_len;
    VMBYTE                need_login;
    VMBYTE                cancel_by_discon;
    VMINT                     rssi;
} vm_wlan_conn_res_struct;

/* this struct is designed for WLAN store query operation */
typedef struct
{
    VMUINT32 ids[VM_MAX_WLAN_ACCOUNT_NUM];    /* profile id list query result */
    VMUINT8  num_ids;                         /* the number of queried id list */
} vm_wlan_prof_list_struct;

/* event structure for setting roaming parameter*/
typedef struct {
    VMBYTE    is_roaming;	// param of roaming, 1 is roming, 0 is non-roaming
} vm_wlan_roaming_para_struct;


/* This struct is designed for wlan srv to tell the ip inforamtion. */
typedef struct
{
    VMUINT8 ip_addr[VM_WLAN_PROF_MAX_IP_ADDR_LEN];    /* IP address (ASCII, MAX: VM_WLAN_PROF_MAX_IP_ADDR_LEN) */
    VMUINT8 netmask[VM_WLAN_PROF_MAX_IP_ADDR_LEN];    /* Netmask (ASCII, MAX: VM_WLAN_PROF_MAX_IP_ADDR_LEN) */
    VMUINT8 gateway[VM_WLAN_PROF_MAX_IP_ADDR_LEN];    /* Gateway (ASCII, MAX: VM_WLAN_PROF_MAX_IP_ADDR_LEN) */
    VMUINT8 dns1[VM_WLAN_PROF_MAX_IP_ADDR_LEN];       /* Primary DNS (ASCII, MAX: VM_WLAN_PROF_MAX_IP_ADDR_LEN) */
    VMUINT8 dns2[VM_WLAN_PROF_MAX_IP_ADDR_LEN];       /* Secondary DNS (ASCII, MAX: VM_WLAN_PROF_MAX_IP_ADDR_LEN) */
}vm_wlan_ip_info_struct;


/* AP information */
typedef struct
{
    VMUINT8 ssid[VM_WLAN_PROF_MAX_SSID_LEN+1];		//SSID of AP
    vm_wlan_auth_mode_enum auth_mode;				//Auth mode, reference vm_wlan_auth_mode_enum
    VMUINT8 password[VM_WLAN_PROF_PSWD_MAX_LEN+1];	//Password of AP
}vm_wlan_ap_info_struct;

/* Connected ap information */
typedef struct 
{
    VMUINT8 bssid[VM_WLAN_WNDRV_MAC_ADDRESS_LEN + 1];
    VMUINT32 prof_id;
    VMINT32 rssi_out;
}vm_wlan_conned_ap_info_struct;


/* part of scan param -- spec ssid list */
typedef struct
{
    VMUINT8 ssid_list_num;
    vm_wlan_ssid_struct ssid_list[VM_WLAN_MAX_SPEC_SSID_LIST_NUM];
}vm_wlan_spec_ssid_list_struct;

typedef struct 
{
    /* AP mode info */    
    vm_wlan_auth_mode_enum auth_mode;
    VMINT8 ssid[VM_WLAN_WNDRV_SSID_MAX_LEN + 1];
    VMINT8 psk[VM_WLAN_PROF_PSWD_MAX_LEN];

    /* add */
}vm_wlan_cfg_ap_struct; 
/*****************************************************************************
 * FUNCTION
 *  vm_wlan_conn_res_cb_func_ptr
 * DESCRIPTION
 *  Prototype of wLAN scan result callback function
 * PARAMETERS
 *  user_data   :   [IN]    APP's piggyback user_data
 *  conn_res    :   [IN]    connect results from DA SRV
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_wlan_conn_res_cb_func_ptr) (
            void *user_data,
            vm_wlan_conn_res_struct *conn_res);
            
/*****************************************************************************
 * FUNCTION
 *  vm_wlan_cb_func_ptr
 * DESCRIPTION
 *  Prototype of wLAN general callback function for no feedback arguments except application piggyback data
 * PARAMETERS
 *  user_data   :   [IN]    APP's piggyback user_data
 *  res         :   [IN]    request result
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_wlan_cb_func_ptr) (void *user_data, vm_wlan_req_res_enum res);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_sniffer_off_cb_func_ptr
 * DESCRIPTION
 *  Prototype of wlan sniffer on callback function. Tell user the result of sniffer on. If successfully, 
 *  function will be called again with AP info.
 * PARAMETERS
 *  user_data   :   [IN]    APP's piggyback user_data
 *  res         :   [IN]    Sniffer on results from WLAN srv
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_wlan_sniffer_on_cb_func_ptr) (
            void *user_data,
            vm_wlan_sniffer_on_res_struct *res);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_sniffer_off_cb_func_ptr
 * DESCRIPTION
 *  Prototype of wlan sniffer off callback function. Tell user the result of sniffer off. 
 * PARAMETERS
 *  user_data   :   [IN]    APP's piggyback user_data
 *  res         :   [IN]    Sniffer off results from WLAN srv
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_wlan_sniffer_off_cb_func_ptr) (
            void *user_data,
            vm_wlan_sniffer_res_enum res);

/*****************************************************************************
 * FUNCTION
 *  vm_wlan_noti_func_ptr
 * DESCRIPTION
 *  Prototype of notification register function. When notification comes, corresponding register
 *  function will be called if it's registered before.
 * PARAMETERS
 *  user_data   :   [IN]    APP's piggyback user_data
 *  noti        :   [IN]    Noti type
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_wlan_noti_func_ptr) (void *user_data, vm_wlan_noti_struct *noti);     

             
  
/*****************************************************************************
 * FUNCTION
 *  vm_wlan_scan_res_cb_func_ptr
 * DESCRIPTION
 *  WLAN scan result callback function
 *  APPs need to copy the bss info byself.
 * PARAMETERS
 *  job_id      :   [IN]    APP's job ID from return value by calling WLAN scan operation
 *  user_data   :   [IN]    APP's piggyback user_data
 *  scan_res    :   [IN]    Scan results from WLAN srv
 * RETURNS
 *  success if 0, else failure.
 *****************************************************************************/
typedef void (*vm_wlan_scan_res_cb_func_ptr) (
            VMUINT32 job_id,
            void *user_data,
            vm_wlan_scan_result_struct *scan_res);



/*****************************************************************************
 * FUNCTION
 *  vm_wlan_connect
 * DESCRIPTION
 *  The function is used to connect the AP specified by the info in ap_info.
 *  1. DA WLAN servive can only support one connection at the same time due to chip constraint.
 *  2. If the new connect request is arrived, current connecting process will be aborted.
 *  3. If there is one connection already, the connection will be disconnected 
 *     then connect a new one.
 * PARAMETERS
 *  prof_id     :   [IN]    prof_id for wlan profile
 *  callback    :   [IN]    connect result callback notify function for APP
 *  user_data   :   [IN]    application associated piggyback data
 * RETURN VALUES
 *  VM_WLAN_RESULT_INVALID_INPUT  : profile_num <= 0 or profile pointer invalid
 *  VM_WLAN_RESULT_STATE_ERROR    : the wlan status can't perform the scan process
 *  VM_WLAN_RESULT_PROCESSING     : accept the connect quest, wait for event notify.
 * SEE ALSO
 *  vm_wlan_prof_connect
 * EXAMPLE
 *  <code>
 *  // STA status is ACTIVED before calling vm_wlan_connect().
 *  vm_wlan_ap_info_struct ap_info = {0};
 *  strcpy(ap_info.ssid, "ssidexample");
 *  ap_info.auth_mode = VM_WLAN_AUTH_MODE_WPA_ONLY_PSK;
 *  strcpy(ap_info.password, "ssidpwd");
 *  vm_wlan_connect(&ap_info, conn_cb, NULL);
 *  void conn_cb(void *user_data, vm_wlan_req_res_enum res)
 *  {
 *       if (VM_WLAN_REQ_RES_DONE == res)
 *       {
 *           // Connection succeeds.
 *       }
 *  }  
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_connect(
    vm_wlan_ap_info_struct *ap_info, 
    vm_wlan_conn_res_cb_func_ptr callback,
    void *user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_wlan_disconnect
 * DESCRIPTION
 *  1. The function is used to disconnect current WLAN connection.
 *  2. After WLAN init process is done, SRV will callback APP with user_data.
 * PARAMETERS
 *  callback    :   [IN]    callback function to notify applications the disconnect operation is done
 *  user_data   :   [IN]    application piggyback data 
 * RETURN VALUES
 *  refer to vm_wlan_result_enum
 *  VM_WLAN_RESULT_STATE_ERROR    :   the wlan status can't perform the disconnect process
 *  VM_WLAN_RESULT_SUCCESS        :   the WLAN status is active.
 *  VM_WLAN_RESULT_PROCESSING     :   accept the disconnect quest, wait for event notify.
 * EXAMPLE
 *  <code>
 *  // STA status is CONNECTED before calling vm_wlan_disconnect().
 *  vm_wlan_disconnect(disconn_cb, NULL);
 *  void disconn_cb(void *user_data, vm_wlan_req_res_enum res)
 *  {
 *       if (VM_WLAN_REQ_RES_DONE == res)
 *       {
 *           // Disconnection succeeds.
 *       }
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_disconnect(vm_wlan_cb_func_ptr callback, void *user_data);



/*****************************************************************************
 * FUNCTION
 *  vm_wlan_mode_set
 * DESCRIPTION
 *  The function is used to switch the mode. 
 *  VM_WLAN_SET_MODE_OFF turns off both AP mode and STA mode.
 *  VM_WLAN_SET_MODE_AP turns only AP mode on.
 *  VM_WLAN_SET_MODE_STA turns only STA mode on.
 *  VM_WLAN_SET_MODE_AP_STA turns both AP mode and STA mode on.
 * PARAMETERS
 *  mode         :   [IN]    The mode wanted to switch on.
 * RETURN VALUES
 *  
 * EXAMPLE
 *  <code>
 *  vm_wlan_mode_set(VM_WLAN_SET_MODE_AP, switch_mode_cb, NULL);
 *  void switch_mode_cb(void *user_data, vm_wlan_req_res_enum res)
 *  {
 *      if (VM_WLAN_REQ_RES_DONE == res)
 *      {
 *          // Switch mode successfully.
 *      }
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_mode_set(vm_wlan_set_mode_enum mode, vm_wlan_cb_func_ptr callback, void *user_data);



/*****************************************************************************
 * FUNCTION
 *  vm_wlan_mode_get
 * DESCRIPTION
 *  The function is query the status of WLAN services.
 * PARAMETERS
 *  void
 * RETURNS
 *  refer to  vm_wlan_mode_status_enum
 * EXAMPLE
 *  <code>
 *  vm_wlan_mode_status_enum mode;
 *  mode = srv_wlan_status();
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_mode_get(void);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_status
 * DESCRIPTION
 *  The function is used to query current status in WLAN STA mode.
 * PARAMETERS
 *  VMINT
 * RETURNS
 *  vm_wlan_sta_status_enum
 *  VM_WLAN_STA_STATUS_BUSY means that WIFI status is changing, 
 *  User need to wait changing finish and poll the result in interval timer
 * EXAMPLE
 *  <code>
 *  srv_wlan_sta_status_enum sta_status;
 *  sta_status = srv_wlan_sta_status(); 
 *  </code>
 *****************************************************************************/ 
VMINT vm_wlan_status(void);



/*****************************************************************************
 * FUNCTION
 *  vm_wlan_get_ip_info
 * DESCRIPTION
 *  The function is used to get ip addr, netmask, gateway ip, dns, when they are available.
 *  These ip info will be available only when wlan srv is in CONNECTED status. And there're 
 *  two situation due to the way of how to get ip.
 *  If using static ip when connecting, the ip will be availabe once connection succeeds.
 *  If using DHCP when connecting, ip will be availabe only when ABM notify the ip by MSG.
 *  That'll take a little time after connection succeeds. 
 * PARAMETERS
 *  ip_info     :   [OUT]    Ip info
 * RETURN VALUES
 *  VM_WLAN_RESULT_SUCCESS:      Successfuly.
 *  VM_WLAN_RESULT_STATE_ERROR:  Wrong time to get ip for ip is not available. 
 *  VM_WLAN_RESULT_FAILED:       Failed.
 * EXAMPLE
 *  <code>
 *  vm_wlan_ip_info_struct ip_info = {0};
 *  vm_wlan_get_ip_info(&ip_info);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_get_ip_info(vm_wlan_ip_info_struct* ip_info);



/*****************************************************************************
 * FUNCTION
 *  vm_wlan_get_mac_address
 * DESCRIPTION
 *  The function is used to get MAC address.
 *  1. dest buffer length must be >= VM_WLAN_WNDRV_MAC_ADDRESS_LEN, i.e. dest_len must 
 *     be >= VM_WLAN_WNDRV_MAC_ADDRESS_LEN, otherwise WLAN SRV will be failure 
 *     and reqired length (VM_WLAN_WNDRV_MAC_ADDRESS_LEN) will be set back to application.
 *  2. Also, if dest = NULL, and req_len exist, it will get failure
 *     with required length in req_len for application.
 * PARAMETERS
 *  mac_address_out     :   [OUT]    MAC address output location
 * RETURN VALUES
 *  success if 0, else failure.
 * EXAMPLE
 *  <code>
 *  CHAR dest[VM_WLAN_WNDRV_MAC_ADDRESS_LEN] = {0};
 *  vm_wlan_prof_str_info_qry_struct mac_addr;
 *  mac_addr.dest = dest;
 *  mac_addr.dest_len = VM_WLAN_WNDRV_MAC_ADDRESS_LEN;
 *  vm_wlan_get_mac_address(&mac_addr);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_get_mac_address(vm_wlan_prof_str_info_qry_struct *mac_address_out);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_get_connected_ap_info
 * DESCRIPTION
 *  The function is used to get information of the connected AP, such as bssid, rssi, 
 *  and profile id. 
 *  
 *  Input parameter, info_type, indicates what kind of information is wanted. User should provide 
 *  enough memory to store the information as following:
 *
 *  info_type                   info
 *  VM_WLAN_AP_INFO_BSSID      U8 array with length at least VM_WLAN_WNDRV_MAC_ADDRESS_LEN + 1
 *  VM_WLAN_AP_INFO_PROF_ID    U32* points to a U32 variable
 *  VM_WLAN_AP_INFO_RSSI       S32* points to an S32 variable
 *  VM_WLAN_AP_INFO_ALL        vm_wlan_conned_ap_info_struct* to an vm_wlan_conned_ap_info_struct variable
 *
 * PARAMETERS
 *  info      [OUT]: parameter used to store ap info. Please refer to the description.
 *  info_type [IN]: vm_wlan_ap_info_type_enum
 * RETURN VALUES
 *  success if 0, else failure.
 * EXAMPLE
 *  <code>
 *  // To get bssid
 *  U8 bssid[VM_WLAN_WNDRV_MAC_ADDRESS_LEN + 1] = {0};
 *  vm_wlan_get_connected_ap_info((void*)bssid, VM_WLAN_AP_INFO_BSSID);
 *  // To get prof id
 *  U32 prof_id;
 *  vm_wlan_get_connected_ap_info((void*)&prof, VM_WLAN_AP_INFO_PROF_ID);
 *  // To get rssi
 *  S32 rssi;
 *  vm_wlan_get_connected_ap_info((void*)&rssi, VM_WLAN_AP_INFO_RSSI);
 *  // To get all inforamtion
 *  vm_wlan_conned_ap_info_struct ap_info = {0};
 *  vm_wlan_get_connected_ap_info((void*)&ap_info, VM_WLAN_AP_INFO_ALL);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_get_connected_ap_info(void *info, VMINT info_type);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_scan
 * DESCRIPTION
 *  The function is used to scan the AP list for applications.
 * PARAMETERS
 *  callback    :   [IN]    scan result callback notify function for APP
 *  user_data   :   [IN]    application piggyback data
 * RETURN VALUES
 *  Job ID > 0 : New scan job created successfully.
 *  Job ID <= 0 : Can't create a new scan job.
 * EXAMPLE
 *  <code>
 *  U32 job_id;
 *  job_id = vm_wlan_scan(scan_cb, NULL);
 *  void scan_cb(
 *           U32 job_id,
 *           void *user_data,
 *           vm_wlan_scan_result_struct *scan_res)
 *  {
 *      if (VM_WLAN_SCAN_RESULT_SUCCESS == scan_res->result)
 *      {
 *          // Scan successfully. Information of APs scaned is in scan_res.
 *      }
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_scan(vm_wlan_scan_res_cb_func_ptr callback, void *user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_scan_abort
 * DESCRIPTION
 *  The function is used to abort the scanning AP list process for applications.
 * PARAMETERS
 *  job_id  :   [IN]    created job ID from calling vm_wlan_scan
 * RETURNS
 *  success if 0, else failure.
 * EXAMPLE
 *  <code>
 *  // scan job_id is returned by vm_wlan_scan().
 *  vm_wlan_scan_abort(job_id);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_scan_abort(VMUINT32 job_id);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_scan_set_param
 * DESCRIPTION
 *  The function is used to set scan parameters, such as dwell time or specific ssid list.
 *  For scan parameters will be initialized to the default value evertytime wlan is turned on
 *  from inactive status, setting scan parameters is not useful at INACTIVE status, so it's not
 *  allowed. 
 *  If scan parameter(s) is(are) not set, default value(s) will be used.
 *  Default values: dwell time: 60  spec_ssid_list: NULL
 * 
 *  Input parameter param_type indicates the kind of scan param that is wanted to be set. User 
 *  should provide proper param to each kind of scan param as following:
 *
 *  param_type                              param
 *  VM_WLAN_SCAN_PARAM_DWELL_TIME          U16* points to a U16 variable
 *  VM_WLAN_SCAN_PARAM_SPEC_SSID_LIST      vm_wlan_spec_ssid_list_struct* points to an
 *                                          vm_wlan_spec_ssid_list_struct variable
 * PARAMETERS
 *  param           [IN] scan parameters
 *  param_type      [IN] vm_wlan_scan_param_type_enum
 * RETURN VALUES
 *  VM_WLAN_RESULT_SUCCESS:        Successfuly.
 *  VM_WLAN_RESULT_FAILED:         Failed.
 *  VM_WLAN_RESULT_INVALID_INPUT:  Invalid input parameter(s).
 *  VM_WLAN_RESULT_STATE_ERROR:    Set scan parameter(s) in INACTIVE status
 * EXAMPLE
 *  <code>
 *  // Set dwell time
 *  U16 dwell_time = 70;
 *  vm_wlan_scan_set_param((void*)&dwell_time, VM_WLAN_SCAN_PARAM_DWELL_TIME, set_dwell_time_cb, NULL);
 *  
 *  void set_dwell_time_cb(void *user_data, vm_wlan_req_res_enum res)
 *  {
 *      if (VM_WLAN_REQ_RES_DONE == res)
 *      {
 *          // Set dwell time successfully.
 *      }
 *  }
 *  // Set specialized ssid list
 *  vm_wlan_spec_ssid_list_struct ssid_list = {0};
 *  ssid_list.ssid_list[0] = {5, "ssid1"};
 *  ssid_list.ssid_list[1] = {5, "ssid2"};
 *  ssid_list.ssid_list[2] = {5, "ssid3"};
 *  ssid_list.ssid_list[3] = {5, "ssid4"};
 *  ssid_list.ssid_list_num = 4;
 *  vm_wlan_scan_set_param((void*)&ssid_list, VM_WLAN_SCAN_PARAM_SPEC_SSID_LIST, set_spec_ssid_list_cb, NULL);
 *  void set_spec_ssid_list_cb(void *user_data, vm_wlan_req_res_enum res)
 *  {
 *      if (VM_WLAN_REQ_RES_DONE == res)
 *      {
 *          // Set specialized ssid list successfully.
 *      }
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_scan_set_param(
    void *param, 
    VMINT32 param_type, 
    vm_wlan_cb_func_ptr callback, 
    void *user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_scan_get_param
 * DESCRIPTION
 *  The function is used to get scan parameters, such as dwell time or specific ssid list.
 * 
 *  Input parameter param_type indicates the kind of scan param that is wanted. User 
 *  should provide proper param to each kind of scan param as following:
 *
 *  param_type                              param
 *  VM_WLAN_SCAN_PARAM_DWELL_TIME          U16* points to a U16 variable
 *  VM_WLAN_SCAN_PARAM_SPEC_SSID_LIST      vm_wlan_spec_ssid_list_struct* points to an
 *                                          vm_wlan_spec_ssid_list_struct variable
 * PARAMETERS
 *  param           [OUT] scan parameters
 *  param_type      [IN]  vm_wlan_scan_param_type_enum
 * RETURN VALUES
 *  VM_WLAN_RESULT_SUCCESS:        Successfuly.
 *  VM_WLAN_RESULT_FAILED:         Failed.
 *  VM_WLAN_RESULT_INVALID_INPUT:  Invalid input parameter(s).
 * EXAMPLE
 *  <code>
 *  // Get dwell time
 *  U16 dwell_time;
 *  vm_wlan_scan_get_param((void*)&dwell_time, VM_WLAN_SCAN_PARAM_DWELL_TIME);
 *  // Get specialized ssid list
 *  vm_wlan_spec_ssid_list_struct ssid_list;
 *  vm_wlan_scan_get_param((void*)&ssid_list, VM_WLAN_SCAN_PARAM_SPEC_SSID_LIST);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_scan_get_param(void *param, VMINT32 param_type);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_reg_noti
 * DESCRIPTION
 *  The function is used to register the handler of notifications, such as ip available notification, or 
 *  WIFI passive disconnect notification. When relative things happens, notification will be actived and
 *  callback function will be invoked if it's registered before. 
 * 
 *  vm_wlan_reg_noti() should be paired with vm_wlan_dereg_noti().
 * PARAMETERS
 *  noti_type           :   [IN]    Notification type. Please refer to vm_wlan_noti_type_enum
 *  callback            :   [IN]    callback function to notify that notification is coming
 *  user_data           :   [IN]    application piggyback data 
 * RETURN VALUES
 *  success if 0, else failure.
 * EXAMPLE
 *  <code>
 *  vm_wlan_reg_noti(VM_WLAN_NOTI_IP_AVAILABLE, ip_available_hdl, NULL);
 *  // When IP is available, ip_available_hdl will be called.
 *  void ip_available_hdl(void *user_data, vm_wlan_noti_struct *noti)
 *  {
 *    if (noti->type == VM_WLAN_NOTI_IP_AVAILABLE)
 *    {
 *      //...
 *    }
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_reg_noti(VMINT noti_type, vm_wlan_noti_func_ptr callback, void *user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_dereg_noti
 * DESCRIPTION
 *  The function is used to deregister the handler of notifications which is registered before.
 *  the type of notification, callback and user_data should be the same as the one that registed 
 *  by using vm_wlan_reg_noti().
 *
 *  vm_wlan_dereg_noti() should be paired with vm_wlan_reg_noti()
 * PARAMETERS
 *  noti_type           :   [IN]    Notification type. Please refer to vm_wlan_noti_type_enum
 *  callback            :   [IN]    callback function to notify that notification is coming
 *  user_data           :   [IN]    application piggyback data 
 * RETURN VALUES
 *  success if 0, else failure.
 * EXAMPLE
 *  <code>
 *  vm_wlan_reg_noti(VM_WLAN_NOTI_IP_AVAILABLE, ip_available_hdl, NULL);
 *  // Deregister with the same callback and user_data. Then when IP is avaliable, ip_available_hdl  
 *  // will not be called.
 *  vm_wlan_dereg_noti(VM_WLAN_NOTI_IP_AVAILABLE, ip_available_hdl, NULL);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_dereg_noti(VMINT noti_type, vm_wlan_noti_func_ptr callback, void *user_data);



/*****************************************************************************
 * FUNCTION
 *  vm_wlan_sniffer_on
 * DESCRIPTION
 *  The function is used to open sniffer in WLAN STA mode.
 * PARAMETERS
 *  sniffer_on_config   :   [IN]    the configuration parameter of sniffer status
 *  callback            :   [IN]    callback function to notify applications the operation is done
 *  user_data           :   [IN]    application piggyback data 
 * RETURN VALUES
 *  VM_WLAN_RESULT_SUCCESS        : Successfuly.
 *  VM_WLAN_RESULT_FAILED         : Failed.
 *  VM_WLAN_RESULT_INVALID_INPUT  : Invalid input parameter(s).
 *  VM_WLAN_RESULT_PROCESSING     : Waiting for result.
 * EXAMPLE
 *  <code>
 *  vm_wlan_sniffer_on(NULL, sniffer_on_cb, NULL);
 *  void sniffer_on_cb(void *user_data, vm_wlan_sniffer_on_res_struct *res)
 *  {
 *      switch (res->cb_type)
 *      {
 *          case VM_WLAN_SNIFFER_ON_RES:
 *          {
 *              if (res->result == VM_WLAN_SNIFFER_SUCCESS)
 *              {
 *                  // Open sniffer successfully.
 *              }
 *              break;
 *          }
 *          case VM_WLAN_SNIFFER_ON_AP_INFO:
 *          {
 *              if (res->result == VM_WLAN_SNIFFER_SUCCESS)
 *              {
 *                  // Get AP information successfully. And Ap information is stored
 *                  // in res->profile.
 *              }
 *              break;
 *          }
 *          default:
 *              break;
 *      }
 *  }
 *  </code>
 *****************************************************************************/ 
VMINT vm_wlan_sniffer_on(vm_wlan_sniffer_on_cfg_struct *sniffer_on_config, vm_wlan_sniffer_on_cb_func_ptr callback, void *user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_sniffer_off
 * DESCRIPTION
 *  The function is used to close sniffer in WLAN STA mode.
 * PARAMETERS
 *  callback            :   [IN]    callback function to notify applications the operation is done
 *  user_data           :   [IN]    application piggyback data 
 * RETURN VALUES
 *  VM_WLAN_RESULT_SUCCESS        : Successfuly.
 *  VM_WLAN_RESULT_FAILED         : Failed.
 *  VM_WLAN_RESULT_INVALID_INPUT  : Invalid input parameter(s).
 *  VM_WLAN_RESULT_PROCESSING     : Waiting for result.
 * EXAMPLE
 *  <code>
 *  vm_wlan_sniffer_off(sniffer_off_cb, NULL);
 *  void sniffer_off_cb(void *user_data, vm_wlan_sniffer_res_enum res)
 *  {
 *      if (VM_WLAN_SNIFFER_SUCCESS == res)
 *      {
 *          // Exist sniffer successfully.
 *      }
 *  }
 *  </code>
 *****************************************************************************/ 
VMINT vm_wlan_sniffer_off(vm_wlan_sniffer_off_cb_func_ptr callback, void *user_data);



/*****************************************************************************
 * FUNCTION
 *  vm_wlan_prof_init
 * DESCRIPTION
 *  The function is used to init the wlan profile structure. In other words, fill in default
 *  values for the structure data members.
 * PARAMETERS
 *  profile :   [OUT]    specified profile to be set
 * RETURN VALUES
 *  refer to vm_wlan_result_enum
 * EXAMPLE
 *  <code>
 *  vm_wlan_prof_struct wlan_prof;
 *  vm_wlan_prof_init(&wlan_prof);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_prof_init(vm_wlan_prof_struct *profile);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_prof_add
 * DESCRIPTION
 *  The function is to add a new wlan profile by specified profile data.
 * PARAMETERS
 *  prof        :   [IN]        profile data buffer to be added
 *  prof_id     :   [OUT]    return prof_id for wlan profile
 * RETURN VALUES
 *  refer to vm_wlan_result_enum
 *  VM_WLAN_RESULT_SUCCESS        : add profile successfully.
 *  VM_WLAN_RESULT_FAILED         : add profile failed.
 *  VM_WLAN_RESULT_ONE_STORE_EXISTS : the profile has already been added.
 *  VM_WLAN_RESULT_INVALID_STORE  : store handle invalid.
 *  VM_WLAN_RESULT_INVALID_INPUT  : the input parameter is invalid.
 *  VM_WLAN_RESULT_STORE_FULL     : storage full
 * EXAMPLE
 *  <code>
 *  vm_wlan_prof_struct wlan_prof;
 *  U32 prof_id = 0;
 *  vm_wlan_result_enum ret;
 *  vm_wlan_prof_init(&wlan_prof);
 *  strcpy(wlan_prof.ssid, "ssidexample");
 *  // If auth mode is VM_WLAN_AUTH_MODE_OPEN, password is no need.
 *  wlan_prof.auth_mode = VM_WLAN_AUTH_MODE_WPA2_ONLY_PSK;
 *  strcpy(wlan_prof.password, "ssidpwd");
 *  ret = vm_wlan_prof_add(&wlan_prof, &prof_id);
 *  if (ret == VM_WLAN_RESULT_SUCCESS)
 *  {
 *      // Add profile successfully.
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_prof_add(const vm_wlan_prof_struct *prof, VMUINT32 *prof_id);                        


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_prof_update
 * DESCRIPTION
 *  The function is to update WLAN profile content by specified profile id. Structure
 *  data members can be updated seperately, or updated all at one time.
 * PARAMETERS
 *  prof_id     :   [IN]    update wlan profile id
 *  wlan_prof   :   [IN]    profile info from application
 *  prof_fields :   [IN]    VM_WLAN_PROF_FIELD_X, such as VM_WLAN_PROF_FIELD_ALL
 * RETURN VALUES
 *  refer to vm_wlan_result_enum
 *  VM_WLAN_RESULT_SUCCESS            : update profile successfully.
 *  VM_WLAN_RESULT_INVALID_STORE      : store handle invalid.
 *  VM_WLAN_RESULT_INVALID_INPUT      : the input parameter is invalid.
 *  VM_WLAN_RESULT_READ_ONLY          : this profile can't be deleted or update 
 * EXAMPLE
 *  <code> 
 *  // Fill in the new value for the data members you want to update.
 *  vm_wlan_prof_struct wlan_prof = {0};
 *  strcpy(wlan_prof.password, "newpwd");
 *  // There's an avaialbe profile id(For how to get an available profile id, please
 *  // refer to vm_wlan_prof_add()).
 *  vm_wlan_prof_update(prof_id, &wlan_prof, VM_WLAN_PROF_FIELD_PW);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_prof_update(VMUINT32 prof_id, vm_wlan_prof_struct *prof, VMUINT32 prof_fields);



/*****************************************************************************
 * FUNCTION
 *  vm_wlan_prof_delete
 * DESCRIPTION
 *  The function is to delete a WLAN profile by specified profile id.
 * PARAMETERS
 *  prof_id     :   [IN]    query wlan profile id
 * RETURN VALUES
 *  refer to vm_wlan_result_enum
 *  VM_WLAN_RESULT_SUCCESS            : delete profile successfully.
 *  VM_WLAN_RESULT_INVALID_STORE      : store handle invalid.
 *  VM_WLAN_RESULT_INVALID_INPUT      : the input parameter is invalid.
 *  VM_WLAN_RESULT_READ_ONLY          : this profile can't be deleted or update
 * EXAMPLE
 *  <code>
 *  // There's an avaialbe profile id(For how to get an available profile id, please
 *  // refer to vm_wlan_prof_add()).
 *  vm_wlan_prof_delete(prof_id);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_prof_delete(VMUINT32 prof_id);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_prof_connect
 * DESCRIPTION
 *  The function is used to connect the applications specified AP for applications.
 *  1. DA WLAN servive can only support one connection at the same time due to chip constraint.
 *  2. If the new connect request is arrived, current connecting process will be aborted.
 *  3. If there is one connection already, the connection will be disconnected 
 *     then connect a new one.
 * PARAMETERS
 *  prof_id     :   [IN]    prof_id for wlan profile
 *  callback    :   [IN]    connect result callback notify function for APP
 *  user_data   :   [IN]    application associated piggyback data
 * RETURN VALUES
 *  refer to vm_wlan_result_enum
 *  VM_WLAN_RESULT_INVALID_INPUT  : profile_num <= 0 or profile pointer invalid
 *  VM_WLAN_RESULT_STATE_ERROR    : the wlan status can't perform the scan process
 *  VM_WLAN_RESULT_PROCESSING     : accept the connect quest, wait for event notify.
 * EXAMPLE
 *  <code>
 *  // STA status is ACTIVED before calling vm_wlan_prof_connect(). And there's an available
 *  // profile id(For how to get an available profile id, please refer to vm_wlan_prof_add()).
 *  vm_wlan_prof_connect(prof_id, conn_cb, NULL);
 *  void conn_cb(void *user_data, vm_wlan_req_res_enum res)
 *  {
 *       if (VM_WLAN_REQ_RES_DONE == res)
 *       {
 *           // Connection succeeds.
 *       }
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_prof_connect(VMUINT32 prof_id, vm_wlan_conn_res_cb_func_ptr callback, void *user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_prof_query
 * DESCRIPTION
 *  The function is to query WLAN profile content by specified profile id.
 * PARAMETERS
 *  prof_id     :   [IN]    query wlan profile id
 *  prof        :   [OUT]    profile info from application
 * RETURN VALUES
 *  refer to vm_wlan_result_enum
 *  VM_WLAN_RESULT_SUCCESS            : query profile successfully.
 *  VM_WLAN_RESULT_INVALID_STORE      : store handle invalid.
 *  VM_WLAN_RESULT_INVALID_INPUT      : the input parameter is invalid.
 * EXAMPLE
 *  <code>
 *  // There's an avaialbe profile id(For how to get an available profile id, please
 *  // refer to vm_wlan_prof_add()).
 *  vm_wlan_prof_struct wlan_prof = {0};
 *  VM_WLAN_RESULT_SUCCESS ret;
 *  ret = vm_wlan_prof_query(prof_id, &wlan_prof);
 *  if (VM_WLAN_RESULT_SUCCESS == ret)
 *  {
 *      // Query profile successfully. wlan_prof returns with detail of the profile.
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_prof_query(VMUINT32 prof_id, vm_wlan_prof_struct *prof);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_prof_query_list
 * DESCRIPTION
 *  The function is to query the number and ids of the WLAN profiles added.
 * PARAMETERS
 *  prof_list   :   [IN]    query wlan profile list
 * RETURN VALUES
 *  refer to vm_wlan_result_enum
 *  VM_WLAN_RESULT_SUCCESS            : query profile successfully.
 *  VM_WLAN_RESULT_INVALID_STORE      : store handle invalid.
 *  VM_WLAN_RESULT_INVALID_INPUT      : the input parameter is invalid.
 * EXAMPLE
 *  <code>
 *  vm_wlan_prof_list_struct prof_list;
 *  vm_wlan_prof_query_list(&prof_list);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_prof_query_list(vm_wlan_prof_list_struct *prof_list);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_set_reconn_prof_id
 * DESCRIPTION
 *  The function is used to set reconnect profile id. It will be stored and may be used 
 *  in reconfig flow. Every time connection succeeds, the reconn prof id will be set to 
 *  be the conn prof id automatically. 
 * PARAMETERS
 *  prof_id            :   [IN]    WLAN profile id which has been stored in WLAN service
 * RETURN VALUES
 *  success if 0, else failure.
 * EXAMPLE
 *  <code>
 *  // There's an avaialbe profile id(For how to get an available profile id, please
 *  // refer to vm_wlan_prof_add()). 
 *  vm_wlan_prof_set_reconn_id(prof_id);
 *  </code>
 *****************************************************************************/ 
VMINT vm_wlan_prof_set_reconn_id(VMUINT32 prof_id);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_get_reconn_prof_id
 * DESCRIPTION
 *  The function is used to get reconnect profile id. It will be stored and may be used
 *  in bootup flow. Everytime connection succeeds, the reconn prof id will be set to be 
 *  the conn prof id automatically. 
 * PARAMETERS
 *  prof_id            :   [OUT]    WLAN profile id which has been stored in WLAN service
 * RETURN VALUES
 *  success if 0, else failure.
 * EXAMPLE
 *  <code>
 *  U32 prof_id;
 *  vm_wlan_prof_get_reconn_id(&prof_id);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_prof_get_reconn_id(VMUINT32 *prof_id);


/*****************************************************************************
 * FUNCTION
 *  vm_wlan_roaming_set
 * DESCRIPTION
 *  The function is used to set roaming parameter.
 * PARAMETERS
 *  enable_roaming     :   [IN]    WLAN roaming parameter
 * RETURN VALUES
 *  VM_WLAN_RESULT_SUCCESS     : Successfuly.
 *  VM_WLAN_RESULT_FAILED      :  Failed.
 *  VM_WLAN_RESULT_PROCESSING  : Waiting for result.
 * EXAMPLE
 *  <code>
 *  MMI_BOOL enable_roaming = MMI_TRUE;
 *  vm_wlan_roaming_set(enable_roaming, set_roaming_cb, NULL);
 *  void set_roaming_cb(void *user_data, vm_wlan_req_res_enum res)
 *  {
 *      if (VM_WLAN_REQ_RES_DONE == res)
 *      {
 *          // Set roaming successfully.
 *      }
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_roaming_set(VMINT enable_roaming, vm_wlan_cb_func_ptr callback, void *user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_wlan_roaming_get
 * DESCRIPTION
 *  The function is used to get roaming parameter.
 * PARAMETERS
 *  is_roaming     :   [OUT]    WLAN roaming parameter
 * RETURN VALUES
 *  VM_WLAN_RESULT_SUCCESS: Successfuly.
 *  VM_WLAN_RESULT_FAILED:  Failed.
 * EXAMPLE
 *  <code>
 *  MMI_BOOL is_roaming = MMI_TRUE;
 *  vm_wlan_roaming_get(&is_roaming);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_roaming_get(VMINT *is_roaming);

           
/*****************************************************************************
 * FUNCTION
 *  vm_srv_wlan_set_para
 * DESCRIPTION
 *  Set parameters under different modes. User should prepare variables with proper types for 
 *  "para" and "flag" input parameters.
 *
 *  Currently, only MODE_AP and MODE_AP_STA are supported to set AP's SSID, Auth mode, and 
 *  Password. For Auth mode, only OPEN and WPA2_ONLY_PSK are supported. To make the parameter(s)
 *  work, do set parameter(s) before AP is turned on.
 *
 *  Default values will be used if parameters are not set or setting operation failed.
 *  Default SSID: MTK_XXXXXX(The value of XXXXXX depends on the last three bytes of mac addr)
 *  Default AUTH MODE:  WPA2_ONLY_PSK
 *  Default Password:   12345678
 *
 * PARAMETERS
 *  para :  [IN] vm_wlan_cfg_ap_struct(in AP mode)
 *  flag :  [IN] Indicate which parameter to config. 
 *               vm_wlan_cfg_ap_para_enum(in AP mode)
 * RETURNS
 *  VM_WLAN_RESULT_SUCCESS: set parameter success
 *  VM_WLAN_RESULT_FAILED: set parameter fail
 *  VM_WLAN_RESULT_STATE_ERROR: set at inappropriate state, such as set AP para when AP is on.
 *  VM_WLAN_RESULT_INVALID_INPUT: invalid input parameters.
  * EXAMPLE
 *  <code>
 *  // Set AP parameter before turning on AP mode.
 *  srv_wlan_cfg_ap_struct ap_param = {0};
 *  ap_param.auth_mode = VM_WLAN_AUTH_MODE_WPA2_ONLY_PSK;
 *  strcpy(ap_param.ssid, "SSIDEXAMPLE");
 *  strcpy(ap_param.pwd, "PWDEXAMPLE")
 *  vm_wlan_set_para(VM_WLAN_SET_MODE_AP, (void*)&ap_param, VM_WLAN_CFG_AP_PARA_ALL);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_set_para(
                    vm_wlan_set_mode_enum mode,
                    void *para,
                    VMINT32 flag);


/*****************************************************************************
 * FUNCTION
 *  vm_srv_wlan_get_para
 * DESCRIPTION
 *  Get parameter under different modes. Currently, only MODE_AP or MODE_AP_STA are 
 *  supported to get AP's SSID, Auth mode, and Password.
 
 *  User should prepare varible with proper type for "para" input parameter.
 * PARAMETERS
 *  para :  [OUT] return parameters to App.
 *                srv_wlan_cfg_ap_struct(under MODE_AP or MODE_AP_STA)
 * RETURNS
 *  VM_WLAN_RESULT_SUCCESS: get parameter success
 *  VM_WLAN_RESULT_FAILED: get parameter fail 
 *  VM_WLAN_RESULT_INVALID_INPUT: invalid input parameters.
  * EXAMPLE
 *  <code> 
 *  vm_wlan_cfg_ap_struct ap_param = {0}; 
 *  vm_wlan_get_para(SRV_WLAN_SET_MODE_AP, (void*)&ap_param);
 *  </code>
 *****************************************************************************/
VMINT vm_wlan_get_para(
                    vm_wlan_set_mode_enum mode,
                    void *para);


                    

#define VM_SCANONLY_MAX_SCAN_AP_NUM			15
#define VM_SCANONLY_MAC_ADDRESS_LEN	    	6
#define VM_SCANONLY_SSID_MAX_LEN				32

typedef enum
{
    VM_WNDRV_RESULT_SUCCESS,
    VM_WNDRV_RESULT_WOULDBLOCK,
    VM_WNDRV_RESULT_TOTAL
} vm_wndrv_result_enum;

typedef enum

{  
   VM_SCANONLY_SUCCESS = 0,
   
   VM_SCANONLY_INIT_BUSY_IS_INITING= 1,
   VM_SCANONLY_INIT_FAIL__ALREAD_INITED,
   VM_SCANONLY_INIT_FAIL__DRIVER_REASON,
   VM_SCANONLY_INIT_FAIL__UNKOWN,

   VM_SCANONLY_DEINIT_BUSY__IS_DEINITING = 10,
   VM_SCANONLY_DEINIT_FAIL__ALREAD_DEINITED,
   VM_SCANONLY_DEINIT_FAIL__DRIVER_REASON,
   VM_SCANONLY_DEINIT_FAIL__UNKOWN,

   VM_SCANONLY_SCAN_BUSY__IS_SCANNING = 20,
   VM_SCANONLY_SCAN_FAIL__NOT_INITED,
   VM_SCANONLY_SCAN_FAIL__DRIVER_REASON,
   VM_SCANONLY_SCAN_FAIL__UNKOWN,
   
   VM_SCANONLY_STATUS_END
}VM_SCANONLY_STATUS_ENUM;

typedef struct
{
    // Reserved struct
    void *para;
} vm_wlan_init_req_struct;

typedef struct
{
    VM_SCANONLY_STATUS_ENUM state;
} vm_wlan_init_cnf_struct;

typedef struct
{
    // Reserved struct
    void *para;
} vm_wlan_deinit_req_struct;

typedef struct
{
    VM_SCANONLY_STATUS_ENUM state;
} vm_wlan_deinit_cnf_struct;

typedef struct
{
    // Reserved struct
    void *para;
} vm_wlan_scan_req_struct;


typedef struct 
{    
  VMUINT8                      		    bssid[ VM_SCANONLY_MAC_ADDRESS_LEN ];
  VMUINT8                       		ssid_len;
  VMUINT8                       		ssid [ VM_SCANONLY_SSID_MAX_LEN ];    
  signed char                        	rssi;                           
  VMUINT8                       		channel_number;    
} vm_scanonly_scan_ap_info_struct;

typedef struct
{
    VM_SCANONLY_STATUS_ENUM                   status;
    VMUINT8                                 scan_ap_num;
    vm_scanonly_scan_ap_info_struct           scan_ap[ VM_SCANONLY_MAX_SCAN_AP_NUM ];
} vm_wlan_scan_cnf_struct;

/* Callback */
typedef void (*vm_wlan_init_cb) (void *user_data, vm_wlan_init_cnf_struct *cnf);
typedef void (*vm_wlan_deinit_cb) (void *user_data, vm_wlan_deinit_cnf_struct *cnf);
typedef void (*vm_wlan_scan_cb) (void *user_data, vm_wlan_scan_cnf_struct *cnf);

/*****************************************************************************
 * FUNCTION
 *  vm_wndrv_init
 * DESCRIPTION
 *  The function is used to switch WIFI on in station mode. 
 * PARAMETERS
 *  req         :   [IN]    reserved parameter
 *  callback    :   [IN]    init result callback notify function for APP
 *  user_data   :   [IN]    application piggyback data
 * RETURNS
 *  VM_WNDRV_RESULT_WOULDBLOCK : Wouldblock. callback will be invoked later to notify the result.
 * EXAMPLE
 *  <code>
 *  vm_wndrv_init(NULL, init_cb, NULL);
 *  void init_cb(void *user_data, vm_wlan_init_cnf_struct *cnf)
 *  {
 *      if (VM_SCANONLY_SUCCESS == cnf->state)
 *      {
 *          // successfully.
 *      }
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wndrv_init(vm_wlan_init_req_struct *req, vm_wlan_init_cb callback, void *user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_wndrv_deinit
 * DESCRIPTION
 *  The function is used to switch WIFI off. 
 * PARAMETERS
 *  req         :   [IN]    reserved parameter
 *  callback    :   [IN]    deinit result callback notify function for APP
 *  user_data   :   [IN]    application piggyback data
 * RETURNS
 *  VM_WNDRV_RESULT_WOULDBLOCK : Wouldblock. callback will be invoked later to notify the result.
 * EXAMPLE
 *  <code>
 *  vm_wndrv_deinit(NULL, deinit_cb, NULL);
 *  void deinit_cb(void *user_data, vm_wlan_deinit_cnf_struct *cnf)
 *  {
 *      if (VM_SCANONLY_SUCCESS == cnf->state)
 *      {
 *          // successfully.
 *      }
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wndrv_deinit(vm_wlan_deinit_req_struct *req, vm_wlan_deinit_cb callback, void *user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_wndrv_scan
 * DESCRIPTION
 *  The function is used to scan the AP list for applications.
 * PARAMETERS
 *  req         :   [IN]    reserved parameter
 *  callback    :   [IN]    scan result callback notify function for APP
 *  user_data   :   [IN]    application piggyback data
 * RETURNS
 *  VM_WNDRV_RESULT_WOULDBLOCK : Wouldblock. callback will be invoked later to notify the result.
 * EXAMPLE
 *  <code>
 *  vm_wndrv_scan(NULL, scan_cb, NULL);
 *  void scan_cb(void *user_data, vm_wlan_scan_cnf_struct *cnf)
 *  {
 *      if (VM_SCANONLY_SUCCESS == cnf->status)
 *      {
 *          // Scan successfully. Information of APs scaned is in cnf.
 *      }
 *  }
 *  </code>
 *****************************************************************************/
VMINT vm_wndrv_scan(vm_wlan_scan_req_struct *req, vm_wlan_scan_cb callback, void *user_data);


#ifdef __cplusplus
}
#endif

#endif /* VM_NWSETTING_SDK_H */
