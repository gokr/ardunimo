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

#ifndef	_VM_MUL_LANG_SDK_
#define	_VM_MUL_LANG_SDK_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/*multi-language segment name*/
#define		MUL_LANG_RES_NAME		"lang.bin"

/*language type list*/
enum{
	VM_LANG_NULL = 0, /*no language*/
	VM_LANG_ENG,/*English*/
	VM_LANG_CHS,/*Chinese Simple*/
	VM_LANG_CHT /*Chinese Tradition*/
};

/*language list begin*/
#define		VM_LANG_ID_START		VM_LANG_ENG

/*language list end*/
#define		VM_LANG_ID_END			VM_LANG_CHT

/*default language*/
#define		VM_LANG_ID_DEFAULT		VM_LANG_ENG



/*****************************************************************************
 * FUNCTION
 *  vm_mul_lang_init
 * DESCRIPTION
 *  init multi-language model. multi-lang resource is in the segment "vm_res" in the vxp file, its name is lang.bin. so it has 
 *   malloc memory operation.
 * PARAMETERS
 *  void 
 * RETURNS
 *  if succeed, return the handle of  multi-lang resource(the resource pointer), otherwise, return NULL
 *****************************************************************************/ 
VMCHAR * vm_mul_lang_init( void );


/*****************************************************************************
 * FUNCTION
 *  vm_mul_lang_deinit
 * DESCRIPTION
 *  release multi-lang resource 
 * PARAMETERS
 *  mul_lang_handle : [IN] the handle of  multi-lang resource, in fact, it is pointer address. 
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_mul_lang_deinit( VMCHAR * mul_lang_handle );



/*****************************************************************************
 * FUNCTION
 *  vm_mul_lang_get_string
 * DESCRIPTION
 *  get the appointed string from multi-lang resource
 * PARAMETERS
 *  lang_buf : [IN]  multi-lang resource pointer address.
 * res_id : [IN]  string resource id
 * lang_id : [IN]  language id
 * str_buf : [OUT] string pointer
 * RETURNS
 *  the length of string. if length is 0, the operation is failed.
 *****************************************************************************/ 
VMINT vm_mul_lang_get_string( VMCHAR * lang_buf, VMINT res_id, VMINT lang_id, VMCHAR ** str_buf );




/*****************************************************************************
 * FUNCTION
 *  vm_mul_lang_set_lang
 * DESCRIPTION
 *  set current language 
 * PARAMETERS
 *  lang_id : [IN] language id
 * RETURNS
 *  if succeed, return 1, otherwise, return 0
 *****************************************************************************/ 
VMINT vm_mul_lang_set_lang( VMINT lang_id );



/*****************************************************************************
 * FUNCTION
 *  vm_mul_lang_set_lang
 * DESCRIPTION
 *  get current language 
 * PARAMETERS
 *  void
 * RETURNS
 *  language id, default value is VM_LANG_ENG
 *****************************************************************************/ 
VMINT vm_mul_lang_get_lang( void );



/*****************************************************************************
 * FUNCTION
 *  vm_graphic_textout_by_id
 * DESCRIPTION
 *  show string to the destination buffer
 * PARAMETERS
 *  disp_buf : [IN] display buffer
 *  x : [IN] x offset of display buffer
 *  y : [IN] y offset of display buffer
 *  lang_buf : [IN] multi-lang resource pointer address.
 *  res_id : [IN] resource id
 *  color : [IN] string color
 * RETURNS
 * void
 *****************************************************************************/ 
void vm_graphic_textout_by_id( VMUINT8* disp_buf, VMINT x, VMINT y, VMCHAR * lang_buf, VMINT res_id, VMUINT16 color);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_string_width_by_id
 * DESCRIPTION
 *  get string width by resource id
 * PARAMETERS
 *  lang_buf : [IN] multi-lang resource pointer address.
 *  res_id	 : [IN] string resource id
 * RETURNS
 *  if succeed, return string width, otherwise, return error code
 *****************************************************************************/ 
VMINT vm_graphic_get_string_width_by_id( VMCHAR * lang_buf, VMINT res_id );

#ifdef __cplusplus
}
#endif

#endif /* _VM_MUL_LANG_SDK_ */
