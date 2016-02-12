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

#ifndef VMKEYPAD_SDK_H
#define VMKEYPAD_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* Key events supported by MRE. */

#define VM_KEY_EVENT_UP       (1)       /* Key up event */
#define VM_KEY_EVENT_DOWN        (2)    /* Key down event */
#define VM_KEY_EVENT_LONG_PRESS  (3)    /* Key long press event */
#define VM_KEY_EVENT_REPEAT      (4)    /* Key repeat event */

/* Key codes supported by MRE. */

#define VM_KEY_UP             (-1)      /* Arrow key up */
#define VM_KEY_DOWN           (-2)      /* Arrow key down */
#define VM_KEY_LEFT              (-3)   /* Arrow key left */
#define VM_KEY_RIGHT          (-4)      /* Arrow key right */
#define VM_KEY_LEFT_SOFTKEY      (-6)   /* Left soft key */
#define VM_KEY_RIGHT_SOFTKEY     (-7)   /* Right soft key */
#define VM_KEY_OK             (-5)      /* OK key */
#define VM_KEY_CLEAR          (-8)      /* Clear key */
#define VM_KEY_BACK              (-9)   /* Back key */
#define VM_KEY_HOME             (-10)    /* Key home */
#define VM_KEY_END                (-11)    /* key end */
#define VM_KEY_POWER          (-12)     /* Power key, not available on all PF */
#define VM_KEY_NUM0           (48)      /* Number key 0 */
#define VM_KEY_NUM1           (49)      /* Number key 1 */
#define VM_KEY_NUM2           (50)      /* Number key 2 */
#define VM_KEY_NUM3           (51)      /* Number key 3 */
#define VM_KEY_NUM4           (52)      /* Number key 4 */
#define VM_KEY_NUM5           (53)      /* Number key 5 */
#define VM_KEY_NUM6           (54)      /* Number key 6 */
#define VM_KEY_NUM7           (55)      /* Number key 7 */
#define VM_KEY_NUM8           (56)      /* Number key 8 */
#define VM_KEY_NUM9           (57)      /* Number key 9 */
#define VM_KEY_VOL_UP            (58)   /* Volume key up */
#define VM_KEY_VOL_DOWN       (59)      /* Volume key down */
#define VM_KEY_POUND          (35)      /* Key # */
#define VM_KEY_STAR              (42)   /* Key * */

/* Key codes from A to Z on a qwerty keypad, each code represents the Unicode value of the corresponding capital letter. */
#define  VM_KEY_A 65    /* A */
#define  VM_KEY_B 66    /* B */
#define  VM_KEY_C 67    /* C */
#define  VM_KEY_D 68    /* D */
#define  VM_KEY_E 69    /* E */
#define  VM_KEY_F 70    /* F */
#define  VM_KEY_G 71    /* G */
#define  VM_KEY_H 72    /* H */
#define  VM_KEY_I 73    /* I */
#define  VM_KEY_J 74    /* J */
#define  VM_KEY_K 75    /* K */
#define  VM_KEY_L 76    /* L */
#define  VM_KEY_M 77    /* M */
#define  VM_KEY_N 78    /* N */
#define  VM_KEY_O 79    /* O */
#define  VM_KEY_P 80    /* P */
#define  VM_KEY_Q 81    /* Q */
#define  VM_KEY_R 82    /* R */
#define  VM_KEY_S 83    /* S */
#define  VM_KEY_T 84    /* T */
#define  VM_KEY_U 85    /* U */
#define  VM_KEY_V 86    /* V */
#define  VM_KEY_W 87    /* W */
#define  VM_KEY_X 88    /* X */
#define  VM_KEY_Y 89    /* Y */
#define  VM_KEY_Z 90    /* Z */
#define  VM_KEY_SPACE 91    /* Space */
#define  VM_KEY_TAB 92    /* Tab */
#define  VM_KEY_DEL 93    /* Delete */
#define  VM_KEY_ALT 94    /* Alt */
#define  VM_KEY_CTRL 95    /* Ctrl */
#define  VM_KEY_WIN 96    /* Winodows key */
#define  VM_KEY_SHIFT 97    /* Shift */
#define  VM_KEY_QUESTION 98    /* Question */
#define  VM_KEY_PERIOD 99    /* Period */
#define  VM_KEY_COMMA 100    /* Comma (,) */
#define  VM_KEY_EXCLAMATION 101    /* Exclamation (!) */
#define  VM_KEY_APOSTROPHE 102    /* Apostrophe (') */
#define  VM_KEY_AT 103    /* @ */
#define  VM_KEY_BACKSPACE 104    /* Backspace */
#define  VM_KEY_QWERTY_ENTER 105    /* Qwerty enter */
#define  VM_KEY_FN 106    /* Function */
#define  VM_KEY_SYMBOL 107    /* Symbol */
#define  VM_KEY_NUM_LOCK 108    /* Number lock */
#define  VM_KEY_QWERTY_MENU 109    /* Qwerty menu */

/*****************************************************************************
 * FUNCTION
 *  vm_kbd_is_key_supported
 * DESCRIPTION
 *  query if specified key code is supported
 * PARAMETERS
 *  keycode    [IN]    key code
 * RETURNS
 *  non-zero  : supported.
 *  zero      : unsupported
 *****************************************************************************/
VMINT vm_kbd_is_key_supported(VMINT keycode);


typedef enum
{
    VM_DEVCONFIG_KEYPAD_TYPE_NORMAL,     /* normal keypad type */
    VM_DEVCONFIG_KEYPAD_TYPE_REDUCED,    /* reduced keypad type */
    VM_DEVCONFIG_KEYPAD_TYPE_QWERTY,     /* qwerty keypad type */
    VM_DEVCONFIG_KEYPAD_TYPE_TOTAL
} vm_devconfig_keypad_type_enum;


/*****************************************************************************
* FUNCTION
*  vm_get_keypad_type
* DESCRIPTION
*  check the current type of keypad
* PARAMETERS
*  void
* RETURN VALUES
*  less than zero : failure
*  VM_DEVCONFIG_KEYPAD_TYPE_NORMAL : normal keypad type.
*  VM_DEVCONFIG_KEYPAD_TYPE_REDUCED : reduced keypad type.
*  VM_DEVCONFIG_KEYPAD_TYPE_QWERTY : qwerty keypad type.
*****************************************************************************/
VMINT vm_get_keypad_type(void);

typedef enum
{
    /* KEY1 Number */
    VM_KEYPAD_1KEY_NUMBER = 0,
    /* KEY2 Number */
    VM_KEYPAD_2KEY_NUMBER,
    /* reserved */
    VM_KEYPAD_3KEY_NUMBER,
    /* KEY1 Qwerty */
    VM_KEYPAD_1KEY_QWERTY,
    /* KEY2 Qwerty */
    VM_KEYPAD_2KEY_QWERTY,
    /* reserved */
    VM_KEYPAD_3KEY_QWERTY,
    /* reserved */
    VM_KEYPAD_MODE_END
} vm_keypad_mode_enum;

typedef enum
{
    VM_KBD_MODE_ERR_PARAM = -2, /* input invalid parameter */
    VM_KBD_MODE_ERR_NOT_AUTHORIZED, /* no authrization */
    VM_KBD_MODE_ERR_SUCCESS = 0 /* success */
}vm_kbd_mode_error_t;

/*****************************************************************************
 * FUNCTION
 *  vm_kbd_set_mode
 * DESCRIPTION
 *  set the concurrent key mode
 * PARAMETERS
 *  mode : [IN] see vm_keypad_mode_enum
 * RETURNS
 *  vm_kbd_mode_error_t
 * RETURN VALUES
 *  0 : success
 *  non-zero : failure
 *****************************************************************************/
VMINT vm_kbd_set_mode(VMUINT8 mode);

/*****************************************************************************
 * FUNCTION
 *  vm_is_support_keyborad
 * DESCRIPTION
 *  Check whether the phone support keypad or not.
 * PARAMETERS
 *  void
 * RETURN VALUES
 *  TRUE : Supports keypad.
 *  FALSE : Not support.
 *****************************************************************************/
VMINT vm_is_support_keyborad(void);



/*****************************************************************************
 * <GROUP  CallbackFunctions>
 *
 * FUNCTION
 *  vm_key_handler_t
 * DESCRIPTION
 *  Callback function type for key event handler.
 * PARAMETERS
 *  event : [IN] Key event.
 *  keycode : [IN] Key code.
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_key_handler_t)(VMINT event, VMINT keycode);

/*****************************************************************************
 * <GROUP  CallbackFunctions>
 *
 * FUNCTION
 *  vm_key_handler_ex_t
 * DESCRIPTION
 *  Callback function type for key event handler.
 * PARAMETERS
 *  event : [IN] Key event.
 *  keycode : [IN] Key code.
 * RETURNS
 *  void
 *****************************************************************************/
typedef VMINT (*vm_key_handler_ex_t)(VMINT event, VMINT keycode);

/*****************************************************************************
 * FUNCTION
 *  vm_reg_keyboard_callback
 * DESCRIPTION
 *  Registers key handler.
 * PARAMETERS
 *  vm_key_handler_t : [IN] Key event handler.
 * RETURNS
 *  void
 *****************************************************************************/
void vm_reg_keyboard_callback(vm_key_handler_t handler);

/*****************************************************************************
 * FUNCTION
 *  vm_reg_keyboard_callback
 * DESCRIPTION
 *  Registers key extension handler. app will take the key event
 *  and not give it back to platform if return value from callback is non-zero,
 *  else not.
 * PARAMETERS
 *  vm_key_handler_ex_t : [IN] Key extension event handler.
 * RETURNS
 *  void
 *****************************************************************************/
VMINT vm_reg_keyboard_callback_ex(vm_key_handler_ex_t handler);

#ifdef __cplusplus
}
#endif

#endif /* VMKEYPAD_SDK_H */ 

