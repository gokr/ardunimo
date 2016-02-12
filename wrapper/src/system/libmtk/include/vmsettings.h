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

#ifndef VMSETTINGS_SDK_H
#define VMSETTINGS_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

#define VM_SETTINGS_RET_OK              0
#define VM_SETTINGS_RET_FAIL            -2
#define VM_SETTINGS_RET_NOT_SUPPORT     -3  
#define VM_SETTINGS_RET_PARAM_ERR       -4 
#define VM_SETTINGS_RET_NO_MEM          -5


typedef VMINT (*vm_settings_set_wallpaper_callback)(void* user_data);

typedef enum
{
    VM_SETTINGS_POWER_ON_TONE,            
    VM_SETTINGS_POWER_OFF_TONE,           
    VM_SETTINGS_POWER_ON_OFF_TONE,        
    VM_SETTINGS_COVER_OPEN_TONE,          
    VM_SETTINGS_COVER_CLOSE_TONE,         
    VM_SETTINGS_SMS_TONE,
    VM_SETTINGS_SMS_CARD2_TONE,     
    VM_SETTINGS_SMS_CARD3_TONE,       
    VM_SETTINGS_SMS_CARD4_TONE, 
    VM_SETTINGS_MMS_TONE,                 
    VM_SETTINGS_MMS_CARD2_TONE,           
    VM_SETTINGS_MMS_CARD3_TONE,           
    VM_SETTINGS_MMS_CARD4_TONE,           
    VM_SETTINGS_EMAIL_TONE,               
    VM_SETTINGS_EMAIL_CARD2_TONE,         
    VM_SETTINGS_EMAIL_CARD3_TONE,         
    VM_SETTINGS_EMAIL_CARD4_TONE,         
    VM_SETTINGS_VOICE_TONE,               
    VM_SETTINGS_VOICE_CARD2_TONE,         
    VM_SETTINGS_VOICE_CARD3_TONE,         
    VM_SETTINGS_VOICE_CARD4_TONE,         
    VM_SETTINGS_MT_CALL_TONE,            
    VM_SETTINGS_MT_CALL_CARD2_TONE,       
    VM_SETTINGS_MT_CALL_CARD3_TONE,       
    VM_SETTINGS_MT_CALL_CARD4_TONE,       
    VM_SETTINGS_VT_CALL_TONE,             
    VM_SETTINGS_VT_CALL_CARD2_TONE,       
    VM_SETTINGS_VT_CALL_CARD3_TONE,       
    VM_SETTINGS_VT_CALL_CARD4_TONE,       
    VM_SETTINGS_TONE_END               
}vm_settings_tone_enum;

typedef enum
{
    VM_SETTINGS_HOME_PAPER,
    VM_SETTINGS_LOCK_PAPER,
    VM_SETTINGS_WALLPAPER_END
}vm_setttings_wallpaper_enum;


VMINT vm_settings_set_tone(vm_settings_tone_enum type, VMWCHAR* path);

VMINT vm_settings_set_wallpaper(vm_setttings_wallpaper_enum type, 
                                            VMWCHAR* path,vm_settings_set_wallpaper_callback callback, void* user_data);
                                            


/* Enum for time format */
typedef enum
{
    VM_SETTING_TIME_FORMAT_12_HOURS,
    VM_SETTING_TIME_FORMAT_24_HOURS,

    VM_SETTING_TIME_FORMAT_END
} vm_setting_time_format_enum;

/* Enum for date format */
typedef enum
{
    VM_SETTING_DATE_FORMAT_DD_MM_YYYY,
    VM_SETTING_DATE_FORMAT_MM_DD_YYYY,        
    VM_SETTING_DATE_FORMAT_YYYY_MM_DD,

    VM_SETTING_DATE_FORMAT_END
} vm_setting_date_format_enum;

/* Enum for date seperator */
typedef enum
{
    VM_SETTING_DATE_SEPERATOR_DOT,
    VM_SETTING_DATE_SEPERATOR_COLON,
    VM_SETTING_DATE_SEPERATOR_SLOPE,    
    VM_SETTING_DATE_SEPERATOR_LINE,

    VM_SETTING_DATE_SEPERATOR_END
} vm_setting_date_seperator_enum;


/*****************************************************************************
 * FUNCTION
 *  vm_setting_get_time_format
 * DESCRIPTION
 *  Get system time format 
 * PARAMETERS
 *  void
 * RETURNS
 *  vm_setting_time_format_enum
 *****************************************************************************/
VMINT vm_setting_get_time_format(void);


/*****************************************************************************
 * FUNCTION
 *  vm_setting_get_date_format
 * DESCRIPTION
 *  Get system date format 
 * PARAMETERS
 *  void
 * RETURNS
 *  vm_setting_date_format_enum
 *****************************************************************************/
VMINT vm_setting_get_date_format(void);


/*****************************************************************************
 * FUNCTION
 *  vm_setting_get_date_seperator
 * DESCRIPTION
 *  Get system date seperator 
 * PARAMETERS
 *  void
 * RETURNS
 *  vm_setting_date_seperator_enum
 *****************************************************************************/
VMINT vm_setting_get_date_seperator(void);

											


/*Setting Type Enum*/
typedef enum
{
    VM_SETTING_ENUM_NULL,             //NULL
    VM_SETTING_CELLULAR_GPRS_SERVICE,   //GPRS on/off
    VM_SETTING_CELLULAR_GPRS_ROAMING,   //GPRS roaming on/off
    VM_SETTING_CELLULAR_CONNECTION_SIM, //SIM selection in multiple SIM case
    VM_SETTING_NETWORK_ACCOUNTS,        //network accounts
    VM_SETTING_DATETIME,                //system datetime
    VM_SETTING_SCHEDULE_POWER_ON_OFF,   //system schedule power on/off
    VM_SETTING_NETWORK_TIME_AUTO_UPDATE,//network time auto update on/off
    VM_SETTING_SIM_GPRS_TRANSFER_PREFER,//call perfer or data prefer
    VM_SETTING_GPS_SYNC_TIME,//GPS sync time setting
    VM_SETTING_ENUM_NUM
}vmsettingModuleTypes;

/*Operation Type Enum for Each module*/

/*
**Operation type for SETTING_CELLULAR_GPRS_SERVICE
*/
typedef enum
{
    VM_OPERATION_GPRS_SERVICE_ON,         //GPRS on
    VM_OPERATION_GPRS_SERVICE_OFF,        //GPRS off
    VM_OPERATION_GPRS_SERVICE_GET_STATUS, //get current GPRS status
    VM_OPERATION_GPRS_SERVICE_NUM
}vmoperationTypesGPRSSrv;


/*
**Operation type for SETTING_CELLULAR_GPRS_ROAMING
*/
typedef enum
{
    VM_OPERATION_GPRS_ROAMING_ON,        //GPRS roaming on
    VM_OPERATION_GPRS_ROAMING_OFF,       //GPRS roaming off
    VM_OPERATION_GPRS_ROAMING_GET_STATUS,//get current roaming status
    VM_OPERATION_GPRS_ROAMING_NUM
}vmoperationTypesGPRSRoaming;

/*
**Operation type for SETTING_CELLULAR_CONNECTION_SIM
*/
typedef enum
{
    VM_OPERATION_CONNECTION_SIM_SET,             //set currently connection SIM id, example SIM1 or SIM2
    VM_OPERATION_CONNECTION_SIM_GET_CURRENT_SIM, //get currently connection SIM id
    VM_OPERATION_CONNECTION_SIM_NUM
}vmoperationTypesGPRSConnectionSIM;

/*
**Operation type for SETTING_NETWORK_ACCOUNTS
*/
typedef enum
{
    VM_OPERATION_NETWORK_ACCOUNTS_ADD,             //add network accounts
    VM_OPERATION_NETWORK_ACCOUNTS_EDIT,            //edit network accounts
    VM_OPERATION_NETOWRK_ACCOUNTS_DELETE,          //delete network accounts
    VM_OPERATION_NETWORK_ACCOUNTS_GET_ACCOUNT_LIST,//get exist accounts list
    VM_OPERATION_NETWORK_ACCOUNTS_NUM
}vmoperationTypesNetworkAccounts;

/*
**Operation type for SETTING_DATETIME
*/
typedef enum
{
    VM_OPERATION_DATETIME_SET,    //set system datetime
    VM_OPERATION_DATETIME_GET,    //get system datetime
    VM_OPERATION_DATETIME_NUM
}vmoperationTypesDatetime;

/*
**Operation type for SETTING_SCHEDULE_POWER_ON_OFF
*/
typedef enum
{
    VM_OPERATION_SET_SCHEDULE_POWER_ON_STATUS,  //switch schedule power on to on/off
    VM_OPERATION_SET_SCHEDULE_POWER_OFF_STATUS, //switch schedule power off to on/off
    VM_OPERATION_SCHEDULE_POWER_ON_OFF_NUM
}vmoperationTypesSchedulePowerOnOff;

/* the sturct for setting enum VM_SETTING_SCHEDULE_POWER_ON_OFF and vmoperationTypesSchedulePowerOnOff */
typedef struct
{
    VMUINT8 type;
    VMUINT8 status;
    VMUINT8 hour;
    VMUINT8 min;
}vm_spof_struct;


/*
**Operation type for SETTING_NETWORK_TIME_AUTO_UPDATE
*/
typedef enum
{
    VM_OPERATION_NETWORK_TIME_ON,  //set network time auto update on
    VM_OPERATION_NETWORK_TIME_OFF, //set network time auto update off
    VM_OPERATION_NETWORK_TIME_GET_STATUS, //get network time auto update status
    VM_OPERATION_NETWORK_TIME_NUM
}vmoperationTypesNetowrkTime;

/*
**Operation type for SETTING_SIM_GPRS_TRANSFER_PREFER
*/
typedef enum
{
    VM_OPERATION_SIM_GPRS_TRANSFER_SET_CALL_PREFER, //set GPRS transfer call prefer
    VM_OPERATION_SIM_GPRS_TRANSFER_SET_DATA_PREFER, //set GPRS transfer data prefer
    VM_OPERATION_SIM_GPRS_TRANSFER_GET_STATUS,    //get GPRS transfer status
    VM_OPERATION_SIM_GPRS_TRANSFER_PREFER_NUM
}vmoperationTypesGPRSTranferPref;


/*
**OPERATION TYPE FOR 
*/
typedef enum
{
    VM_OPERATION_DATETIME_GPS_TIME_SYNC_ON, //ALLOW GPS TO UPDATE TIME
    VM_OPERATION_DATETIME_GPS_TIME_SYNC_OFF,//DEFUSE GPS TO UPDATE TIME
    VM_OPERATION_DATETIME_GPS_TIME_SYNC_GET,//GET GPS UPDATED TIME
    VM_OPERATION_DATETIME_GPS_TIME_SYNC_NUM
}vmoperationTypesDTGPSSyncTime;



/*
** Data Account profile sim type enum
*/
typedef enum
{
    VM_SRV_DTCNT_SIM_TYPE_NONE = 0,
    VM_SRV_DTCNT_SIM_TYPE_1,       /*SIM 1*/
    VM_SRV_DTCNT_SIM_TYPE_2,       /*SIM 2*/
    VM_SRV_DTCNT_SIM_TYPE_3,       /*SIM 2*/
    VM_SRV_DTCNT_SIM_TYPE_4,       /*SIM 4*/
    VM_SRV_DTCNT_SIM_TYPE_TOTAL
} vm_srv_dtcnt_sim_type_enum;


/* Data Account bearer enum */
typedef enum
{
    VM_SRV_DTCNT_BEARER_UNKNOWN    = 0, /* unknown type profile */
    VM_SRV_DTCNT_BEARER_CSD        = 1, /* For csd type profile */
    VM_SRV_DTCNT_BEARER_GPRS       = 2, /* For GPRS type profile */
    VM_SRV_DTCNT_BEARER_WIFI       = 4, /* For WIFI type profile */
    VM_SRV_DTCNT_BEARER_TOTAL
} vm_srv_dtcnt_bearer_enum;

/* Data Account services result enum */
typedef enum
{
    VM_SRV_DTCNT_RESULT_SUCCESS    = 0,    /* success */
    VM_SRV_DTCNT_RESULT_FAILED,            /* general failed case */
    VM_SRV_DTCNT_RESULT_PROCESSING,        /* processing state implies Event notify */
    VM_SRV_DTCNT_RESULT_STATE_ERROR,       /* service status error */
    VM_SRV_DTCNT_RESULT_INVALID_INPUT,     /* the input parameter is invalid */
    VM_SRV_DTCNT_RESULT_ABORTED,           /* the process is aborted */
    VM_SRV_DTCNT_RESULT_TERMINATED,        /* the process is terminated */
    VM_SRV_DTCNT_RESULT_ONE_STORE_EXISTS,  /* currently only support one store */
    VM_SRV_DTCNT_RESULT_STORE_NOT_COMMIT,  /* store doesn't be config commited before */
    VM_SRV_DTCNT_RESULT_INVALID_STORE,     /* store invalid */
    VM_SRV_DTCNT_RESULT_STORE_FULL,        /* reach maximum profile storage */
    VM_SRV_DTCNT_RESULT_READ_ONLY,         /* can't delete or update read_only profile */
    VM_SRV_DTCNT_RESULT_FIRST_BOOTUP,      /* first bootup rerurn code for store open */
    VM_SRV_DTCNT_RESULT_RESET_FACTORY,     /* the data base sim profiles folder is deleted */
    VM_SRV_DTCNT_RESULT_FS_ERROR,          /* the database file system error */
    VM_SRV_DTCNT_RESULT_IGNORE,
    VM_SRV_DTCNT_RESULT_TOTAL
} vm_srv_dtcnt_result_enum;

/* this struct is designed for Data account store profile content operations*/
typedef struct
{
    void *prof_data;                     /* profile data pointer */
    VMUINT32 prof_fields;                /* profile enabled attributes */
    vm_srv_dtcnt_bearer_enum prof_type;  /* profile bearer type */
} vm_srv_dtcnt_store_prof_data_struct;

/*****************************************************************************
 *
 * FUNCTION
 *  vm_srv_dtcnt_store_delete_cb_func_ptr
 * DESCRIPTION
 *  store account deleting callback function
 * PARAMETERS
 *  user_data       :   [IN]    APP's piggyback user_data
 *  deleting_acc_id :   [IN]    the account id to be deleted
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_srv_dtcnt_store_delete_cb_func_ptr) (VMUINT32 deleting_acc_id, void *user_data);

/* Data Account profile type enum */
typedef enum
{
    VM_SRV_DTCNT_PROF_TYPE_USER_CONF = 0,  /* user configured account */
    VM_SRV_DTCNT_PROF_TYPE_OTA_CONF,       /* OTA configured account */
    VM_SRV_DTCNT_PROF_TYPE_FACTORY_CONF,   /* Factory default */
    VM_SRV_DTCNT_PROF_TYPE_SIM_PROF,       /* SIM provisioning account */
    VM_SRV_DTCNT_PROF_TYPE_DM_CONF,        /* DM configured account */
    VM_SRV_DTCNT_PROF_TYPE_TOTAL
} vm_srv_dtcnt_prof_acc_type_enum;

/* this struct is designed for Data account store query operation */
typedef struct
{
    vm_srv_dtcnt_sim_type_enum         sim_qry_info;       /* sim query data for filter settings (used if OR'd set in filters) */
    vm_srv_dtcnt_bearer_enum           bearer_qry_info;    /* bearer query data for filter settings (used if OR'd set in filters) */
    vm_srv_dtcnt_prof_acc_type_enum    acc_type_info;      /* account type query data for filter settings (used if OR'd set in filters) */
    VMUINT16                           filters;            /* query settings (OR'd operation by srv_dtcnt_store_qry_type_enum) */
    VMUINT64                           app_type;           /* app_type query data for filter settings (used if OR'd set in filters) */
} vm_srv_dtcnt_store_prof_qry_filter_struct;

/* this struct is designed for Data account store query operation */
#define VM_SRV_DTCNT_STORE_IDS_QRY_MAX_SIZE    (64)		/* maximum size of ids query id buffer */
typedef struct
{
    vm_srv_dtcnt_store_prof_qry_filter_struct  qry_info;   /* query information from DA APP */
    VMUINT32 ids[VM_SRV_DTCNT_STORE_IDS_QRY_MAX_SIZE];    /* account id list query result */
    VMUINT8  num_ids;                                /* the number of queried id list */
} vm_srv_dtcnt_store_prof_qry_struct;

/* srv dtcnt add prof cntx struct */
typedef struct
{
    vm_srv_dtcnt_store_prof_data_struct *prof;
    VMUINT32 *acc_prof_id;
    vm_srv_dtcnt_result_enum operate_result;
} vm_srv_dtcnt_add_prof_cntx_struct;

/* srv dtcnt update prof cntx */
typedef struct
{
    vm_srv_dtcnt_store_prof_data_struct *prof;
    VMUINT32 acc_prof_id;
    vm_srv_dtcnt_result_enum operate_result;
} vm_srv_dtcnt_update_prof_cntx_struct;

/* srv dtcnt delete prof cntx */
typedef struct
{
    VMUINT32 acc_prof_id;
    VMBOOL force_exec;
    void *user_data;
    vm_srv_dtcnt_store_delete_cb_func_ptr callback;
    vm_srv_dtcnt_result_enum operate_result;
}vm_srv_dtcnt_delete_prof_cntx_struct;

/* srv dtcnt get prof ids cntx*/
typedef struct
{
    vm_srv_dtcnt_store_prof_qry_struct *qry;
    vm_srv_dtcnt_result_enum operate_result;
} vm_srv_dtcnt_get_prof_ids_cntx_struct;


/* time struct for setting srv */
typedef struct
{
    VMUINT16 nYear;
    VMUINT8 nMonth;
    VMUINT8 nDay;
    VMUINT8 nHour;
    VMUINT8 nMin;
    VMUINT8 nSec;
    VMUINT8 DayIndex; /* 0=Sunday */
} vm_time_struct;


/* spof nvram struct for mre */
typedef struct
{
    VMBYTE Type;
    VMBYTE Status;
    VMBYTE Hour;
    VMBYTE Min;
} vm_spof_nvram_struct;


/* nitz status */
typedef enum
{
    VM_SRV_NITZ_OFF,
    VM_SRV_NITZ_CONFIRM_FIRST,
    VM_SRV_NITZ_ON
}vm_srv_nitz_type_enum;


typedef enum
{
    VM_SIM_NONE = 0, /* No bit-wise operation for none case */
    VM_SIM1 = 0x0001,
    VM_SIM2 = 0x0002,
    VM_SIM3 = 0x0004,
    VM_SIM4 = 0x0008,
    VM_SIM_END_OF_ENUM
}vm_setting_sim_enum;

typedef struct
{
    /* Event id */
    VMUINT16 evt_id; 
    /* Event structure size */
    VMUINT16 size; 
    /* User data pointer */
    void *user_data;
}vm_mmi_event_struct;

/* vm mmi proc function type */
typedef VMINT (*vm_mmi_proc_func) (vm_mmi_event_struct *param);

/* srv gprs tranfer cntx */
typedef struct
{
    vm_setting_sim_enum sim_type;
    vm_mmi_proc_func ptr_func;
    void *user_data;
} vm_srv_gprs_tranfer_cntx_struct;


//Error code
/*ok means setting apply done*/
#define VM_SETTING_RESULT_OK 0
/*fail means system error when apply setting*/
#define VM_SETTING_RESULT_FAIL -1
/*would block means current setting is a asynchronous mode, result and data will notify to callback*/
#define VM_SETTING_RESULT_WOULD_BLOCK -2
/*invalid means wrong type and operation combination*/
#define VM_SETTING_RESULT_INVALID -3

/*Interface and callback function*/

/*****************************************************************************
 *
 * FUNCTION
 *  srv_setting_result_callback
 * DESCRIPTION
 *  setting result callback funtion, app should provide a callback funtion when apply
 *  settings, and this function will be called if current setting is asynchronous mode
 * PARAMETERS
 *  result:             [IN] Operation result
 *  user_data:          [IN] User data
 * RETURN VALUES
 *  void
 *****************************************************************************/
typedef void(* vm_setting_srv_result_callback)(VMINT32 result, void *user_data);


/*vm_setting_srv_enum*/
typedef enum
{
    VM_SETTING_SRV_NO_ERROR                          = 0,//operator suceed
    VM_SETTING_SRV_GET_MEM_FAIL                      = -1,//memory is not enough
    VM_SETTING_SRV_ERROR_OF_RES                      = -2,// out of resource
    VM_SETTING_SRV_ERROR_INVALID_ID                  = -3, //Invalid res id
    VM_SETTING_SRV_ERROR_OF_PROCESS                  = -4,//process error
    VM_SETTING_SRV_ERR_OTHERS                      = -65535,// other errors
    VM_SETTING_SRV_ERR_END                        = -65536//end mark
}vm_setting_srv_enum;


/*****************************************************************************
 *
 * FUNCTION
 *  vm_settings_srv_command
 * DESCRIPTION
 *  General setting command interface, which is use to set/get platfrom related settings
 *  
 * PARAMETERS
 *  type:               [IN] setting type, refer enum settingModuleTypes
 *  user_data:          [IN] setting operation, refer to setting operation enum for each setting type
 *  in:                 [IN] in parameters, if you use set/add/edit/delete related operaitons, 
 *                           please provide in para
 *  out:                [OUT] out data, if you use get/query related operations, please provide out para
 *  srv_setting_result_callback: [IN] setting result callback funtion, will be called by 
 *                               system when current setting is asynchronous mode
 * RETURN VALUES
 *  void
 *
 * EXAMPLE
 * <code>
 * Sample Code1
 *   //switch on mobile data connection.
 *   VMINT32 result = VM_SETTING_SRV_NO_ERROR;
 *   result = vm_setting_srv_command(VM_SETTING_CELLULAR_GPRS_SERVICE, VM_OPERATION_GPRS_SERVICE_ON, NULL, NULL, NULL, NULL);
 *   if (result == VM_SETTING_RESULT_OK)
 *	 {
 *		 vm_log_debug("This case is passed");
 *	 }
 *	 else if (result == VM_SETTING_RESULT_INVALID)
 *	 {
 *		 vm_log_debug("This case is not support");
 *	 }
 *	 else
 *	 {
 *		 vm_log_debug("This case is failed.");
 *	 }
 *
 * Sample Code2
 *   //set system time
 *   VMINT32 result = VM_SETTING_SRV_NO_ERROR;
 *	 vm_time_struct get_time, set_time;
 *   vm_setting_srv_command(VM_SETTING_DATETIME, VM_OPERATION_DATETIME_GET, NULL, &get_time, NULL, NULL);
 *	 set_time = get_time;
 *	 set_time.nHour = 12;
 *	 set_time.nMin = 14;
 *	 result = vm_setting_srv_command(VM_SETTING_DATETIME, VM_OPERATION_DATETIME_SET, &set_time, NULL, NULL, NULL);
 *   if (result == VM_SETTING_RESULT_OK)
 *	 {
 *		vm_log_debug("This case is passed");
 *	 }
 *	 else if (result == VM_SETTING_RESULT_INVALID)
 *	 {
 *		 vm_log_debug("This case is not support");
 *	 }
 *	 else
 *	 {
 *		 vm_log_debug("This case is failed");
 *	 }
 *
 * Sample code3
 * //schedule power on
 * vm_spof_struct spof_data_on;
 * VMINT return_result = 0;
 * spof_data_on.type = 0;
 * spof_data_on.status = 1;//enable is 1,disable is 0
 * spof_data_on.hour = 12;
 * spof_data_on.min = 10;
 * return_result  = vm_setting_srv_command(VM_SETTING_SCHEDULE_POWER_ON_OFF, VM_OPERATION_SET_SCHEDULE_POWER_ON_STATUS, &spof_data_on, NULL, NULL, NULL);
 * vm_log_debug(¡°return result is %d¡±, return_result);
 *
 * //schedule power off
 * vm_spof_struct spof_data_off;
 * VMINT return_result = 0;
 * spof_data_off.type = 1;
 * spof_data_off.status = 1;//enable is 1,disable is 0
 * spof_data_off.hour = 12;
 * spof_data_off.min = 10;
 * return_result  = vm_setting_srv_command(VM_SETTING_SCHEDULE_POWER_ON_OFF, VM_OPERATION_SET_SCHEDULE_POWER_OFF_STATUS, &spof_data_off, NULL, NULL, NULL);
 * vm_log_debug(¡°return result is %d¡±, return_result);
 * </code>
 *****************************************************************************/
VMINT32 vm_setting_srv_command(VMUINT16 type, 
								VMUINT16 operation, 
								void *in, 
								void *out, 
								vm_setting_srv_result_callback cb,
								void *user_data);



typedef void (*vm_srv_sensor_hr_data_cb)(void *sensor_data); 
typedef void (*vm_srv_sensor_acc_data_cb)(void *acc_x, void *acc_y, void *acc_z); 

void vm_srv_sensor_hr_data_rigister_cb(vm_srv_sensor_hr_data_cb event_hdlr);
void vm_srv_sensor_acc_data_rigister_cb(vm_srv_sensor_acc_data_cb event_hdlr);

typedef void (*vm_idle_swatch_pedometer_cb)(void *data);
void vm_idle_swatch_pedometer_register_callback(vm_idle_swatch_pedometer_cb event_hdlr);
void vm_switch_bt_call(VMBOOL on);
VMBOOL vm_is_bt_call_allowed(void);

#ifdef __cplusplus
}
#endif 

#endif /* VMSETTINGS_SDK_H */

