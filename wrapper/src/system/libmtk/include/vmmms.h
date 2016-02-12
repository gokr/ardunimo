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

#ifndef VMMMS_SDK_H
#define VMMMS_SDK_H 


#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/**
 *maxium length of xml file path, including '\0'
 */
#define MAX_MMS_APP_NAME_LEN  100

/*Max length of address MMS adaptor supports*/
#define VM_MMS_MAX_ADDR_LEN 128
/*Max length of subbject MMS adaptor supports*/
#define VM_MMS_MAX_SUBJECT_LEN 41

#define VM_MMS_MSG_ID_LIST_LEN 100
typedef enum
{
    VM_MMS_CANCEL = -3,						 /*user cancelled sending*/
    VM_MMS_FAIL = -2,                        /*operation request error*/     
    VM_MMS_MEMORY_NOT_ENOUGH = -1,    		 /*not enough memory*/
    VM_MMS_SUCCESS							 /*operation successfully*/
 }vm_mms_result_enum;

typedef enum
{
	VM_MMS_TYPE_SMIL_MMS = 0,       			 /*SMIL type of XML */
	VM_MMS_TYPE_MIXED_MMS          				 /*MIXED type of XML */
}vm_mms_type_enum;

typedef enum
{
	VM_MMS_SIM_ID_SIM1 = 0x01,          			 	 /*sim1 card */
	VM_MMS_SIM_ID_SIM2 = 0x02,                				 /*sim2 card */
	VM_MMS_SIM_ID_SIM3 = 0x04,          			 	 /*sim3 card */
	VM_MMS_SIM_ID_SIM4 = 0x08,                				 /*sim4 card */
}vm_mms_sim_id_enum;

typedef struct
{
	VMUWCHAR xml_filepath[MAX_MMS_APP_NAME_LEN];/*XML file path*/
	VMUINT xml_size;							 /*XML file size*/
	VMUINT8 mms_type;                    		 /*refer to vm_mms_type_enum*/
	VMUINT8 sim_id;                        		 /*refer to vm_mms_sim_id_enum*/
}vm_send_mms_req_t;

typedef enum
{
    VM_MMS_ADDR_PHONE_NUM = 0,
    VM_MMS_ADDR_EMAIL,
    VM_MMS_ADDR_IP
}vm_mms_addr_type_enum;



typedef enum
{
    VM_EVT_ID_MMS_NEW_MSG,
    VM_EVT_ID_MMS_MAX_ENUM
}vm_mms_event_enum;


/* This enum is used to specify MMS contains only one media type objects. */
typedef enum
{
    VM_MMS_MEDIA_MSG_NONE = 0, /* Not specified */
    VM_MMS_MEDIA_MSG_TEXT,     /* Text MMS: One MMS only contains text object */
    VM_MMS_MEDIA_MSG_AUDIO,    /* Audio MMS: One MMS only contains audio object */
    VM_MMS_MEDIA_MSG_PHOTO,    /* Photo MMS: One MMS only contains image object */
    VM_MMS_MEDIA_MSG_VIDEO     /* Video MMS: One MMS only contains video object */
} vm_mms_media_msg_enum;


/* This enum is used to specify message type. */
typedef enum
{
    VM_MMS_MSG_TYPE_NOTIFICATION,     /* MMS notification */
    VM_MMS_MSG_TYPE_DELIVERY_REPORT,  /* MMS delivery report */
    VM_MMS_MSG_TYPE_READ_REPORT,      /* MMS read report v1.1 */
    VM_MMS_MSG_TYPE_MMS,              /* normal MMS message */
    VM_MMS_MSG_TYPE_JAVA,             /* Java MMS */   
    VM_MMS_MSG_TYPE_TEMPLATE,         /* MMS template */
    VM_MMS_MSG_TYPE_POSTCARD,          /* MMS postcard */
    VM_MMS_MSG_TYPE_UNSUPPORTED
}vm_mms_msg_type_enum;

typedef enum
{
    VM_MMS_MSG_STORAGE_NONE = 0X00,
    VM_MMS_MSG_STORAGE_PHONE = 0X01,
    VM_MMS_MSG_STORAGE_CARD1 = 0X02,
    VM_MMS_MSG_STORAGE_TOTAL = 0X03 
} vm_mms_msg_storage_type_enum;

/* This enum is used to specify MMS folder. */
typedef enum
{
    VM_MMS_FOLDER_NONE = 0x0,
    VM_MMS_FOLDER_INBOX = 0x1,
    VM_MMS_FOLDER_OUTBOX = 0x2,
    VM_MMS_FOLDER_SENT = 0x4,
    VM_MMS_FOLDER_DRAFT = 0x8,
    VM_MMS_FOLDER_TEMPLATE = 0x10,        /* This folder is for predefined MMS template */
    VM_MMS_FOLDER_USRDEF_TEMPLATE = 0x20, /* This folder is for user to save MMS as template */
    VM_MMS_FOLDER_ARCHIVE = 0x40,
    VM_MMS_FOLDER_HIDDEN = 0x80,
    VM_MMS_FOLDER_REPORT_BOX = 0x100,
}vm_mms_folder_enum;
typedef enum
{
    VM_MMS_RESULT_OK,                              /* 0 */
    VM_RESULT_DELAYED,                         /* 1 */
    VM_RESULT_CONTINUE,                        /* 2 */
    VM_RESULT_FAIL,                            /* 3 */
    VM_RESULT_FAIL_IN_CALL,                    /* 4 */
    VM_RESULT_FAIL_NOT_READY,                  /* 5 */
    VM_RESULT_FAIL_BUSY,                       /* 6 */
    VM_RESULT_FAIL_INSUFFICIENT_MEMORY,        /* 7 */
    VM_RESULT_FAIL_INSUFFICIENT_STORAGE,       /* 8 */
    VM_RESULT_FAIL_MAX_MSG_NUM_REACHED,        /* 9 */
    VM_RESULT_FAIL_MAX_MSG_SIZE_REACHED,       /* 10 */
    VM_RESULT_FAIL_MAX_SLIDE_NUM_REACHED,      /* 11 */
    VM_RESULT_FAIL_MAX_ATTACHMENT_NUM_REACHED, /* 12 */
    VM_RESULT_FAIL_FILE_EMPTY,                 /* 13 */
    VM_RESULT_FAIL_FILE_NOT_FOUND,             /* 14 */
    VM_RESULT_FAIL_FILE_CORRUPTED,             /* 15 */
    VM_RESULT_FAIL_FILE_IN_USE,                /* 16 */
    VM_RESULT_FAIL_FILE_IO,                    /* 17 */
    VM_RESULT_FAIL_FOLDER_NOT_FOUND,           /* 18 */
    VM_RESULT_FAIL_UNSUPPORT_CONTENT,          /* 19 */
    VM_RESULT_FAIL_COMM_UNSUPPORT_CONTENT,     /* 20 */
    VM_RESULT_FAIL_COMM_CONFIG_ERROR,          /* 21 */
    VM_RESULT_FAIL_COMM_CONNECT_ERROR,         /* 22 */
    VM_RESULT_FAIL_COMM_SERVER_ERROR,          /* 23 */
    VM_RESULT_FAIL_COMM_SERVER_TIMEOUT,        /* 24 */
    VM_RESULT_FAIL_COMM_SERVICE_DENIED,        /* 25 */
    VM_RESULT_FAIL_COMM_UNKNOWN_APN,           /* 26 */
    VM_RESULT_FAIL_COMM_UNAUTHORIZED,          /* 27 */
    VM_RESULT_FAIL_USER_CANCEL,                /* 28 */
    VM_RESULT_FAIL_INVALID_PARAMETER,          /* 29 */
    VM_RESULT_FAIL_INVALID_MSGID,              /* 30 */
    VM_RESULT_FAIL_INVALID_FOLDER,             /* 31 */
    VM_RESULT_FAIL_QUEUE_FULL,                 /* 32 */
    VM_RESULT_FAIL_PARSE,                      /* 33 */
    VM_RESULT_FAIL_MSGID_IS_USING,             /* 34 */
    VM_RESULT_FAIL_CREATION_MODE_MAX_MSG_SIZE_REACHED,    /* 35 */
    VM_RESULT_FAIL_UPDATE_CHECKSUM_INVALID_PARAM,         /* 36 */
    VM_RESULT_FAIL_IN_USB_MODE,                /* 37 */
    VM_RESULT_FAIL_FILE_ACCESS_IN_USB_MODE,    /* 38 */
    VM_RESULT_FAIL_TERMINATING,                /* 39 */
    VM_RESULT_FAIL_USERDEF_TEMPLATE_FULL,      /* 40 */
    VM_RESULT_FAIL_WAP_CONN_MAX_MSG_SIZE_REACHED,         /* 41 */
    VM_RESULT_OK_WITH_WARNING_CONTENT,         /* 42 */
    VM_RESULT_ABORTED,                         /* 43 */
    VM_RESULT_FAIL_SUSPENDED_MODE,             /* 44 */
    VM_RESULT_FAIL_MSG_EXPIRED,                /* 45 */
    VM_RESULT_FAIL_IN_VIDEO_CALL,              /* 46 */ 
    VM_RESULT_FAIL_IMAGE_TOO_LARGE,            /* 47 */ 
    VM_RESULT_FAIL_MEM_CARD_NOT_PRESENT,       /* 48 */
    VM_RESULT_FAIL_MEM_CARD_NOT_PRESENT_USE_PHONE,       /* 49 */ 
    VM_RESULT_FAIL_MEM_CARD_NOT_PRESENT_INSERT_CARD,      /* 50 */  
    VM_RESULT_FAIL_MAX_MSG_REACHED_ON_PHONE_MEMORY,      /* 51 */
    VM_RESULT_FAIL_MAX_MSG_REACHED_ON_MEM_CARD,           /* 52 */
    VM_RESULT_FAIL_MEM_CARD_PLUG_OUT,          /* 53 */
    VM_RESULT_FAIL_UNSUPPORT_MMS_TYPE,
    VM_RESULT_FAIL_ROOT_DIR_FULL,
                /*NEW ADDED AS REMOVAL OF SLS*/
    VM_SMIL_RESULT_SMIL_NOT_CREATED,
    VM_SMIL_RESULT_MISSING_MEDIA_OBJECTS,
    VM_SMIL_RESULT_MISSING_MEDIA_OBJECT_SRC,
    VM_RESULT_END
}vm_result_enum;

/* This enum is used to specify MMS folder. */
typedef enum
{
    VM_FOLDER_NONE = 0x0,
    VM_FOLDER_INBOX = 0x1,
    VM_FOLDER_OUTBOX = 0x2,
    VM_FOLDER_SENT = 0x4,
    VM_FOLDER_DRAFT = 0x8,
    VM_FOLDER_TEMPLATE = 0x10,        /* This folder is for predefined MMS template */
    VM_FOLDER_USRDEF_TEMPLATE = 0x20, /* This folder is for user to save MMS as template */
    VM_FOLDER_ARCHIVE = 0x40,
    VM_FOLDER_HIDDEN = 0x80,
    VM_FOLDER_REPORT_BOX = 0x100,
    VM_FOLDER_ALL = 0xFFFF
}vm_folder_enum;

/* This enum is used to specify MMS creation mode. */
typedef enum
{
    VM_CREATION_MODE_FREE,        /* Creation mode: Free*/
    VM_CREATION_MODE_RESTRICTED,  /* Creation mode: Restricted */
    VM_CREATION_MODE_WARNING      /* Creation mode: Warning*/
}vm_creation_mode_enum;

/* This enum is used to specify the MMS priority. */
typedef enum
{
    VM_PRIORITY_NOT_SET,  /*Prority is not defined */
    VM_PRIORITY_LOW,      /*Prority is low */
    VM_PRIORITY_MEDIUM,   /*Prority is medium */
    VM_PRIORITY_HIGH      /*Prority is high */
}vm_priority_enum;

/* This enum is used to specify MMS expiry time. Count by seconds*/
typedef enum
{
    VM_EXPIRY_NOT_SET = 0,           /* epxiry time is not defined */
    VM_EXPIRY_1_HOUR = 3600,         /* epxiry time is 1 hour */
    VM_EXPIRY_6_HOURS = 21600,       /* epxiry time is 6 hours */ 
    VM_EXPIRY_12_HOURS = 43200,      /* epxiry time is 12 hours */ 
    VM_EXPIRY_1_DAY = 86400,         /* epxiry time is 1 day */
    VM_EXPIRY_1_WEEK = 604800,       /* epxiry time is 1 week */
    VM_EXPIRY_MAX = 0                /* epxiry time is not defined */
}vm_expiry_time_enum;

/* This enum is used to specify MMS delivery time. */
typedef enum
{
    VM_DELIVERY_NOT_SET = 0,        /* delivery time is not defined */
    VM_DELIVERY_IMMEDIATE = 0,      /* delivery time is 0 hour */     
    VM_DELIVERY_1_HOUR = 3600,      /* delivery time is 1 hours */
    VM_DELIVERY_2_HOUR = 7200,      /* delivery time is 2 hours */
    VM_DELIVERY_12_HOURS = 43200,   /* delivery time is 12 hours */   
    VM_DELIVERY_24_HOURS = 86400    /* delivery time is 1 day */      
}vm_delivery_time_enum;             

/* This enum is used to specify the MMS header field type. */                                     
typedef enum
{
    VM_HEADER_UNKNOWN,  /* Unknowm */
    VM_HEADER_ADDRESS,  /* Address */
    VM_HEADER_SUBJECT   /* Subject */
}vm_header_attr_enum;

/* This enum is used to specify the media type which the object will be inserted as. */
typedef enum
{
    VM_INSERT_UNKNOWN,    /* Unknown */
    VM_INSERT_TEXT,       /* Text */
    VM_INSERT_IMAGE,      /* image */
    VM_INSERT_AUDIO,      /* audio */
    VM_INSERT_VIDEO,      /* video */
    VM_INSERT_REF,        /* object embeded in <ref> tag */
    VM_INSERT_ATTACHMENT  /* attachment */
}vm_insert_type_enum;

/*This enum is used to specify the DRM type.*/
typedef enum
{ 
    VM_DRM_NONE,              /*Not DRM object*/
    VM_DRM_FL_CD,             /* forward-lock or combined delivery */
    VM_DRM_SD,                /* seperate-delivery */
    VM_DRM_SD_NO_RIGHT,       /* Separate-delivery object without right */
    VM_DRM_PDCF_V2,           /* DRM v2.0 PDCF or V2 object */
    VM_DRM_PDCF_V2_NO_RIGHT,  /* DRM v2.0 PDCF or V2 object without right */
    VM_DRM_TYPE_TOTAL
}vm_drm_type_enum;
           
/*This enum is used to specify slide layout.*/
typedef enum
{
    VM_LAYOUT_NONE,          /* No relative layout specification */
    VM_LAYOUT_IMAGE_ON_TOP,  /* Image on top; text on bottom */
    VM_LAYOUT_TEXT_ON_TOP,   /* Text on top; image on bottom */
    VM_LAYOUT_IMAGE_AT_LEFT, /* Image at left; text at right */
    VM_LAYOUT_TEXT_AT_LEFT   /* Text at left; image at right */
}vm_slide_layout_enum;

/* This enum is used to specify connection type. */
typedef enum
{
    VM_CONN_TYPE_HTTP_PROXY,   /* HTTP connection with proxy */
    VM_CONN_TYPE_HTTP_DIRECT,  /* HTTP connection without proxy */
    VM_CONN_TYPE_WSP_CL,       /* WSP connectionless */
    VM_CONN_TYPE_WSP_CO,       /* WSP connection oriented */
    VM_CONN_TYPE_WSP_SEC_CL,   /* WSP connectionless with security */
    VM_CONN_TYPE_WSP_SEC_CO    /* WSP connection oriented with security */
}vm_connection_type_enum;

/* This enum is used to specify 'text style' like bold and italic. Also, these two are mutually exclusive. */
typedef enum
{
    VM_TEXT_STYLE_BOLD = 0x01,   /* Bold text */
    VM_TEXT_STYLE_ITALIC = 0x02  /* Italic text */
}vm_text_style_enum;

/* This enum is used to specify 'text size */
typedef enum
{
    VM_TEXT_SIZE_SMALL = 1,  /* Small text */
    VM_TEXT_SIZE_MEDIUM,     /* Medium text */
    VM_TEXT_SIZE_LARGE       /* Large text */
}vm_text_size_enum;

/* This enum is used to specify address group type. */
typedef enum
{
    VM_ADDRESS_GROUP_TYPE_TO,
    VM_ADDRESS_GROUP_TYPE_CC,
    VM_ADDRESS_GROUP_TYPE_BCC,
    VM_ADDRESS_GROUP_TYPE_FROM,
    VM_ADDRESS_GROUP_TYPE_TOTAL_NUM
} vm_address_group_type_enum;

/* This enum is used to specify address type. */
typedef enum
{
    VM_ADDR_TYPE_NONE,          /* Unknown */
    VM_ADDR_TYPE_PHONE_NUMBER,  /* Phone number */
    VM_ADDR_TYPE_EMAIL,          /* Email */
    VM_ADDR_TYPE_IPV4           /* IPv4 */
}vm_addr_type_enum;

/* This enum is used to specify message class. */
typedef enum
{
	VM_MSG_CLASS_NOT_SET,
    VM_MSG_CLASS_PERSONAL,         /* MMS message is created by person */
    VM_MSG_CLASS_ADVERTISEMENT,    /* MMS message is for advertisement */
    VM_MSG_CLASS_INFORMATIONAL,    /* MMS message is for informational */
    VM_MSG_CLASS_AUTO              /* MMS message is created automatically */
}vm_msg_class_enum;

/* This enum is used to specify message type. */
typedef enum
{
    VM_MSG_TYPE_NOTIFICATION,     /* MMS notification */
    VM_MSG_TYPE_DELIVERY_REPORT,  /* MMS delivery report */
    VM_MSG_TYPE_READ_REPORT,      /* MMS read report v1.1 */
    VM_MSG_TYPE_MMS,              /* normal MMS message */
    VM_MSG_TYPE_JAVA,             /* Java MMS */   
    VM_MSG_TYPE_TEMPLATE,         /* MMS template */
    VM_MSG_TYPE_POSTCARD,          /* MMS postcard */
    VM_MSG_TYPE_UNSUPPORTED
}vm_msg_type_enum;

/* This enum is used to specify message status.*/
typedef enum
{
    VM_MSG_STATUS_WAITING_SENDING,      /* The status is for msg in outbox */
    VM_MSG_STATUS_SENDING,              /* The status is for msg in outbox */
    VM_MSG_STATUS_WAITING_DOWNLOADING,  /* The status is for msg in inbox folder */
    VM_MSG_STATUS_DOWNLOADING,          /* The status is for msg in inbox folder */
    VM_MSG_STATUS_NORMAL,               /* It is for template, draft, received MMS, delivery report and read report. */
    VM_MSG_STATUS_FAILED                /* The status is for msg in sent or inbox folder. In case of inbox folder, the msg shall be mms notification. */
}vm_msg_status_enum;

/* This enum is used to specify retrieval mode. */
typedef enum
{
    VM_RETRIEVAL_MODE_IMMED,    /* Immediate retrieval */
    VM_RETRIEVAL_MODE_DEFERRED, /* delayed retrieval */
    VM_RETRIEVAL_MODE_REJECT,   /* Reject to retrieve MMS message */
    VM_RETRIEVAL_MODE_AS_HOME   /* Same as setting in home network */
}vm_retrieval_mode_enum;

/* This enum is used to specify delivery report status (value refer to X-Mms-Status header field). */
typedef enum
{
    VM_DR_STATUS_PENDING = 0,
    VM_DR_STATUS_EXPIRED = 0x80,       /* MMS is expired */
    VM_DR_STATUS_RETRIEVED = 0x81,     /* MMS is retrieved */
    VM_DR_STATUS_REJECTED = 0x82,      /* MMS is rejected */
    VM_DR_STATUS_DEFERRED = 0x83,      /* MMS is defered */
    VM_DR_STATUS_UNRECOGNISED = 0x84,  /* MMS is unrecognized */
    VM_DR_STATUS_INDETERMINATE = 0x85, /* MMS is indeterminate */
    VM_DR_STATUS_FORWARDED = 0x86,     /* MMS is forwarded */
    VM_DR_STATUS_UNREACHABLE = 0x87    /* MMS is unreachable */
}vm_dr_status_enum;

/*This enum is used to specify read report status (value refer to X-Mms-Read-Status header field).*/
typedef enum
{
    VM_RR_STATUS_PENDING = 0,
    VM_RR_STATUS_READ = 0x80,              /* MMS is read */
    VM_RR_STATUS_DELETED_NO_READ = 0x81    /* MMS is deleted without reading */
}vm_rr_status_enum;

/* This enum is used to specify MMS version (value refer to X-Mms-MMS-Version). */
typedef enum
{
    VM_VERSION_10 = 0x10,  /* MMS V1.0 */
    VM_VERSION_11 = 0x11,  /* MMS V1.1 */
    VM_VERSION_12 = 0x12   /* MMS V1.2 */
}vm_version_enum;

/* This enum is used to specify region fit parameter. */
typedef enum
{
    VM_REGION_FIT_NONE,    /* Not specified */
    VM_REGION_FIT_MEET,    /* Scale the object so that its aspect ratio is kept, and it is stays fully visible  */
    VM_REGION_FIT_SCROLL,  /* Scale the object so that its aspect ratio is kept, and some parts are cropped */
    VM_REGION_FIT_HIDDEN,  /* Do not resize the media object, but fill the box with the background color, or crop the object  */
    VM_REGION_FIT_FILL,    /* Resize the media object so that it fills the width and height defined in the SMIL document  */
    VM_REGION_FIT_SLICE    /* Add a scrolling mechanism if the object exceeds the box */
}vm_region_fit_enum;

/* This enum is used to specify text encoding charset (value refer to IANA MIBEnum).*/
typedef enum
{
    VM_CHARSET_UNKNOWN = 0,        /* Not specified */
    VM_CHARSET_ASCII = 3,          /* ASCII */
    VM_CHARSET_ISO_8859_1 = 4,     /* ISO 8859-1 */
    VM_CHARSET_UTF8 = 106,         /* UFT8 */
    VM_CHARSET_UCS2 = 1000,        /* UCS2 */
    VM_CHARSET_UTF16BE = 1013,     /* UTF16BE */
    VM_CHARSET_UTF16LE = 1014,     /* UTF16LE */
    VM_CHARSET_UTF16 = 1015,       /* UTF16 */
    VM_CHARSET_GB2312 = 2025,      /* GB2312 */
    VM_CHARSET_BIG5 = 2026         /* BIG5 */
}vm_charset_enum;

/* This enum is used to specify UC filter mode. */
typedef enum
{
    VM_UC_FILTER_MODE_AUDIO_OPEN_MODE, /*audio type when creation mode is free*/
    VM_UC_FILTER_MODE_IMAGE_OPEN_MODE, /*image type when creation mode is free*/
    VM_UC_FILTER_MODE_TEXT_OPEN_MODE, /*text type when creation mode is free*/
    VM_UC_FILTER_MODE_VIDEO_OPEN_MODE, /*video type when creation mode is free*/    
    VM_UC_FILTER_MODE_ATTACHMENT_OPEN_MODE, /*image type when creation mode is free*/
    VM_UC_FILTER_MODE_AUDIO_RESTRICTED_MODE, /*audio type when creation mode is restricted*/
    VM_UC_FILTER_MODE_IMAGE_RESTRICTED_MODE, /*image type when creation mode is restricted*/
    VM_UC_FILTER_MODE_TEXT_RESTRICTED_MODE, /*text type when creation mode is restricted*/
    VM_UC_FILTER_MODE_VIDEO_RESTRICTED_MODE, /*video type when creation mode is restricted*/
    VM_UC_FILTER_MODE_ATTACHMENT_RESTRICTED_MODE /*image type when creation mode is restricted*/
}vm_uc_filter_mode_enum;

/* This enum is used to specify UC filter mode. */
typedef enum
{
    VM_EVENT_NEW_MSG,                  /* For new message */
    VM_EVENT_DELETE_MSG,               /* When one message is deleted. Send after delete. */
    VM_EVENT_SAVE_MSG,                 /* When one message is saved to another folder. Send after saved. */
    VM_EVENT_DELETE_FOLDER,            /* Send before delete a folder */
    VM_EVENT_UM_DELETE_FOLDER_DONE,    /* Send after MMA finish deleting folder */
    VM_EVENT_TOTAL
}vm_event_enum;

/* This enum is used to specify MMS contains only one media type objects. */
typedef enum
{
    VM_MEDIA_MSG_NONE = 0, /* Not specified */
    VM_MEDIA_MSG_TEXT,     /* Text MMS: One MMS only contains text object */
    VM_MEDIA_MSG_AUDIO,    /* Audio MMS: One MMS only contains audio object */
    VM_MEDIA_MSG_PHOTO,    /* Photo MMS: One MMS only contains image object */
    VM_MEDIA_MSG_VIDEO     /* Video MMS: One MMS only contains video object */
} vm_media_msg_enum;


/* This enum is used to specify MMS sending size limit */
typedef enum
{
    VM_SETTING_SIZE_LIMIT_100 = 102400,    /* 100KB */
    VM_SETTING_SIZE_LIMIT_300 = 307200,    /* 300KB */
    VM_SETTING_SIZE_LIMIT_600 = 614400,    /* 600KB */
    VM_SETTING_SIZE_LIMIT_MAX 	
}vm_setting_size_limit_enum;

typedef enum
{
    VM_TRUNCATED_ATTACHMENT = 0X01,
    VM_TRUNCATED_SLIDE = 0X02,
    VM_TRUNCATE_TEXT = 0X04,
    VM_TRUNCATED_TOTAL = 0XFF	
}vm_content_truncated_enum;


typedef enum
{
    VM_MSG_STORAGE_NONE = 0X00,
    VM_MSG_STORAGE_PHONE = 0X01,
    VM_MSG_STORAGE_CARD1 = 0X02,
    VM_MSG_STORAGE_TOTAL = 0X03 
} vm_msg_storage_type_enum;

typedef enum
{
    VM_MMS_STORAGE_ACTION_COPY_MMS, 
    VM_MMS_STORAGE_ACTION_MOVE_MMS, 
    VM_MMS_STORAGE_ACTION_TOTAL
}vm_mms_storage_action_type_enum;

/* This enum is used to specify delivery report status (value refer to X-Mms-Status header field). */
typedef enum
{
    VM_MSG_ICON_STATUS_NONE = 0,
    VM_MSG_ICON_STATUS_WAITING_FOR_SEND,       /* MMS status is waiting sending */
    VM_MSG_ICON_STATUS_SENDING,     /* MMS status is sending */
    VM_MSG_ICON_STATUS_SEND_FAIL,      /* MMS status is send failed */
    VM_MSG_ICON_STATUS_POSTPONE_FOR_SEND,      /* MMS status is defered to send*/
    VM_MSG_ICON_STATUS_CORRUPTED_MMS,      /* MMS status is corrupted mms*/
    VM_MSG_ICON_STATUS_JAVA_MMS,  /* MMS status is JAVA mms */
    VM_MSG_ICON_STATUS_PRIO_HIGH_MMS, /* MMS status is high priority MMS */
    VM_MSG_ICON_STATUS_PRIO_LOW_MMS,     /* MMS status is low priority MMS */
    VM_MSG_ICON_STATUS_PRIO_MED_MMS,   /* MMS status is Medium/default priority MMS */
    VM_MSG_ICON_STATUS_DR_MMS,   /* MMS status is Delivery Report */
    VM_MSG_ICON_STATUS_RR_MMS,   /* MMS status is Read Report */
    VM_MSG_ICON_STATUS_DRAFT_MMS,   /* MMS status is draft/Normal MMS */
    VM_MSG_ICON_STATUS_NOTIFICATION_MMS,  /* MMS status is Notification */
    VM_MSG_ICON_TOTAL_MAX_STATUS   /* Total MAX MMS status */
}vm_msg_icon_status_enum;


typedef enum
{
    VM_MMS_FROM_ADDRESS_PRESENT = 128, /*!< The address is added by the client */
    VM_MMS_FROM_INSERT_ADDRESS  = 129  /*!< The address is added by the server */
} vm_mms_from_type_enum;


typedef enum
{
    VM_MMS_TIME_ABSOLUTE           = 128,
    VM_MMS_TIME_RELATIVE           = 129
} vm_mms_time_type_enum;


typedef enum
{
    VM_MMS_READ_REPLY_NOT_SET  =   0,
    VM_MMS_READ_REPLY_YES      = 128,      /*!< Read reply is requested. */
    VM_MMS_READ_REPLY_NO       = 129       /*!< Read reply is not requested. */
} vm_mms_read_reply_enum;


typedef enum
{
    VM_MMS_DELIVERY_REPORT_NOT_SET =   0,
    VM_MMS_DELIVERY_REPORT_YES     = 128,  /*!< Delivery report is requested. */
    VM_MMS_DELIVERY_REPORT_NO      = 129   /*!< Delivery report is not requested. */
} vm_mms_delivery_report_enum;


typedef enum
{
    VM_MMS_SENDER_VISIBILITY_NOT_SET   =   0,  /*!< Show unless sender has secret address*/
    VM_MMS_SENDER_HIDE                 = 128,  /*!< Don't show the address. */
    VM_MMS_SENDER_SHOW                 = 129   /*!< Show even secret address. */
} vm_mms_sender_visibility_enum;


typedef enum
{
    VM_MMS_OBJECT_TYPE_IMAGE,
    VM_MMS_OBJECT_TYPE_AUDIO,
    VM_MMS_OBJECT_TYPE_VIDEO,
    VM_MMS_OBJECT_TYPE_TEXT,
    VM_MMS_OBJECT_TYPE_ATTACHMENT,
	VM_MMS_OBJECT_TYPE_REF,	/*needed by UC*/
    VM_MMS_OBJECT_TYPE_UNKNOWN,
    VM_MMS_OBJECT_TYPE_MAX
} vm_mms_viewer_object_type_enum;

/* This enum is used to define UC current state of operation. It will be need to set when launch UC. As each state have different type of flow. */
typedef enum
{
    VM_MMS_STATE_WRITE_NEW_MSG,     /* Writing new msg state. */
    VM_MMS_STATE_EDIT_EXISTED_MSG,  /* Edit existing msg state. */
    VM_MMS_STATE_FORWARD,           /* Forward existing msg state. Only for inbox and sent box msgs. */
    VM_MMS_STATE_SEND,              /* Send existing msg state. Only for outbox and draft box msgs. */
    VM_MMS_STATE_REPLY,             /* Reply existing msg state. */
    VM_MMS_STATE_REPLY_ALL,         /* Reply all existing msg state. */
    VM_MMS_STATE_TOTAL_NUM          /* Max number of msg states in UC. */
} vm_mms_state_enum;

/* This enum is used to specify the group types of addresses. */
typedef enum
{
    VM_MMS_ADDRESS_GROUP_TYPE_TO,       /* To group. */
    VM_MMS_ADDRESS_GROUP_TYPE_CC,       /* Cc group. */
    VM_MMS_ADDRESS_GROUP_TYPE_BCC,      /* Bcc group. */
    VM_MMS_ADDRESS_GROUP_TYPE_FROM,     /* From group. */
    VM_MMS_ADDRESS_GROUP_TYPE_TOTAL_NUM /* Max number of address group. */
} vm_mms_address_group_type_enum;


typedef struct
{
    VMUINT  msg_id;                             /* Message id */
    VMUINT  msg_size;                           /* The size of message. Counted by byte */
    VMUINT  user_elements_size;                 /* The size of MMS bodies and subject*/
    VMUINT  date;                               /* The date field is in mms header of mms message. It should be given in seconds since 1.Jan. 1970 GMT. */
    VMUINT  expiry_date;                        /* Expiration date. The format is in relative seconds value. */
    VMUINT  received_date;                      /* Received date. This value is only valid for the received MMS message. */
    VMINT16  from_address[VM_MMS_MAX_ADDR_LEN];  /* SRV_MMS_MAX_ADDR_LEN From address of the MMS. Encoded by USC2 */
    VMINT16  subject[VM_MMS_MAX_SUBJECT_LEN];    /* SRV_MMS_MAX_SUBJECT_LEN Subject of the MMS. Encoded by USC2 */
    VMBOOL  need_read_report;              /* Specify if the MMS message require to send read report to sender. */
    VMBOOL  isRead;                        /* Specify if the MMS message is already read. */
    VMBOOL  isForwardLock;                 /* When MMS contain any DRM forward-lock or combine-delivery object, the value is KAL_TRUE. Because separate-delivery DRM object can be forwarded. */
    VMBOOL  isDRM;                         /* When MMS contain any DRM object, the value is KAL_TRUE */
    VMBOOL  isFollowPhoneMMSContentClass;  /* Specify if the MMS follow handset content class */   
    VMBOOL  hasAttachment;                 /* Specify if the MMS message contain any attachment. */
    VMUINT8   result;                             /* 0 means success, other fail */
    VMUINT8   msg_media_type;                     /* vm_mms_media_msg_enum, media type , for no media=0,text=1,audio=2,photo=3,video=4 */
    VMUINT8   from_address_type;                  /* vm_mms_addr_type_enum, from address type,unknown=0,phone=1,email=2,IPV4=3 */
    VMUINT8   msg_type;                           /* vm_mms_msg_type_enum, message type Notification=0,DR=1,RR=2,MMS=3,JAVA=4,Template=5,postcard=6 */
	VMUINT8   storage_type;                       /* vm_mms_msg_storage_type_enum, storage type,phone=1,card=2*/
    VMUINT8   sim_id;                             /* vm_mms_sim_id_enum, sim ID SIM1=1 SIM2=2 SIM3=4 ,SIM4=8 */  
}vm_mms_msg_info;

typedef struct
{
    VMINT sim; // sim card :1,2,3,4
    vm_mms_addr_type_enum addr_type;
    VMWCHAR* addr; // address UCS2
    VMWCHAR* subject; //subject UCS2
    VMWCHAR* content; //content UCS2
    VMWCHAR* att_path; //attach_file
}vm_mms_launch_data;

typedef struct
{
    VMINT result; //0 means success
    VMINT msg_num;
    VMINT msg_id_list[VM_MMS_MSG_ID_LIST_LEN];
}vm_mms_get_msg_id_list_rsp;

typedef struct vm_mms_addr_list_struct_t 
{
	 VMCHAR *address; 
     VMUINT8 addr_type;  /*unused*/  
     VMUINT8 group;      /*unused*/

    /*! Address for current element */
   // vm_mms_address_struct current;                 
    struct vm_mms_addr_list_struct_t *prev;
    /*! Next address list element or NULL if last element */
    struct vm_mms_addr_list_struct_t *next;  
	
} vm_mms_addr_list_struct;

typedef struct
{
    VMUINT8  charset;    /*unused */
    VMCHAR    *text;      /*!< Text buffer, must be NULL terminated */
} vm_mms_encoded_text_struct;

typedef struct
{
    VMUINT8  class_identifier;    /*unused */
    VMCHAR   *text_string;        /*!< Textual representation of a message class */
}vm_mms_msg_class_struct;

typedef struct
{                            

    VMUINT8 version;/*reserved*/

    /*! [M] The address of the message sender. */ 
    vm_mms_addr_list_struct *from;                    

    /*! [O] The addressee of the message. The address field can contain one or
     *      several addresses. The parameter is a reference to a list 
     *      containing the recipient addresses. One element in the list carries 
     *      the address (PLMN or e-mail) and the text string representing the 
     *      recipient real name (e.g. Joe User) to be used in multimedia 
     *      messages. Please note that PLMN addresses cannot make use of real 
     *      names. A message needs always at least one specified address in one
     *      of the to, cc or bcc field.    
     */ 
	 VMUINT8 from_type; /*vm_mms_from_type_enum*/ 


    vm_mms_addr_list_struct *to;                 

    /*! [O] See To field. */    
    vm_mms_addr_list_struct *cc;                 

    /*! [O] See To field. */ 
    vm_mms_addr_list_struct *bcc;                

    /*! [O] The text string containing the subject of the message. See also 
     *      configuration setting for the maximum length of this field in 
     *      mms_cfg.h.
     */
    vm_mms_encoded_text_struct subject;             

    /*! [O] Arrival time (in seconds since 1970-01-01) of the message at the 
     *      MMS Proxy-Relay. The MMS Proxy-Relay will generate this field if 
     *      not supplied.
     */
    VMUINT32 date;                    

    /*! [O] The message class field labels the message type as Auto, 
     *      Informational or Advertisement. When the message class is not set 
     *      the class will be interpreted as Personal at the recipient. It is 
     *      recommended not to set this field in normal MMS Applications. 
     */ 
    vm_mms_msg_class_struct msg_class;           

        
    /*! [O] The type of expiry time, absolute or relative. Absolute means that
     *      an absolute time (in seconds since 1970-01-01) is given. Relative
     *      means that the server will add the given number of seconds to
     *      current time.
     */
    VMUINT8 expiry_time_type;/*vm_mms_time_type_enum*/

    /*! [O] Defines the time when the message will be removed from the 
     *      recipient's MMS Proxy-Relay. If not set the maximum time will be 
     *      used. The maximum value is dependent on the MMS Proxy-Relay. 
     */
    VMUINT32 expiry_time;              

//#ifdef MTK_TMP_PATCH  /* TR 29894 */
    /*! [O] The type of delivery time, absolute or relative. Absolute means that
     *      an absolute time (in seconds since 1970-01-01) is given. Relative
     *      means that the server will add the given number of seconds to
     *      current time.
     */
    VMUINT8 delivery_time_type;/*vm_mms_time_type_enum*/
//#endif

    /*! [O] This time value indicates for the MMS Proxy-Relay when the message 
     *      should be delivered to the recipient(s) at a later time. When this 
     *      field is not set the message is delivered immediately.
     */
    VMUINT32 delivery_time;            

    /*! [O] This value defines the message priority. */ 
    VMUINT8 priority;/*vm_mms_priority_enum*/               

    /*! [O] This value is used to control if the "From" address is displayed 
     *      in the message at the recipient's MMS Application.
     */ 
    VMUINT8 visibility; /*vm_mms_sender_visibility_enum*/    

    /*! [O] This field is requesting the retrieving MMS Applications to send a 
     *      read reply message when the message was read. Note; a retrieving 
     *      MMS Application may cancel the request. A read reply message sent
     *      is seen as an ordinary message and the MMS Application controls 
     *      the contents.
     */ 
    VMUINT8 read_reply;             /*vm_mms_read_reply_enum*/

    /*! [O] The setting of this flag will cause the MMS Proxy-Relay to send 
     *      back a notification message when the recipient retrieves the 
     *      message. A retrieving MMS Application may prevent a Delivery 
     *      Report from being sent.
     */ 
    VMUINT8 delivery_report; /*vm_mms_delivery_report_enum*/
    
    /*! [M] Id of the message.
     *      This field is only used when retrieving a message, NOT used when 
     *      sending.
     */
    VMUINT8 to_num;
  
	VMUINT8 cc_num;
      
	VMUINT8 bcc_num;

	VMUINT8 status;

	VMWCHAR reported_subject[VM_MMS_MAX_SUBJECT_LEN];
     VMCHAR *presentation;
     VMCHAR *app_id;
     VMCHAR *reply_app_id;
	 /*notif*/
     VMUINT32 download_size;
     VMCHAR *content_location;   
	/*report*/
     VMUINT8 dr_status;
     VMUINT8 rr_status;
} vm_mms_header_struct;

typedef struct
{
    vm_mms_header_struct *header;         /* used when parsing */
} vm_mms_description_header_struct;

typedef struct vm_mms_object_struct_t
{
    VMUINT32 size;
    VMUINT32 offset;
    VMUINT32 id;   
	VMUINT32 encoding;
	VMUINT16 reference_count;
    VMUINT32 charset; /*vm_charset_enum*/
    VMCHAR *file_path;     
    VMCHAR *file_name;  
	VMWCHAR *file_path_ucs;     
    VMWCHAR *file_name_ucs;  
	VMWCHAR *mime_type_ext;
	VMUINT8 type;    /*vm_mms_viewer_object_type_enum*/
    VMBOOL is_attachment;
    VMBOOL is_virtual_file;
    VMBOOL rights_expired;
    VMBOOL is_restricted;
	VMBOOL is_mixed_obj;
    VMUINT8 drm_type; /*vm_drm_type_enum*/
    VMUINT8 drm_process_type;
	VMCHAR *mime_str;

	 VMUINT32 drm_ext[5];//SRV_FMGR_PATH_MAX_FILE_EXT_LEN defined in filemgrgprot.h
         VMCHAR *drm_mime_type;
	 VMUINT32 consume_id;
	 VMUINT32 drm_offset;
     VMUINT32 drm_size;
     VMBOOL consume_only_timed;
	 VMBOOL is_drm_processed;
	 VMUINT8 mime_type;/*applib_mime_type_enum*/
	VMCHAR *content_id;       // Used By JSR
    VMCHAR *content_location;  //USED by JSR
	/*requested by ashok to process JSR message */
	VMCHAR *content_type;       
	VMUINT32 content_type_value;
	VMUINT8 encoding_scheme;
	VMBOOL auto_delete_file;
	VMBOOL is_invallid;
	struct vm_mms_object_struct_t *next;
      struct vm_mms_object_struct_t *prev;
//	#ifdef __DRM_SUPPORT__
//	 drm_cid_struct *cid;
//	#endif /* __DRM_SUPPORT__ */      
} vm_mms_object_struct;

typedef struct
{
    VMUINT32 value;
    VMUINT8 type;/*vm_mms_time_type_enum*/
}vm_mms_type_value_struct;

typedef struct
{
    vm_mms_type_value_struct x;  
    vm_mms_type_value_struct y;  
    vm_mms_type_value_struct w;  
    vm_mms_type_value_struct h;  
} vm_mms_object_area_struct;

typedef struct vm_mms_slide_object_struct_t
{
    vm_mms_object_struct *object;
    VMUINT32 begin;   
    VMUINT32 end;    
	vm_mms_object_area_struct *region_area;
    VMCHAR *alt;
    VMUINT16 id;  
	  struct vm_mms_slide_object_struct_t *next;
} vm_mms_slide_object_struct;

typedef struct vm_mms_slide_text_object_struct_t
{
    vm_mms_object_struct *object;
    VMUINT32 bg_color;    
    VMUINT32 fg_color;    
    VMUINT8 text_style;/*vm_text_style_enum*/
    VMUINT16 char_count; 
    VMUINT16 utf8_msg_len;
    VMUINT16 extension_char_count;
    VMUINT16 UCS2_count;
    VMUINT8 text_size;/*vm_text_size_enum*/
    VMUINT32 begin;   
    VMUINT32 end;   
    VMCHAR *alt;
    VMUINT16 id;  
	VMUINT16 str_id;
	
	vm_mms_object_area_struct *region_area;
	
 
}vm_mms_slide_text_object_struct;

typedef struct vm_mms_slide_ref_object_struct_t
{
    vm_mms_object_struct *object;
    VMUINT32 bg_color;    
    VMUINT32 fg_color;   
    VMUINT8 text_style;/*vm_text_style_enum*/
    VMUINT8 text_size;/*vm_text_size_enum*/
    VMUINT32 begin;  
    VMUINT32 end;     
    VMCHAR *alt;
    VMUINT16 id;  
	vm_mms_object_area_struct *region_area;
    struct vm_mms_slide_ref_object_struct_t *next;
    struct vm_mms_slide_ref_object_struct_t *prev;  
} vm_mms_slide_ref_object_struct;

typedef struct vm_mms_slide_struct_t
{	

	struct vm_mms_slide_struct_t *prev;
	vm_mms_slide_object_struct img;
	vm_mms_slide_object_struct vid;
	vm_mms_slide_object_struct aud;
	vm_mms_slide_text_object_struct txt;
	vm_mms_slide_ref_object_struct *ref_items;	
    VMUINT32 duration;   
    VMUINT16 slide_num; 
    struct vm_mms_slide_struct_t *next;
} vm_mms_slide_struct;

typedef struct vm_mms_attachment_info_struct_t
{
	vm_mms_object_struct *object;
    struct vm_mms_attachment_info_struct_t *next;
    struct vm_mms_attachment_info_struct_t *prev;
} vm_mms_attachment_info_struct;

typedef struct{
    vm_mms_slide_struct *slides;
    vm_mms_object_struct *objects;
    vm_mms_slide_struct *curr_slide;
    vm_mms_object_struct *curr_object;
    vm_mms_attachment_info_struct *attachment;
    VMUINT32 slide_no;
    VMUINT32 bgColor; 
    VMUINT32 fgColor;
    VMUINT32 obj_no;
    VMUINT32 total_attach_no;
    VMUINT32 total_ref_no;
    VMUINT16 total_address;
    VMUINT8 layout;/*vm_slide_layout_enum*/
    VMUINT8 text_fit;        /*vm_region_fit_enum*//* this one also insertion of regions in the main context */
    VMUINT8 image_fit;      /*vm_region_fit_enum*//* this one also insertion of regions in the main context */
}vm_mms_description_body_struct;

typedef struct
{
  vm_mms_description_header_struct *header;  /*new one to be used*/
  vm_mms_description_body_struct  *body;
}vm_mms_description_struct;

typedef struct
{
    VMUINT  msg_id;                                         /* Message id */
    VMUINT  req_id;                                         /* request id for get content rsp*/
    VMUINT  mms_header_size;                                /* Size of MMS headers */
    VMUINT  mms_body_size;                                  /* Size of MMS bodies */
    VMBOOL    isFollowPhoneMMSContentClass;             /* Specify if the MMS follow handset content class */
    VMUINT8   app_id;                                         /* unused*/
    VMUINT8   result;                                         /* result  OK=0 */
    VMUINT8   unused;                                       /* Unused */
	vm_mms_description_struct   *content_info;
}vm_mms_get_content_rsp_struct;

typedef void (*vm_mms_get_content_callback_type)(vm_mms_get_content_rsp_struct *rsp_data, void *user_data);

typedef struct
{
    VMUINT  msg_id;                   /* Message id */
    void * user_data;                 /* Service will save this data and will return in callback*/
    vm_mms_get_content_callback_type callback;/*  srv_mms_funcptr_type, Callback API which service will use to response back to caller Application*/
    VMUINT   reserved;              /*reserved*/
    VMUINT8   mode;                     /* vm_app_mode_enum, Content request mode edit=0 send=1 reply=2 replyall=3 forwward=4 upload=5 header=6 view=7 raw=8 abort=10 postcard=11 mixed=12 template=13 */
    VMUINT8   creation_mode;            /* vm_creation_mode_enum, Creation mode to filter content.Free=0,restricted=1,Warning=2*/
}vm_mms_get_content_req_struct;

/*****************************************************************************     
 *
 * FUNCTION
 *    vm_mms_interrupt_callback
 * DESCRIPTION
 *  MMS interrupt callback function 
 * RETURN VALUES   
 *  result :  [IN]  TRUE means deleted the MMS, othewise return FALSE
*****************************************************************************/
typedef VMBOOL (*vm_mms_interrupt_callback)(vm_mms_msg_info* param, void* user_data);


/*****************************************************************************      
 *
 * FUNCTION
 *    vm_mms_delete_callback
 * DESCRIPTION
 *  MMS delete callback function 
 * RETURN VALUES   
 *  
*****************************************************************************/
typedef VMINT (*vm_mms_delete_callback)(
                                VMINT result, VMUINT* msg_id_list,VMINT* result_list,VMUINT num,void* user_data);

/*****************************************************************************      
 *
 * FUNCTION
 *    vm_mms_callback_type
 * DESCRIPTION
 *  MMS callback function 
 * PARAMETERS
 *  result :  [IN]  refer to vm_mms_result_enum.
*****************************************************************************/
typedef void (*vm_mms_callback_type)(VMINT  result);


typedef void (*vm_mms_get_msg_id_list_callback_type)(vm_mms_get_msg_id_list_rsp *rsp_data, void *user_data);


/*****************************************************************************
* FUNCTION
 *    vm_mms_send_mms
 * DESCRIPTION
 *  Send MMS. The result will be returned in callback. 
 * PARAMETERS
 *  req_ptr : [IN]  MMS information to send, refer to vm_send_mms_req_t
 *  callback : [IN] callback function pointer. 
 * RETURNS
 *  send request successfully or failed.
 * RETURN VALUES                                      
 *  FALSE : failed to send request.
 *  TRUE : send request successfully.
 *
*****************************************************************************/
VMINT vm_mms_send_mms(vm_send_mms_req_t * req_ptr,  vm_mms_callback_type callback);

/*****************************************************************************
* FUNCTION
 *    vm_mms_cancel_send_mms
 * DESCRIPTION
 *  Cancel the procedure of sending MMS. If the MMS has sent already and callback
 *  has been invoked or there is no sending function invoked before, this cancelling
 *  will be ignored.
 *
*****************************************************************************/
void vm_mms_cancel_send_mms(void);

/*****************************************************************************
* FUNCTION
 *    vm_mms_launch
 * DESCRIPTION
 *  launch native editor to edit mms
 * PARAMETERS
 *  data : [IN]  MMS info
 *  data_size : [IN] sizeof data
 * RETURN VALUES                                      
 *  0 means success
 *
*****************************************************************************/
VMINT vm_mms_launch(vm_mms_launch_data* data, VMINT data_size);

/*****************************************************************************
* FUNCTION
 *    vm_mms_set_interrupt_event_handler
 * DESCRIPTION
 *  set handler to interrupt MMS
 * PARAMETERS
 *  event : [IN]  MMS event type
 *  callback : [IN] sizeof data
 *  user_data : [IN] user_data
 * RETURN VALUES                                      
 *  0 means success
 *
*****************************************************************************/
VMINT vm_mms_set_interrupt_event_handler(vm_mms_event_enum event, vm_mms_interrupt_callback callback, void* user_data);

/*****************************************************************************
* FUNCTION
 *    vm_mms_clear_interrupt_event_handler
 * DESCRIPTION
 *  clear handler 
 * PARAMETERS
 *  event : [IN]  MMS event type
 * RETURN VALUES                                      
 *  0 means success
 *
*****************************************************************************/
VMINT vm_mms_clear_interrupt_event_handler(vm_mms_event_enum event);

/*****************************************************************************
* FUNCTION
 *    vm_mms_download
 * DESCRIPTION
 *  download mms
 * PARAMETERS
 *  msg_id : [IN]  message id
 *  sim : [IN]  sim card id
 *  storage_type : [IN] storage type    
 * RETURN VALUES  
 *  0 means success
 *
*****************************************************************************/
VMINT vm_mms_download(VMUINT msg_id, vm_mms_sim_id_enum sim, vm_mms_msg_storage_type_enum storage_type);

/*****************************************************************************
* FUNCTION
 *    vm_mms_cancel_download
 * DESCRIPTION
 *  cancel downloading mms
 * PARAMETERS
 *  msg_id : [IN]  message id
 * RETURN VALUES  
 *
*****************************************************************************/
void vm_mms_cancel_download(VMINT msg_id);

/*****************************************************************************
* FUNCTION
 *    vm_mms_delete
 * DESCRIPTION
 *  delete mms
 * PARAMETERS
 *  msg_id_list : [IN]  message id
 *  msg_num : [IN]  sim card id
 *  folder : [IN] storage type    
 *  vm_mms_delete_callback : [IN]  sim card id
 *  user_data : [IN] storage type   
 * RETURN VALUES  
 *  0 means success
 *
*****************************************************************************/
VMINT vm_mms_delete(VMUINT* msg_id_list, VMUINT msg_num, vm_mms_folder_enum folder, vm_mms_delete_callback callback,void* user_data);

/*****************************************************************************
* FUNCTION
 *    vm_mms_get_msg_id_list
 * DESCRIPTION
 *  get mms message id list
 * PARAMETERS
 *  folder : [IN] where to get message
 *  callback : [IN]  callback
 *  user_data: [IN] user data
 * RETURN VALUES  
 *  0 means success
 *
*****************************************************************************/
VMINT vm_mms_get_msg_id_list(vm_mms_folder_enum folder, vm_mms_get_msg_id_list_callback_type callback, void* user_data);

/*****************************************************************************
* FUNCTION
 *    vm_mms_get_content
 * DESCRIPTION
 *  get mms content
 * PARAMETERS
 *  req_data : [IN]  request struct 
 * RETURN VALUES  
 *  0 means success
 *
*****************************************************************************/
VMINT vm_mms_get_content(vm_mms_get_content_req_struct *req_data);

#ifdef __cplusplus
}
#endif

#endif /* VMMMS_SDK_H */




