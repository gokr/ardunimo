/*******************************************************************************
*  Modification Notice:
*  --------------------------
*  This software is modified by MediaTek Inc. and the information contained
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
*******************************************************************************/

 /*******************************************************************************
 * Filename:
 * ---------
 *  vmeditor_sdk.h
 *
 * Project:
 * --------
 *  Maui_Software
 *
 * Description:
 * ------------
 *  Inline editor APIs
 *
 * Author:
 * -------
 *  Keith Chen
 *
 *==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!! 
 *------------------------------------------------------------------------------
 * $Log$
 *
 * 07 09 2014 liu.cheng
 * [MAUI_03508170] [Wearable_Phase2] VM_GRAPH_ID_3 of ID_14~15.vxp is crashing
 * .
 * 
 * 09 03 2012 hongtao.liu
 * [MAUI_03230059] [RenRenV2.0][Renren_QVGA_Key_2M_20120829.vxp]已输入的帐号信息显示不完整
 * add new API : vm_editor_show_from_start.
 *
 * 07 14 2012 hongtao.liu
 * [MAUI_03213274] [ARTMicroBlogV3Vxp_HVGA_0707.vxp]转发微博时，应该highlight最前面
 * add API : vm_editor_show_from_first_line
 *
 * 06 27 2012 hongtao.liu
 * [MAUI_03112870] Check in MRE editor
 * add vm_editor_get_cursor_index, vm_editor_set_cursor_index, vm_editor_insert_string, vm_editor_set_default_text.
 *
 * 06 05 2012 hongtao.liu
 * [MAUI_03191785] [MRE][Inline Editor] check in MRE Editor
 * 
 * add api : vm_editor_set_imui_background_filler and vm_editor_set_update_text_with_cursor_rect_callback
 * 
 *
 * 05 25 2012 hongtao.liu
 * [MAUI_03191785] [MRE][Inline Editor] check in MRE Editor
 * check in MRE Editor
 * 
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================
 *******************************************************************************/
#ifndef VMEDITOR_SDK_H_
#define VMEDITOR_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"
#include "vmgraph.h"
#include "vmio.h"
#include "vminput.h"

/***************************************************************************** 
* Define
*****************************************************************************/
/* Enum values which are used to describe different types of softkey. */
typedef enum
{
    VM_LEFT_SOFTKEY,    /* Is an enum value which represents the left softkey */
    VM_RIGHT_SOFTKEY,   /* Is an enum value which represents the right softkey */
    VM_CENTER_SOFTKEY,  /* Is an enum value which represents the center softkey */

    /* DOM-NOT_FOR_SDK-BEGIN */
    VM_MAX_SOFTKEYS /* Is the max count of all softkeys */
    /* DOM-NOT_FOR_SDK-END */
} VM_SOFTKEY_ENUM;

typedef enum
{
    VM_EDITOR_NO_BORDER,
    VM_EDITOR_SINGLE_BORDER,
    VM_EDITOR_DOUBLE_BORDER,
    VM_EDITOR_BORDER_END
} VM_EDITOR_BORDER_TYPE;

/*
 * The 24 bits of input type are internally divided two parts
 * 1. 0-19 bit are used for generic cases (Currently 18 bits out of which are being used)
 * 2. 20-24 bit are used for external input types for special scenarios
 */
typedef enum
{
    VM_INPUT_TYPE_NONE = 0,
    VM_INPUT_TYPE_NUMERIC = 0x1,                            /* For Number only */
    VM_INPUT_TYPE_PHONE_NUMBER = (0x1 << 1),                /* For Phone Number */
    VM_INPUT_TYPE_DECIMAL_NUMERIC = (0x1 << 2),             /* For  Number with Decimal */
    VM_INPUT_TYPE_SIGNED_NUMERIC = (0x1 << 3),              /* For Signed Numbers */
    VM_INPUT_TYPE_SIGNED_DECIMAL_NUMERIC = (0x1 << 4),      /* For Signed Numbers with Decimal */
    VM_INPUT_TYPE_URL = (0x1 << 5),                         /* For url input */
    VM_INPUT_TYPE_QUICK_SEARCH = (0x1 << 6),                /* For quick search */
    VM_INPUT_TYPE_SENTENCE = (0x1 << 7),                    /* all kind of character are allowed  */
    VM_INPUT_TYPE_ENGLISH_SENTENCE = (0x1 << 8),            /* only English character are allowed. */
    VM_INPUT_TYPE_USER_SPECIFIC = (0x1 << 9),               /* App defines the input method it wants */
    VM_INPUT_TYPE_KEYPAD_NUMERIC = (0x1 << 10), /* For all numbers mapped on keyboard 0-9 * and # */
    VM_INPUT_TYPE_SIM_NUMERIC = (0x1 << 11),                /* for numeric input with + and * */
    VM_INPUT_TYPE_ENGLISH_SENTENCE_UPPERCASE = (0x1 << 12), /* English  with Uppercase */
    VM_INPUT_TYPE_ENGLISH_SENTENCE_LOWERCASE = (0x1 << 13), /* English  with Lowercase */
    VM_INPUT_TYPE_EMAIL = (0x01 << 14),                     /* For Email Input */
    VM_INPUT_TYPE_PHONE_NUMBER_WILDCHAR = (0x01 << 15),     /* For Phone number with + , p , w and ? */
    VM_INPUT_TYPE_NUMERIC_SYMBOL = (0x01 << 16),            /* For number input with symbold allowed */
    VM_INPUT_TYPE_ASCII_CHAR = (0x01 << 17),                /* ALL ASCII Characters  */
    VM_INPUT_TYPE_NO_TITLECASE_SENTENCE = (0x01 << 18),     /* All characters , but no titlecase */
    VM_INPUT_TYPE_SAT_NUMERIC_PASSWORD = (VM_INPUT_TYPE_KEYPAD_NUMERIC | 0x800000),
    VM_INPUT_TYPE_DECIMAL_NUMERIC_PASSWORD = (VM_INPUT_TYPE_DECIMAL_NUMERIC | 0x800000),
    VM_INPUT_TYPE_SIGNED_NUMERIC_PASSWORD = (VM_INPUT_TYPE_SIGNED_NUMERIC | 0x800000),
    VM_INPUT_TYPE_SIGNED_DECIMAL_NUMERIC_PASSWORD = (VM_INPUT_TYPE_SIGNED_DECIMAL_NUMERIC | 0x800000),
    VM_INPUT_TYPE_NUMERIC_PASSWORD = (VM_INPUT_TYPE_NUMERIC | 0x800000),
    VM_INPUT_TYPE_ALPHANUMERIC_PASSWORD = (VM_INPUT_TYPE_ENGLISH_SENTENCE | VM_INPUT_TYPE_NUMERIC_SYMBOL | 0x800000),
    VM_INPUT_TYPE_ASCII_PASSWORD = (VM_INPUT_TYPE_ASCII_CHAR | 0x800000),
    VM_INPUT_TYPE_MULTITAP_SENTENCE = (0x200000 | VM_INPUT_TYPE_SENTENCE),
    VM_INPUT_TYPE_END
} vm_input_type_enum;

typedef enum
{
    VM_EDITOR_MESSAGE_NONE = 0x0,
    VM_EDITOR_MESSAGE_REDRAW_FLOATING_UI,
    VM_EDITOR_MESSAGE_ACTIVATE,
    VM_EDITOR_MESSAGE_DEACTIVATE,
    VM_EDITOR_MESSAGE_REDRAW_IMUI_RECTANGLE,
    VM_EDITOR_MESSAGE_END
} vm_editor_message_id_enum;

typedef enum
{
    VM_EDITOR_SINGLELINE,
    VM_EDITOR_MULTILINE,
    VM_EDITOR_END
} VM_EDITOR_TYPE;

typedef struct
{
    VMINT32 x;
    VMINT32 y;
    VMINT32 width;
    VMINT32 height;
} vm_editor_rect;

typedef struct
{
    VMUINT32 message_id;
    vm_editor_rect rect;    /* floating UI rectangle or IMUI rectangle */
} vm_editor_message_struct, *vm_editor_message_struct_p;

typedef struct
{
    VMUINT8 bold;
    VMUINT8 italic;
    VMUINT8 underline;
    VMUINT8 size;
} vm_editor_font_attribute;

typedef struct
{
	VMINT32 x1, y1, x2, y2;
} vm_editor_rect_points, *vm_editor_rect_points_p;

/*****************************************************************************
 * FUNCTION
 *  Soft key callback function.
 * DESCRIPTION
 *  This callback will be invoke when the soft key be pressed.
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_soft_key_handle_funcptr) (void);

// TODO: VM_EDITOR_MESSAGE_DEACTIVATE param??
/*****************************************************************************
 * FUNCTION
 *  IME callback function.
 * DESCRIPTION
 *  This Call back is used to receive IME message, message id refer to vm_editor_message_id_enum.
 *  1. When floating UI overlap the editor, we send message VM_EDITOR_MESSAGE_REDRAW with parameters:
 *    msg_ptr->param_0 : 1
 *    msg_ptr->param_1 : (vm_editor_rect *)floating UI rectangle 
 *    In this case, you do not need to redraw the whole screen, only need to redraw the affected area(previous floating UI rectangle).
 *  2. When application call vm_editor_activate(), we send message VM_EDITOR_MESSAGE_ACTIVATE with parameters:
 *    msg_ptr->param_0 : reserved
 *    msg_ptr->param_1 : reserved
 *  3. When application call vm_editor_deactivate(), we send message VM_EDITOR_MESSAGE_DEACTIVATE with parameters:
 *    msg_ptr->param_0 : 1
 *    msg_ptr->param_1 : reserved
 *  4. When Virtual Keypad(VK) update status, we send message VM_EDITOR_MESSAGE_VK_STATUS with parameters:
 *    msg_ptr->param_0 : VK width
 *    msg_ptr->param_1 : VK height
 * PARAMETERS
 *  editor_handle          : [IN] Is the editor handle
 *  msg_ptr          : [IN] Is the message pointer
 * RETURNS
 *  Reserved (PLease return 0 now).
 *****************************************************************************/
typedef VMUINT32(*vm_editor_message_funcptr) (VMINT32 editor_handle, vm_editor_message_struct_p msg_ptr);

/*****************************************************************************
 * FUNCTION
 *  Text update callback function.
 * DESCRIPTION
 *  This callback will be invoke when User input a charactor.
 * PARAMETERS
 *  text          : [IN] Point to the begin of the input string.
 *  cursor          : [IN] Point to the current cusor position.
 *  text_length          : [IN] Length of the input string.
 * RETURNS
 *  void
 *****************************************************************************/
typedef void (*vm_update_text_funcptr) (VMUINT8 *text, VMUINT8 *cursor, VMINT32 text_length);

/*****************************************************************************
 * FUNCTION
 *	Text update with cursor rect callback function
 * DESCRIPTION
 *	This callback will be invoked when user input or delete a charactor.
 *	The difference between this callback and vm_update_text_funcptr is:
 *		vm_update_text_funcptr will be invoked before editor redraw.
 *		vm_update_text_with_cursor_rect_funcptr will be invoked after editor redraw.
 * PARAMETERS
 *	text	:				[IN]	Point to the begin of the input string.
 *	cursor	:				[IN]	Point to the current cursor position.
 *	text_length	:			[IN]	length of the input string.
 *	cursor_rect_points	:	[IN]	rect of the cursor.
 * RETURNS
 *	void
 *****************************************************************************/
typedef void (*vm_update_text_with_cursor_rect_funcptr)(
					VMUINT8 *text, 
					VMUINT8 *cursor, 
					VMINT32 text_length, 
					vm_editor_rect_points_p cursor_rect_points);

/*****************************************************************************
 * FUNCTION
 *	callback function to draw imui background
 * DESCRIPTION
 *	draw imui background
 * PARAMETERS
 *	x1	:	[IN]	x-coordination of top-left point.
 *	y1	:	[IN]	y-coordination of top-left point.
 *	x2	:	[IN]	x-coordination of down-right point.
 *	y2	:	[IN]	y-coordination of down-right point.
 * RETURNS
 *	void
 *****************************************************************************/
typedef void (*vm_draw_imui_background_funcptr)(VMINT32 x1, VMINT32 y1, VMINT32 x2, VMINT32 y2);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_create
 * DESCRIPTION
 *  Creates an editor, it will use some application's heap memory.
 *  For single line editor, it will malloc 550Byte; For multiple line editor, it will malloc xxxByte.
 * PARAMETERS
 *  editor_type             [IN]        Is the editor type
 *  x                       [IN]        Is the left-top corner (x coordinate)
 *  y                       [IN]        Is the left-top corner (y coordinate)
 *  width                   [IN]        Is the width of the editor
 *  height                  [IN]        Is the height of the editor
 *  text_buffer             [IN]        Is the text buffer the editor should use (pre-allocated)
 *  text_buffer_size        [IN]        Is the text buffer size in Bytes
 *  is_disable_softkey      [IN]        Disable softkey or not
 *  layer_handle            [IN]        Is the layer handle
 * RETURNS
 *  NULL : Failed to create editor.
 *  Other : If successful.
 *****************************************************************************/
VMINT32 vm_editor_create(
            VM_EDITOR_TYPE editor_type,
            VMINT32 x,
            VMINT32 y,
            VMINT32 width,
            VMINT32 height,
            VMUWSTR text_buffer,
            VMINT32 text_buffer_size,
            VMBOOL is_disable_softkey,
            VM_GDI_HANDLE layer_handle);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_close
 * DESCRIPTION
 *  Close the editor, it will free the editor memory in this API.
 *  Application must call this API before exit or go to background, if not, there will be memory leak.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_close(VMINT32 editor_handle);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_IME
 * DESCRIPTION
 *  To set IME input type, input mode and callback function.
 * PARAMETERS
 *  editor_handle           [IN]        Is the editor handle
 *  input_type              [IN]        Is the input type, refer to vm_input_type_enum
 *  input_mode_array      [IN]        Is the input mode set, can pass null to use default mode set.
 *                                              If want to use user defined input mode list, 
 *                                              1. You need to set input_type as VM_INPUT_TYPE_USER_SPECIFIC.
 *                                              2. Application need to use global array variable and end with VM_INPUT_MODE_NONE.
 *                                              3. The max length of the array can not more than 10.
 *                                              Example:
 *                                              static vm_input_mode_enum my_input_modes_lower_first[]
 *                                              {
 *                                                 VM_INPUT_MODE_MULTITAP_LOWERCASE_ABC,
 *                                                 VM_INPUT_MODE_MULTITAP_UPPERCASE_ABC,
 *                                                 VM_INPUT_MODE_123,
 *                                                 VM_INPUT_MODE_SM_PINYIN,
 *                                                 VM_INPUT_MODE_NONE
 *                                              };
 *  default_input_mode      [IN]        Is the default input mode
 *  ime_callback            [IN]        Is the ime callback function
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_IME(
        VMINT32 editor_handle,
        VMUINT32 input_type,
        vm_input_mode_enum *input_mode_array,
        vm_input_mode_enum default_input_mode,
        vm_editor_message_funcptr ime_callback);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_softkey
 * DESCRIPTION
 *  Set editor softkey. Only send key press event to application, other key event will be discarded.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  s                   [IN]        Is the label
 *  key                 [IN]        Is softkey type
 *  f                   [IN]        Is the softkey handle
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_softkey(VMINT32 editor_handle, VMUWSTR s, VM_SOFTKEY_ENUM key, vm_soft_key_handle_funcptr f);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_get_softkey_height
 * DESCRIPTION
 *  Get editor softkey height.
 * PARAMETERS
 *  void
 * RETURNS
 *  Soft key height.
 *****************************************************************************/
VMUINT32 vm_editor_get_softkey_height(void);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_show
 * DESCRIPTION
 *  Display the editor (not flush to screen).
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_show(VMINT32 editor_handle);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_multiline_text_font
 * DESCRIPTION
 *  Set multi line editor input text font. Recommended that use font_size_t type to define size. 
 *  If use number directly, you need to check if the phone support vector font.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  text_font           [IN]        Is the text font
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_multiline_text_font(VMINT32 editor_handle, vm_editor_font_attribute text_font);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_get_font_attribute
 * DESCRIPTION
 *  Get editor font attribute.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  text_font           [OUT]        Is the text font
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_get_font_attribute(VMINT32 editor_handle, vm_editor_font_attribute *text_font);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_bg_image
 * DESCRIPTION
 *  Set the normal and focuss image pointers for image background
 *  (there are two styles of background: image background and rectangle background)
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  focus_image        [IN]        Is the focuss image
 *  normal_image        [IN]        Is the normal image
 *  focus_image_size        [IN]        Is the focuss image size
 *  normal_image_size        [IN]        Is the normal image size
 * RETURNS
 *  0 : If successful.
 *  -1 : Parameter error.
 *  -2 : Focus image type error.
 *  -3 : Normal image type error.
 *****************************************************************************/
VMINT32 vm_editor_set_bg_image(
            VMINT32 editor_handle,
            VMUINT8 *focus_image,
            VMUINT8 *normal_image,
            VMINT32 focus_image_size,
            VMINT32 normal_image_size);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_bg_border_style
 * DESCRIPTION
 *  Set border style for rectangle background
 *  (there are two styles of background: image background and rectangle background)
 * PARAMETERS
 *  editor_handle           [IN]        Is the editor handle
 *  border_width            [IN]        Is the border width(no border/single border/double border)
 *  border_normal_color     [IN]        Is the border color of normal style
 *  border_focuss_color     [IN]        Is the border color of focuss style
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_bg_border_style(
        VMINT32 editor_handle,
        VM_EDITOR_BORDER_TYPE border_width,
        VMUINT16 border_normal_color,
        VMUINT16 border_focuss_color);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_margin
 * DESCRIPTION
 *  Set margin for editor
 *  (for singleline, align center along y direction, so no need to set top/down margin)
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  top                 [IN]        Top >0: set new value; -1: use default value
 *  down                [IN]        Down >0: set new value; -1: use default value
 *  left                [IN]        Left >0: set new value; -1: use default value
 *  right               [IN]        Right >0: set new value; -1: use default value
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_margin(VMINT32 editor_handle, VMINT32 top, VMINT32 down, VMINT32 left, VMINT32 right);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_layer_handle
 * DESCRIPTION
 *  Set editor layer handle
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  layer_handle        [IN]        Is the layer handle
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_layer_handle(VMINT32 editor_handle, VM_GDI_HANDLE layer_handle);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_update_text_callback
 * DESCRIPTION
 *  Set update text call back.
 * PARAMETERS
 *  editor_handle               [IN]        Is the editor handle
 *  update_text_callback        [IN]        Is update text callback
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_update_text_callback(VMINT32 editor_handle, vm_update_text_funcptr update_text_callback);

/*****************************************************************************
 * FUNCTION
 *	vm_editor_set_update_text_with_cursor_rect_callback
 * DESCRIPTION
 *	set update text with cursor rect callback.
 *	notice that this callback will be invoked after editor redraw.
 * PARAMETERS
 *	editor_handle	:							[IN]	the editor handle.
 *	update_text_with_cursor_rect_callback	:	[IN] update text with cursor rect callback.
 * RETURNS
 *	void
 *****************************************************************************/
void vm_editor_set_update_text_with_cursor_rect_callback(
		VMINT32 editor_handle,
		vm_update_text_with_cursor_rect_funcptr update_text_with_cursor_rect_callback);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_pos
 * DESCRIPTION
 *  Move the editor and show.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  x                   [IN]        Is the left-top corner
 *  y                   [IN]        Is the left-top corner
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_pos(VMINT32 editor_handle, VMINT32 x, VMINT32 y);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_get_pos
 * DESCRIPTION
 *  Get editor position.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  x                   [OUT]       Is the left-top corner
 *  y                   [OUT]       Is the left-top corner
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_get_pos(VMINT32 editor_handle, VMINT32 *x, VMINT32 *y);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_size
 * DESCRIPTION
 *  Resize the editor and show.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  width               [IN]        Is the width of the editor
 *  height              [IN]        Is the height of the editor
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_size(VMINT32 editor_handle, VMINT32 width, VMINT32 height);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_get_size
 * DESCRIPTION
 *  Get the editor size.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  width               [OUT]       Is the width of the editor
 *  height              [OUT]       Is the height of the editor
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_get_size(VMINT32 editor_handle, VMINT32 *width, VMINT32 *height);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_text
 * DESCRIPTION
 *  Set the text show in the editor.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  text_buffer         [IN]        Is the text buffer
 *  text_size           [IN]        Is the text buffer size(byte)
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_text(VMINT32 editor_handle, VMUWSTR text_buffer, VMINT32 text_size);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_get_text
 * DESCRIPTION
 *  Get the input text of the editor.
 * PARAMETERS
 *  editor_handle       [IN]            Is the editor handle
 *  text_buffer         [IN/OUT]        Is the text buffer
 *  text_size           [IN]            Is the text buffer size(byte)
 * RETURNS
 *  VMINT32: text length
 *****************************************************************************/
VMINT32 vm_editor_get_text(VMINT32 editor_handle, VMUWSTR text_buffer, VMINT32 text_size);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_text_color
 * DESCRIPTION
 *  set text color
 * PARAMETERS
 *  editor_handle       [IN]            Is the editor handle
 *  text_color      [IN]        Is the text color
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_text_color(VMINT32 editor_handle, VMUINT16 text_color);

/*****************************************************************************
 * FUNCTION
 *  wgui_editor_set_cursor_color
 * DESCRIPTION
 *  set cursor color
 * PARAMETERS
 *  editor_handle       [IN]            Is the editor handle
 *  cursor_color    [IN]        Is the cursor color
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_cursor_color(VMINT32 editor_handle, VMUINT16 cursor_color);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_activate
 * DESCRIPTION
 *  Activate the editor.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 *  is_vk_default_on      [IN]        If TRUE, the VK will be on when active the editor; 
 *                                            If FALSE, the VK will be not on when active the editor, you need extra tap to show VK.
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_activate(VMINT32 editor_handle, VMBOOL is_vk_default_on);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_deactivate
 * DESCRIPTION
 *  Deactivate the editor.
 *  If application state switch to inactive/background/unload, must call this API.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_deactivate(VMINT32 editor_handle);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_get_active_editor
 * DESCRIPTION
 *  Get current active editor.
 * PARAMETERS
 *  void
 * RETURNS
 *  The active editor handle.
 *****************************************************************************/
VMINT32 vm_editor_get_active_editor(void);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_get_fit_height
 * DESCRIPTION
 *  Get the fit editor height. This API only used to calculate single line editor height.
 *  For text_font_size, you can use font_size_t type to define the size or use number directly.
 * PARAMETERS
 *  vertical_margin_size       [IN]         Is the vertical margin size
 *  text_font_size       [IN]         Is the text font size
 * RETURNS
 *  editor height.
 *****************************************************************************/
VMINT32 vm_editor_get_fit_height(VMUINT8 vertical_margin_size, VMUINT8 text_font_size);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_get_indicator_height
 * DESCRIPTION
 *  Get indicator height.
 * PARAMETERS
 *  void
 * RETURNS
 *  Indicator height.
 *****************************************************************************/
VMINT32 vm_editor_get_indicator_height(void);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_save
 * DESCRIPTION
 *  Save the history info of the editor.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_save(VMINT32 editor_handle);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_restore
 * DESCRIPTION
 *  Restore the history info to the editor.
 * PARAMETERS
 *  editor_handle       [IN]        Is the editor handle
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_restore(VMINT32 editor_handle);

/*****************************************************************************
* FUNCTION
*  vm_editor_is_draw_floating_indicator
* DESCRIPTION
*  Set if draw ime floating indicator.
* PARAMETERS
*  is_draw_floating_indicator        [IN]        if draw ime floating indicator
* RETURNS
*  void
*****************************************************************************/
void vm_editor_is_draw_floating_indicator(VMBOOL is_draw_floating_indicator);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_redraw_floating_ui_within_rect
 * DESCRIPTION
 *  Redraw ime floating ui within given rectangle area.
 * PARAMETERS
 *  rect               [IN]        Is the given rectangle area
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_redraw_floating_ui_within_rect(vm_editor_rect rect);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_redraw_ime_screen
 * DESCRIPTION
 *  Redraw ime UIs(floating ui and fixed ui).
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_redraw_ime_screen(void);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_get_extra_imui_layer_handler
 * DESCRIPTION
 *  get extra imui layer handler (like handwriting drawn layer).
 * PARAMETERS
 *  void
 * RETURNS
 *  Layer handle.
 *****************************************************************************/
VM_GDI_HANDLE vm_editor_get_extra_imui_layer_handler(void);

/*****************************************************************************
 * FUNCTION
 *	vm_editor_draw_imui_background_filler
 * DESCRIPTION
 *	set the callback function to draw imui background
 * PARAMETERS
 *	draw_imui_background_callback	:	[IN]	the callback to draw imui background.
 * RETURNS
 *	void
 *****************************************************************************/
void vm_editor_set_imui_background_filler(vm_draw_imui_background_funcptr draw_imui_background_callback);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_insert_string
 * DESCRIPTION
 *  insert string.
 * PARAMETERS
 *  editor_handle   :   [IN]    the handle of editor.
 *  str :   [IN]    string to be inserted.
 *  len :   [IN]    length of string.
 * RETURNS
 *  the length of string actually inserted.
 *****************************************************************************/
VMINT32 vm_editor_insert_string(VMINT32 editor_handle, VMUWSTR str, VMINT32 len);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_set_cursor_index
 * DESCRIPTION
 *  set editor cursor index
 * PARAMETERS
 *  editor_handle   :   [IN]    the handle of editor.
 *  cursor_index    :   [IN]    the cursor index
 * RETURNS
 *  void
 *****************************************************************************/
void vm_editor_set_cursor_index(VMINT32 editor_handle, VMINT32 cursor_index);

/*****************************************************************************
 * FUNCTION
 *  vm_editor_get_cursor_index
 * DESCRIPTION
 *  get editor cursor index
 * PARAMETERS
 *  editor_handle   :   [IN]    the handle of editor.
 * RETURNS
 *  the cursor index.
 *****************************************************************************/
VMINT32 vm_editor_get_cursor_index(VMINT32 editor_handle);

/*****************************************************************************
* FUNCTION
*   vm_editor_set_default_text
* DESCRIPTION
*   set default text.
* PARAMETERS
*   editor_handle   :   [IN]    the handle of editor.
*   default_text_buffer :   [IN]    the buffer that stores default text.
* RETURNS
*   void
*****************************************************************************/
void vm_editor_set_default_text(VMINT32 editor_handle, VMUWSTR default_text_buffer);

/*****************************************************************************
* FUNCTION
*  vm_editor_show_from_first_line
* DESCRIPTION
*  jump to start to show from the first line of multiline editor.
* PARAMETERS
*  editor_handle	:	[IN]	handle of the editor.
* RETURNS
*  void
*****************************************************************************/
void vm_editor_show_from_first_line(VMINT32 editor_handle);

/*****************************************************************************
* FUNCTION
*  vm_editor_show_from_start
* DESCRIPTION
*  for multi-line editor, show from the first line.
*  for single-line editor, show from the first charactor.	
* PARAMETERS
*  editor_handle	:	[IN]	handle of the editor.
* RETURNS
*  void
*****************************************************************************/
void vm_editor_show_from_start(VMINT32 editor_handle);

#ifdef __cplusplus
}
#endif

#endif /* VMEDITOR_SDK_H_ */ 

