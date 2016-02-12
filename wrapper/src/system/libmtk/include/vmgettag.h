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

#ifndef VMTAG_SDK_H_
#define VMTAG_SDK_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "vmio.h"
#include "vmsys.h"

#define		MULTI_TAG_MAX			10

#define PPID		1
#define USAGE_MODE	2
#define PARAM		3
#define PRICE		4
#define TRIAL		5
#define CN_NAME		6
#define DEVELOPER	7
#define SERIAL_NUM	8
#define VERSION		9
#define ICON		10


#define GET_TAG_TRUE		1   /* get tag success */
#define GET_TAG_ERROR		0   /* read tag error */
#define	GET_TAG_INSUFFICIENT_BUF	(-1)  /* memory not enough */
#define	GET_TAG_NULL_BUF			(-2)  /* buffer size is zero */
#define	GET_TAG_NOT_FOUND 			(-3)  /* not find this tag */
#define	GET_TAG_FILE_ERROR			(-4)  /* read file error */
#define GET_TAG_NOT_A_LIST_TAG		(-5)  /* tag id is not corrent */
#define GET_TAG_LANG_NOT_FOUND		(-6)  /* not find language id */
#define GET_TAG_CACHE_ERROR		    (-7)  /* file seek error */

/* multi tag stucture */
typedef struct multi_tag_t
{
	VMINT		tag_id[MULTI_TAG_MAX];   /* tag id array, max size is 10 */
	VMINT		tag_len[MULTI_TAG_MAX];  /* tag lenth array, max size is 10 */
	VMUCHAR *	tag_content[MULTI_TAG_MAX];  /* tag content pointer array, max size is 10 */
} MULTI_TAG;

/*****************************************************************************
 * FUNCTION
 *    vm_get_vm_tag
 * DESCRIPTION
 *  get one tag from file or preload file, this support file in file system and in ROM.
 * PARAMETERS
 *  filename : [IN] file name, if it is preload file, it should be @:\xx.rom format.
 *  tag_num : [IN] tag id, refer tag define in vmcert.h.
 *  buf : [OUT] tag value.
 *  buf_size : [OUT] tag value size.
 * RETURNS
 *  get tag success or not.
 * RETURN VALUES
 *  GET_TAG_TRUE : get tag success.
 *  GET_TAG_NOT_FOUND : not find this tag.
 *  GET_TAG_ERROR : read tag error.
 *  GET_TAG_INSUFFICIENT_BUF : buffer size is error.
 * SEE ALSO
 *  vm_get_vm_tag_from_rom
 * EXAMPLE
 *  (a). get tag and know the tag size
 *     <code>
 *     VMINT file_type;
 *	 VMINT buffSize = 4;   // tag size is 4
 *     
 *	if (vm_get_vm_tag(filename, VM_CE_INFO_FILE_TYPE, (void*)&liner_type, &buffSize) != GET_TAG_TRUE)
 *     {
 *	     // get tag error
 *     }
 *     else
 *     {
 *	     // get tag success
 *     }
 *     </code> 
 *
 *  (b). get tag and don't know the tag size
 *	  <code>
 *	  VMUINT8* tagName;
 *	  VMINT buffSize;
 *      
 *	  // get tag size 
 * 	  if (vm_get_vm_tag(fileName, VM_CE_INFO_NAME, NULL, &bufSize) == GET_TAG_TRUE)
 *	  {
 *		tagName = (VMUINT8 *)vm_calloc(bufSize + 1);
 *		
 *		if(tagName)
 *		{
 *			if(vm_get_vm_tag(fileName, VM_CE_INFO_NAME, tagName, &bufSize) != GET_TAG_TRUE)
 *			{
 *				vm_free(tagName);    // failed
 *			}
 *		}
 *	  }
 *      ....
 *     // free it when no use
 *      vm_free(tagName);
 *	  </code> 
*****************************************************************************/
VMINT vm_get_vm_tag(short* filename,int tag_num, void* buf ,int* buf_size);


/*****************************************************************************
 * FUNCTION
 *    vm_get_multi_tags
 * DESCRIPTION
 *  get some tags from file or preload file, max size refer to MULTI_TAG_MAX
 * PARAMETERS
 *  filename : [IN] file name, if it is preload file, it should be @:\xx.rom format.
 *  tag_req : [IN & OUT] tag id and value.
 * RETURNS
 *  get tags success or not.
 * RETURN VALUES
 *  GET_TAG_TRUE : get tag success.
 *  GET_TAG_NOT_FOUND : not find this tag.
 *  GET_TAG_ERROR : read tag error. 
 * SEE ALSO
 *  vm_get_vm_tag
 * EXAMPLE
 *	 <code>
 *	 MULTI_TAG multi_tag;
 *     memset(&multi_tag, 0, sizeof(MULTI_TAG));
 * 	 multi_tag. tag_id[0] = VM_CE_INFO_APP_ID;
 * 	 multi_tag. tag_id[1] = VM_CE_INFO_CERT_ID;
 * 	 multi_tag. tag_id[2] = VM_CE_INFO_NAME;
 * 	 
 *	 // get tag size 
 *	 if (vm_get_multi_tags(fileName, &multi_tag) == GET_TAG_TRUE)
 *	 {
 *	   multi_tag. tag_content[0]  = (VMUINT8 *)vm_calloc(multi_tag. tag_len[0] + 1);
 *	   multi_tag. tag_content[1]  = (VMUINT8 *)vm_calloc(multi_tag. tag_len[1] + 1);
 *	   multi_tag. tag_content[2]  = (VMUINT8 *)vm_calloc(multi_tag. tag_len[2] + 1);
 *
 *	   if(tagName)
 *	   {
 *		   if(vm_get_multi_tags(fileName, &multi_tag) != GET_TAG_TRUE)
 *		   {
 *			    // failed
 *			   vm_free(multi_tag. tag_content[0] );	
 *			   vm_free(multi_tag. tag_content[1] );	
 *			   vm_free(multi_tag. tag_content[2] );	
 *		   }
 *	   }
 *	 }
 *	   ....
 *     // free them when no use
 *	 vm_free(multi_tag. tag_content[0] );	
 *	 vm_free(multi_tag. tag_content[1] );	
 *	 vm_free(multi_tag. tag_content[2] );	
 *	 </code> 
*****************************************************************************/
VMINT vm_get_multi_tags( short* filename,   MULTI_TAG* tag_req);


/*****************************************************************************
 * FUNCTION
 *    vm_get_tag_by_lang_id
 * DESCRIPTION
 *  get a tag from tag id and language id.
 * PARAMETERS
 *  filename : [IN] file name, if it is preload file, it should be @:\xx.rom format.
 *  tag_num : [IN] tag id, refer tag define in vmcert.h.
 *  lang_id : [IN] lang id.
 *  buf : [OUT] tag value.
 *  buf_size : [OUT] tag value size.
 * RETURNS
 *  get a tag success or not.
 * RETURN VALUES
 *  GET_TAG_TRUE : get tag success.
 *  GET_TAG_ERROR : get tag error.
 *  GET_TAG_NOT_FOUND : not find this tag.
 *  GET_TAG_LANG_NOT_FOUND : not find language id.
 *  GET_TAG_NOT_A_LIST_TAG : tag id is not corrent.
 *  GET_TAG_FILE_ERROR : read tag error from file.
 *  GET_TAG_INSUFFICIENT_BUF : buffer size is error.
 *  GET_TAG_NULL_BUF : buffer size is zero
 * EXAMPLE
 *  get app's english (language id is 44, this id can be get from reseditor) name 
 *	  <code>
 *	  VMUINT8* tagName;
 *	  VMINT buffSize;
 *	  
 *      if (vm_get_tag_by_lang_id(fileName, VM_CE_INFO_MULTI_NAME_LIST, NULL, &buffSize, 44) == GET_TAG_TRUE)
 *	  {
 *            tagName = (VMUINT8 *)vm_calloc(bufSize + 1);
 *		vm_get_tag_by_lang_id(fileName, VM_CE_INFO_MULTI_NAME_LIST, tagName, &buffSize, 44);
 *	  }
 *	 </code> 

*****************************************************************************/
VMINT vm_get_tag_by_lang_id( short* filename, int tag_num, void* buf, int* buf_size, int lang_id );


/*****************************************************************************
 * FUNCTION
 *    vm_get_multi_tags_by_lang_id
 * DESCRIPTION
 *  get tags from tag id and language id.
 * PARAMETERS
 *  filename : [IN] file name, if it is preload file, it should be @:\xx.rom format.
 *  lang_id : [IN] lang id.
 *  tag_req : [IN & OUT] tag id and value.
 * RETURNS
 *  get tags success or not.
 * RETURN VALUES
 *  GET_TAG_TRUE : get tag success.
 *  GET_TAG_ERROR : get tag error.
 *  GET_TAG_LANG_NOT_FOUND : not find language id.
 *  GET_TAG_INSUFFICIENT_BUF : there is no enough memroy.
 * EXAMPLE
 *	<code>
 *	MULTI_TAG multi_tag;
 *	memset(&multi_tag, 0, sizeof(MULTI_TAG));
 *	multi_tag. tag_id[0] = VM_CE_INFO_NAME_LIST;
 *	multi_tag. tag_id[1] = VM_CE_INFO_DESC_LIST;
 *	multi_tag. tag_id[2] = VM_CE_INFO_ZIMO_LIST;
 *	
 *	// get tag size 
 *	if (vm_get_multi_tags_by_lang_id(fileName, &multi_tag, 44) == GET_TAG_TRUE)
 *	{
 *	  multi_tag. tag_content[0]  = (VMUINT8 *)vm_calloc(multi_tag. tag_len[0] + 1);
 *	  multi_tag. tag_content[1]  = (VMUINT8 *)vm_calloc(multi_tag. tag_len[1] + 1);
 *	  multi_tag. tag_content[2]  = (VMUINT8 *)vm_calloc(multi_tag. tag_len[2] + 1);
 *
 *	  if(tagName)
 *	  {
 *		  if(vm_get_multi_tags_by_lang_id(fileName, &multi_tag, 44) != GET_TAG_TRUE)
 *		  {
 *			   // failed
 *			  vm_free(multi_tag. tag_content[0] ); 
 *			  vm_free(multi_tag. tag_content[1] ); 
 *			  vm_free(multi_tag. tag_content[2] ); 
 *		  }
 *	  }
 *	}
 *	  ....
 *	  // free them when no use
 *	vm_free(multi_tag. tag_content[0] );   
 *	vm_free(multi_tag. tag_content[1] );   
 *	vm_free(multi_tag. tag_content[2] );   
 *	</code> 
*****************************************************************************/
VMINT vm_get_multi_tags_by_lang_id( short* filename,   MULTI_TAG * tag_req, int lang_id );


/*****************************************************************************
 * FUNCTION
 *    vm_get_vm_tag_from_rom
 * DESCRIPTION
 *  get a tag from rom.
 * PARAMETERS
 *  rom : [IN] the address of preload app.
 *  tag_num : [IN] tag id, refer tag define in vmcert.h.
 *  buf : [OUT] tag value.
 *  buf_size : [OUT] tag value size.
 * RETURNS
 *  get tag success or not.
 * RETURN VALUES
 *  GET_TAG_TRUE : get tag success.
 *  GET_TAG_NOT_FOUND : not find this tag.
 *  GET_TAG_ERROR : read tag error.
 *  GET_TAG_INSUFFICIENT_BUF : buffer size is error.
 * SEE ALSO
 *  vm_get_vm_tag
 * EXAMPLE
 *	 <code>
 *	 VMUINT8* tagName;
 *	 VMINT buffSize;
 *	 
 *	   if (vm_get_vm_tag_from_rom(address, VM_CE_INFO_IMSI, NULL, &buffSize) == GET_TAG_TRUE)
 *	 {
 * 		tagName = (VMUINT8 *)vm_calloc(bufSize + 1);
 *	   	vm_get_vm_tag_from_rom(fileName, VM_CE_INFO_IMSI, tagName, &buffSize);
 *	 }
 *	</code> 
*****************************************************************************/
VMINT vm_get_vm_tag_from_rom(VMUINT8* rom, int tag_num, void* buf , int* buf_size);


#ifdef __cplusplus
}
#endif

#endif /* VMTAG_SDK_H_ */
