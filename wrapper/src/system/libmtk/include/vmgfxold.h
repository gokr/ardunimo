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


#ifndef VMCPT_SDK_H_
#define VMCPT_SDK_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"
#include "vmgraph.h"
#include "vmlog.h"

/* vmgraph.h*/

/******************************************************************************
* FUNCTION
*  vm_graphic_lock
* DESCRIPTION
* create layer and set clip region. clip region is full screen.
* PARAMETERS
* void
* RETURNS
*  void
*****************************************************************************/
void vm_graphic_lock(void);



/******************************************************************************
* FUNCTION
*  vm_graphic_unlock
* DESCRIPTION
* blt the layer to LCD and delete layer
* PARAMETERS
* void
* RETURNS
*  void
*****************************************************************************/
void vm_graphic_unlock(void);



/******************************************************************************
* FUNCTION
*  vm_graphic_get_buffer
* DESCRIPTION
* get the layer buffer
* PARAMETERS
* void
* RETURNS
*  the layer buffer pointer
*****************************************************************************/
VMUINT8 * vm_graphic_get_buffer(void);



/******************************************************************************
* FUNCTION
*  vm_graphic_flush_buffer
* DESCRIPTION
* blt the layer to LCD. 
* PARAMETERS
* void
* RETURNS
*  void
*****************************************************************************/
void vm_graphic_flush_buffer(void);


/******************************************************************************
* FUNCTION
*  vm_initialize_screen_buffer
* DESCRIPTION
* create base layer(if not exist) and reset clip region to full screen. 
* PARAMETERS
* void
* RETURNS
*  void
*****************************************************************************/
void vm_initialize_screen_buffer(void);



/******************************************************************************
* FUNCTION
*  vm_finalize_screen_buffer
* DESCRIPTION
* delete base layer. 
* PARAMETERS
* void
* RETURNS
*  void
*****************************************************************************/
void vm_finalize_screen_buffer(void);


/******************************************************************************
* FUNCTION
*  vm_graphic_draw_gif
* DESCRIPTION
* decode the gif image to base layer
* PARAMETERS
* gif	: [IN] image data pointer
* gif_len : [IN]image data length
* x : [IN]x offset of source start position
* y : [IN]y offset of source start position
* width : [IN]source image width
* height : [IN]source image height
* frame_index : [IN]frame index of gif image
* RETURNS
*  always return 0, make no sense
*****************************************************************************/
VMINT vm_graphic_draw_gif(VMUINT8* gif, VMINT gif_len, VMINT x, VMINT y, VMINT width, VMINT height, VMINT frame_index);


/******************************************************************************
* FUNCTION
*  vm_graphic_bitblt
* DESCRIPTION
* draw the resource to base layer
* PARAMETERS
* resid : [IN] resource id
* x : [IN] x offset of destination 
* y : [IN] y offset of destination
* RETURNS
*  always return -1, make no sense
*****************************************************************************/
VMINT vm_graphic_bitblt(VMINT resid, int x, int y);



/******************************************************************************
* FUNCTION
*  vm_graphic_drawtext
* DESCRIPTION
* draw the text to base layer
* PARAMETERS
* x : [IN] x offset of destination 
* y : [IN] y offset of destination
* s : [IN] to be shown string buffer pointer
* length : [IN] string length
* color : [IN] string color
* RETURNS
*  void
*****************************************************************************/
void vm_graphic_drawtext(VMINT x, VMINT y, VMWSTR s, VMINT32 length, VMINT color);


/******************************************************************************
* FUNCTION
*  vm_graphic_setpixel
* DESCRIPTION
* draw the point to base layer
* PARAMETERS
* x : [IN] x offset of destination 
* y : [IN] y offset of destination
* color : [IN] point color
* RETURNS
*  void
*****************************************************************************/
void vm_graphic_setpixel(VMINT x, VMINT y, VMINT color);


/******************************************************************************
* FUNCTION
*  vm_graphic_drawline
* DESCRIPTION
* draw the line to base layer
* PARAMETERS
* x0	: [IN] x offset of start position 
* y0	: [IN] y offset of start position
* x1	: [IN] x offset of end position 
* y1	: [IN] y offset of end position
* color : [IN] line color 
* RETURNS
*  void
*****************************************************************************/
void vm_graphic_drawline(VMINT x0, VMINT y0, VMINT x1, VMINT y1, VMINT color);


/******************************************************************************
* FUNCTION
*  vm_graphic_drawrect
* DESCRIPTION
* draw the rect to base layer
* PARAMETERS
* x : [IN] x offset of start position 
* y : [IN] y offset of start position
* width : [IN] rect width 
* height : [IN] rect height
* color : [IN] rect color 
* RETURNS
*  void
*****************************************************************************/
void vm_graphic_drawrect(VMINT x, VMINT y, VMINT width, VMINT height, VMINT color);


/******************************************************************************
* FUNCTION
*  vm_graphic_fillrect
* DESCRIPTION
* draw the filled rect to base layer
* PARAMETERS
* x : [IN] x offset of start position 
* y : [IN] y offset of start position
* width : [IN] rect width 
* height : [IN] rect height
* color : [IN] rect color 
* RETURNS
*  void
*****************************************************************************/
void vm_graphic_fillrect(VMINT x, VMINT y, int width, int height, int color);


/* vmddraw.h*/

/******************************************************************************
 * FUNCTION
 *  vm_dd_initialize_clip_rect
 * DESCRIPTION
 *  get layer buffer and set clip region to the full screen size
 * PARAMETERS
 *  void 		
 * RETURNS
 *  void
 *****************************************************************************/
void vm_dd_initialize_clip_rect(void);



/******************************************************************************
 * FUNCTION
 *  vm_dd_set_clip
 * DESCRIPTION
 *  set the clip region
 * PARAMETERS
 * x	: [IN] x offset of start position 
 * y	: [IN] y offset of start position
 * width : [IN] clip region width 
 * height	: [IN] clip region height	
 * RETURNS
 *  void
 *****************************************************************************/
void vm_dd_set_clip(VMINT x, VMINT y, VMINT width, VMINT height);



/******************************************************************************
 * FUNCTION
 *  vm_dd_initialize_clip_rect
 * DESCRIPTION
 *  reset clip region to the full screen size
 * PARAMETERS
 *  void 		
 * RETURNS
 *  void
 *****************************************************************************/
void vm_dd_reset_clip(void);


/******************************************************************************
 * FUNCTION
 *  vm_dd_blt_all_cutting_frames
 * DESCRIPTION
 *  reduce  the image to appointed size
 * PARAMETERS
 *  buf : [IN] destination buffer
 *  source_surface	: [IN] source buffer		
 *  x_num : [IN] resized width		
 *  y_num : [IN] resized height		
 *  width : [IN] source width		
 *  height : [IN] source height		
 * RETURNS
 *  void
 *****************************************************************************/
void vm_dd_blt_all_cutting_frames(VMBYTE *buf, VMBYTE *source_surface, VMINT x_num, VMINT y_num, VMINT width, VMINT height);


/******************************************************************************
 * FUNCTION
 *  vm_dd_img_flood
 * DESCRIPTION
 *  draw the appointed frame index image to destination buffer
 * PARAMETERS
 *  buf : [IN] destination buffer
 *  x_dst	: [IN] x offset of destination 		
 *  y_dst	: [IN] y offset of destination		
 *  source_surface	: [IN] source buffer		
 *  width : [IN] source width		
 *  height : [IN] source height	
 * frame_index : [IN]frame index
 * RETURNS
 *  void
 *****************************************************************************/
void vm_dd_img_flood(VMBYTE *buf, VMINT x_dst, VMINT y_dst,VMBYTE *source_surface,  VMINT width, VMINT height, VMINT frame_index);


/******************************************************************************
 * FUNCTION
 *  vm_dd_copy
 * DESCRIPTION
 *  copy the appointed frame index/mirror mode/position image to destination buffer
 * PARAMETERS
 *  buf	: [IN] destination buffer
 *  x_dest : [IN] x offset of destination 		
 *  y_dest : [IN] y offset of destination		
 *  source_surface	: [IN] source buffer
 *  x_src	: [IN]x offset of source
 *  y_src	: [IN]y offset of source
 *  width	: [IN] source width		
 *  height	 : [IN] source height	
 * frame_index : [IN]frame index
 * direction : [IN] copy direction, means mirror direction
 * RETURNS
 *  void
 *****************************************************************************/
void vm_dd_copy(VMBYTE *buf, VMINT x_dest, VMINT y_dest, VMBYTE *source_surface,  VMINT x_src, VMINT y_src, VMINT width, VMINT height, VMINT frame_index, VMINT direction);


/******************************************************************************
 * FUNCTION
 *  vm_dd_flood_4_regional
 * DESCRIPTION
 *  copy  the appointed frame index image to destination buffer twice,  vertical alignment
 * PARAMETERS
 *  buf : [IN] destination buffer
 *  x_dst	: [IN] x offset of destination 		
 *  y_dst	: [IN] y offset of destination		
 *  source_surface	: [IN] source buffer		
 *  width	: [IN] source width		
 *  height	 : [IN] source height	
 * frame_index : [IN]frame index
 * RETURNS
 *  void
 *****************************************************************************/
void vm_dd_flood_4_regional(VMBYTE *buf, VMINT x_dst, VMINT y_dst,VMBYTE *source_surface, VMINT width, VMINT height, VMINT frame_index);


/******************************************************************************
 * FUNCTION
 *  vm_dd_load_image
 * DESCRIPTION
 *  image decode
 * PARAMETERS
 *  img : [IN] source image buffer
 *  img_len : [IN] source image length
 * RETURNS
 *  if succeed ,return pointer of decoded data, otherwise return NULL
 *****************************************************************************/
VMUINT8* vm_dd_load_image(VMUINT8 *img, VMINT img_len);


/******************************************************************************
 * FUNCTION
 *  vm_dd_get_img_property
 * DESCRIPTION
 *  get the appointed frame property
 * PARAMETERS
 *  img : [IN] source image buffer
 *  frame_index : [IN] source image index
 * RETURNS
 *  frame property structure pointer
 *****************************************************************************/
struct frame_prop * vm_dd_get_img_property(VMUINT8 *img,  VMUINT8 frame_index);


/******************************************************************************
 * FUNCTION
 *  vm_dd_get_frame_number
 * DESCRIPTION
 *  get the gif image frame number
 * PARAMETERS
 *  img : image pointer 		
 * RETURNS
 *  frame number
 *****************************************************************************/
VMINT vm_dd_get_frame_number(VMUINT8 *img);


/******************************************************************************
 * FUNCTION
 *  vm_dd_clean
 * DESCRIPTION
 *  clean the buffer with the appointed color
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *color16 : [IN] color value
 * RETURNS
 *  void
 *****************************************************************************/
void vm_dd_clean(VMUINT8* buf, VMUINT16 color16);



/******************************************************************************
 * FUNCTION
 *  vm_dd_active_layer
 * DESCRIPTION
 *  active layer handle
 * PARAMETERS
 *  handle : [IN] layer handle 		
 * RETURNS
 *  void
 *****************************************************************************/
void vm_dd_active_layer(VMINT handle);


/******************************************************************************
 * FUNCTION
 *  vm_graph_drawtext
 * DESCRIPTION
 *  show string to base layer
 * PARAMETERS
 *  x : [IN] x offset of destination	
 *  y : [IN] y offset of destination	
 *  s : [IN] string pointer	
 *  length : [IN] string length	
 *  color : [IN]	string color
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graph_drawtext(VMINT x, VMINT y, VMWSTR s, VMINT32 length, VMUINT16 color);


/******************************************************************************
 * FUNCTION
 *  vm_graph_release_surface
 * DESCRIPTION
 *  free buffer
 * PARAMETERS
 *  off_surface : [IN]buffer pointer	
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graph_release_surface(VMUINT8 * off_surface);


/******************************************************************************
 * FUNCTION
 *  vm_graph_create_custom_buf
 * DESCRIPTION
 *  create canvas
 * PARAMETERS
 *  width : [IN] buffer width	
 *  height : [IN] buffer height
 * RETURNS
 *  buffer pointer
 *****************************************************************************/
VMUINT8 * vm_graph_create_custom_buf(VMINT width, VMINT height);

 
/******************************************************************************
 * FUNCTION
 *  vm_graph_delete_custom_buf
 * DESCRIPTION
 *  delete canvas
 * PARAMETERS
 *  custom_buf : [IN] canvas handle, it means buffer pointer	
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graph_delete_custom_buf(VMUINT8 * custom_buf);


/******************************************************************************
 * FUNCTION
 *  vm_graph_move
 * DESCRIPTION
 *  copy buffer from source to destination
 * PARAMETERS
 *  screen_buf	: [IN] destination buffer pointer	
 *  x_dest : [IN] x offset of destination
 *  y_dest : [IN] y offset of destination
 * custom_buf : [IN] source buffer pointer
 *  x_src : [IN]x offset of source
 *  y_src : [IN]y offset of source
 *  width : [IN]source width
 *  height : [IN]source height
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graph_move(VMBYTE *screen_buf, VMINT x_dest, VMINT y_dest, VMBYTE *custom_buf, VMINT x_src, VMINT y_src, VMINT width, VMINT height);


/* define vm_graphic_set_text_clip, only for compatible with older version */
#define vm_graphic_set_text_clip 			vm_graphic_set_clip

/* define vm_graphic_reset_text_clip, only for compatible with older version */
#define vm_graphic_reset_text_clip 		vm_graphic_reset_clip
/* define vm_dd_clean_ex, only for compatible with older version */
#define vm_dd_clean_ex 					vm_dd_clean

/* define vm_dd_copy_ex, only for compatible with older version */
#define vm_dd_copy_ex 					vm_dd_copy

/* define vm_dd_setpixel_ex, only for compatible with older version */
#define vm_dd_setpixel_ex 				vm_graphic_set_pixel	

/* define vm_dd_setpixel, only for compatible with older version */
#define vm_dd_setpixel 					vm_graphic_set_pixel

/* define vm_dd_getpixel_ex, only for compatible with older version */
#define vm_dd_getpixel_ex 				vm_graphic_get_pixel	

/* define vm_dd_getpixel, only for compatible with older version */
#define vm_dd_getpixel 					vm_graphic_get_pixel

/* define vm_dd_line_ex, only for compatible with older version */
#define vm_dd_line_ex 					vm_graphic_line	

/* define vm_dd_line, only for compatible with older version */
#define vm_dd_line 						vm_graphic_line

/* define vm_dd_rect_ex, only for compatible with older version */
#define vm_dd_rect_ex 					vm_graphic_rect	

/* define vm_dd_rect, only for compatible with older version */
#define vm_dd_rect 						vm_graphic_rect

/* define vm_dd_fillrect_ex, only for compatible with older version */
#define vm_dd_fillrect_ex 				vm_graphic_fill_rect	

/* define vm_dd_fillrect, only for compatible with older version */
#define vm_dd_fillrect 					vm_graphic_fill_rect

/* define vm_dd_blt_ex, only for compatible with older version */
#define vm_dd_blt_ex 					vm_graphic_blt	

/* define vm_dd_blt, only for compatible with older version */
#define vm_dd_blt 						vm_graphic_blt

/* define vm_dd_rotate_ex, only for compatible with older version */
#define vm_dd_rotate_ex 				vm_graphic_rotate	

/* define vm_dd_rotate, only for compatible with older version */
#define vm_dd_rotate 					vm_graphic_rotate

/* define vm_dd_mirror_ex, only for compatible with older version */
#define vm_dd_mirror_ex 				vm_graphic_mirror	

/* define vm_dd_mirror, only for compatible with older version */
#define vm_dd_mirror 					vm_graphic_mirror

/* define vm_dd_blt_with_opacity, only for compatible with older version */
#define vm_dd_blt_with_opacity 			vm_graphic_blt_ex

/* define vm_graph_initialize, only for compatible with older version */
#define vm_graph_initialize						vm_initialize_screen_buffer	

/* define vm_graph_finalize, only for compatible with older version */
#define vm_graph_finalize						vm_finalize_screen_buffer

/* define vm_graph_get_buffer, only for compatible with older version */
#define vm_graph_get_buffer						vm_graphic_get_buffer

/* define vm_graph_flush_buffer, only for compatible with older version */
#define vm_graph_flush_buffer					vm_graphic_flush_buffer

/* define vm_graph_initialize_clip_rect, only for compatible with older version */
#define vm_graph_initialize_clip_rect				vm_dd_initialize_clip_rect

/* define vm_graph_blt_all_cutting_frames, only for compatible with older version */
#define vm_graph_blt_all_cutting_frames			vm_dd_blt_all_cutting_frames

/* define vm_graph_img_flood, only for compatible with older version */
#define vm_graph_img_flood						vm_dd_img_flood

/* define vm_graph_copy, only for compatible with older version */
#define vm_graph_copy							vm_dd_copy

/* define vm_graph_load_image, only for compatible with older version */
#define vm_graph_load_image					vm_dd_load_image

/* define vm_graph_get_img_property, only for compatible with older version */
#define vm_graph_get_img_property 				vm_dd_get_img_property

/* define vm_graph_get_frame_number, only for compatible with older version */
#define vm_graph_get_frame_number				vm_dd_get_frame_number

/* define vm_graph_clean, only for compatible with older version */
#define vm_graph_clean							vm_dd_clean

/* define vm_graph_get_bits_per_pixel, only for compatible with older version */
#define vm_graph_get_bits_per_pixel				vm_graphic_get_bits_per_pixel

/* define vm_graph_set_clip, only for compatible with older version */
#define vm_graph_set_clip						vm_graphic_set_clip

/* define vm_graph_reset_clip, only for compatible with older version */
#define vm_graph_reset_clip						vm_graphic_reset_clip

/* define vm_graphic_reset_text_clip, only for compatible with older version */
#define vm_graph_get_screen_width				vm_graphic_get_screen_width

/* define vm_graph_get_screen_height, only for compatible with older version */
#define vm_graph_get_screen_height				vm_graphic_get_screen_height

/* define vm_graph_get_character_height, only for compatible with older version */
#define vm_graph_get_character_height			vm_graphic_get_character_height

/* define vm_graph_get_character_width, only for compatible with older version */
#define vm_graph_get_character_width 			vm_graphic_get_character_width

/* define vm_graph_measure_character, only for compatible with older version */
#define vm_graph_measure_character				vm_graphic_measure_character

/* define vm_graph_get_string_width, only for compatible with older version */
#define vm_graph_get_string_width				vm_graphic_get_string_width

/* define vm_graph_set_font, only for compatible with older version */
#define vm_graph_set_font						vm_graphic_set_font

/* define vm_graph_setpixel, only for compatible with older version */
#define vm_graph_setpixel						vm_graphic_set_pixel

/* define vm_graph_getpixel, only for compatible with older version */
#define vm_graph_getpixel						vm_graphic_get_pixel

/* define vm_graph_line, only for compatible with older version */
#define vm_graph_line							vm_graphic_line

/* define vm_graph_rect, only for compatible with older version */
#define vm_graph_rect							vm_graphic_rect

/* define vm_graph_fillrect, only for compatible with older version */
#define vm_graph_fillrect							vm_graphic_fill_rect	

/* define vm_graph_blt, only for compatible with older version */
#define vm_graph_blt								vm_graphic_blt

/* define vm_graph_rotate, only for compatible with older version */
#define vm_graph_rotate							vm_graphic_rotate

/* define vm_graph_mirror, only for compatible with older version */
#define vm_graph_mirror							vm_graphic_mirror

/* define vm_graph_draw_gif, only for compatible with older version */
#define vm_graph_draw_gif						vm_graphic_draw_gif

#ifdef __cplusplus
}
#endif

#endif /* VMCPT_SDK_H_ */
