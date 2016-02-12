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

#ifndef VMCHSET_SDK_H_
#define VMCHSET_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* The maximum length of character conversion. */
#define CONVERT_CHSET_MAX_LEN 4096

/*****************************************************************************
 * FUNCTION
 *  vm_ucs2_to_gb2312
 * DESCRIPTION
 *  Converts the UCS2 string to GB2312 string.
 * PARAMETERS
 *  dst : [OUT] Pointer to destination string.
 *  size : [IN] Size in bytes of destination.
 *  src : [IN] Pointer to input string.
 * RETURNS
 *  The error code of the operation.
 * RETURN VALUES
 *  0 : If successful.
 *  -1 : If failed.
 *****************************************************************************/
VMINT vm_ucs2_to_gb2312(VMSTR dst, VMINT size, VMWSTR src);

/*****************************************************************************
 * FUNCTION
 *  vm_gb2312_to_ucs2
 * DESCRIPTION
 *  Converts the GB2312 string to UCS2 string.
 * PARAMETERS
 *  dst : [OUT] Pointer to destination string.
 *  size : [IN] Size in bytes of destination.
 *  src : [IN] Pointer to input string.
 * RETURNS
 *  The error code of the operation.
 * RETURN VALUES
 *  0 : If successful.
 *  -1 : If failed.
 *****************************************************************************/
VMINT vm_gb2312_to_ucs2(VMWSTR dst, VMINT size, VMSTR src);

/*****************************************************************************
 * FUNCTION
 *  vm_ucs2_to_ascii
 * DESCRIPTION
 *  Converts the UCS2 string to ASCII string.
 * PARAMETERS
 *  dst : [OUT] Pointer to destination string.
 *  size : [IN] Size in bytes of destination.
 *  src : [IN] Pointer to input string.
 * RETURNS
 *  The error code of the operation.
 * RETURN VALUES
 *  0 : If successful.
 *  -1 : If failed.
 *****************************************************************************/
VMINT vm_ucs2_to_ascii(VMSTR dst, VMINT size, VMWSTR src);

/*****************************************************************************
 * FUNCTION
 *  vm_ascii_to_ucs2
 * DESCRIPTION
 *  Converts the ASCII string to UCS2 string.
 * PARAMETERS
 *  dst : [OUT] Pointer to destination string.
 *  size : [IN] Size in bytes of destination.
 *  src : [IN] Pointer to input string.
 * RETURNS
 *  The error code of the operation.
 * RETURN VALUES
 *  0 : If successful.
 *  -1 : If failed.
 *****************************************************************************/
VMINT vm_ascii_to_ucs2(VMWSTR dst, VMINT size, VMSTR src);

/* Phone language */
typedef enum
{
    LANG_UNKOWN = 0, /* Unkown language */
    GB = 1, /* Simplified Chinese */
    ENGLISH, /* ENGLISH */ 
    BIG5, /* Traditional Chinese */ 
    JAPANESE, /* JAPANESE */
    KOREAN, /* KOREAN */
    SPANISH, /* SPANISH */ 
    FRENCH, /* FRENCH */ 
    DANISH, /* DANISH */ 
    POLISH, /* POLISH */ 
    PORTUGUESE, /* PORTUGUESE */ 
    ALBANIAN, /* ALBANIAN */ 
    ICELANDIC, /* ICELANDIC */ 
    SERBIAN, /* SERBIAN */ 
    AZERBAIJANI, /* AZERBAIJANI */ 
    CATALAN, /* CATALAN */	
    HAUSA, /* HAUSA */ 
    KAZAKH, /* KAZAKH */ 
    MACEDONIAN, /* MACEDONIAN */ 
    SESOTHO, /* SESOTHO */ 
    TAGALOG, /* TAGALOG */ 
    YORUBA, /* YORUBA */ 
    ITALIAN, /* ITALIAN */ 
    GERMAN, /* GERMAN */ 	
    MALAY, /* MALAY */ 
    INDONESIAN, /* INDONESIAN */ 
    CZECH, /* CZECH */ 
    NORWEGIAN, /* NORWEGIAN */ 
    SLOVAK, /* SLOVAK */ 
    DUTCH, /* DUTCH */ 
    FINNISH, /* FINNISH */ 
    HUNGARIAN, /* HUNGARIAN */ 
    VIETNAMESE, /* VIETNAMESE */ 
    TURKISH, /* TURKISH */ 
    RUSSIAN, /* RUSSIAN */ 
    UKRAINIAN, /* UKRAINIAN */ 
    ARABIC, /* ARABIC */ 
    PERSIAN, /* PERSIAN */ 
    URDU, /* URDU */
    HEBREW, /* HEBREW */ 
    THAI, /* THAI */ 
    GREEK, /* GREEK */ 
    SWEDISH, /* SWEDISH */ 
    CROATIAN, /* CROATIAN */ 
    ROMANIAN, /* ROMANIAN */ 
    SLOVENIAN, /* SLOVENIAN */ 
    HINDI, /* HINDI */ 
    MARATHI, /* MARATHI */ 
    TAMIL, /* TAMIL */	
    GUJARATI, /* GUJARATI */ 
    BENGALI, /* BENGALI */ 
    ASSAMESE, /* ASSAMESE */ 
    PUNJABI, /* PUNJABI */ 
    TELUGU, /* TELUGU */ 
    KANNADA, /* KANNADA */ 
    MALAYALAM, /* MALAYALAM */ 
    ORIYA, /* ORIYA */ 
    XHOSA, /* XHOSA */ 
    SWAHILI, /* SWAHILI */ 
    AFRIKAANS, /* AFRIKAANS */ 
    ZULU, /* ZULU */ 
    LITHUANIAN, /* LITHUANIAN */ 
    LATVIAN, /* LATVIAN */ 
    ESTONIAN, /* ESTONIAN */ 
    ARMENIAN, /* ARMENIAN */ 
    GEORGIAN, /* GEORGIAN */ 
    MOLDOVAN, /* MOLDOVAN */ 
    GALICIAN, /* GALICIAN */
    BASQUE, /* BASQUE */ 
    IGBO, /* IGBO */ 
    FILIPINO, /* FILIPINO */ 
    IRISH, /* IRISH */ 
    SA_SPANISH, /* SA_SPANISH */
    SA_PORTUGUESE, /* SA_PORTUGUESE */
    UK_ENGLISH, /* UK_ENGLISH */
    CA_FRENCH, /* CA_FRENCH */
    BULGARIAN /* BULGARIAN */
} vm_language_t;

/*****************************************************************************
 * FUNCTION
 *  vm_get_language
 * DESCRIPTION
 *  To get current language.
 * RETURNS
 *  The current language.
 * RETURN VALUES
 *  GB : Simplified Chinese.
 *  ENGLISH : English.
 *  BIG5 : Traditional Chinese.
 *  Other value : Please refer to vm_language_t.
 *****************************************************************************/
vm_language_t vm_get_language(void);

/* Character sets */
typedef enum
{
    VM_CHSET_BASE = 0, /* BASE */
    VM_CHSET_ASCII, /* ASCII */
    VM_CHSET_ARABIC_ISO, /* ARABIC_ISO */
    VM_CHSET_ARABIC_WIN, /* ARABIC_WIN */
    VM_CHSET_PERSIAN_CP1097, /* PERSIAN_CP1097 */
    VM_CHSET_PERSIAN_CP1098, /* PERSIAN_CP1098 */
    VM_CHSET_BALTIC_ISO, /* BALTIC_ISO */
    VM_CHSET_BALTIC_WIN, /* BALTIC_WIN */
    VM_CHSET_CEURO_ISO, /* CEURO_ISO */
    VM_CHSET_CEURO_WIN, /* CEURO_WIN */
    VM_CHSET_CYRILLIC_ISO, /* CYRILLIC_ISO */
    VM_CHSET_CYRILLIC_WIN, /* CYRILLIC_WIN */
    VM_CHSET_GREEK_ISO, /* GREEK_ISO */
    VM_CHSET_GREEK_WIN, /* GREEK_WIN */
    VM_CHSET_HEBREW_ISO, /* HEBREW_ISO */
    VM_CHSET_HEBREW_WIN, /* HEBREW_WIN */
    VM_CHSET_LATIN_ISO, /* LATIN_ISO */
    VM_CHSET_NORDIC_ISO, /* NORDIC_ISO */
    VM_CHSET_SEURO_ISO, /* SEURO_ISO */
    VM_CHSET_TURKISH_ISO, /* TURKISH_ISO */
    VM_CHSET_TURKISH_WIN, /* TURKISH_WIN */
    VM_CHSET_WESTERN_ISO, /* WESTERN_ISO */
    VM_CHSET_ARMENIAN_ISO, /* ARMENIAN_ISO */
    VM_CHSET_WESTERN_WIN, /* WESTERN_WIN */
    VM_CHSET_BIG5, /* BIG5 */
    VM_CHSET_GB2312, /* GB2312 */
    VM_CHSET_HKSCS, /* HKSCS */
    VM_CHSET_SJIS, /* SJIS */
    VM_CHSET_GB18030, /* GB18030 */
    VM_CHSET_UTF7, /* UTF7 */
    VM_CHSET_EUCKR, /* EUCKR */
    VM_CHSET_THAI_WIN, /* THAI_WIN */
    VM_CHSET_VIETNAMESE_WIN, /* VIETNAMESE_WIN */
    VM_CHSET_KOI8_R, /* KOI8_R */
    VM_CHSET_TIS_620, /* TIS_620 */
    VM_CHSET_UTF16LE, /* UTF16LE */
    VM_CHSET_UTF16BE, /* UTF16BE */
    VM_CHSET_UTF8, /* UTF8 */
    VM_CHSET_UCS2, /* UCS2 */
    VM_CHSET_TOTAL /* TOTAL */
} vm_chset_enum;

/* The return value of vm_chset_convert */

#define VM_CHSET_CONVERT_SUCCESS                (0) /* If successful. */
#define VM_CHSET_CONVERT_ERR_PARAM              (-1) /* Parameter error. */
#define VM_CHSET_CONVERT_SRC_UNSUPPORT_CHSET    (-2) /* Character set used by input string is not supported. */
#define VM_CHSET_CONVERT_DST_UNSUPPORT_CHSET    (-3) /* Character set used by destination string is not supported. */
#define VM_CHSET_CONVERT_FATAL_ERROR               (-4) /* General failure. */

/*****************************************************************************
 * FUNCTION
 *  vm_chset_convert
 * DESCRIPTION
 *  Converts string between 2 character sets. (will add the terminate character)
 * PARAMETERS
 *  src_type : [IN] Character set in which the input string is encoded.
 *  dest_type : [IN] Character set in which the destination string is encoded.
 *  src : [IN] Pointer to input string.
 *  dest : [OUT] Pointer to destination string.
 *  dest_size : [IN] Size in bytes of destination.
 * RETURNS
 *  The error code of the operation.
 * RETURN VALUES
 *  VM_CHSET_CONVERT_SUCCESS : If successful.
 *  VM_CHSET_CONVERT_ERR_PARAM : Parameter error.
 *  VM_CHSET_CONVERT_SRC_UNSUPPORT_CHSET : Character set used by input string is not supported.
 *  VM_CHSET_CONVERT_DST_UNSUPPORT_CHSET : Character set used by destination string is not supported.
 *  VM_CHSET_CONVERT_FATAL_ERROR : General failure.
 *****************************************************************************/
VMINT vm_chset_convert(vm_chset_enum src_type, vm_chset_enum dest_type, VMCHAR *src, VMCHAR *dest, VMINT dest_size);

/*****************************************************************************
 * FUNCTION
 *  vm_get_language_ssc
 * DESCRIPTION
 *  Get curent language's ssc string
 * PARAMETERS
 *  ssc : [OUT] SSC String
 * RETURNS
 *  index of cur language
 *****************************************************************************/
extern VMINT32 vm_get_language_ssc(VMINT8 *ssc);

/*****************************************************************************
 * FUNCTION
 *  vm_get_current_lang_country_code
 * DESCRIPTION
 *  To get current language's country code
 *  This is used to get current language's country code
 * PARAMETERS
 *  void
 * RETURNS
 *  country code
 *****************************************************************************/
VMUSTR vm_get_current_lang_country_code(void);


/*****************************************************************************
 * FUNCTION
 *  vm_get_language_num
 * DESCRIPTION
 *  To query support language number.
 * PARAMETERS
 *  void
 * RETURNS
 *  the language number.
 *****************************************************************************/
VMINT32 vm_get_language_num(void);


#ifdef __cplusplus
}
#endif

#endif /* VMCHSET_SDK_H_ */ 

