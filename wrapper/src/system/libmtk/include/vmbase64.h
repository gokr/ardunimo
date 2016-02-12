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

#ifndef VMBASE64_SDK_H_
#define VMBASE64_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "vmsys.h"

/* System used, the structure used to record and maintain the context of base64 */
typedef struct
{
    VMUINT8 buf[4];     /* private data, All the fileds in this structure are absolutely private data, which only will be accessed by BASE64 lib inside. So no detail information about them be here. */  
    VMUINT8 buf_cnt;    /* private data */  
    VMUINT8 finish_flag;/* private data */  
    VMUINT8 illchr_flag;/* private data */  
    VMUINT8 illpad_flag;/* private data */  

    VMUINT8 wrap_count; /* private data */  
    VMUINT8 wrap_max;   /* private data */  
    VMUINT8 reserved[2];/* private data */  
}vm_base64_part_context;

/*****************************************************************************
* FUNCTION
*  vm_base64_encode_basic 
* DESCRIPTION
*  The vm_base64_encode_basic function encodes a piece of data into BASE64 format.
* PARAMETERS
*  src  : [IN] Point to the source content buffer to be encoded. 
*  srcl : [IN] Number of the size of source content buffer to be encoded.
*  dst  : [IN/OUT] Point to the output buffer of encoded content.
*                 If the parameter is NULL, the return value will be the needed output buffer size. 
*  dstl : [IN] Number of the size of output buffer of encoded content.
*              If the [dst] parameter is NULL, this parameter will be ignored.
*  auto_line_wrap : [IN]  Line break (CRLF) will be added after each 76 bytes have been written to output buffer.
* RETURN VALUES
*  -1  :   It indicates that the given output buffer size is not enough, which SHOULD be avoid.
*  >=0 :  the number of needed output buffer size OR the number of bytes written to the buffer pointed to by [dst].
* EXAMPLE
* <code>
*	#define VM_BASE64_LEN    (64)
*	
*	char src[] = "MediaTek (Beijing) Inc";
*	char des_encode[VM_BASE64_LEN];
*	char des_decode[VM_BASE64_LEN];
*    
*	VMINT32   src_len, des_len1, des_len2;
*
*	src_len = strlen(src);
*	memset(des_encode, 0, sizeof(des_encode));
*  
*	des_len1 = VM_BASE64_LEN;
*	des_len2 = VM_BASE64_LEN;
*
*	vm_base64_encode_basic(
*            src,  
*            src_len,
*            des_encode, 
*            des_len1, 
*            TRUE); 
*  
*	memset(des_decode, 0, sizeof(des_decode));
*	des_len2 = VM_BASE64_LEN;
*	des_len1 = strlen(des_encode);
*   
*	vm_base64_decode_basic(
*                des_encode, 
*                des_len1, 
*                des_decode, 
*                des_len2); 
*                
* </code>
*****************************************************************************/
VMINT32 vm_base64_encode_basic(
                    const VMCHAR *src, 
                    VMINT32 srcl,
                    VMCHAR *dst,
                    VMINT32 dstl,
                    VMBOOL auto_line_wrap);

/*****************************************************************************
 * FUNCTION
 *  vm_base64_decode_basic
 * DESCRIPTION
 *  This function is used to decode Base64 string.
 * PARAMETERS
 *  src  :       [IN]            Pointer to the buffer containing encoded data
 *  srcl :       [IN]            Length of the encoded data
 *  dst  :       [IN/OUT]        Point to the output buffer of decoded content.
 *                              If the parameter is NULL, the return value will be the needed output buffer size.
 *                              Note that the returned value is not accurate; it may be larger than the indeed decoded size.
 *  dstl :       [IN]            Length of destination buffer.
 * RETURN VALUES
 *  -1 :  It indicates that the given output buffer size is not enough, which should be avoid
 *  >=0 :  The number of needed output buffer size OR the number of bytes written to the buffer pointed to by [dst].
 * EXAMPLE
 * <code>
 *	 #define VM_BASE64_LEN	  (64)
 *	 
 *	 char src[] = "MediaTek (Beijing) Inc";
 *	 char des_encode[VM_BASE64_LEN];
 *	 char des_decode[VM_BASE64_LEN];
 *	  
 *	 VMINT32   src_len, des_len1, des_len2;
 *
 *	 src_len = strlen(src);
 *	 memset(des_encode, 0, sizeof(des_encode));
 *	
 *	 des_len1 = VM_BASE64_LEN;
 *	 des_len2 = VM_BASE64_LEN;
 *
 *	 vm_base64_encode_basic(
 *			  src,	
 *			  src_len,
 *			  des_encode, 
 *			  des_len1, 
 *			  TRUE); 
 *	
 *	 memset(des_decode, 0, sizeof(des_decode));
 *	 des_len2 = VM_BASE64_LEN;
 *	 des_len1 = strlen(des_encode);
 *	 
 *	 vm_base64_decode_basic(
 *				  des_encode, 
 *				  des_len1, 
 *				  des_decode, 
 *				  des_len2); 
 *				  
 * </code>
 *****************************************************************************/
VMINT32 vm_base64_decode_basic(
                    const VMCHAR *src, 
                    VMINT32 srcl,
                    VMCHAR *dst,
                    VMINT32 dstl);

/*****************************************************************************
 * FUNCTION
 *  vm_base64_part_encode_init
 * DESCRIPTION
 *  This function initializes the STREAM-STYLE part by part BASE64 
 *  encode process and calculate the needed output buffer size per-part.
 * PARAMETERS
 *  cntx               : [IN]        point to the vm_base64_part_context
 *  max_part_buf_size  : [IN]        the number of MAX input buffer size per-part.
 *  auto_line_wrap     : [IN]        Line break (CRLF) will be added after each 76 bytes have been written to output buffer.
 * RETURN VALUES
 *  -1 :   Invalid parameter, It the context is NULL
 *  >= 0  : The MIN output buffer size needed for the per-parts process.
 * EXAMPLE
 * <code>
 *	 #define VM_BASE64_LEN	  (64)
 *	 
 *	 char src[] = "MediaTek (Beijing) Inc";
 *	 char des_encode[VM_BASE64_LEN];
 *	 char des_decode[VM_BASE64_LEN];
 *	 vm_base64_part_context cntx;
 *	 VMINT32   src_len, des_len1, des_len2, temp;
 *
 *     src_len = strlen(src);
 *	 memset(des_encode, 0, sizeof(des_encode));
 *	 des_len1 = VM_BASE64_LEN;
 *	 
 *	 vm_base64_part_encode_init(&cntx, 0, TRUE);
 *
 *	 temp =src_len;
 *	 vm_base64_part_encode_append(&cntx, src, &temp, des_encode, des_len1);
 *	 
 *	 vm_base64_part_encode_finish(&cntx, des_encode+reval, des_len1-reval);
 *
 *	 vm_base64_part_decode_init(&cntx,0); 
 *
 *	 temp=des_len1;
 *	 memset(des_decode, 0, sizeof(des_decode));
 *	 des_len2 = VM_BASE64_LEN;
 *	 vm_base64_part_decode_append(&cntx, des_encode, &temp, des_decode,des_len2);
 *
 *	 vm_base64_part_decode_finish(&cntx, NULL);	 
 *				  
 * </code>
 *****************************************************************************/
VMINT32 vm_base64_part_encode_init(
                    vm_base64_part_context *cntx,
                    VMINT32 max_part_buf_size,
                    VMBOOL auto_line_wrap);

/*****************************************************************************
 * FUNCTION
 *  vm_base64_part_encode_append
 * DESCRIPTION
 *  The vm_base64_part_encode_append function accepts next part of source data, encode them to BASE64 format.
 * PARAMETERS
 *  cntx   :     [IN]            Point to the BASE64 part context.
 *  src    :     [IN]            Point to the source content buffer to be encoded. 
 *  srcl   :     [IN/OUT]        Point to the number of the size of source content buffer to be encoded, it MUST NOT be NULL, the the number MUST NOT be less than ZERO.
 *  dst    :     [IN/OUT]        Point to the output buffer of encoded content. 
 *  dstl   :     [IN]            Number of the size of output buffer.
 * RETURN VALUES
 *  -1 : If the context is NULL or it was modified outside, the return value is -1.
 *  >=0 : If the function succeeds, the return value is the number of bytes written to output buffer, and the [*srcl] indicates how many input buffer was processed. Note that: if the output buffer size is NOT LESS THAN the return value of the vm_base64_part_decode_init function, and the input size buffer is NOT LARGER THAN the [max_part_buf_size] value, the OUT [*srcl] value is always equal to the IN [*src] value, in this case you can ignore the OUT [*srcl] value safely.
 * EXAMPLE
 * <code>
 *	 #define VM_BASE64_LEN	  (64)
 *	 
 *	 char src[] = "MediaTek (Beijing) Inc";
 *	 char des_encode[VM_BASE64_LEN];
 *	 char des_decode[VM_BASE64_LEN];
 *	 vm_base64_part_context cntx;
 *	 VMINT32   src_len, des_len1, des_len2, temp;
 *
 *     src_len = strlen(src);
 *	 memset(des_encode, 0, sizeof(des_encode));
 *	 des_len1 = VM_BASE64_LEN;
 *	 
 *	 vm_base64_part_encode_init(&cntx, 0, TRUE);
 *
 *	 temp =src_len;
 *	 vm_base64_part_encode_append(&cntx, src, &temp, des_encode, des_len1);
 *	 
 *	 vm_base64_part_encode_finish(&cntx, des_encode+reval, des_len1-reval);
 *
 *	 vm_base64_part_decode_init(&cntx,0); 
 *
 *	 temp=des_len1;
 *	 memset(des_decode, 0, sizeof(des_decode));
 *	 des_len2 = VM_BASE64_LEN;
 *	 vm_base64_part_decode_append(&cntx, des_encode, &temp, des_decode,des_len2);
 *
 *	 vm_base64_part_decode_finish(&cntx, NULL);	 
 *				  
 * </code>
 *****************************************************************************/
VMINT32 vm_base64_part_encode_append(
                    vm_base64_part_context *cntx,
                    const VMCHAR *src,
                    VMINT32 *srcl,
                    VMCHAR  *dst,
                    VMINT32 dstl);

/*****************************************************************************
 * FUNCTION
 *  vm_base64_part_encode_finish
 * DESCRIPTION
 *  The vm_base64_part_encode_finish function finish the part-by-part encode process, encode the last bytes into BASE64 format if there are.
 * PARAMETERS
 *  cntx     :   [IN]            Point to the vm_qprint_context
 *  dst      :   [IN/OUT]        Point to the output buffer of decoded content.
 *  dstl     :   [IN]            Number of the size of output buffer of encoded content. It must be larger than 6.
 * RETURN VALUES
 *  >=0 : If the function succeeds, the return value is the number of bytes written to output buffer, 
 *  -1 : If the function failed, the return value is -1 it means the context data was NULL or be changed outsides or the output buffer size is too small.
 * EXAMPLE
 * <code>
 *	 #define VM_BASE64_LEN	  (64)
 *	 
 *	 char src[] = "MediaTek (Beijing) Inc";
 *	 char des_encode[VM_BASE64_LEN];
 *	 char des_decode[VM_BASE64_LEN];
 *	 vm_base64_part_context cntx;
 *	 VMINT32   src_len, des_len1, des_len2, temp;
 *
 *     src_len = strlen(src);
 *	 memset(des_encode, 0, sizeof(des_encode));
 *	 des_len1 = VM_BASE64_LEN;
 *	 
 *	 vm_base64_part_encode_init(&cntx, 0, TRUE);
 *
 *	 temp =src_len;
 *	 vm_base64_part_encode_append(&cntx, src, &temp, des_encode, des_len1);
 *	 
 *	 vm_base64_part_encode_finish(&cntx, des_encode+reval, des_len1-reval);
 *
 *	 vm_base64_part_decode_init(&cntx,0); 
 *
 *	 temp=des_len1;
 *	 memset(des_decode, 0, sizeof(des_decode));
 *	 des_len2 = VM_BASE64_LEN;
 *	 vm_base64_part_decode_append(&cntx, des_encode, &temp, des_decode,des_len2);
 *
 *	 vm_base64_part_decode_finish(&cntx, NULL);	 
 *				  
 * </code>
 *****************************************************************************/
VMINT32 vm_base64_part_encode_finish(
                    vm_base64_part_context* cntx,
                    VMCHAR *dst,
                    VMINT32 dstl);

/*****************************************************************************
 * FUNCTION
 *  vm_base64_part_decode_init
 * DESCRIPTION
 *  The vm_base64_part_decode_init function initialize the part by part style BASE64 decode process and calculate the needed output buffer size per-part.
 * PARAMETERS
 *  cntx              :  [IN]        Point to the BASE64 part context.
 *  max_part_buf_size :  [IN]        The number of MAX input buffer size per-part.
 * RETURN VALUES
 *  >=0 : If the function succeeds, the return value is the MIN output buffer size needed for the per-part process.
 *  -1 : If the context is NULL, the return value is -1.
 * EXAMPLE
 * <code>
 *	 #define VM_BASE64_LEN	  (64)
 *	 
 *	 char src[] = "MediaTek (Beijing) Inc";
 *	 char des_encode[VM_BASE64_LEN];
 *	 char des_decode[VM_BASE64_LEN];
 *	 vm_base64_part_context cntx;
 *	 VMINT32   src_len, des_len1, des_len2, temp;
 *
 *     src_len = strlen(src);
 *	 memset(des_encode, 0, sizeof(des_encode));
 *	 des_len1 = VM_BASE64_LEN;
 *	 
 *	 vm_base64_part_encode_init(&cntx, 0, TRUE);
 *
 *	 temp =src_len;
 *	 vm_base64_part_encode_append(&cntx, src, &temp, des_encode, des_len1);
 *	 
 *	 vm_base64_part_encode_finish(&cntx, des_encode+reval, des_len1-reval);
 *
 *	 vm_base64_part_decode_init(&cntx,0); 
 *
 *	 temp=des_len1;
 *	 memset(des_decode, 0, sizeof(des_decode));
 *	 des_len2 = VM_BASE64_LEN;
 *	 vm_base64_part_decode_append(&cntx, des_encode, &temp, des_decode,des_len2);
 *
 *	 vm_base64_part_decode_finish(&cntx, NULL);	 
 *				  
 * </code>
 *****************************************************************************/
VMINT32 vm_base64_part_decode_init(
                    vm_base64_part_context *cntx,
                    VMINT32 max_part_buf_size);

/*****************************************************************************
 * FUNCTION
 *  vm_base64_part_decode_append
 * DESCRIPTION
 *  This function accepts next part of source data; 
 *  decode them from BASE64 format
 * PARAMETERS
 *  cntx      :  [IN]        Point to the BASE64 part context.
 *  src       :  [IN]        Point to the source content buffer to be decoded. 
 *  srcl      :  [IN]        Point to the number of the size of source content buffer to de encoded. 
 *  dst       :  [IN/OUT]    Point to the output buffer of decoded content. 
 *  dstl      :  [IN]        Number of the size of output buffer.
 * RETURN VALUES
 *  >=0 : If the function succeeds, the return value is the number of bytes written to output buffer. and the [*srcl] indicates how many input buffer was processed. Note that: if the output buffer size is NOT LESS THAN the return value of the vm_base64_part_decode_init function, and the input size buffer is NOT LARGER THAN the [max_part_buf_size] value, the OUT [*srcl] value is always equal to the IN [*src] value
 *  -1 : It the context is NULL or modified outside, the return value is -1.
 * EXAMPLE
 * <code>
 *	 #define VM_BASE64_LEN	  (64)
 *	 
 *	 char src[] = "MediaTek (Beijing) Inc";
 *	 char des_encode[VM_BASE64_LEN];
 *	 char des_decode[VM_BASE64_LEN];
 *	 vm_base64_part_context cntx;
 *	 VMINT32   src_len, des_len1, des_len2, temp;
 *
 *     src_len = strlen(src);
 *	 memset(des_encode, 0, sizeof(des_encode));
 *	 des_len1 = VM_BASE64_LEN;
 *	 
 *	 vm_base64_part_encode_init(&cntx, 0, TRUE);
 *
 *	 temp =src_len;
 *	 vm_base64_part_encode_append(&cntx, src, &temp, des_encode, des_len1);
 *	 
 *	 vm_base64_part_encode_finish(&cntx, des_encode+reval, des_len1-reval);
 *
 *	 vm_base64_part_decode_init(&cntx,0); 
 *
 *	 temp=des_len1;
 *	 memset(des_decode, 0, sizeof(des_decode));
 *	 des_len2 = VM_BASE64_LEN;
 *	 vm_base64_part_decode_append(&cntx, des_encode, &temp, des_decode,des_len2);
 *
 *	 vm_base64_part_decode_finish(&cntx, NULL);	 
 *				  
 * </code>
 *****************************************************************************/
VMINT32 vm_base64_part_decode_append(
                    vm_base64_part_context* cntx,
                    const VMCHAR *src,
                    VMINT32 *srcl,
                    VMCHAR *dst,
                    VMINT32 dstl);

/*****************************************************************************
 * FUNCTION
 *  vm_base64_part_decode_finish
 * DESCRIPTION
 *  This function finishes the part-by-part decoding process.
 * PARAMETERS
 *  cntx           : [IN]        Point to the BASE64 part context.
 *  illegal_format : [IN/OUT]    Point to the illegal format flag, if you can ignore this safely, you can set it NULL.
 * RETURN VALUES
 *  0 : If the function succeeds, the return value is 0. if illegal character or invalid pad character  was found during the process, and the [illegal_format] is NOT NULL, the [illegal_format] will be set as TRUE.
 *  -1 : If the context is NULL or modified outside, the return value is -1.
 * EXAMPLE
 * <code>
 *	 #define VM_BASE64_LEN	  (64)
 *	 
 *	 char src[] = "MediaTek (Beijing) Inc";
 *	 char des_encode[VM_BASE64_LEN];
 *	 char des_decode[VM_BASE64_LEN];
 *	 vm_base64_part_context cntx;
 *	 VMINT32   src_len, des_len1, des_len2, temp;
 *
 *     src_len = strlen(src);
 *	 memset(des_encode, 0, sizeof(des_encode));
 *	 des_len1 = VM_BASE64_LEN;
 *	 
 *	 vm_base64_part_encode_init(&cntx, 0, TRUE);
 *
 *	 temp =src_len;
 *	 vm_base64_part_encode_append(&cntx, src, &temp, des_encode, des_len1);
 *	 
 *	 vm_base64_part_encode_finish(&cntx, des_encode+reval, des_len1-reval);
 *
 *	 vm_base64_part_decode_init(&cntx,0); 
 *
 *	 temp=des_len1;
 *	 memset(des_decode, 0, sizeof(des_decode));
 *	 des_len2 = VM_BASE64_LEN;
 *	 vm_base64_part_decode_append(&cntx, des_encode, &temp, des_decode,des_len2);
 *
 *	 vm_base64_part_decode_finish(&cntx, NULL);	 
 *				  
 * </code>
 *****************************************************************************/
VMINT32 vm_base64_part_decode_finish(
                    vm_base64_part_context* cntx,
                    VMBOOL* illegal_format);

#ifdef __cplusplus
}
#endif

#endif /* VMSTDLIB_SDK_H_ */
