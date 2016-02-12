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
#ifndef _VRE4RES_SDK_H_
#define	_VRE4RES_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#define VM_RES_SUCCESS          0   /* load resource success */
#define VM_RES_OUT_OF_MEM       -1  /* memory not enough */
#define VM_RES_PARAM_ERROR      -2  /* parameter is not right */
#define VM_RES_ITEM_NOT_FOUND   -3  /* resource not find or file open faild*/

#undef __VM_RES_DEBUG_DATA__

#ifdef __LINKIT_SDK__
#define GetString(x) vm_res_get_string((VMUINT32)x)
#define GetImage(x) vm_res_get_image((VMUINT32)x)
#define GetAudio(x) vm_res_get_audio((VMUINT32)x)
#define FreeRes(x) vm_res_delete((VMUINT32)x);
#endif

/*****************************************************************************
 * FUNCTION
 *  vm_res_init
 * DESCRIPTION
 *  Init LINKIT resource, will load current language table into RAM
 *  Need to be called before use LINKIT Resource.
 * PARAMETERS
 *  VMINT32  
 * RETURNS
 *  VM_RES_SUCCESS
 *  VM_RES_ITEM_NOT_FOUND : file cannot open
 * SEE ALSO
 *  vm_res_deinit
 * EXAMPLE
 *  init the resource
 *     <code>
 *     vm_res_init();
 *     ...
 *     vm_res_deinit();
 *     </code> 
 *****************************************************************************/
extern VMINT32 vm_res_init(void);


/*****************************************************************************
 * FUNCTION
 *  vm_res_init_with_language
 * DESCRIPTION
 *  Init LINKIT resource, will load special language table into RAM
 *  Need to be called before use LINKIT Resource.
 * PARAMETERS
 *  language : language id to load, the id can be get for reseditor
 * RETURNS
 *  VM_RES_SUCCESS
 *  VM_RES_ITEM_NOT_FOUND : file cannot open
 * EXAMPLE
 *  init the resource
 *     <code>
 *     vm_res_init_with_language(44);   // load english
 *     ...
 *     vm_res_deinit();
 *     </code> 
 *****************************************************************************/
extern VMINT32 vm_res_init_with_language(VMUINT32 language);


/*****************************************************************************
 * FUNCTION
 *  vm_res_deinit
 * DESCRIPTION
 *  Release all LINKIT resource, will free all memory of resource
 *  Could be called after use LINKIT Resource.
 * PARAMETERS
 *  VMINT32
 * RETURNS
 *  VM_RES_SUCCESS
 *  VM_RES_ITEM_NOT_FOUND : file cannot open
 * SEE ALSO
 *  vm_res_deinit
 * EXAMPLE
 *  init the resource
 *     <code>
 *     vm_res_init();
 *     ...
 *     vm_res_deinit();
 *     </code> 
 *****************************************************************************/
extern VMINT32 vm_res_deinit(void);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_string
 * DESCRIPTION
 *  Get the string by ID, no need to delete
 * PARAMETERS
 *  string_id         [IN]      ID to get.
 * RETURNS
 *  VMUINT8 *                   String pointer of the ID, only current language, NULL for not found
 * EXAMPLE
 *  display a string in resource
 *     <code>
 *	 int x;
 *	 int y;
 *	 int wstr_len;
 *	 VMWSTR s;
 *	 vm_graphic_color color;
 *	 
 *     vm_res_init();
 *     s = (VMWSTR)vm_res_get_string(STR_ID_HELLO);
 *	 
 *	 wstr_len = vm_graphic_get_string_width(s);
 *
 *	 x = (vm_graphic_get_screen_width() - wstr_len) / 2;
 *	 y = (vm_graphic_get_screen_height() - vm_graphic_get_character_height()) / 2;
 *
 *	 color.vm_color_565 = VM_COLOR_WHITE;
 *	 vm_graphic_setcolor(&color);
 *	 
 *	 vm_graphic_fill_rect_ex(layer_hdl[0], 0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height());
 *	 
 *     color.vm_color_565 = VM_COLOR_BLUE;
 *	 vm_graphic_setcolor(&color);
 *	 
 *	 vm_graphic_textout_to_layer(layer_hdl[0],x, y, s, wstr_len);
 *	 
 *	 vm_graphic_flush_layer(layer_hdl, 1);
 *	 
 *     vm_res_deinit();
 *     </code> 
 *****************************************************************************/
extern VMUINT8 *vm_res_get_string(VMUINT32 string_id);

/* DOM-NOT_FOR_SDK-BEGIN */
/*****************************************************************************
 * FUNCTION
 *  vm_res_load_image_start
 * DESCRIPTION
 *  phase out, no use now
 * PARAMETERS
 *  void
 * RETURNS
 *  VMINT32
 *****************************************************************************/
extern VMINT32 vm_res_load_image_start(void);


/*****************************************************************************
 * FUNCTION
 *  vm_res_load_image_end
 * DESCRIPTION
 *  phase out, no use now
 * PARAMETERS
 *  void
 * RETURNS
 *  VMINT32
 *****************************************************************************/
extern VMINT32 vm_res_load_image_end(void);
/* DOM-NOT_FOR_SDK-END */


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_image
 * DESCRIPTION
 *  Get Image data by ID. Will alloc memory, need to use FreeRes/vm_res_delete to free.
 *  Only alloc 1 time for the same ID. Will return Image size at the same time.
 * PARAMETERS
 *  image_id :        [IN]      ID to get.
 *  size :            [OUT]     Image size
 * RETURNS
 *  VMUINT8 *                  Image pointer of the ID
 * EXAMPLE
 *     <code>
 *	 VMUINT8 *res=NULL;
 *	 VMUINT8 *target_layer_buf;
 *	 VMUINT32 size;
 *	 VMINT canvas;
 *	 VMUINT8 *canvas_buffer = NULL;
 *	 struct frame_prop* image_prop = NULL;
 *	 
 *     vm_res_init();
 *     target_layer_buf = vm_graphic_get_layer_buffer(layer_hdl[0]);
 *	
 *	res = vm_res_get_image_and_size(IMAGE_1,&size);
 *	 
 *	 if(!res)
 *	{
 *		return;
 *	}
 *
 *	canvas = vm_graphic_load_image(res,size);
 *	canvas_buffer = vm_graphic_get_canvas_buffer(canvas);
 *	image_prop = vm_graphic_get_img_property(canvas,1);
 *	vm_graphic_fill_rect(target_layer_buf, 0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height(), VM_COLOR_BLUE, VM_COLOR_BLUE);
 *	vm_graphic_blt(target_layer_buf,45,80,canvas_buffer,0,0,image_prop->width,image_prop->height,1);
 *	vm_graphic_release_canvas(canvas); 
 *	vm_graphic_flush_layer(layer_hdl, 1);
 *	vm_res_delete(IMAGE_1);	 
 *     vm_res_deinit();
 *     </code> 
 *****************************************************************************/
extern VMUINT8 *vm_res_get_image_and_size(VMUINT32 image_id, VMUINT32 *size);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_image_with_header
 * DESCRIPTION
 *  this is use for vpp file, get Image data by ID. Will alloc memory, need to use FreeRes/vm_res_delete to free.
 *  Only alloc 1 time for the same ID.
 * PARAMETERS
 *  image_id         [IN]      ID to get.
 * RETURNS
 *  VMUINT8 *                  Image pointer of the ID
 * SEE ALSO
 *  vm_res_get_image_and_size_with_header
 *****************************************************************************/
extern VMUINT8 *vm_res_get_image_with_header(VMUINT32 image_id);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_image_and_size_with_header
 * DESCRIPTION
 *  this is use for vpp file, get Image data by ID. Will alloc memory, need to use FreeRes/vm_res_delete to free.
 *  Only alloc 1 time for the same ID. Will return Image size at the same time.
 * PARAMETERS
 *  image_id :        [IN]      ID to get.
 *  size :            [OUT]     Image size
 * RETURNS
 *  VMUINT8 *                  Image pointer of the ID
 * SEE ALSO
 *  vm_res_get_image_and_size
 *****************************************************************************/
extern VMUINT8 *vm_res_get_image_and_size_with_header(VMUINT32 image_id, VMUINT32 *size);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_image_and_size_from_file
 * DESCRIPTION
 *  Get other file's image data by ID. this api need application to alloc memory.
 * PARAMETERS
 *  filename :        [IN]        File full path
 *  image_id :       [IN]     ID to get.
 *  buff :               [IN]     Buffer to put image data,  if the is NULL, the function will return image size
 *  size :              [IN/OUT]     when buff is NULL, this is output parameter, will get image size; when buff is not NULL, this is input parameter
 * RETURNS
 *  VMINT                 1 is ok, o is error
 * SEE ALSO
 *  vm_res_get_audio_and_size_from_file
 * EXAMPLE
 *     <code>
 	VMINT result;
 *	 VMUINT8 *res=NULL;
 *	 VMUINT8 *target_layer_buf;
 *	 VMUINT32 size;
 *	 VMINT canvas;
 *	 VMUINT8 *canvas_buffer = NULL;
 *	 struct frame_prop* image_prop = NULL;
 *	 
 *     vm_res_init();
 *     target_layer_buf = vm_graphic_get_layer_buffer(layer_hdl[0]);
 *	
 *	result = vm_res_get_image_and_size_from_file("E:\\sample.vxp", IMAGE_1,NULL, &size);
 *	 
 *	 if(!result )
 *	{
 *		return;
 *	}
 *
 *    res = vm_calloc(size+1);
 *	result = vm_res_get_image_and_size_from_file("E:\\sample.vxp", IMAGE_1,res, &size);
 *	
 *	 if(!result )
 *	{
 *		vm_free(res);
 *		return;
 *	}
 *
 *	canvas = vm_graphic_load_image(res,size);
 *	canvas_buffer = vm_graphic_get_canvas_buffer(canvas);
 *	image_prop = vm_graphic_get_img_property(canvas,1);
 *	vm_graphic_fill_rect(target_layer_buf, 0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height(), VM_COLOR_BLUE, VM_COLOR_BLUE);
 *	vm_graphic_blt(target_layer_buf,45,80,canvas_buffer,0,0,image_prop->width,image_prop->height,1);
 *	vm_graphic_release_canvas(canvas); 
 *	vm_graphic_flush_layer(layer_hdl, 1);
 *	vm_free(res)	 
 *     vm_res_deinit();
 *     </code> 
 *****************************************************************************/
extern VMINT vm_res_get_image_and_size_from_file(VMWSTR filename, VMUINT32 image_id, void* buff, VMUINT32 *size);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_audio_and_size_from_file
 * DESCRIPTION
 *  Get file's audio data by ID. this api need application to alloc memory.
 * PARAMETERS
 *  filename :        [IN]      File full path
 *  image_id :       [IN]     ID to get.
 *  buff :               [IN]     Buffer to put audio data,  if the is NULL, the function will return audio size
 *  size :              [IN/OUT]     when buff is NULL, this is output parameter, will get audio size; when buff is not NULL, this is input parameter
 * RETURNS
 *  VMINT                 1 is ok, o is error
 * SEE ALSO
 *  vm_res_get_image_and_size_from_file
 * EXAMPLE
 *     <code>
 *	VMINT result;
 *	 VMUINT8 *res=NULL;
 *	 VMUINT32 size;
 *	 
 *     vm_res_init();
 *	
 *	result = vm_res_get_audio_and_size_from_file("E:\\sample.vxp", AUDIO_1,NULL, &size);
 *	 
 *	 if(!result )
 *	{
 *		return;
 *	}
 *
 *    res = vm_calloc(size+1);
 *	result = vm_res_get_audio_and_size_from_file("E:\\sample.vxp", AUDIO_1,res, &size);
 *	
 *	 if(!result )
 *	{
 *		vm_free(res);
 *		return;
 *	}
 *
 *	vm_free(res)	 
 *     vm_res_deinit();
 *     </code> 
 *****************************************************************************/
extern VMINT vm_res_get_audio_and_size_from_file(VMWSTR filename, VMUINT32 audio_id, void *buff, VMUINT32 *size);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_string_and_size_from_file
 * DESCRIPTION
 *  Get file's string data by ID. this api need application to alloc memory.
 * PARAMETERS
 *  filename :        [IN]        File full path
 *  image_id :       [IN]     ID to get.
 *  buff :               [IN]     Buffer to put string data,  if the is NULL, the function will return string size
 *  size :              [IN/OUT]     when buff is NULL, this is output parameter, will get string size; when buff is not NULL, this is input parameter
 * RETURNS
 *  VMINT                 1 is ok, o is error
 * SEE ALSO
 *  vm_res_get_audio_and_size_from_file
 * EXAMPLE
 *     <code>
 *	VMINT result;
 *	 VMUINT8 *res=NULL;
 *	 VMUINT32 size;
 *	 
 *     vm_res_init();
 *	
 *	result = vm_res_get_string_and_size_from_file("E:\\sample.vxp", STRING_1,NULL, &size);
 *	 
 *	 if(!result )
 *	{
 *		return;
 *	}
 *
 *    res = vm_calloc(size+1);
 *	result = vm_res_get_string_and_size_from_file("E:\\sample.vxp", STRING_1,res, &size);
 *	
 *	 if(!result )
 *	{
 *		vm_free(res);
 *		return;
 *	}
 *
 *	vm_free(res)	 
 *     vm_res_deinit();
 *     </code> 
 *****************************************************************************/
extern VMINT vm_res_get_string_and_size_from_file(VMWSTR filename, VMUINT32 string_id, void *buff, VMUINT32 *size);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_image_and_size_from_rom
 * DESCRIPTION
 *  Get rom app's image data by ID. this api no need application to alloc memory.
 * PARAMETERS
 *  filename :        [IN]        File full path
 *  image_id :       [IN]     ID to get.
 *  buff :               [OUT]     image data pointer
 *  size :              [OUT]     image size
 * RETURNS
 *  VMINT                 1 is ok, o is error
 * SEE ALSO
 *  vm_res_get_audio_and_size_from_rom
 * EXAMPLE
 *  display a string in resource
 *     <code>
 	VMINT result;
 *	 VMUINT8 *res=NULL;
 *	 VMUINT8 *target_layer_buf;
 *	 VMUINT32 size;
 *	 VMINT canvas;
 *	 VMUINT8 *canvas_buffer = NULL;
 *	 struct frame_prop* image_prop = NULL;
 *	 
 *     vm_res_init();
 *     target_layer_buf = vm_graphic_get_layer_buffer(layer_hdl[0]);
 *	
 *	result = vm_res_get_image_and_size_from_rom("@:\xxxxx.rom", IMAGE_1,&res, &size);
 *	
 *	 if(!result )
 *	{
 *		return;
 *	}
 *
 *	canvas = vm_graphic_load_image(res,size);
 *	canvas_buffer = vm_graphic_get_canvas_buffer(canvas);
 *	image_prop = vm_graphic_get_img_property(canvas,1);
 *	vm_graphic_fill_rect(target_layer_buf, 0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height(), VM_COLOR_BLUE, VM_COLOR_BLUE);
 *	vm_graphic_blt(target_layer_buf,45,80,canvas_buffer,0,0,image_prop->width,image_prop->height,1);
 *	vm_graphic_release_canvas(canvas); 
 *	vm_graphic_flush_layer(layer_hdl, 1); 
 *     vm_res_deinit();
 *     </code> 
 *****************************************************************************/
extern VMINT vm_res_get_image_and_size_from_rom(VMWSTR filename, VMUINT32 image_id, void **buff, VMUINT32 *size);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_audio_and_size_from_rom
 * DESCRIPTION
 *  Get rom app's  audio data by ID. this api no need application to alloc memory.
 * PARAMETERS
 *  filename :        [IN]        File full path
 *  image_id :       [IN]     ID to get.
 *  buff :               [OUT]     audio data pointer
 *  size :              [OUT]     audio size
 * RETURNS
 *  VMINT                 1 is ok, o is error
 * SEE ALSO
 *  vm_res_get_image_and_size_from_rom
 *****************************************************************************/
extern VMINT vm_res_get_audio_and_size_from_rom(VMWSTR filename, VMUINT32 audio_id, void **buff, VMUINT32 *size);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_string_and_size_from_rom
 * DESCRIPTION
 *  Get rom app's  string data by ID. this api no need application to alloc memory.
 * PARAMETERS
 *  filename :        [IN]        File full path
 *  image_id :       [IN]     ID to get.
 *  buff :               [OUT]     string data pointer
 *  size :              [OUT]     string size
 * RETURNS
 *  VMINT                 1 is ok, o is error
 * SEE ALSO
 *  vm_res_get_audio_and_size_from_rom
 *****************************************************************************/
extern VMINT vm_res_get_string_and_size_from_rom(VMWSTR filename, VMUINT32 string_id, void **buff, VMUINT32 *size);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_image
 * DESCRIPTION
 *  Get Image data by ID. Will alloc memory, need to use FreeRes/vm_res_delete to free.
 *  Only alloc 1 time for the same ID.
 * PARAMETERS
 *  image_id         [IN]      ID to get.
 * RETURNS
 *  VMUINT8 *                  Image pointer of the ID
 * SEE ALSO
 *  vm_res_get_image_and_size
 * EXAMPLE
 *     <code>
 *	 VMUINT8 *res=NULL;
 *	
 *	res = vm_res_get_image(IMAGE_1);
 *	 
 *	 if(!res)
 *	{
 *		return;
 *	}
 *    // do somthing
 *	vm_res_delete(IMAGE_1);	 
 *     </code> 
 *****************************************************************************/
extern VMUINT8 *vm_res_get_image(VMUINT32 image_id);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_audio
 * DESCRIPTION
 *  Get audio data by ID. Will alloc memory, need to use FreeRes/vm_res_delete to free.
 *  Only alloc 1 time for the same ID.
 * PARAMETERS
 *  audio_id         [IN]      ID to get.
 * RETURNS
 *  VMUINT8 *                  Audio pointer of the ID
 * SEE ALSO
 *  vm_res_get_image
 * EXAMPLE
 *     <code>
 *	 VMUINT8 *res=NULL;
 *	
 *	res = vm_res_get_audio(AUDIO_1);
 *	 
 *	 if(!res)
 *	{
 *		return;
 *	}
 *    // do somthing
 *	vm_res_delete(AUDIO_1);	 
 *     </code> 
 *****************************************************************************/
extern VMUINT8 *vm_res_get_audio(VMUINT32 audio_id);


/*****************************************************************************
 * FUNCTION
 *  vm_res_delete
 * DESCRIPTION
 *  Management the list of current allocated resource. This is the delete node func
 * PARAMETERS
 *  id         [IN]      ID of the resource
 * RETURNS
 *  VM_RES_SUCCESS
 *  VM_RES_PARAM_ERROR
 *  VM_RES_ITEM_NOT_FOUND
 * SEE ALSO
 *  vm_res_get_image_and_size
 * EXAMPLE
 *     <code>
 *	 VMUINT8 *res=NULL;
 *	
 *	res = vm_res_get_audio(AUDIO_1);
 *	 
 *	 if(!res)
 *	{
 *		return;
 *	}
 *    // do somthing
 *	vm_res_delete(AUDIO_1);	 
 *     </code> 
 *****************************************************************************/
extern VMINT32 vm_res_delete(VMUINT32 id);


/*****************************************************************************
 * FUNCTION
 *  vm_res_get_virtual_image
 * DESCRIPTION
 *	load resource from current file, system will alloc 16 bytes as virtual image for graphic interface 
 *	this need to call vm_res_delete after use. this will not load the real data of image, only load res offset
 *	and file handle, graphic interface will load the real data when it to show the image
 * PARAMETERS
 *  image_id         [IN]      ID of the resource
 * RETURNS
 *  NULL: resource error
 *  VMUINT8 *                  virtual struct pointer
 * EXAMPLE
 *     <code>
 *	 VMUINT8 *res=NULL;
 *	
 *	res = vm_res_get_virtual_image(IMAGE_1);
 *	 
 *	 if(!res)
 *	{
 *		return;
 *	}
 *    // do somthing
 *	vm_res_delete(IMAGE_1);	 
 *     </code> 
 *****************************************************************************/
extern VMUINT8 *vm_res_get_virtual_image(VMUINT32 image_id);


#ifdef __cplusplus
}
#endif

#endif /* _VRE4RES_SDK_H_ */

