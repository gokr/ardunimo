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
 * vmpn.h
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  MRE push
 *
 * Author:
 * -------
 * Feng Lin(mtk80996)
 *
*==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *------------------------------------------------------------------------------
 * $Log$
 *
 * 06 14 2012 feng.lin
 * [MAUI_03129054] MRE PUSH Receiver check in CR
 * .
 *
 * 05 15 2012 jianying.li
 * [MAUI_03185909] [MREPUSH2.0] push 2.0 check-in
 * .
 *
 * 05 10 2012 feng.lin
 * [MAUI_02997195] [MRE_SOC]
 * query key supported & pn supported.
 *
 * 04 23 2012 zhibo.tong
 * [MAUI_03129054] MRE PUSH Receiver check in CR
 * .
 *
 * 04 10 2012 zhibo.tong
 * [MAUI_03129054] MRE PUSH Receiver check in CR
 * .
 *
 * 04 10 2012 zhibo.tong
 * [MAUI_03129054] MRE PUSH Receiver check in CR
 * .
 *
 * 04 09 2012 zhibo.tong
 * [MAUI_03129054] MRE PUSH Receiver check in CR
 * .
 *
 * 04 05 2012 feng.lin
 * [MAUI_03129054] MRE PUSH Receiver check in CR
 * .
 *
 * 04 01 2012 feng.lin
 * [MAUI_03129054] MRE PUSH Receiver check in CR
 * .
 *
 * 04 01 2012 zhibo.tong
 * [MAUI_03129054] MRE PUSH Receiver check in CR
 * .
 *
 * 03 27 2012 feng.lin
 * [MAUI_02997195] [MRE_SOC]
 * push.
 *
 * 03 26 2012 zhibo.tong
 * [MAUI_03129054] MRE PUSH Receiver check in CR
 * .
 *
 * 03 22 2012 feng.lin
 * [MAUI_02997195] [MRE_SOC]
 * vmpn.
 *
 * *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *============================================================================== 
 *******************************************************************************/
#ifndef VM_PN_SDK_H
#define VM_PN_SDK_H

     
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vmsys.h"

#define VM_SRV_PNS_ALERT_TEXT_MAX_LEN 150   /* include '\0' */
#define VM_SRV_PNS_MAX_MSGBODY_SIZE 257     /* include '\0' */
#define VM_SRV_PNS_REGID_LEN  26             /* include '\0' */
#define VM_SRV_PNS_ACTION_TEXT_MAX_LEN 51
#define VM_SRV_PNS_MAX_MPS_ARGS_NUM 3
#define VM_SRV_PNS_MAX_MPS_ARG_LEN 21 /* include '\0' */

#define VM_PN_EVT_PARAM_HEADER \
VMUINT16 evt_id; \
VMUINT16 size; \
void * user_data


typedef enum
{
    VM_SRV_PNS_NO_ERROR                         = 0,
    VM_SRV_PNS_SERVICE_NOT_AVAILABLE            = -1,
    VM_SRV_PNS_INVALID_DATA_CONNECTION          = -2,
    VM_SRV_PNS_TOO_MANY_REGISTRATIONS           = -3,
    VM_SRV_PNS_INVALID_SENDER                   = -4,
    VM_SRV_PNS_INVALID_APPID                    = -5,
    VM_SRV_PNS_LAST_MSG_ON_PROCESSING           = -6,
    VM_SRV_PNS_SYSTEM_ERROR                     = -7,

    VM_SRV_PNS_ALREADY_IN_QUEUE                 = -8,
    VM_SRV_PNS_JSON_PARSING_ERR                 = -9,
    VM_SRV_PNS_JSON_PAYLOAD_FORMAT_ERR          = -10,
    VM_SRV_PNS_JSON_PAYLOAD_NOT_FOUND           = -11,

    VM_SRV_PNS_PARAM_ERR                        = -12,
    VM_SRV_PNS_QUERY_FAIL                       = -13,

    VM_SRV_PNS_ERR_TOTAL                        = -100
} vm_srv_pns_result;

typedef enum 
{
	// list/File
	SRV_MRE_PUSH_TYPE_LIST_NULL 				= -100,
	SRV_MRE_PUSH_TYPE_LIST_NOT_FIND,
	SRV_MRE_PUSH_TYPE_FILE_SAVE_FAIL,

	// dereg / reg
	SRV_MRE_PUSH_TYPE_REG_ID_ALREADY_REG 	= -70,
	SRV_MRE_PUSH_TYPE_DEREG_BADPARA,

	// Setting
	SRV_MRE_PUSH_TYPE_SETTING_OFF		= -50,
	
	// normal
	SRV_MRE_PUHS_TYPE_BADPARA   			= -30,
	SRV_MRE_PUHS_TYPE_INTERNAL_ERROR,
	SRV_MRE_PUHS_TYPE_SUCCESS				= 0,
	SRV_MRE_PUHS_TYPE_FILE_EXIT,
	SRV_MRE_PUHS_TYPE_FILE_NOT_EXIT,
	SRV_MRE_PUHS_TYPE_END,
}srv_mre_push_type_enum;


typedef enum
{
	VM_SRV_MRE_MPR_QUERY_APP_ID = 0,
	VM_SRV_MRE_MPR_QUERY_SENDER_ID,		
	VM_SRV_MRE_MPR_QUERY_REGISTER_ID,
    VM_SRV_MRE_MPR_QUERY_SETTING_STATUS,
	VM_SRV_MRE_MPR_QUERY_BADGE,
	VM_SRV_MRE_MPR_QUERY_PAYLOAD,
	VM_SRV_MRE_MPR_QUERY_PAYLOAD_COUNT,
	VM_SRV_MRE_MPR_QUERY_PAYLOAD_BY_INDEX,
	VM_SRV_MRE_MPR_QUERY_MULTIPLE_PAYLOAD,
    VM_SRV_MRE_MPR_QUERY_END,
} vm_srv_pns_query_event;


/*
 * please notify that:high-Weight is means ON/OFF.
 * so if you add style don't change this for new type
 * so never use 0x10000000 express a kind of style,
*/
typedef enum
{
	VM_SRV_MRE_MPR_NOTIFY_STYLE_TEXT_PREVIEW	= 0x00000001,
	VM_SRV_MRE_MPR_NOTIFY_STYLE_POPUP 			= 0x00000010,
    VM_SRV_MRE_MPR_NOTIFY_STYLE_END,
} vm_srv_pns_notify_style;

typedef enum
{
	VM_SRV_MRE_MPR_NOTIFY_OFF = 0x00000000,
	VM_SRV_MRE_MPR_NOTIFY_ON  = 0x10000000,
	VM_SRV_MRE_MPR_NOTIFY_END,
} vm_srv_pns_notify_switch;

typedef struct
{
	VMUINT32  index;
	VMCHAR * app_payload; /*the length of this should be VM_SRV_PNS_MAX_MSGBODY_SIZE or larger*/
}vm_query_one_payload_by_index; /*when user query one payload,should transfer this struct to query function*/

typedef      VMCHAR  	vm_one_payload_struct[VM_SRV_PNS_MAX_MSGBODY_SIZE];
typedef struct
{
	VMUINT32 * payload_count; /*this is an input and also an output*/
	vm_one_payload_struct * app_payload;
}vm_query_multiple_payload_by_count;/*when user query multiple payload,should transfer this struct to query function*/

typedef struct 
{
    VM_PN_EVT_PARAM_HEADER;
}vm_srv_pns_event_struct;

typedef struct 
{
    VM_PN_EVT_PARAM_HEADER;
	VMINT  appId;
    VMCHAR reg_id[VM_SRV_PNS_REGID_LEN];
    vm_srv_pns_result result;	
}vm_srv_pns_identity_event_struct;


typedef struct 
{
    /* alert begin */
    VMINT32 mainLen;
    VMCHAR main[VM_SRV_PNS_ALERT_TEXT_MAX_LEN];
    VMINT32 hintLen;
    VMCHAR hint[VM_SRV_PNS_ALERT_TEXT_MAX_LEN];
    VMINT32 mainResId;
    VMINT32 hintResId;
    /* alert end */

	VMINT32 actionLen;
    VMCHAR  action[VM_SRV_PNS_ACTION_TEXT_MAX_LEN];
	
    VMINT32 badge;
    VMINT32 icon;
    VMINT32 sound;
}vm_srv_pns_msg_mps_struct;

typedef struct 
{
    /* alert begin */
    VMINT32 mainLen;
    VMCHAR main[VM_SRV_PNS_ALERT_TEXT_MAX_LEN];
    VMINT32 hintLen;
    VMCHAR hint[VM_SRV_PNS_ALERT_TEXT_MAX_LEN];
    VMINT32 mainResId;
	VMCHAR main_args[VM_SRV_PNS_MAX_MPS_ARGS_NUM][VM_SRV_PNS_MAX_MPS_ARG_LEN];
    VMINT32 main_args_num;

    VMINT32 hintResId;
	VMCHAR hint_args[VM_SRV_PNS_MAX_MPS_ARGS_NUM][VM_SRV_PNS_MAX_MPS_ARG_LEN];
    VMINT32 hint_args_num;
    /* alert end */

	VMINT32 actionLen;
    VMCHAR  action[VM_SRV_PNS_ACTION_TEXT_MAX_LEN];
	VMINT32 actionResId;
	
    VMINT32 badge;
    VMINT32 icon;
    VMINT32 sound;
}vm_srv_pns_msg_mps_struct_ex;
typedef struct 
{
    VMBYTE dictionary;
    VMCHAR msgBody[VM_SRV_PNS_MAX_MSGBODY_SIZE];
}vm_srv_pns_msg_value_struct;


typedef VMINT (*vm_pn_cb)(vm_srv_pns_event_struct * evt, void * user_data);


VMINT vm_pn_is_support(void);

VMINT vm_pn_get_global_setting(void); // 0 off; 1 on.

VMINT vm_pn_reg(vm_pn_cb cb, void* user_data);
VMINT vm_pn_dereg();
VMINT vm_pn_query(vm_srv_pns_query_event query_id, void * user_data);
VMINT vm_pn_get_mps_info(const VMCHAR * msgBody, vm_srv_pns_msg_mps_struct * mpsPtr);
VMINT vm_pn_get_object(const VMCHAR * msgBody, const VMCHAR * key, vm_srv_pns_msg_value_struct * value);
VMINT vm_pn_set_notify_style(vm_srv_pns_notify_switch OnOff, vm_srv_pns_notify_style style);
VMINT vm_pn_set_badge(VMINT32 badge_number);
VMINT vm_pn_get_mps_info_ex(const VMCHAR * msgBody, vm_srv_pns_msg_mps_struct_ex * mpsPtr);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VM_PN_H */
