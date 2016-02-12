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

#ifndef VMSMS_SDK_H_
#define VMSMS_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

#define VM_SMS_MSG_CONTENT_LEN             500

#define VM_SMS_MAX_ADDR_LEN            21

#define VM_SMS_MSG_INFO_CONTENT_LEN   (61 + 19)

#define  VM_SMS_SUPPORT_SYN_SCA   1
#define  VM_SMS_NOT_SUPPORT_SYN_SCA   -2

typedef enum
{
    VM_SMS_IDENTIFY_ERROR = -4,
    VM_SMS_MIBR_NOT_IN_PROCESS_SPACE = -3,
    VM_SMS_MIBR_ERROR = -2,
    VM_SMS_REQ_ERROR = -1,             /*SMS operation request failure*/
    VM_SMS_REQ_NO_ERROR,                /*SMS operation request succeed*/
    VM_SMS_REQ_CALLBACK_REGISTERED
} vm_sms_error_enum;


typedef enum
{
    VM_SMS_BOX_INBOX        = 0x01,                 /*inbox*/
    VM_SMS_BOX_OUTBOX       = 0x02,                 /*sent box*/
    VM_SMS_BOX_DRAFTS       = 0x04,                 /*draft box*/
    VM_SMS_BOX_UNSENT       = 0x08,                 /*to be sent box*/
    VM_SMS_BOX_SIM          = 0x10,                 /*sim card*/
    VM_SMS_BOX_ARCHIVE      = 0x20,                 /*archive box */
    
    VM_SMS_BOX_RESERVED     = 0x40		 
  
} vm_sms_box_enum;

/* Message Folder Type */
typedef enum
{
    VM_SMS_FOLDER_DEFAULT,          /* default folder */
    VM_SMS_FOLDER_ARCHIVE           /* archive folder */
} vm_sms_folder_enum;

/* Message Storage Type */
typedef enum
{

    VM_SMS_STATUS_UNREAD       = 0x01,        /*unread*/
    VM_SMS_STATUS_READ         = 0x02,        /*read*/
    VM_SMS_STATUS_SENT         = 0x04,        /*sent*/
    VM_SMS_STATUS_UNSENT       = 0x08,        /*to be sent*/
    VM_SMS_STATUS_DRAFT        = 0x10,        /*draft*/
    
    VM_SMS_STATUS_UNSUPPORTED  = 0x20   
} vm_sms_status_enum;


/* Message Type Indication */
typedef enum
{
   VM_SMS_MTI_DELIVER          = 0x00,      /* deliver type */
   VM_SMS_MTI_DELIVER_REPORT   = 0x00,      /* deliver report type */
   VM_SMS_MTI_SUBMIT           = 0x01,      /* submit type */
   VM_SMS_MTI_SUBMIT_REPORT    = 0x01,      /* submit report type */
   VM_SMS_MTI_STATUS_REPORT    = 0x02,      /* status report type */
   VM_SMS_MTI_COMMAND          = 0x02,      /* command type */
   VM_SMS_MTI_RESERVED         = 0x03
} vm_sms_mti_enum;


/* Message Storage Type */
typedef enum
{
    VM_SMS_STORAGE_ME,              /*phone*/
    VM_SMS_STORAGE_SIM,             /*SIM card*/

    VM_SMS_STORAGE_UNSPECIFIC
} vm_sms_storage_enum;

typedef enum
{
    VM_MMI_SIM_1 = 0x0001,       /* SIM 1 */
    VM_MMI_SIM_2 = 0x0002,      /* SIM 2 */
    VM_MMI_SIM_3 = 0x0004,       /* SIM 1 */
    VM_MMI_SIM_4 = 0x0008      /* SIM 2 */
  }vm_sim_enum;

/* network type*/
typedef enum
{
    VM_MMI_GSM = 0x0100     /* GSM network */
  } vm_network_enum;

/* SIM Card Type */
typedef enum
{
    VM_SMS_SIM_1 = VM_MMI_GSM | VM_MMI_SIM_1,   /* sim1 */
    VM_SMS_SIM_2 = VM_MMI_GSM | VM_MMI_SIM_2,  /* sim2 */
    VM_SMS_SIM_3 = VM_MMI_GSM | VM_MMI_SIM_3,  /* SIM Card 3, the SIM card inserted in the slot 3 */
    VM_SMS_SIM_4 = VM_MMI_GSM | VM_MMI_SIM_4,  /* SIM Card 4, the SIM card inserted in the slot 4 */
    VM_SMS_TOTAL
} vm_sms_sim_enum;


/* Message Class Type */
typedef enum
{
   VM_SMS_CLASS_0  = 0x00,      /* class 0 */
   VM_SMS_CLASS_1  = 0x01,      /* class 1 */
   VM_SMS_CLASS_2  = 0x02,      /* class 2 */
   VM_SMS_CLASS_3  = 0x03       /* class 3 */
} vm_sms_class_enum;


/* Validity-Period */
typedef enum
{
    VM_SMS_VP_1_HR     = 11,      /* 1 hour */          
    VM_SMS_VP_6_HR     = 71,      /* 6 hours */ 
    VM_SMS_VP_12_HR    = 143,      /* 12 hours */ 
    VM_SMS_VP_24_HR    = 167,      /* 24 hours */ 
    VM_SMS_VP_72_HR    = 169,      /* 72 hours */
    VM_SMS_VP_1_WEEK   = 173,      /* 1 week */
    VM_SMS_VP_MAX      = 255
} vm_sms_vp_enum;


/* SMS DCS */
typedef enum
{
    VM_SMS_DCS_7BIT        = 0x00, /* GSM 7 bit default alphabet */
    VM_SMS_DCS_8BIT        = 0x04, /* 8 bit data */
    VM_SMS_DCS_UCS2        = 0x08, /* UCS2 (16bit) */
    VM_SMS_DCS_RESERVED    = 0x0c
} vm_sms_dcs_enum;


/* Protocol Identifier */
typedef enum
{
    VM_SMS_PID_DEFAULT             = 0x00, /* Text SMS */
    VM_SMS_PID_EMAIL               = 0x32, /* Internet Electronic Mail */

    VM_SMS_PID_TYPE_0              = 0x40, /* Short Message Type 0 */
    VM_SMS_PID_REPLACE_TYPE_1      = 0x41, /* Replace Short Message Type 1 */
    VM_SMS_PID_REPLACE_TYPE_2      = 0x42, /* Replace Short Message Type 2 */
    VM_SMS_PID_REPLACE_TYPE_3      = 0x43, /* Replace Short Message Type 3 */
    VM_SMS_PID_REPLACE_TYPE_4      = 0x44, /* Replace Short Message Type 4 */
    VM_SMS_PID_REPLACE_TYPE_5      = 0x45, /* Replace Short Message Type 5 */
    VM_SMS_PID_REPLACE_TYPE_6      = 0x46, /* Replace Short Message Type 6 */
    VM_SMS_PID_REPLACE_TYPE_7      = 0x47, /* Replace Short Message Type 7 */

    VM_SMS_PID_RETURN_CALL_MSG     = 0x5F, /* Return Call Message */
    VM_SMS_PID_ANSI_136_RDATA      = 0x7C, /* ANSI-136 R-DATA */
    VM_SMS_PID_ME_DOWNLOAD         = 0x7D, /* ME Data Download */
    VM_SMS_PID_ME_DE_PERSONAL      = 0x7E, /* ME De-personalization Short Message */
    VM_SMS_PID_SIM_DOWNLOAD        = 0x7F, /* (U)SIM Data Download */

    VM_SMS_PID_RESERVED
} vm_sms_pid_enum;


/* SMS Action Type */
typedef enum
{
    VM_SMS_ACTION_NONE,                 /* no action */
    VM_SMS_ACTION_SEND,                 /* send action */ 
    VM_SMS_ACTION_READ,                 /* read action */ 
    VM_SMS_ACTION_DELETE,               /* delete action */ 
    VM_SMS_ACTION_SAVE,                 /* save action */
    VM_SMS_ACTION_UPDATE,               /* update action */ 
    VM_SMS_ACTION_COPY,                 /* copy action */
    VM_SMS_ACTION_MOVE,                 /* move action */
    VM_SMS_ACTION_QUERY,                /* query action */
    VM_SMS_ACTION_CHANGE_STATUS,        /* change status action */
    VM_SMS_ACTION_MOVE_TO_ARCHIVE,      /* move to archive action */
    VM_SMS_ACTION_GET_CONTENT,          /* get content action */
    VM_SMS_ACTION_GET_SIM_NUM,          /* get sim number action */
    VM_SMS_ACTION_GET_SC_ADDR           /* get SMS center address action */
} vm_sms_action_enum;


/* SMS Cause Tpye, and MMI defined error codes for others  */
typedef enum
{
    VM_SMS_CAUSE_NO_ERROR = 0,

    
    VM_SMS_CAUSE_ME_FAILURE        = 300,   /* Reference TS 27.005 Clause 3.2.5, For AT Command and MMI  */
    VM_SMS_CAUSE_OP_NOT_ALLOWED    = 302,   /* Reference TS 27.005 Clause 3.2.5, For AT Command and MMI  */
    VM_SMS_CAUSE_OP_NOT_SUPPORTED  = 303,   /* Reference TS 27.005 Clause 3.2.5, For AT Command and MMI  */
    VM_SMS_CAUSE_INVALID_PDU_PARA  = 304,   /* Reference TS 27.005 Clause 3.2.5, For AT Command and MMI  */
    VM_SMS_CAUSE_INVALID_TEXT_PARA = 305,   /* Reference TS 27.005 Clause 3.2.5, For AT Command and MMI  */
    VM_SMS_CAUSE_SIM_NOT_INSERTED  = 310,   /* Reference TS 27.005 Clause 3.2.5, For AT Command and MMI  */
    VM_SMS_CAUSE_SIM_FAILURE       = 313,   /* Reference TS 27.005 Clause 3.2.5, For AT Command and MMI  */
    VM_SMS_CAUSE_MEMORY_FAILURE    = 320,   /* Reference TS 27.005 Clause 3.2.5, For AT Command and MMI  */
    VM_SMS_CAUSE_INVALID_MEM_INDEX = 321,   /* Reference TS 27.005 Clause 3.2.5, For AT Command and MMI  */
    VM_SMS_CAUSE_MEM_FULL          = 322,   /* Reference TS 27.005 Clause 3.2.5, For AT Command and MMI  */
    VM_SMS_CAUSE_SCA_UNKNOWN       = 330,   /* Reference TS 27.005 Clause 3.2.5, For AT Command and MMI  */

    VM_SMS_CAUSE_NOT_READY         = 341,    /*SMS not ready*/
    VM_SMS_CAUSE_SEND_BUSY,                  /*busy on sending*/
    VM_SMS_CAUSE_SEND_ABORT,
    VM_SMS_CAUSE_MEM_INSUFFICIENT,           /*memory insufficient*/
    VM_SMS_CAUSE_DATA_INVALID,               /*invalid data*/
    VM_SMS_CAUSE_DATA_EXCEED,                /*data exceed*/
    VM_SMS_CAUSE_NUMBER_EMPTY,               /*destination number is empty*/
    VM_SMS_CAUSE_NUMBER_INVALID,             /*destination number is invalid*/
    VM_SMS_CAUSE_SC_EMPTY,                   /*SMS center number is empty*/
    VM_SMS_CAUSE_SC_INVALID,                 /*SMS center number is invalid*/
    VM_SMS_CAUSE_FDL_FAIL,                   /* FDL fail */
    VM_SMS_CAUSE_AT_CONFLICT,                /* AT conflict */
    VM_SMS_CAUSE_OP_CONFLICT,                /* OP conflict */
    VM_SMS_CAUSE_EMAIL_NO_SPACE,             /* email no space */
    VM_SMS_CAUSE_FS_ERROR,                   /* FS error */

    VM_SMS_CAUSE_UNKNOWN_ERROR     = 500
} vm_sms_cause_enum;

/* SMS Parameter Flag */
typedef enum
{
    VM_SMS_PARA_NONE           = 0x00000000,

    VM_SMS_PARA_NUM            = 0x00000001,    /* parameter of number */
    VM_SMS_PARA_SCA            = 0x00000002,    /* parameter of SCA */
    VM_SMS_PARA_PID            = 0x00000004,    /* parameter of PID */
    VM_SMS_PARA_DCS            = 0x00000008,    /* parameter of DCS */
    VM_SMS_PARA_VP             = 0x00000010,    /* parameter of VP */
    VM_SMS_PARA_STATUS_REPORT  = 0x00000020,    /* parameter of status report */
    VM_SMS_PARA_REPLY_PATH     = 0x00000040,    /* parameter of reply path */
    VM_SMS_PARA_PORT           = 0x00000080,    /* parameter of port */
    VM_SMS_PARA_CLASS          = 0x00000100,    /* parameter of class */
    VM_SMS_PARA_MMS            = 0x00000200,    /* parameter of MMS */
    VM_SMS_PARA_FO             = 0x00000400,    /* parameter of FO */

    VM_SMS_PARA_STATUS         = 0x00000800,    /* parameter of status */
    VM_SMS_PARA_SIM_ID         = 0x00001000,    /* parameter of SIM ID */
    VM_SMS_PARA_STORAGE_TYPE   = 0x00002000,    /* parameter of storage type */
    VM_SMS_PARA_TIMESTAMP      = 0x00004000,    /* parameter of time stamp */

    VM_SMS_PARA_CONTENT_EMS    = 0x00008000,    /* parameter of EMS */
    VM_SMS_PARA_CONTENT_BUFF   = 0x00010000,    /* parameter of buffer */
    VM_SMS_PARA_CONTENT_FILE   = 0x00020000     /* parameter of file */
} vm_sms_para_enum;



/* SMS Sort Type */
typedef enum
{
    VM_SMS_SORT_NONE,
    VM_SMS_SORT_TIMESTAMP,        /*by timestamp*/
    VM_SMS_SORT_MSG_TYPE,         /*by message type*/
    VM_SMS_SORT_STORAGE_TYPE,     /*by storage type*/
    VM_SMS_SORT_NUMBER,           /*by number*/
    VM_SMS_SORT_CONTENT,          /*by content*/
    VM_SMS_SORT_PID,              /*by PID*/
    VM_SMS_SORT_SIM_ID            /*by SIM*/

} vm_sms_sort_enum;


/* SMS Sorting Order */
typedef enum
{
    VM_SMS_ORDER_DEFAULT,         /*default order*/
    VM_SMS_ORDER_ASC,             /*ascending*/
    VM_SMS_ORDER_DESC             /*descending*/
} vm_sms_order_enum;


/* SMS new message event type*/
typedef enum
{

    VM_EVT_ID_SMS_NEW_MSG,       /* SMS event of new message */
    VM_EVT_ID_SMS_NEW_MSG_EX
} vm_sms_event_enum;

typedef enum
{
    VM_SMS_ADDR_PHONE_NUM = 0,
    VM_SMS_ADDR_EMAIL,
    VM_SMS_ADDR_IP
}vm_sms_addr_type_enum;

/* SMS Operation Callback Data Structure */
typedef struct
{
    VMINT  result;              /* 1: operation succeed; 0: operation failure */            
    vm_sms_cause_enum cause;    /* cause description, refer to vm_sms_cause_enum */
    vm_sms_action_enum action;  /* action type, refer to vm_sms_action_enum */
    void *action_data;          /* action data depending on action type */
    void *user_data;            /* user data */
} vm_sms_callback_t;

/* SMS Event Structure */
typedef struct
{
     VMINT event_id;    /* event ID registered */
     VMINT size;        /* event information size */
     void * user_data;  /* user data */
     void *event_info;  /* event information pointer */
} vm_sms_event_t;


/* Message Data Struture */
typedef struct
{
    VMINT8 number[(VM_SMS_MAX_ADDR_LEN + 1)*2 ]; /* SMS number */
    vm_sms_status_enum status;  /* SMS status */
    vm_sms_mti_enum mti;  /* mti */
    
    VMUINT8 tp_st; /* TP-Status, for Status Report */
    vm_sms_folder_enum folder_id; /* folder */

    vm_sms_para_enum para_flag; /* parameter flag */

    vm_sms_storage_enum storage_type; /* storage type */
    vm_sms_sim_enum sim_id; /* SIM ID */
    vm_time_t  timestamp; /* time stamp */
	
    VMINT8 sc_address[(VM_SMS_MAX_ADDR_LEN + 1)*2]; /* SMS center address */
    vm_sms_pid_enum pid; /* pid */
    vm_sms_vp_enum vp; /* vp */

    VMINT status_report; /* status report */
    VMINT  reply_path; /* reply path */

    VMUINT16 src_port; /* source port */
    VMUINT16 dest_port; /* destination port */
    vm_sms_dcs_enum dcs; /* dcs */
    vm_sms_class_enum msg_class; /* message class */
    VMUINT16 content_buff_size; /* content buffer size */
    VMINT8 *content_buff; /* content buffer */
    VMINT8 *content_file_path; /* content file path */

    void *content_ems; /* content ems */
} vm_sms_msg_data_t;

/* Add Message Callback Data Structure */
typedef struct
{
	vm_sms_status_enum status;  /* status */
	vm_sms_sim_enum sim_id; /* SIM ID */
	vm_sms_storage_enum storage_type; /* storage type */
	vm_time_t  timestamp; /* time stamp */
	VMUINT16 content_size; /* content buffer size */
	VMINT8 *content; /* content buffer */
	VMINT8 number[(VM_SMS_MAX_ADDR_LEN + 1)*2 ]; /* destination number */
} vm_sms_add_msg_data_t;


/* Query Data Structure */
typedef struct
{
    vm_sms_sort_enum sort_flag; /* sort flag */
    vm_sms_order_enum order_flag; /* order flag */
    vm_sms_status_enum status;  /* status */
  
} vm_sms_query_t;


/* new Message Data Structure */
typedef struct
{
    VMUINT16 msg_id;
    VMUINT16 dest_port;                               /* destination port */
    VMUINT16 src_port;                                /* source port */
    VMUINT16 message_len;                             /* message length */
    VMUINT16 ref;                                                               /* concat. message reference */
    VMUINT8 number[VM_SMS_MAX_ADDR_LEN + 1];          /* source number */
    VMUINT8 sc_number[VM_SMS_MAX_ADDR_LEN + 1];
    vm_time_t timestamp;                              /* timestamp of service center*/
    VMUINT8 total_seg;                                /* total segment */
    VMUINT8 seg;                                      /* segment number */
    VMUINT8 dcs;                                      /* encoding format */
    VMUINT8 mti;                                      /* message type identication */
    VMUINT8 pid;                                      /* protocol ID */
    VMUINT8 fo;
    VMUINT8 data[1];                                  /* data */
    vm_sms_sim_enum sim_id;                           /* SIM ID */
    vm_sms_storage_enum storage_type;                 /* storage */
} vm_sms_new_msg_t;


/* Read Message Callback Data Structure */
typedef struct
{
    vm_sms_msg_data_t *msg_data;        /* message data */
} vm_sms_read_msg_cb_t;


/* Add Message Callback Data Structure */
typedef struct
{
    VMUINT16 msg_id; /* message ID */
} vm_sms_save_msg_cb_t;


/* Delete Message Callback Data Structure */
typedef struct
{
    void *dummy; /* dummy */
} vm_sms_delete_msg_cb_t;


/* Delete Message List Callback Data Structure */
typedef struct
{
     VMUINT16 deleted_msg_num; /* number of deleted message */
} vm_sms_delete_msg_list_cb_t;



/* Query Message Callback Data Structure */
typedef struct
{
    VMUINT16 msg_num;          /* message number */
    VMUINT16 *msg_id_list;     /* message ID list */
} vm_sms_query_msg_cb_t;


/* Message New SMS Interrupt Event Callback Data Structure */
typedef struct
{
    VMUINT16  msg_id;          /* message ID */
    VMUINT8  *content;
    void *msg_data;            /* new msg structure (vm_sms_new_msg_t ) */
} vm_sms_event_new_sms_t;

/* get SMS center number Callback Data Structure */
typedef struct
{
     VMINT8 sc_addr[VM_SMS_MAX_ADDR_LEN + 1];
}vm_sms_get_sc_addr_cb_t;

typedef struct
{
    VMINT sim; // sim card :1,2,3,4
    vm_sms_addr_type_enum addr_type;
    VMWCHAR* addr; // address UCS2
    VMWCHAR* subject; //subject UCS2
    VMWCHAR* content; //content UCS2
}vm_sms_launch_data;


/*****************************************************************************      
 *
 * FUNCTION
 *  VmSmsCallbackFunc
 * DESCRIPTION
 *  SMS operation callback function
 * PARAMETERS
 *  callback_data : [IN] refer to vm_sms_callback_t
 *  
*****************************************************************************/
typedef void(*VmSmsCallbackFunc)(vm_sms_callback_t* callback_data);


/*****************************************************************************      
 *
 * FUNCTION
 *  VmSmsEventFunc
 * DESCRIPTION
 *  SMS event callback function
 * PARAMETERS
 *  event_data : [IN] refer to vm_sms_event_t
 * RETURNS
 *
*****************************************************************************/
typedef VMINT(*VmSmsEventFunc)(vm_sms_event_t* event_data);


/*****************************************************************************
 * FUNCTION
 *  vm_sms_read_msg
 * DESCRIPTION
 *  1. Read Message's Data, included message status, number, content and other attributes
 *     (Storage Type, SIM Card, Profile element, etc.) indicated by the flag;
 *  2. The buffer to save the content should be provided by caller.
 *  3. The Callback Action Data Structure is srv_sms_read_msg_cb_struct;
 * PARAMETERS
 *  msg_id : [IN]        Message ID
 *  change_status : [IN]        Whether change the UNREAD Msg to READ
 *  msg_data : [IN/OUT]    Message Data For Filling back read data
 *  callback_func : [IN]        Callback Function
 *  user_data : [IN]        User Data
 * RETURNS
 *  refer to vm_sms_error_enum
 *****************************************************************************/
VMINT vm_sms_read_msg(VMUINT16 msg_id, VMINT change_status,  vm_sms_msg_data_t* msg_data, 
	            VmSmsCallbackFunc  callback_func, void* user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_sms_add_msg
 * DESCRIPTION
 *  1. Save a new message to SMS Storage.
 *  2. If Caller specify those parameters (Status, Address, Content, SIM Card, Storage Type,
 *     Profile element, we will use them, otherwise, it will user the defaut value (If the 
 *     parameters is in the SMS setting, it will use the setting's value as defaut).
 *  3. The Callback Action Data Struct is vm_sms_save_msg_cb_t.
 * PARAMETERS
 *  msg_data : [IN]  message data to be added
 *  callback_func : [IN]        Callback Function
 *  user_data : [IN]        User Data
 * RETURNS
 *  refer to vm_sms_error_enum
 *****************************************************************************/
VMINT vm_sms_add_msg(vm_sms_add_msg_data_t * msg_data, VmSmsCallbackFunc callback_func, void* user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_sms_delete_msg
 * DESCRIPTION
 *  1. Delete an existed message;
 *  2. If the message is not existed, the result is FALSE;
 *  3. The Callback Action Data Structure is vm_sms_delete_msg_cb_t;
 * PARAMETERS
 *  msg_id : [IN]        Message ID
 *  callback_func : [IN]        Callback Function
 *  user_data : [IN]        User Data
 * RETURNS
 *  refer to vm_sms_error_enum
 *****************************************************************************/
VMINT vm_sms_delete_msg(VMUINT16 msg_id, VmSmsCallbackFunc callback_func,  void* user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_sms_delete_msg_list
 * DESCRIPTION
 *  1. Delete all the existed message of specified list
 *  2. If the message is not existed, the result is FALSE;
 *  3. The Callback Action Data Structure is vm_sms_delete_msg_list_cb_t;
 * PARAMETERS
 *  box_type : [IN]        refer to vm_sms_box_enum, can be combination of multiple boxes.
 *  sim_id : [IN]       refer to vm_sms_sim_enum
 *  callback_func : [IN]        Callback Function
 *  user_data : [IN]        User Data
 * RETURNS
 *  refer to vm_sms_error_enum
 *****************************************************************************/
VMINT vm_sms_delete_msg_list(vm_sms_box_enum box_type,  vm_sms_sim_enum sim_id, VmSmsCallbackFunc callback_func,  void* user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_sms_get_msg_id_list
 * DESCRIPTION
 *  1. Query the messages with some properties.
 *  2. The caller can set the query_flag, and the corresponding paramenters of
 *     the propertied they wanted. The folder ID is mandatory in the current version;
 *  3. The caller also can specify the sort flag, in the current version, we only 
 *     support sorting by timestamp.
 *  4. The Callback Action Data Structure is srv_sms_query_msg_cb_struct;
 * PARAMETERS
 *  query_data : [IN]        Query Data
 *  callback_func : [IN]        Callback Function
 *  user_data : [IN]        User Data
 * RETURNS
 *  refer to vm_sms_error_enum
 *****************************************************************************/
VMINT vm_sms_get_msg_id_list(vm_sms_query_t* query_data,  VmSmsCallbackFunc callback_func,  void* user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_sms_get_msg_id
 * DESCRIPTION
 *  Get message ID of the message in the box list
 * PARAMETERS
 *  box_type : [IN]        Message Box List Type
 *  msg_index : [IN]        The position of message in the Box List
 *             for example: msg_id_list[msg_index] = msg_id;
 *                   msg_id_list[0]=0                                                       msg_id_list[0]=0                                            msg_id_list[0]=0
 *             msg_id_list[1]=1  delete msg_id=2  msg_id_list[1]= 1  add a message  msg_id_list[1]=1
 *             msg_id_list[2]=2  -------------->msg_id_list[2]= 3  ------------>msg_id_list[2]=2
 *                   msg_id_list[3]=3                                                                                                                           msg_id_list[3]=3
 * RETURNS
 *  msg_id if non-negative number, -1 means the msg-index does not exist.
 *****************************************************************************/
VMINT16 vm_sms_get_msg_id(vm_sms_box_enum box_type, VMUINT16 msg_index);


/*****************************************************************************
 * FUNCTION
 *  vm_sms_get_box_size
 * DESCRIPTION
 *  Get number of the messages in a box list 
 * PARAMETERS
 *  box_type : [IN]        Message Box List Type, refer to vm_sms_box_enum
 * RETURNS
 *  number of message
 *****************************************************************************/
VMINT16 vm_sms_get_box_size(vm_sms_box_enum box_type);

/*****************************************************************************
 * FUNCTION
 *  vm_sms_get_sc_address
 * DESCRIPTION
 *  Get SC number (asyn) 
 * PARAMETERS
 *  sim_id : [IN]        SIM card, refer to vm_sms_sim_enum.
 *  callback_func : [IN]  Callback Function.
 *  user_data : [IN]  user data
 * RETURNS
 *  refer to vm_sms_error_enum
 *****************************************************************************/
VMINT vm_sms_get_sc_address( vm_sms_sim_enum sim_id, VmSmsCallbackFunc callback_func, void* user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_sms_set_interrupt_event_handler
 * DESCRIPTION
 *  Set Interrupt Event Handler of the Event
 * PARAMETERS
 *  event_id : [IN]        Event ID
 *  event_func : [IN]        Event Handler Function
 *  user_data : [IN]        User Data
 * RETURNS
 *  refer to vm_sms_error_enum
 *****************************************************************************/
VMINT vm_sms_set_interrupt_event_handler(vm_sms_event_enum event_id,  VmSmsEventFunc event_func,  void* user_data);


/*****************************************************************************
 * FUNCTION
 *  vm_sms_clear_interrupt_event_handler
 * DESCRIPTION
 *  Clear Interrupt Event Handler of the Event
 * PARAMETERS
 *  event_id : [IN]        Event ID
 *  event_func : [IN]        Event Handler Function
 *  user_data : [IN]        User Data
 * RETURNS
 *  refer to vm_sms_error_enum
 *****************************************************************************/
VMINT vm_sms_clear_interrupt_event_handler(vm_sms_event_enum event_id,  VmSmsEventFunc event_func,  void* user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_sms_get_sc_address_syn
 * DESCRIPTION
 *  Get SC number (sync) 
 * PARAMETERS
 *  vm_sc_addr : [OUT]        output SC number
 *  sim_id : [IN]   SIM card
 * RETURNS
 *  result of get sc address.
* RETURN VALUES                                      
 *  VM_SMS_REQ_ERROR : support sync mode, request failed.
 *  VM_SMS_SUPPORT_SYN_SCA : support sync mode, request succeed.
 *  VM_SMS_NOT_SUPPORT_SYN_SCA : not support sync mode, request failed.
 *****************************************************************************/
VMINT vm_sms_get_sc_address_syn(vm_sms_get_sc_addr_cb_t * vm_sc_addr,  vm_sms_sim_enum sim_id);
/*****************************************************************************
 * FUNCTION
 *  vm_sms_set_interrupt_event_handler_forpay
 * DESCRIPTION
 *  Set Interrupt Event Handler of the Event
 * PARAMETERS
 *  event_id : [IN]        Event ID
 *  event_func : [IN]        Event Handler Function
 *  user_data : [IN]        User Data
 * RETURNS
 *  refer to vm_sms_error_enum
 *****************************************************************************/
VMINT vm_sms_set_interrupt_event_handler_forpay(vm_sms_event_enum event_id,  VmSmsEventFunc event_func,  void* user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_sms_clear_interrupt_event_handler_forpay
 * DESCRIPTION
 *  Clear Interrupt Event Handler of the Event
 * PARAMETERS
 *  event_id : [IN]        Event ID
 *  event_func : [IN]        Event Handler Function
 *  user_data : [IN]        User Data
 * RETURNS
 *  refer to vm_sms_error_enum
 *****************************************************************************/
VMINT vm_sms_clear_interrupt_event_handler_forpay(vm_sms_event_enum event_id,  VmSmsEventFunc event_func,  void* user_data);
/*****************************************************************************
 * FUNCTION
 *  vm_sms_delete_msg_forpay
 * DESCRIPTION
 *  1. Delete an existed message;
 *  2. If the message is not existed, the result is FALSE;
 *  3. The Callback Action Data Structure is vm_sms_delete_msg_cb_t;
 * PARAMETERS
 *  event_id : [IN]        Event ID
 *  callback_func : [IN]        Event Handler Function
 *  user_data : [IN]        User Data
 * RETURNS
 *  refer to vm_sms_error_enum
 *****************************************************************************/
VMINT vm_sms_delete_msg_forpay(VMUINT16 msg_id, VmSmsCallbackFunc callback_func,  void* user_data);

/*****************************************************************************
 * FUNCTION
 *  vm_sms_launch
 * DESCRIPTION
 *  1. Launch a sms editor to edit sms
 * PARAMETERS
 *  vm_sms_launch_data : [IN]        launch data
 *  data_size : [IN]        size of launch data
 * RETURNS
 *  0:success
 *****************************************************************************/
VMINT vm_sms_launch(vm_sms_launch_data* data, VMINT data_size);

/**
 * send SMS successfully
 */
#define VM_SMS_RESULT_OK			1

/**
 * failed to send SMS
 */
#define VM_SMS_RESULT_ERROR			2

/**
 * Cancel sending SMS
 */
#define VM_SMS_RESULT_ABORT			3

/*****************************************************************************
* FUNCTION
 *    vm_send_sms
 * DESCRIPTION
 *  send SMS 
 * PARAMETERS
 *  phone_number : [IN]  destination phone number.
 *  content : [IN] SMS content.
 *  callback : [IN] callback function for sending SMS
 * RETURNS
 *  result of sending SMS request
 * RETURN VALUES                                      
 *  TRUE : request succeed.
 *  FALSE : request failure
 *
*****************************************************************************/
VMINT vm_send_sms(VMWSTR phone_number, VMWSTR content, void (*callback)(VMINT result));

/*****************************************************************************
* FUNCTION
 *    vm_cancel_send_sms
 * DESCRIPTION
 *  cancel sending SMS.
 *  The function can be used only when: 1) after call the function vm_send_sms() and return TRUE
 *                                                       2) before callback is invoked
 *  Or the function will be invalid.
 *
*****************************************************************************/
void vm_cancel_send_sms(void);

/*****************************************************************************
 * FUNCTION
 *  vm_sms_is_sms_ready
 * DESCRIPTION
 *  check whether sms is ready
 * PARAMETERS
 *  void
 * RETURNS
 *  result of whether sms is ready
 * RETURN VALUES                                      
 *  VM_TRUE : sms is ready
 *  VM_FALSE : sms is not ready
 *****************************************************************************/
VMBOOL vm_sms_is_sms_ready(void);

#ifdef __cplusplus
}
#endif

#endif /* VMSMS_SDK_H_ */
