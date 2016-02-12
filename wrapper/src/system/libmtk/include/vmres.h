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
 
#ifndef VMRES_SDK_H
#define VMRES_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* cache data structure */
typedef struct _vm_res_read_hint_struct
{
	VMINT res_offset;   /* res offset */
	VMINT res_size;     /* res size */
}vm_res_read_hint_struct;

/*****************************************************************************
 * FUNCTION
 *    vm_load_resource
 * DESCRIPTION
 *  load resource from current file, system will alloc memory and read the 
 *  resource from file to memory,need to call vm_free after use.
 * PARAMETERS
 *  res_name : [IN]  Resource name, not include path.
 *  res_size : [OUT] Resource size, bytes.
 * RETURNS
 *  Resource pointer
 * SEE ALSO
 *  vm_load_resource_from_file
 * EXAMPLE
 *  get resource named "mre-2.0"
 *     <code>
 *     VMCHAR* res_buf;
 *     
 *	res_buf = vm_load_resource("mre-2.0", (VMINT*)&res_size);
 *    if(res_buf == NULL)
 *     {
 *		// get error
 *     }
 *     else
 *     {
 *	     // get success
 *         ...
 *         vm_free(res_buf);   // release the resource after use it.
 *     }
 *     </code> 
*****************************************************************************/
VMUINT8* vm_load_resource(char* res_name, VMINT* res_size);


 /*****************************************************************************
 * FUNCTION
 *  vm_load_resource_from_file
 * DESCRIPTION
 *  Load Resource from one filesystem will alloc memory and read the 
 *  res from file to memory,need to call vm_free after use.
 * PARAMETERS
 *  filename : [IN] full path need to read the resource.
 *  res_name : [IN] Resource name, not include path.
 *  res_size : [OUT] Resource size, bytes.
 * RETURNS
 *  Resource pointer
 * SEE ALSO
 *  vm_load_resource
 * EXAMPLE
 *  get resource named "mre-2.0"
 *	  <code>
 *	  VMCHAR* res_buf;
 *	  
 *      res_buf = vm_load_resource_from_file("E:\\sample.vxp", "mre-2.0", (VMINT*)&res_size);
 *	 if(res_buf == NULL)
 *	  {
 *	   // get error
 *	  }
 *	  else
 *	  {
 *		// get success
 *		  ...
 *		  vm_free(res_buf);   // release the resource after use it.
 *	  }
 *	  </code> 
*****************************************************************************/
VMUINT8* vm_load_resource_from_file(VMWSTR filename, char *res_name, VMINT *res_size);

 /*****************************************************************************
  * FUNCTION
  *    vm_load_virtual_resource
  * DESCRIPTION
  *  load resource from current file, system will alloc 16 bytes as virtual image for graphic interface 
  *  this need to call vm_free after use. this will not load the real data of image, only load res offset
  *  and file handle, graphic interface will load the real data when it to show the image
  * PARAMETERS
  *  res_name : [IN]  Resource name, not include path.
  *  res_size : [OUT] Resource size, bytes.
  * RETURNS
  *  Resource pointer
  * EXAMPLE
  *  get resource named "logo"
  *	 <code>
  *	 VMCHAR* res_buf;
  *	  
  *    res_buf = vm_load_virtual_resource( "logo", (VMINT*)&res_size);
  *	 if(res_buf == NULL)
  *	  {
  *	   // get error
  *	  }
  *	  else
  *	  {
  *		// get success
  *		  ...
  *		  vm_free(res_buf);   // release the resource after use it.
  *	  }
  *	  </code> 
 *****************************************************************************/
VMUINT8 *vm_load_virtual_resource(char *res_name, VMINT *res_size);

/*****************************************************************************
 * FUNCTION
 *  vm_resource_get_data
 * DESCRIPTION
 *  Function to Get data from current app file, some app have it own resource format, so they can make all their resource
 * as on MRE resource, and get the resource offset form vm_get_resource_offset, then they can manage the data by themslef
 * PARAMETERS
 *  data    [IN]    Buffer of data
 *  offset  [IN]    Offset of the file
 *  size    [IN]    Size of the data
 * RETURNS
 *  0 successful
 * SEE ALSO
 *  vm_resource_get_data_from_file
 * EXAMPLE
 *	get data of the resource "mre-2.0", size is 1200 bytes
 *	<code>
 *	VMCHAR* res_buf;
 *	VMUINT offset;
 *    offset = vm_get_resource_offset("mre-2.0");
 *    res_buf = vm_malloc(1200);
 *	result = vm_resource_get_data( res_buf, offset, 1200);
 *	if(result == 0)
 *	 {
 *	  // get error
 *	 }
 *	 else
 *	 {
 *	   // get success
 *		 ...
 *		 vm_free(res_buf);	 // release the resource after use it.
 *	 }
 *	 </code> 
 *****************************************************************************/
extern VMINT32 vm_resource_get_data(VMUINT8 *data, VMUINT32 offset, VMUINT32 size);

/*****************************************************************************
 * FUNCTION
 *  vm_resource_get_data_from_file
 * DESCRIPTION
 *  Function to Get data from file with full path.
 * PARAMETERS
 *  filename[IN]     File full path
 *  data    [IN]    Buffer of data
 *  offset  [IN]    Offset of the file
 *  size    [IN]    Size of the data
 * RETURNS
 *  0 successful
 * SEE ALSO
 *  vm_get_resource_offset_from_file
 * EXAMPLE
 *	get data of the resource "mre-2.0", size is 1200 bytes
 *	<code>
 *	VMCHAR* res_buf;
 *	VMUINT offset;
 *    offset = vm_get_resource_offset_from_file("E:\\sample.vxp","mre-2.0");
 *    res_buf = vm_malloc(1200);
 *	result = vm_resource_get_data_from_file( "E:\\sample.vxp", res_buf, offset, 1200);
 *	if(result == 0)
 *	 {
 *	  // get error
 *	 }
 *	 else
 *	 {
 *	   // get success
 *		 ...
 *		 vm_free(res_buf);	 // release the resource after use it.
 *	 }
 *	 </code> 
 *****************************************************************************/
VMINT32 vm_resource_get_data_from_file(VMWSTR filename, VMUINT8 *data, VMUINT32 offset, VMUINT32 size);

/*****************************************************************************
 * FUNCTION
 *    vm_get_resource_offset
 * DESCRIPTION
 *  get resource's offset from current file
 * PARAMETERS
 *  res_name : [IN]  Resource name, not include path.
 * RETURNS
 *  Resource offset
 *  0 is error
 * SEE ALSO
 *  vm_get_resource_offset_from_file
 * EXAMPLE
 *  get offset of the resource "mre-2.0"
 *	 <code>
 *	 VMUINT offset;
 *     offset = vm_get_resource_offset("mre-2.0");
 *	 </code> 
*****************************************************************************/
VMUINT vm_get_resource_offset(char *res_name);

 /*****************************************************************************
 * FUNCTION
 *  vm_get_resource_offset_from_file
 * DESCRIPTION
 *  get resource offset from one file
 * PARAMETERS
 *  filename : [IN] The file need to read the resource.
 *  res_name : [IN] Resource name, not include path.
 * RETURNS
 *  Resource offset
 *  0 is error
 * SEE ALSO
 *  vm_get_resource_offset
 * EXAMPLE
 *  get offset of the resource "mre-2.0"
 *	 <code>
 *	 VMUINT offset;
 *	  
 *     offset = vm_get_resource_offset("E:\\sample.vxp", "mre-2.0");
 *	 </code> 
*****************************************************************************/
VMUINT vm_get_resource_offset_from_file(VMWSTR filename, char *res_name);


 /*****************************************************************************
 * FUNCTION
 *  vm_get_resource_offset_and_size_from_file
 * DESCRIPTION
 *  get resource offset and size from one file
 * PARAMETERS
 *  filename : [IN] The file need to read the resource.
 *  res_name : [IN] Resource name, not include path.
 *  res_size : [OUT] res size.
 * RETURNS
 *  Resource offset
 *  0 is error
 * SEE ALSO
 *  vm_get_resource_offset_from_file
 * EXAMPLE
 *  get offset of the resource "mre-2.0"
 *	<code>
 *	VMUINT offset;
 *	VMINT size;
 *	offset = vm_get_resource_offset("E:\\sample.vxp", "mre-2.0", (VMINT*)&size);
 *	</code> 
*****************************************************************************/
VMUINT vm_get_resource_offset_and_size_from_file(VMWSTR filename, char *res_name, VMINT* res_size);


/*****************************************************************************
 * FUNCTION
 *  vm_load_resource_use_outside_memory
 * DESCRIPTION
 *  get resource use outside memory
 * PARAMETERS
 *  filename : [IN] The file need to read the resource.
 *  res_name : [IN] Resource name, not include path.
 *  buffer : [IN] buffer to put resource data.
 *  buffer_size : [IN] buffer size. 
 *  hint : [OUT] buffer size and offset.  this will cache data to speed up resource loading time
 * RETURNS
 *  Resource offset
 *  0 is error
 * EXAMPLE
 *  get data of the resource "mre-2.0"
 *  <code>
 *  VMCHAR* res_buf;
 *  vm_res_read_hint_struct hint;
 *  VMINT buffer_size;
 *  vm_load_resource_use_outside_memory("E:\\sample.vxp","mre-2.0", NULL, 0, &hint);
 *  res_buf = vm_malloc(hint.res_size);
 *  result = vm_load_resource_use_outside_memory("E:\\sample.vxp","mre-2.0", res_buf, hint.res_size, &hint);
 *  if(result == 0)
 *	{
 *	 // get error
 *	}
 *	else
 *	{
 *	  // get success
 *		...
 *		vm_free(res_buf);	// release the resource after use it.
 *	}
 *	</code> 
*****************************************************************************/
VMBOOL vm_load_resource_use_outside_memory(VMWSTR filename, char *res_name, void* buffer, VMINT buffer_size, vm_res_read_hint_struct* hint);

#ifdef __cplusplus
}
#endif

#endif /* VMRES_SDK_H */
