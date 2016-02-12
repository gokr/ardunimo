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
 * vmuimisc_sdk.h
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  ui misc
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
#ifndef VM_UIMISC_SDK_H
#define VM_UIMISC_SDK_H
#ifdef __cplusplus
extern "C"{
#endif/*__cplusplus*/
#include "vmsys.h"
typedef enum
{
   VM_TOUCH_FEEDBACK_DOWN,
    VM_TOUCH_FEEDBACK_DOWN_VIBRATE,
    VM_TOUCH_FEEDBACK_DOWN_TONE,
    VM_TOUCH_FEEDBACK_HOLD,
    VM_TOUCH_FEEDBACK_SPECIAL,
    VM_TOUCH_FEEDBACK_TOTAL
} vm_touch_feedback_enum;

typedef enum
{
    VM_SCREEN_ROTATE_0,   /* Normal screen */
    VM_SCREEN_ROTATE_90,  /* Rotate 90 clockwise */
    VM_SCREEN_ROTATE_180, /* Rotate 180 */
    VM_SCREEN_ROTATE_270, /* Rotate 270 clockwise */

	/*Add new enums above this*/
	VM_SCREEN_ROTATE_END = 0XFFFF
} vm_screen_rotate_enum;

#define VM_PI         3.1415926f

/* General color type methods */
#define VM_COLOR32_MAKE(a, r, g, b)      ((VMCOLOR32)((VMUINT32)(a) << 24 | (VMUINT32)(r) << 16 | (VMUINT32)(g) << 8 | (VMUINT32)(b)))
#define VM_COLOR32_GET_A(c)              ((c) >> 24)
#define VM_COLOR32_GET_R(c)              ((c) << 8 >> 24)
#define VM_COLOR32_GET_G(c)              ((c) << 16 >> 24)
#define VM_COLOR32_GET_B(c)              ((c) << 24 >> 24)

/* default colors */
#define VM_COLOR32_BLACK                 VM_COLOR32_MAKE(255, 0, 0, 0)
#define VM_COLOR32_WHITE                 VM_COLOR32_MAKE(255, 255, 255, 255)
#define VM_COLOR32_RED                   VM_COLOR32_MAKE(255, 255, 0, 0)
#define VM_COLOR32_GREEN                 VM_COLOR32_MAKE(255, 0, 255, 0)
#define VM_COLOR32_BLUE                  VM_COLOR32_MAKE(255, 0, 0, 255)
#define VM_COLOR32_AQUA                  VM_COLOR32_MAKE(255, 0, 255, 255)
#define VM_COLOR32_FUCHSIA               VM_COLOR32_MAKE(255, 255, 0, 255)
#define VM_COLOR32_YELLOW                VM_COLOR32_MAKE(255, 255, 255, 0)
#define VM_COLOR32_GREY                  VM_COLOR32_MAKE(255, 128, 128, 128)
#define VM_COLOR32_TEAL                  VM_COLOR32_MAKE(255, 0, 128, 128)
#define VM_COLOR32_PURPLE                VM_COLOR32_MAKE(255, 128, 0, 128)
#define VM_COLOR32_OLIVE                 VM_COLOR32_MAKE(255, 128, 128, 0)
#define VM_COLOR32_SILVER                VM_COLOR32_MAKE(255, 192, 192, 192)
#define VM_COLOR32_TRANSPARENT           VM_COLOR32_MAKE(0, 0, 0, 255)

/* Redian convert macros */
#define VM_DEG_TO_RAD(x)               ((VMFLOAT)((VMFLOAT)(x)) * VM_PI / 180.0f)
#define VM_RAD_TO_DEG(x)               ((VMFLOAT)((VMFLOAT)(x)) * 180.0f / VM_PI)

/* Float, Fixed conversion */
#define VM_X_TO_F(x)                   ((VMFLOAT)x / 65536.0f)
#define VM_F_TO_X(x)                   (VMINT32)((x) * 65536.0f)

/*****************************************************************************
 * FUNCTION
 *  vm_get_sys_scene
 * DESCRIPTION
 *  get system setting profile
 * PARAMETERS
 *  void
 * RETURNS
 *  0 : standard mode
 *  1: meeting mode
 *  2: outside mode
 *  3: indoor mode
 *  4: earphone mode
 *  5: silent mode
 *  6: bluetooth mode
 *****************************************************************************/ 
VMINT vm_get_sys_scene(void);
/*****************************************************************************
 * FUNCTION
 *  vm_clipboard_is_available
 * DESCRIPTION
 *  Check whether the current project support clipboard
 * PARAMETERS
 *  NULL
 * RETURNS
 *  TRUE : Support clipboard
 *  FALSE: Not support clipboard
 *****************************************************************************/
VMBOOL vm_clipboard_is_available(void);

/*****************************************************************************
 * FUNCTION
 *  vm_clipboard_text_set_data
 * DESCRIPTION
 *  Set text data to clipboard.
 *  The text encoded type should be unicode.
 *  Clipboard only could stores 2048 wchars at most.
 *  The memory is provided by system.
 * PARAMETERS
 *  str     : [IN] unicode string pointer
 *  str_len : [IN] string length (could be less than the total length, in other words, a part of string)
 * RETURNS
 *  TRUE : 1. Operation success
 *         2. str == NULL (clear the clipboard)
 *  FALSE: 1. memory not enough
 *         2. memory overlapped
 *         3. str_len <= 0
 *****************************************************************************/
VMBOOL vm_clipboard_text_set_data(const VMWSTR str, VMUINT str_len);


/*****************************************************************************
 * FUNCTION
 *  vm_clipboard_text_get_data
 * DESCRIPTION
 *  Get text data from clipboard.
 *  This is a blobal string pointer saved in system memory.
 * PARAMETERS
 *  void
 * RETURNS
 *  Valid pointer: unicode string pointer
 *  NULL: clipboard is empty
 *****************************************************************************/
VMWSTR vm_clipboard_text_get_data(void);

void vm_set_touch_feedback ( vm_touch_feedback_enum type);

#ifdef __cplusplus
}
#endif/*__cplusplus*/

#endif/*VM_UIMISC_SDK_H*/