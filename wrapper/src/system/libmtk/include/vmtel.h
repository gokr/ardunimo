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

#ifndef VMTEL_SDK_H
#define VMTEL_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"


typedef enum
{
	VM_CALLOUT_ERR_STATE = -7,	/* application is not foreground state */
	VM_CALLOUT_ERR_NO_SIM ,	 	/* No SIM */
	VM_CALLOUT_ERR_FLIGHT, 		/* flight mode */
	VM_CALLOUT_ERR_BUSY,		/* device busy */
	VM_CALLOUT_ERR_PHONE_NUM,	/* destination number error */
	VM_CALLOUT_ERR_PROCESS,		/* process error */
	VM_CALLOUT_ERR_NO_RES,		/* resource unavailable*/
	VM_CALLOUT_NO_ERR
}vm_callout_error_t;

typedef enum
{
	VM_CALLOUT_IDEL = 0,
	VM_CALLOUT_BUSY
}vm_callout_status_t;

/*****************************************************************************
* <GROUP  CallBackFunctions>        
*
 * FUNCTION
 *    VM_CALLOUT_RESPONSE_T
 * DESCRIPTION
 *  callback function of callout 
 * PARAMETERS
 *  VMWSTR :  [IN]  destination phone number string encoding with UCS2 format
 *  VMINT :  [IN] calling result. 
*****************************************************************************/
typedef void (*VM_CALLOUT_RESPONSE_T)(VMWSTR, VMINT);

/*****************************************************************************
* FUNCTION
 *    vm_callout
 * DESCRIPTION
 *  make call. 
 *  Application can use this funtion only during foreground running and END key
 *  will be handled by call application for hang up calling firstly.
 * PARAMETERS
 *  phnum : [IN]  destination phone number string encoding with UCS2 format.
*****************************************************************************/
void vm_callout(VMWSTR phnum);

/*****************************************************************************
* FUNCTION
 *    vm_callout
 * DESCRIPTION
 *  make call. 
 *  Application can use this funtion only during foreground running and END key
 *  will be handled by call application for hang up calling firstly.
 * PARAMETERS
 *  phnum : [IN]  destination phone number string encoding with UCS2 format.
 *  callback : [IN]  callback function
* RETURNS
 *  refer to vm_callout_error_t
*****************************************************************************/
VMINT vm_callout_ex(VMWSTR phnum, VM_CALLOUT_RESPONSE_T callback);



/*****************************************************************************
 * FUNCTION
 *  vm_dialer_launch
 * DESCRIPTION
 *  1. Launch a dialer
 * PARAMETERS
 *  phone_num : [IN]    phone num, can be NULL
 * RETURNS
 *  0:success
 *****************************************************************************/
VMINT vm_dialer_launch(VMWSTR phone_num);


/**
 *Open URL successfully
 */
#define VM_OPEN_WAP_URL_SUCCESS				(0)
/**
 * Parameter error
 */
#define VM_OPEN_WAP_URL_ERROR_PARAM			(-1)
/**
 * No WAP service
 */
#define VM_OPEN_WAP_URL_NO_SERVICE			(-2)
/**
 * Process not during foreground running
 */
#define VM_OPEN_WAP_URL_ERROR_STATUS		(-3)

/*****************************************************************************
* FUNCTION
 *    vm_open_wap_url
 * DESCRIPTION
 *  Lauch WAP brower and go to specified address. 
 * PARAMETERS
 *  url : [IN]  WAP address.
 * RETURNS
 *  result of Open browser URL
 * RETURN VALUES                                      
 *  VM_OPEN_WAP_URL_SUCCESS : Open URL successfully.
 *  VM_OPEN_WAP_URL_ERROR_PARAM : Parameter error.
 *  VM_OPEN_WAP_URL_NO_SERVICE : No WAP service.
 *  VM_OPEN_WAP_URL_ERROR_STATUS : Process not during foreground running.
 *
*****************************************************************************/
VMINT vm_open_wap_url(VMWSTR url);

typedef enum
{
    VM_IVR_FAIL = -1,//vm_ivr_call fail
    VM_IVR_CALLED_OUT, //already called out
    VM_IVR_INTERRUPT, //end by interrupt (incoming call)
    VM_IVR_CALL_END, //call end normally
}vm_ivr_status_enum;

typedef struct
{
    vm_ivr_status_enum status;
    void* user_data;
}ivr_callback_data;

typedef void (*vm_ivr_cb)(ivr_callback_data* data);

typedef struct
{
    VMWSTR   phone_num; //destination phone number
    VMINT   sim_card; //sim card: 1,2,3,4...
    vm_ivr_cb callback;
    void*     user_data;
}vm_ivr_call_data;

/*****************************************************************************
* FUNCTION
 *    vm_ivr_call
 * DESCRIPTION
 *   start call in background
 * PARAMETERS
 *  vm_ivr_call_data : [IN]  
 * RETURNS
 *  0 means success, others fail
*****************************************************************************/
VMINT vm_ivr_call(vm_ivr_call_data* data);

/*****************************************************************************
* FUNCTION
 *    vm_ivr_dial_number
 * DESCRIPTION
 *   dial number after vm_ivr_call invoked
 * PARAMETERS
 *  number : [IN]  number to dial. e.g. "3";
 * RETURNS
 *  0 means success, others fail
*****************************************************************************/
VMINT vm_ivr_dial_number(VMCHAR number);

/*****************************************************************************
* FUNCTION
 *    vm_ivr_end
 * DESCRIPTION
 *   end call start by vm_ivr_call
 * PARAMETERS
 *  
 * RETURNS
 *  0 means success, others fail
*****************************************************************************/
VMINT vm_ivr_end(void);


/* Maximum number length */
#define VM_UCM_MAX_NUM_URI_LEN (41)

/* Maximum error message length */
#define VM_UCM_MAX_ERR_MSG_LEN (50)

/* Maximum IP number length */
#define VM_UCM_MAX_IP_NUMBER_LEN (10)

/* UCM error cause enum */
typedef enum
{
    VM_UCM_RESULT_OK, /* OK */
    VM_UCM_RESULT_UNSPECIFIED_ERROR, /* Unspecified error */
    VM_UCM_RESULT_CANCEL, /* Cancel */
    VM_UCM_RESULT_USER_ABORT, /* User abort */
    VM_UCM_RESULT_ACTION_NOT_ALLOWED, /* Action not allowed */
    VM_UCM_RESULT_NOT_ALLOWED_TO_DIAL, /* Not allowed to dial */
    VM_UCM_RESULT_NOT_ALLOWED_TO_ACCEPT, /* Not allowed to accept */
    VM_UCM_RESULT_NO_ACTIVE_CALL, /* No active call */
    VM_UCM_RESULT_CALLED_PARTY_BUSY, /* Called party busy */
    VM_UCM_RESULT_NETWORK_NOT_AVAILABLE, /* Network not available */
    VM_UCM_RESULT_CALLED_PARTY_NOT_ANSWERED, /* Called party not answered */
    VM_UCM_RESULT_SOS_NUMBER_ONLY, /* SOS number only */
    VM_UCM_RESULT_INVALID_NUMBER, /* Invalid number */
    VM_UCM_RESULT_EMPTY_NUMBER, /* Empty number */
    VM_UCM_RESULT_SOS_CALL_EXISTS, /* Exist SOS call */
    VM_UCM_RESULT_PREFERRED_MODE_PROHIBIT, /* Preferred mode prohibit */
    VM_UCM_RESULT_FLIGHT_MODE_PROHIBIT, /* Flight mode prohibit */
    VM_UCM_RESULT_LOW_BATTERY, /* Low battery */
    VM_UCM_RESULT_UCM_BUSY, /* Busy */
    VM_UCM_RESULT_VT_FALLBACK, /* VT fallback */
    VM_UCM_RESULT_END_OF_ENUM /* end of the enum */
} vm_ucm_result_enum;



/* Indication opcode enum */
typedef enum
{
	VM_UCM_INCOMING_CALL_IND = 0,//incomming
	VM_UCM_OUTGOING_CALL_IND, //outcomming
	VM_UCM_CONNECT_IND, // answered
    VM_UCM_CALL_END, //call end normally
}vm_ucm_ind_opcode_enum;

/* Call type enum */
typedef enum
{
    VM_UCM_VOICE_CALL_TYPE         = 0x0001, /* SIM1 voice call type */
    VM_UCM_VOICE_CALL_TYPE_SIM2    = 0x0020, /* SIM2 voice call type */
    VM_UCM_VOICE_CALL_TYPE_SIM3    = 0x0200, /* SIM3 voice call type */
    VM_UCM_VOICE_CALL_TYPE_SIM4    = 0x1000, /* SIM4 voice call type */
} vm_ucm_call_type_enum;

/* Call id struct, should be unique */
typedef struct
{
    vm_ucm_call_type_enum call_type; /* Call type */
    VMUINT16 group_id; /* group id */
    VMUINT16 call_id; /* call id*/
} vm_ucm_id_info_struct;

typedef struct
{
    vm_ucm_id_info_struct uid_info; /* Call id */
    VMUINT8 num_uri[VM_UCM_MAX_NUM_URI_LEN + 1]; /* Number, ascii */
} vm_ucm_incoming_call_ind_struct;


/* Outgoing call indication struct */
typedef struct
{
    vm_ucm_id_info_struct uid_info; /* Call id */
    VMUINT8 num_uri[VM_UCM_MAX_NUM_URI_LEN + 1]; /* Number, ascii */
} vm_ucm_outgoing_call_ind_struct;

/* Answer indication struct */
typedef struct
{
    vm_ucm_id_info_struct uid_info; /* Call id */
}vm_ucm_connect_ind_struct;

/* Listen call event callback structure */
typedef struct
{
    vm_ucm_ind_opcode_enum   type_op; // vm_call_type incomming ,outcomming
    void*   data; //data of the event
}vm_call_listener_data;


typedef void (*vm_call_listener_func)(vm_call_listener_data* data);



/* Action opcode enum */
typedef enum
{
    VM_UCM_NO_ACT = 0, /* No action */
    VM_UCM_DIAL_ACT, /* Dial action, vm_ucm_dial_act_req_struct, vm_ucm_act_rsp_struct*/
    VM_UCM_ACCEPT_ACT, /* Accept action, vm_ucm_single_call_act_req_struct, vm_ucm_act_rsp_struct*/
    VM_UCM_HOLD_ACT, /* Hold action, vm_ucm_single_group_act_req_struct, vm_ucm_act_rsp_struct*/
    VM_UCM_END_SINGLE_ACT, /* End single action, vm_ucm_single_call_act_req_struct, vm_ucm_act_rsp_struct */
}vm_call_action_type;


/* action struct VM_UCM_DIAL_ACT */
typedef struct
{
    vm_ucm_call_type_enum call_type; /* Call type */
    VMUINT16 num_uri[VM_UCM_MAX_NUM_URI_LEN + 1]; /* Number, ucs2 */
    VMUINT8 module_id; /* Initiate module id, set 0 as default */
    VMBOOL is_ip_dial; /* IP dial, currently only for GSM&3G, set 0 as default */
    void *phb_data; /* Bypass phonebook data for call service to query caller info. set NULL as default*/
} vm_ucm_dial_act_req_struct;

/* action struct VM_UCM_ACCEPT_ACT & VM_UCM_END_SINGLE_ACT */
typedef struct
{
    vm_ucm_id_info_struct action_uid; /* Call id */
} vm_ucm_single_call_act_req_struct;

/* action struct VM_UCM_HOLD_ACT */
typedef struct
{
    vm_ucm_call_type_enum call_type; /* Call type */
    VMUINT16 action_group; /* Group id */
} vm_ucm_single_group_act_req_struct;




/* Action CALLBACK structure */
typedef struct
{
    vm_ucm_result_enum result; /* Result */
    VMUINT16 error_msg[VM_UCM_MAX_ERR_MSG_LEN + 1]; /* Recommand error message, ucs2 */
} vm_ucm_result_info_struct;

typedef struct
{
    vm_ucm_result_info_struct result_info; /* Result */
    VMBOOL no_counter; /* Start to count duration or not, only for accept action */
} vm_ucm_act_rsp_struct;

typedef struct
{
    vm_call_action_type type_act;           // action type accept ,hold on, end
    vm_ucm_act_rsp_struct data_act_rsp;		//data of the action callback struct
    void*   userdata;	                    //userdata of APP
}vm_call_actions_callback_data;

typedef void (*vm_call_actions_func)(vm_call_actions_callback_data* data);



/* Action structure */
typedef struct
{
    vm_call_action_type   type_act;		// action type accept ,hold on, end
    void*   data_act;					//data of the action struct
    void*   userdata;				//user data of APP
    vm_call_actions_func callback;	//callback function of the action
}vm_call_actions_data;



/*****************************************************************************
* FUNCTION
 *    vm_call_reg_listener
 * DESCRIPTION
 *  APP use this function to register a callback function to listen call events
 * PARAMETERS
 *  func : [IN]  callback functions, reference vm_call_listener_func
* RETURNS
 *  0 is success
*****************************************************************************/
VMINT vm_call_reg_listener(vm_call_listener_func func);


/*****************************************************************************
* FUNCTION
 *    vm_call_actions
 * DESCRIPTION
 *  APP use this function to control call progress, accept a incoming call, 
 *  or hold on/ hung up a going call
 * PARAMETERS
 *  data : [IN]  Action command , please reference vm_call_actions_data
* RETURNS
 *  0 is success
*****************************************************************************/
VMINT vm_call_actions(const vm_call_actions_data* data);

#ifdef __cplusplus
}
#endif

#endif /* VMTEL_SDK_H */
