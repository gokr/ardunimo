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

#ifndef VMSALUI_SDK_H_
#define VMSALUI_SDK_H_

#include "vmsys.h"

/* If set thsi flag for behavior_mask, it will show nothing if this ui is not supported */
#define VM_COMMON_UI_MASK_NO_SHOW_UNSUPPORTED 0x1

typedef enum
{
	VM_COMMON_UI_ERROR_INVALID_ID = -7,
	VM_COMMON_UI_ERROR_OF_PROCESS,
	VM_COMMON_UI_ERROR_OF_RES ,
	VM_COMMON_UI_ERROR_OF_MEM ,
	VM_COMMON_UI_ERROR_UNSUPPORTED,
	VM_COMMON_UI_ERROR_WRONG_PARAM,
	VM_COMMON_UI_ERROR ,
	VM_COMMON_UI_OK
} vm_common_ui_error_t;

/* popup type */
typedef enum
{
    VM_COMMON_UI_POPUP_TYPE_FAILURE,
    VM_COMMON_UI_POPUP_TYPE_INFO,
    VM_COMMON_UI_POPUP_TYPE_WARNING,
    VM_COMMON_UI_POPUP_TYPE_SUCCESS,
    VM_COMMON_UI_POPUP_TYPE_PROGRESS,
    VM_COMMON_UI_POPUP_TYPE_QUERY,
    
    VM_COMMON_UI_POPUP_TYPE_MAX    
} vm_common_ui_popup_type_enum;

/* confirm type - one button(confirm) or two button(user defeind and cancel) */
typedef enum
{
    VM_COMMON_UI_CONFIRM_TYPE_ONE_BUTTON,
    VM_COMMON_UI_CONFIRM_TYPE_TWO_BUTTON,
    
    VM_COMMON_UI_CONFIRM_TYPE_MAX
} vm_common_ui_confirm_type_enum;

/* common ui type */
typedef enum
{
	VM_COMMON_UI_TYPE_BALLOON,
	VM_COMMON_UI_TYPE_TEXT_PREVIEW,	// If app is foreground, text preview just can show when statusbar exist
	VM_COMMON_UI_TYPE_POPUP,
	VM_COMMON_UI_TYPE_CONFIRM,
	VM_COMMON_UI_TYPE_END_OF_ENUM
}vm_common_ui_type;						   

/* receive event in confirm popup callback function */
typedef enum
{    
    VM_COMMON_UI_CONFIRM_EVENT_BUTTON_NONE,
    VM_COMMON_UI_CONFIRM_EVENT_USER_1,
    VM_COMMON_UI_CONFIRM_EVENT_USER_2,
    
    VM_COMMON_UI_CONFIRM_EVENT_MAX
} vm_common_ui_confirm_evt_enum;

typedef void (*VM_COMMONUIPROC_T)(vm_common_ui_confirm_evt_enum evt_id, void *user_data);


/* Balloon information */    
typedef struct {
    const VMWCHAR *display_string;
}vm_common_ui_balloon_struct;

/* Text preview information */
typedef struct {
    const VMWCHAR *display_string;
}vm_common_ui_text_preview_struct;

/* Popup information*/    
typedef struct {
    vm_common_ui_popup_type_enum popup_type;
    const VMWCHAR *display_string;
}vm_common_ui_popup_struct;

/* Confirm Popup information*/
typedef struct
{    
    vm_common_ui_confirm_type_enum confirm_type;	
	vm_common_ui_popup_type_enum confirm_popup_type;
    const VMWCHAR *popup_string;
    const VMWCHAR *popup_button_string1;
    const VMWCHAR *popup_button_string2;
	VM_COMMONUIPROC_T confirm_popup_proc;
	void *user_data;
} vm_common_ui_confirm_popup_struct;


typedef struct
{
	vm_common_ui_type ui_type;
	VMUINT16 behavior_mask;

    /*balloon parameter*/
    vm_common_ui_balloon_struct balloon_para;   	
    /*text preview parameter*/
    vm_common_ui_text_preview_struct text_preview_para;   
    /*popup parameter*/    
    vm_common_ui_popup_struct popup_para; 
    /*confirm popup parameter*/    
    vm_common_ui_confirm_popup_struct confirm_popup_para; 
}vm_common_ui_info_struct;

VMINT vm_common_ui_show(vm_common_ui_info_struct *ui_info);
VMINT vm_common_ui_cancel(VMINT id);


#endif
