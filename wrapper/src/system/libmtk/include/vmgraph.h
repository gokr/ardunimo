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

#ifndef VMGRAPHIC_SDK_H_
#define VMGRAPHIC_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* GDI return code */
typedef enum
{
    VM_GDI_ERR_BASE_LAYER_EXIST = -17,      //baselayer exist when set wallpaper
    VM_GDI_FONTSIZE_NOT_SUPPORT = -16,      //self define size not support
    VM_GDI_ERR_NOT_SUPPORT_ROTATE = -15,
    VM_GDI_MIBR_ERR = -14,         /*general MIBR error*/
	VM_GDI_MIBR_RES_ERR,           /*GDI MIBR resource error*/
	VM_GDI_MIBR_NOT_FORE,           /*APP is not in foreground status*/
	VM_GDI_MIBR_NO_RES,             /*no resource */
	VM_GDI_ERR_PLATFORM_DECODE_FAILED, /*platform decode error*/
	VM_GDI_ERR_BASE_LAYER_NOT_EXIST,     /*base layer not exist*/
	VM_GDI_ERR_UNSUPPORT_IMAGE_TYPE,      /*decode image type no support*/
	VM_GDI_ERR_MALLOC_FAILED,             /*can not malloc memory*/
	VM_GDI_ERR_LAYER_BIND,                /*layer bind with canvas error*/
	VM_GDI_ERR_FREE_RES,                  /*free resource error*/
	VM_GDI_ERR_CREATE_LAYER_FAILED,          /*create layer fail*/
	VM_GDI_ERR_CREATE_CANVAS_FAILED,        /*general MIBR fail*/
	VM_GDI_ERR_WRONG_PARAM,                  /*parameter error*/
	VM_GDI_FAILED,                            /*general GDI error*/
	VM_GDI_SUCCEED                           /*general GDI succeed*/
}vm_graphic_result;                          

/*GDI rotate type*/
typedef enum
{
      VM_GDI_ROTATE_NORMAL = 0,  /*rotate 0 degree*/
      VM_GDI_ROTATE_90 = 0x01,   /*rotate 90 degree*/
      VM_GDI_ROTATE_180 = 0x02,	 /*rotate 180 degree*/
      VM_GDI_ROTATE_270 = 0x03,  /*rotate 270 degree*/
      VM_GDI_MIRROR = 0x80,      /*mirror*/
      VM_GDI_MIRROR_ROTATE_90 = 0x81,/*mirror 90 degree*/
      VM_GDI_MIRROR_ROTATE_180 = 0x82,/*mirror 180 degree*/
      VM_GDI_MIRROR_ROTATE_270 = 0x83/*mirror 270 degree*/
}vm_graphic_rotate_value;


/*GDI gradient paint style*/
typedef enum
{
    VM_GDI_GP_HOR = 0,  /*horizon*/
    VM_GDI_GP_VER,      /*vertical*/
    VM_GDI_GP_DIA,      /*lean 45 degree */
    VM_GDI_GP_DIA_INV,  /*de-lean 45 degree*/
    VM_GDI_GP_FLIP      /*from middle to edge*/
}vm_graphic_gp_style;

/*screen rotate type enum*/
typedef enum
{
    VM_GRAPHIC_SCREEN_ROTATE_0=0,
    VM_GRAPHIC_SCREEN_ROTATE_90,//1
    VM_GRAPHIC_SCREEN_ROTATE_180,//2
    VM_GRAPHIC_SCREEN_ROTATE_270,//3
    VM_GRAPHIC_SCREEN_ROTATE_MIRROR_0,//4
    VM_GRAPHIC_SCREEN_ROTATE_MIRROR_90,//5
    VM_GRAPHIC_SCREEN_ROTATE_MIRROR_180,//6
    VM_GRAPHIC_SCREEN_ROTATE_MIRROR_270,//7
    VM_GRAPHIC_SCREEN_ROTATE_MAX_TYPE//8
} vm_graphic_screen_rotate_value;


typedef enum
{
    VM_FONT_ENGINE_ERROR = -1,
    VM_FONT_ENGINE_NO_ERROR = 0,
    VM_FONT_ENGINE_NO_TRUNCATION,
    VM_FONT_ENGINE_TRUNCATION,
    VM_FONT_ENGINE_ERROR_NULL_STRING,
    VM_FONT_ENGINE_ZERO_LENGTH,
    VM_FONT_ENGINE_ERROR_NO_TRUNCATION_AVAILABLE,
    VM_FONT_ENGINE_END_OF_ENUM
} vm_font_engine_error_message_enum;

/*
 *This macro is not work now,just keep for compatibility.
 */
#define MAX_BLT_LAYER					(4)  
/* GDI_RESULT define*/
#define VM_GDI_RESULT VMINT

/* GDI_HANDLE define*/
#define VM_GDI_HANDLE VMINT

/* max layer width*/
#define MAX_LAYER_WIDTH 				(65535)

/*max layer height*/
#define MAX_LAYER_HEIGHT 				(65535)

/*max layer count*/
#define MAX_LAYER						(16)


/*max layer number when flatten to other layer or canvas*/
#define MAX_FLATTEN_LAYER				(4)

/*max multiples when enlarge image */
#define MAX_PIXEL_ENLARGE				(512)

/* canvas signature size */
#define VM_CANVAS_SIGNATURE_SIZE            (12)    

/* canvas property size */
#define VM_CANVAS_FRAME_PROPERTY_SIZE       (20)    

/*the offset from the canvas beginning to the image data*/
#define CANVAS_BUF_OFFSET 				(VM_CANVAS_SIGNATURE_SIZE + VM_CANVAS_FRAME_PROPERTY_SIZE)

/*layer or canvas attribute: no transparent color*/
#define VM_NO_TRANS_COLOR				(-1)


/* RGB565 white color */
#define VM_COLOR_WHITE				    (0XFFFF)			

/* RGB565 black color */
#define VM_COLOR_BLACK					(0X0000)			

/* RGB565 red color */
#define VM_COLOR_RED					(0XF800)			

/* RGB565 green color */
#define VM_COLOR_GREEN					(0X07E0)			

/* RGB565 blue color */
#define VM_COLOR_BLUE					(0X001F)			

/* get color value from RGB value */
#define VM_RGB(r, g, b)					((b << 16) + (g << 8) + r)

/* get RGB32 color value (BGRA) from ARGB value */
#define VM_RGB32_ARGB(a, r, g, b)		((b << 24) + (g << 16) + (r << 8) + a)

/* get RGB565 color value from ARGB value, the same as VM_COLOR_888_TO_565(r, g, b) */
#define VM_RGB565_ARGB(a, r, g, b)		(((r & 0xf8) + ((g & 0xe0) >> 5)) << 8) + ((g & 0x1c) << 3) + (b >> 3)

/* get a RGB32 value of int type (BGRA) from 565 color*/
#define VM_COLOR_RGB565_TO_RGB32(color16)	((color16 & 0x001F) << 27) + ((color16 & 0x07E0) << 13) + ((color16 & 0xF800))

/* get 565 color from a value of int type */
#define VM_COLOR_INT_TO_565(i)			((i & 0xf8) << 8) + ((i & 0xfc00) >> 5) + ((i & 0xf80000) >> 19)

/* convert color format from 888 to 565 */
#define VM_COLOR_888_TO_565(r, g, b)	(((r & 0xf8) + ((g & 0xe0) >> 5)) << 8) + ((g & 0x1c) << 3) + (b >> 3)

/* convert color format from 565 to 888 */
#define VM_COLOR_565_TO_888(color16)	((color16 & 0x001F) << 19) + ((color16 & 0x07E0) << 5) + ((color16 & 0xF800) >> 8)

/* get Red value from a rgb value */
#define VM_COLOR_GET_RED(color16)		((color16 & 0xF800) >> 8)

/* get Green value from a rgb value  */
#define VM_COLOR_GET_GREEN(color16)	    ((color16 & 0x07E0) >> 3)

/* get Blue value from a rgb value  */
#define VM_COLOR_GET_BLUE(color16)		((color16 & 0x001F) << 3)

#define VM_CANVAS_DATA_OFFSET            (32)

typedef void (*vm_graphic_screen_rotate_event_callback)(VMINT, VMINT); // 1:envent  2:inside/outside|| horizontal/vertical


/*clip region*/	
typedef struct clip_rect{
	VMINT16 left;			/*x offset at begin*/
	VMINT16 top;			/*y offset  at begin*/	
	VMINT16 right;			/*x offset at end*/	
	VMINT16 bottom;			/*y offset at end*/
	VMBYTE	flag;			/* flag = 0: the clip region is invalid; flag =1: the clip region is valid*/
}clip_rect;


/* single frame info for gif image  */
struct frame_prop 
{
	VMUINT8  flag;					/* marker to show it is  frame beginning  */
	VMUINT8  is_resize;                             /* if resize */
	VMUINT16 left;					/* x offset */
	VMUINT16 top;					/* y offset */
	VMUINT16 width;					/*image width */
	VMUINT16 height;				/* image height*/
	VMUINT16 delay_time;			/* the interval between two frames*/	
	VMUINT8  trans_color_index;		/* reserved*/	
	VMUINT16 trans_color;			/* transparent color*/	
	VMUINT32 offset;				/* current frame size , unit:byte */	
};

/*image property*/
typedef struct _vm_graphic_imgprop
{
	VMINT width;   /*image widtg*/
	VMINT height;   /*image height*/
}vm_graphic_imgprop;

/*character infomation*/
typedef struct _vm_graphic_char_info
{
    VMINT dwidth;  /*the real width of the character, can be used for typeset*/
    VMINT width;   /*the width of the character, not include padding*/
    VMINT height;  /*the height of the character*/
    VMINT ascent;  /*base line*/
    VMINT descent; /*the length from the character bottom to the baseline*/ 
}vm_graphic_char_info;

/* font size */
typedef enum {
	VM_SMALL_FONT,          /*small font*/
	VM_MEDIUM_FONT,         /*medium font*/
	VM_LARGE_FONT           /*large font*/
} font_size_t;

/*create mode of layer */
typedef enum{
	VM_BASE_LAYER = 1,          /*create base layer*/
	VM_FAST_LAYER ,             /*create fast layer(no need to malloc memory*/
	VM_BUF,                     /*create layer using outside memory*/
	VM_CREATE_CANVAS            /*create layer, and create canvas at the same time*/
}vm_layer_mode;

/*property of canvas*/
typedef enum{
	VM_CANVAS_LEFT = 1,   /*x offset*/
	VM_CANVAS_TOP,        /*y offset*/
	VM_CANVAS_WIDTH,      /*canvas width*/
	VM_CANVAS_HEIGHT,      /*canvas height*/
	VM_CANVAS_CF,		  /*canvas color format*/
	VM_CANVAS_DATASIZE	  /*canvas data size*/
}vm_canvas_prop;


/*point structure*/
typedef struct _vm_graphic_point{
	VMINT16 x;   /*x offset*/
	VMINT16 y;   /*y offset*/
}vm_graphic_point;

/*color structure*/
typedef struct _vm_graphic_color{
	VMUINT vm_color_565;     /*color value in 565 style*/
	VMUINT vm_color_888;     /*color value in 888 style*/
}vm_graphic_color;


typedef struct _vm_graphic_color_argb{
    VMUINT8 a;    /* alpha */
    VMUINT8 r;    /* red   */
    VMUINT8 g;    /* green */
    VMUINT8 b;    /* blue  */
}vm_graphic_color_argb;


/*pen structure*/
typedef struct _vm_graphic_pen{
	VMBYTE cycle;     /*the length of one cycle*/ 
	VMBYTE *bitvalues;/*the value of one cycle ,example:VMBYTE bitvalues[] = {1,1,1,0,0};
                                                                                         vm_graphic_pen pen;
                                                                                         pen.cycle = sizeof(bitvalues);
                                                                                         pen.bitvalues = bitvalues;        */
}vm_graphic_pen;


typedef enum
{
    VM_GRAPHIC_COLOR_FORMAT_16,                    /* 16-bit, rgb 565 */
    VM_GRAPHIC_COLOR_FORMAT_24,                    /* 24-bit, B,G,R       8,8,8 */
    VM_GRAPHIC_COLOR_FORMAT_32,                    /* 32-bit, B,G,R,A  8,8,8,8 */
    VM_GRAPHIC_COLOR_FORMAT_32_PARGB,              /* 32-bit, PB,PG,PR,A  8,8,8,8 */
    VM_GRAPHIC_COLOR_FORMAT_END           
} vm_graphic_color_famat_enum;


typedef VMUINT8 vm_graphic_color_famat;


typedef enum
{
    VM_FRM_SCREEN_ROTATE_0,
    VM_FRM_SCREEN_ROTATE_90,
    VM_FRM_SCREEN_ROTATE_180,
    VM_FRM_SCREEN_ROTATE_270,
    VM_FRM_SCREEN_ROTATE_MIRROR_0,
    VM_FRM_SCREEN_ROTATE_MIRROR_90,
    VM_FRM_SCREEN_ROTATE_MIRROR_180,
    VM_FRM_SCREEN_ROTATE_MIRROR_270,
    VM_FRM_SCREEN_ROTATE_MAX_TYPE
} vm_frm_screen_rotate_enum;

typedef enum {
	VM_NON_CACHEABLE,    
	VM_CACHEABLE,       
} vm_cacheable_t;



/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_screen_width
 * DESCRIPTION
 *  get the screen width
 * PARAMETERS
 *  void
 * RETURNS
 *  the width of the screen
 *****************************************************************************/
VMINT vm_graphic_get_screen_width(void);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_screen_height
 * DESCRIPTION
 *  get the screen height
 * PARAMETERS
 *  void
 * RETURNS
 *  the height of the screen
 *****************************************************************************/
VMINT vm_graphic_get_screen_height(void);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_create_layer 
 * DESCRIPTION
 *  Create layer.layer is the simulation for LCD.
 *  using this api, user can create two layers at most, and user needn't to require additional memory for it.    
 *  layer 0: same with LCD's size and position. it means, top left coordination must be (0,0),  width = screen width and  height = screen height
 *  layer 1: user can set the opacity, position,size(can not larger than LCD's size).
 * the two layers can be merged with the appointed opacity
 * PARAMETERS
 *  x : [IN]x_top left coordination
 *  y : [IN]y_top left coordination
 * width : [IN] the width of the layer, the unit:pixel
 * height : [IN]the height of the layer, the unit:pixel
 * trans_color : [IN]the transparent color. -1 means no transparent color.
 * RETURNS
 *  if succeed, return the layer handle, if fail, return the error code
 * EXAMPLE
 * VMINT layer_hdl[2] = {0};			
 * layer_hdl[0] = vm_graphic_create_layer(0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height(), VM_NO_TRANS_COLOR);
 * //user can draw on the layer
 *      vm_graphic_line_ex( layer_hdl[0],0,0,100,100);
 *     ....
 * // when need to show it to the LCD
 *   vm_graphic_flush_layer( layer_hdl[0], 1);
 * //when no more use the layer, delete it
 *   vm_graphic_delete_layer(layer_hdl[0]);
 *****************************************************************************/
VMINT vm_graphic_create_layer(VMINT x, VMINT y, VMINT width, VMINT height, VMINT trans_color);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_delete_layer
 * DESCRIPTION
 *  delete the layer created by vm_graphic_create_layer. user can release the layer when app exits
 * PARAMETERS
 *  handle : [IN] the layer handle to be deleted
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED. otherwise, return error code
 *****************************************************************************/
VMINT vm_graphic_delete_layer(VMINT handle);



/*****************************************************************************
 * FUNCTION
 *  vm_graphic_active_layer
 * DESCRIPTION
 *  active layer. all the GDI operation is valid only to the active layer. 
 * PARAMETERS
 *  handle : [IN]the layer handle to be actived.if the layer handle is wrong, system will not change, it means 
 * current active layer will not change
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED. otherwise, return error code
 *****************************************************************************/
VMINT vm_graphic_active_layer(VMINT handle);



/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_layer_buffer
 * DESCRIPTION
 *  get the appointed layer's buffer
 * PARAMETERS
 *  handle : [IN]layer handle 
 * RETURNS
 *  if succeed, return buffer address. otherwise, return NULL
 *****************************************************************************/
VMUINT8* vm_graphic_get_layer_buffer (VMINT handle);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_clear_layer_bg
 * DESCRIPTION
 *  clean the layer with the transparent color. the color is same as the trans_color used in vm_graphic_create_layer()
 * PARAMETERS
 *  handle : [IN]layer handle 
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED. otherwise, return VM_GDI_FAILED
 *****************************************************************************/ 
VMINT vm_graphic_clear_layer_bg (VMINT handle);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_flush_layer
 * DESCRIPTION
 *  flatten layers to one layer and blt to LCD. Only call this API does app can update LCD
 * PARAMETERS
 *  layer_handles : [IN] the pointer of layer array 
 *  count	: [IN] layer number that  to be flushed. if the number is larger than max layer count (get by vm_graphic_get_blt_layer_count()), 
 *                 		just use the max layer count
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED. otherwise, return error code
 *****************************************************************************/ 
VMINT vm_graphic_flush_layer(VMINT* layer_handles, VMINT count);

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_flush_layer_non_block
 * DESCRIPTION
 *  flatten layers to one layer and blt to LCD non block.
 * PARAMETERS
 *  layer_handles : [IN] the pointer of layer array 
 *  count	: [IN] layer number that  to be flushed. if the number is larger than max layer count (get by vm_graphic_get_blt_layer_count()), 
 *                 		just use the max layer count
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED. otherwise, return error code
 *****************************************************************************/
VMINT vm_graphic_flush_layer_non_block(VMINT* layer_handles, VMINT count);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_layer_count
 * DESCRIPTION
 *  get the max layer number of current platform
 * PARAMETERS
 *  void
 * RETURNS
 *  the max layer number
 *****************************************************************************/ 


VMINT vm_graphic_get_layer_count(void);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_layer_position
 * DESCRIPTION
 *  get the layer position
 * PARAMETERS
 *  handle : [IN] layer handle
 *  x	: [OUT] x_top left coordination
 *  y	: [OUT] y_top left coordination
 *  width	: [OUT] layer width
 *  height : [OUT] layer height
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED,otherwise return error code
 *****************************************************************************/  
VMINT vm_graphic_get_layer_position(VMINT handle, VMINT *x, VMINT *y, VMINT *width, VMINT *height);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_set_layer_opacity
 * DESCRIPTION
 *  set the layer opacity. value range:[0,100], 0 means the layer is transparent. 
 * PARAMETERS
 *  handle : [IN] layer handle
 *  percent : [IN] the percent of opacity
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED,otherwise return error code
 *****************************************************************************/ 
VMINT vm_graphic_set_layer_opacity(VMINT handle, VMINT percent);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_bits_per_pixel
 * DESCRIPTION
 *  get the byte number of one pixel in current platform
 * PARAMETERS
 *  void
 * RETURNS
 *  the number of byte
 *****************************************************************************/ 
VMINT vm_graphic_get_bits_per_pixel(void);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_pixel
 * DESCRIPTION
 *  get the color of the appointed point in the buffer 
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the point 
 *  y	 : [IN] y offset of the point 
 * RETURNS
 *  the color of the point
 *****************************************************************************/  
VMUINT16 vm_graphic_get_pixel(VMUINT8 *buf, VMINT x, VMINT y);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_pixel_cf
 * DESCRIPTION
 *  get the color of the appointed point in the buffer 
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the point 
 *  y	 : [IN] y offset of the point 
 * RETURNS
 *  the color of the point, the color value include a, r, g, b value 
 *****************************************************************************/  
vm_graphic_color_argb vm_graphic_get_pixel_cf(VMUINT8 *buf, VMINT x, VMINT y);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_set_pixel
 * DESCRIPTION
 *  draw a point on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the point 
 *  y	 : [IN] y offset of the point 
 * color : [IN] color of the point
 * RETURNS
 *  void
 *****************************************************************************/  
void vm_graphic_set_pixel(VMUINT8 *buf, VMINT x,VMINT y, VMUINT16 color);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_set_pixel_cf
 * DESCRIPTION
 *  draw a point on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the point 
 *  y	 : [IN] y offset of the point 
 * color : [IN] color of the point, the color value include a, r, g, b value
 * RETURNS
 *  void
 *****************************************************************************/  
void vm_graphic_set_pixel_cf(VMUINT8 *buf, VMINT x, VMINT y, vm_graphic_color_argb* color);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_line
 * DESCRIPTION
 *  draw a line on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y	 : [IN] y offset of the start point 
 *  x	 : [IN] x offset of the end point 
 *  y	 : [IN] y offset of the end point 
 *color : [IN] color of the line
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_line(VMUINT8 *buf, VMINT x0, VMINT y0, VMINT x1, VMINT y1, VMUINT16 color);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_line_cf
 * DESCRIPTION
 *  draw a line on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y	 : [IN] y offset of the start point 
 *  x	 : [IN] x offset of the end point 
 *  y	 : [IN] y offset of the end point 
 *color : [IN] color of the line, the color value include a, r, g, b value
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_line_cf(VMUINT8 *buf, VMINT x0, VMINT y0, VMINT x1, VMINT y1, vm_graphic_color_argb* color);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_rect
 * DESCRIPTION
 *  draw a rect on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y : [IN] y offset of the start point 
 *  width : [IN] width of the rect 
 *  height : [IN] height of the rect 
 *color : [IN] color of the rect
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_rect(VMUINT8 *buf, VMINT x, VMINT y, VMINT width, VMINT height, VMUINT16 color);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_rect_cf
 * DESCRIPTION
 *  draw a rect on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y : [IN] y offset of the start point 
 *  width : [IN] width of the rect 
 *  height : [IN] height of the rect 
 *color : [IN] color of the rect, the color value include a, r, g, b value
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_rect_cf(VMUINT8 *buf, VMINT x, VMINT y, VMINT width, VMINT height, vm_graphic_color_argb* color);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_fill_rect
 * DESCRIPTION
 *  draw a filled rect on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y	 : [IN] y offset of the start point 
 *  width : [IN] width of the rect 
 *  height : [IN] height of the rect 
 * line_color : [IN] color of the frame
 * back_color : [IN]  color of the filled
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_fill_rect(VMUINT8 *buf, VMINT x, VMINT y, VMINT width, VMINT height, VMUINT16 line_color, VMUINT16 back_color);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_fill_rect_cf
 * DESCRIPTION
 *  draw a filled rect on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y	 : [IN] y offset of the start point 
 *  width : [IN] width of the rect 
 *  height : [IN] height of the rect 
 * line_color : [IN] color of the frame, the color value include a, r, g, b value
 * back_color : [IN]  color of the filled, the color value include a, r, g, b value
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_fill_rect_cf(VMUINT8 *buf,VMINT x,VMINT y,VMINT width,VMINT height,vm_graphic_color_argb* line_color,vm_graphic_color_argb* back_color);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_roundrect
 * DESCRIPTION
 *  draw a round rectangle  on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y : [IN] y offset of the start point 
 *  width : [IN] width of the round rectangle  
 *  height	 : [IN] height of the round rectangle  
 * corner_width : [IN] radius of the rounded angle. the value must less than half of width, if not, the api will have no effect
 *  color : [IN] color of the round rectangle 
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_roundrect (VMUINT8 * buf, VMINT x, VMINT y, VMINT width, VMINT height, VMINT corner_width, VMUINT16 color);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_roundrect_cf
 * DESCRIPTION
 *  draw a round rectangle  on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y : [IN] y offset of the start point 
 *  width : [IN] width of the round rectangle  
 *  height	 : [IN] height of the round rectangle  
 * corner_width : [IN] radius of the rounded angle. the value must less than half of width, if not, the api will have no effect
 *  color : [IN] color of the round rectangle, the color value include a, r, g, b value 
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_roundrect_cf (VMUINT8 * buf, VMINT x, VMINT y, VMINT width, VMINT height, VMINT corner_width, vm_graphic_color_argb*  color);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_fill_roundrect
 * DESCRIPTION
 *  draw a filled round rectangle  on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y	 : [IN] y offset of the start point 
 *  width : [IN] width of the round rectangle  
 *  height : [IN] height of the round rectangle  
 * corner_width : [IN] radius of the rounded angle. the value must less than half of width, if not, the api will have no effect
 *  color : [IN] color of the filled round rectangle 
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_fill_roundrect (VMUINT8 * buf, VMINT x,	VMINT y, VMINT width, VMINT height, VMINT corner_width, VMUINT16 color);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_fill_roundrect_cf
 * DESCRIPTION
 *  draw a filled round rectangle  on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y	 : [IN] y offset of the start point 
 *  width : [IN] width of the round rectangle  
 *  height : [IN] height of the round rectangle  
 * corner_width : [IN] radius of the rounded angle. the value must less than half of width, if not, the api will have no effect
 *  color : [IN] color of the filled round rectangle, the color value include a, r, g, b value 
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_fill_roundrect_cf (VMUINT8 * buf, VMINT x,	VMINT y, VMINT width, VMINT height, VMINT corner_width, vm_graphic_color_argb* color);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_ellipse
 * DESCRIPTION
 *  draw a ellipse on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y	 : [IN] y offset of the start point 
 *  width : [IN] width of the ellipse 
 *  height	 : [IN] height of the ellipse 
 *  color : [IN] color of the ellipse
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_ellipse (VMUINT8 * buf, VMINT x, VMINT y, VMINT width, VMINT height, VMUINT16 color);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_ellipse_cf
 * DESCRIPTION
 *  draw a ellipse on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y	 : [IN] y offset of the start point 
 *  width : [IN] width of the ellipse 
 *  height	 : [IN] height of the ellipse 
 *  color : [IN] color of the ellipse, the color value include a, r, g, b value 
 * RETURNS
 *  void
 *****************************************************************************/ 
void vm_graphic_ellipse_cf(VMUINT8* buf, VMINT x, VMINT y, VMINT width, VMINT height, vm_graphic_color_argb* color);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_fill_ellipse
 * DESCRIPTION
 *  draw a filled ellipse on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y : [IN] y offset of the start point 
 *  width : [IN] width of the ellipse 
 *  height	 : [IN] height of the ellipse 
 *  color : [IN] color of the filled ellipse
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_fill_ellipse (VMUINT8 * buf, VMINT x, VMINT y, VMINT width, VMINT height, VMUINT16 color);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_fill_ellipse_cf
 * DESCRIPTION
 *  draw a filled ellipse on the appointed position of the buffer
 * PARAMETERS
 *  buf : [IN] buffer pointer
 *  x	 : [IN] x offset of the start point 
 *  y : [IN] y offset of the start point 
 *  width : [IN] width of the ellipse 
 *  height	 : [IN] height of the ellipse 
 *  color : [IN] color of the filled ellipse, the color value include a, r, g, b value 
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_fill_ellipse_cf(VMUINT8* buf, VMINT x, VMINT y, VMINT width, VMINT height, vm_graphic_color_argb* color);



/******************************************************************************
 * FUNCTION
 *  vm_graphic_create_canvas
 * DESCRIPTION
 *  create canvas
 * PARAMETERS
 *  width : [IN] width of the canvas 
 *  height	 : [IN] height of the height 
 * RETURNS
 *  if succeed, return the canvas handle, otherwise, return error code
 * EXAMPLE
 * hcanvas = vm_graphic_create_canvas(width, height);
 * if(hcanvas>0)
 * {   
 *    //get the destination pointer of the data to be displayed
 *     frame_buffer = (VMUINT8*)hcanvas + VM_CANVAS_SIGNATURE_SIZE + VM_CANVAS_FRAME_PROPERTY_SIZE;
 *    //use the buffer to create layer
 *      layer_handle = vm_graphic_create_layer_ex(0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height(), VM_NO_TRANS_COLOR,VM_BUF,frame_buffer);
 *    //the following operation is same with vm_graphic_create_layer
 * }
 * else
 * {
 *   //error handle
 * }
 *
 *****************************************************************************/
VMINT vm_graphic_create_canvas(VMINT width, VMINT height);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_create_canvas_cf
 * DESCRIPTION
 *  create canvas
 * PARAMETERS
 *  cf : [IN] color format
 *  width : [IN] width of the canvas 
 *  height	 : [IN] height of the height 
 * RETURNS
 *  if succeed, return the canvas handle, otherwise, return error code
 * EXAMPLE
 * hcanvas = vm_graphic_create_canvas(width, height);
 * if(hcanvas>0)
 * {   
 *    //get the destination pointer of the data to be displayed
 *     frame_buffer = (VMUINT8*)hcanvas + VM_CANVAS_SIGNATURE_SIZE + VM_CANVAS_FRAME_PROPERTY_SIZE;
 *    //use the buffer to create layer
 *      layer_handle = vm_graphic_create_layer_ex(0, 0, vm_graphic_get_screen_width(), vm_graphic_get_screen_height(), VM_NO_TRANS_COLOR,VM_BUF,frame_buffer);
 *    //the following operation is same with vm_graphic_create_layer
 * }
 * else
 * {
 *   //error handle
 * }
 *
 *****************************************************************************/
VMINT vm_graphic_create_canvas_cf(vm_graphic_color_famat cf, VMINT width, VMINT height);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_release_canvas
 * DESCRIPTION
 *  release the  resource created by vm_graphic_create_canvas or vm_graphic_load_image
 * PARAMETERS
 *  hcanvas : [IN] canvas handle
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_release_canvas(VMINT hcanvas);



/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_canvas_buffer
 * DESCRIPTION
 *  get the pointer of the canvas's display buffer
 * PARAMETERS
 *  hcanvas : [IN] canvas handle
 * RETURNS
 *  the pointer of the canvas's display buffer
 *****************************************************************************/
VMUINT8* vm_graphic_get_canvas_buffer(VMINT hcanvas);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_canvas_buffer_size
 * DESCRIPTION
 *  get the size of the canvas's display buffer
 * PARAMETERS
 *  hcanvas : [IN] canvas handle
 * RETURNS
 *  the size of the canvas's display buffer
 *****************************************************************************/
VMINT vm_graphic_get_canvas_buffer_size (VMINT hcanvas);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_load_image
 * DESCRIPTION
 *  image decode, and draw the decoded image to the new-created canvas.
 * PARAMETERS
 *  img : [IN] pointer of source image data
 *  img_len : [IN] image length
 * RETURNS
 *  the pointer of the canvas's display buffer
 *****************************************************************************/
VMINT vm_graphic_load_image(VMUINT8 *img, VMINT img_len);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_load_image_cf
 * DESCRIPTION
 *  image decode, and draw the decoded image to the new-created canvas.
 * PARAMETERS
 *  cf : [IN] color format 
 *  img : [IN] pointer of source image data
 *  img_len : [IN] image length
 * RETURNS
 *  the pointer of the canvas's display buffer
 *****************************************************************************/
VMINT vm_graphic_load_image_cf(vm_graphic_color_famat cf, VMUINT8 *img_data, VMINT img_len);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_img_property
 * DESCRIPTION
 *  get the appointed frame property of the image
 * PARAMETERS
 *  hcanvas : [IN] canvas handle which hold the decoded image data
 *  frame_index : [IN] frameindex ,begin from 0 
 * RETURNS
 *  the pointer of the image property structure
 *****************************************************************************/
struct frame_prop * vm_graphic_get_img_property(VMINT hcanvas, VMUINT8 frame_index);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_img_buffer
 * DESCRIPTION
 *  get the appointed frame buffer of the image
 * PARAMETERS
 *  hcanvas : [IN] canvas handle which hold the decoded image data
 *  frame_index : [IN] frameindex ,begin from 0 
 * RETURNS
 *  the pointer of the image buffer poniter
 *****************************************************************************/
VMUINT8* vm_graphic_get_img_buffer(VMINT hcanvas, VMUINT8 frame_index);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_frame_number
 * DESCRIPTION
 *  get the frame number of the image
 * PARAMETERS
 *  hcanvas : [IN] canvas handle which hold the decoded image data,get by vm_graphic_load_image()
 * RETURNS
 *  frame number
 *****************************************************************************/
VMINT vm_graphic_get_frame_number(VMINT hcanvas);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_blt
 * DESCRIPTION
 *  copy the data from the souce display buffer to the destination buffer. just copy, no merge. 
 *  the destination can be LCD buffer or canvas display buffer
 * PARAMETERS
 *  dst_disp_buf : [IN] destination buffer pointer
 *  x_dest : [IN] x offset of destination position
 *  y_dest : [IN] y offset of destination position
 *  src_disp_buf : [IN] source buffer pointer
 *  x_src : [IN] x offset of source position
 *  y_src : [IN] y offset of source position
 *  width : [IN] the image width
 *  height	 : [IN] the image height
 *  frame_index : [IN] frame number
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_blt(VMBYTE * dst_disp_buf, VMINT x_dest, VMINT y_dest, VMBYTE * src_disp_buf, 
					 VMINT x_src, VMINT y_src, VMINT width, VMINT height, VMINT frame_index);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_blt_ex
 * DESCRIPTION
 *  copy the data from the souce display buffer to the destination buffer. merge with the destination data using the  alpha value. 
 *  the destination can be LCD buffer or canvas display buffer
 * PARAMETERS
 *  dst_disp_buf : [IN] destination buffer pointer
 *  x_dest : [IN] x offset of destination position
 *  y_dest : [IN] y offset of destination position
 *  src_disp_buf : [IN] source buffer pointer
 *  x_src : [IN] x offset of source position
 *  y_src : [IN] y offset of source position
 *  width : [IN] the image width
 *  height	 : [IN] the image height
 *  frame_index : [IN] frame number
 *  alpha : [IN]the value of transparent,value range [0,255], 0 means completely transparent
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_blt_ex(VMBYTE * dst_disp_buf, VMINT x_dest, VMINT y_dest, VMBYTE * src_disp_buf, 
						VMINT x_src, VMINT y_src, VMINT width, VMINT height, VMINT frame_index, VMINT alpha);
					 


/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_character_height
 * DESCRIPTION
 *  get current font height, for dot character, it is precise. for vector font,it is usually higher than 
 *  single character, it is the string height.
 * PARAMETERS
 *  void			
 * RETURNS
 *  the height of the font
 *****************************************************************************/
VMINT vm_graphic_get_character_height(void);



/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_character_width
 * DESCRIPTION
 *  get current character width, for dot character, it is precise. for vector font, it isn't include the 
 *  padding between characters 
 * PARAMETERS
 *  c : [IN] character vlue			
 * RETURNS
 *  the width of the character
 *****************************************************************************/
VMINT vm_graphic_get_character_width(VMWCHAR c);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_string_width
 * DESCRIPTION
 *  get the width of the appointed string
 * PARAMETERS
 *  str : [IN]string pointer			
 * RETURNS
 *  the width of the string
 *****************************************************************************/
VMINT vm_graphic_get_string_width(VMWSTR str);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_string_height
 * DESCRIPTION
 *  get the string of the appointed string
 * PARAMETERS
 *  str : [IN]string pointer			
 * RETURNS
 *  the height of the string
 *****************************************************************************/
VMINT vm_graphic_get_string_height(VMWSTR str);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_measure_character
 * DESCRIPTION
 *  get the width and height of the appointed character. Unit:pixel
 * PARAMETERS
 *  c	 : [IN]the value of character
 *width : [OUT]character width
 *height : [OUT]character height
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED,otherwise, return error code
 *****************************************************************************/
VMINT vm_graphic_measure_character(VMWCHAR c, VMINT *width, VMINT *height);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_character_info
 * DESCRIPTION
 *  get the info of the appointed character
 * PARAMETERS
 *  c	 : [IN]the value of character
 *  char_info : [OUT]character infomation
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED,otherwise, return error code
 *****************************************************************************/

VMINT vm_graphic_get_character_info(VMWCHAR c, vm_graphic_char_info *char_info);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_set_font
 * DESCRIPTION
 *  set font size
 * PARAMETERS
 *  size : [IN]font size 		
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_set_font(font_size_t size);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_textout
 * DESCRIPTION
 *  show text to the display buffer. font size is defined by vm_graphic_set_font(),defaul value is VM_MEDIUM_FONT
 * PARAMETERS
 *  disp_buf : [IN] display buffer pointer 
 * x : [IN] x offset of start position
 * y : [IN] y offset of start position
 * s : [IN] string pointer
 * length : [IN] string length
 * color : [IN] string color
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_textout (VMUINT8* disp_buf, VMINT x, VMINT y, VMWSTR s, VMINT length, VMUINT16 color);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_textout_cf
 * DESCRIPTION
 *  show text to the display buffer. font size is defined by vm_graphic_set_font(),defaul value is VM_MEDIUM_FONT
 * PARAMETERS
 *  disp_buf : [IN] display buffer pointer 
 * x : [IN] x offset of start position
 * y : [IN] y offset of start position
 * s : [IN] string pointer
 * length : [IN] string length
 * color : [IN] string color, the color value include a, r, g, b value
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_textout_cf (VMUINT8* disp_buf, VMINT x, VMINT y, VMWSTR s, VMINT length, vm_graphic_color_argb* color);



/******************************************************************************
 * FUNCTION
 *  vm_graphic_textout_by_baseline
 * DESCRIPTION
 *  show text to the display buffer according baseline. font size is defined by vm_graphic_set_font(),defaul value is VM_MEDIUM_FONT
 * PARAMETERS
 * disp_buf : [IN] display buffer pointer 
 * x : [IN] x offset of start position
 * y : [IN] y offset of start position
 * s : [IN] string pointer
 * length : [IN] string length
 * color : [IN] string color
 * baseline : [IN] the baseline to be aligned 
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_textout_by_baseline (VMUINT8* disp_buf, VMINT x, VMINT y, VMWSTR s, VMINT length, VMUINT16 color,VMINT baseline);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_textout_by_baseline_cf
 * DESCRIPTION
 *  show text to the display buffer according baseline. font size is defined by vm_graphic_set_font(),defaul value is VM_MEDIUM_FONT
 * PARAMETERS
 * disp_buf : [IN] display buffer pointer 
 * x : [IN] x offset of start position
 * y : [IN] y offset of start position
 * s : [IN] string pointer
 * length : [IN] string length
 * color : [IN] string color, the color value include a, r, g, b value
 * baseline : [IN] the baseline to be aligned 
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_textout_by_baseline_cf (VMUINT8* disp_buf, VMINT x, VMINT y, VMWSTR s, VMINT length, vm_graphic_color_argb* color,VMINT baseline);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_set_clip
 * DESCRIPTION
 *  set clip region. any GDI operation out of the clip region will have no effect. It is a global value, when the aim changes, the clip region 
 *  must be reset.
 * PARAMETERS
 *  x1 : [IN]  x offset of top left position	
 *  y1 : [IN] y offset of top left
 *  x2 : [IN] x offset of bottom right position
 *  y2 : [IN] y offset of bottom right position
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_set_clip(VMINT x1, VMINT y1, VMINT x2, VMINT y2);



/******************************************************************************
 * FUNCTION
 *  vm_graphic_reset_clip
 * DESCRIPTION
 *  reset clip region to the full screen size
 * PARAMETERS
 *  void 		
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_reset_clip(void);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_flush_screen
 * DESCRIPTION
 *  notify system to re-paint screen. once APP calls the API, system will send VM_PAINT to the callback fuction  registered
 *  by vm_reg_sysevt_callback
 * PARAMETERS
 *  void 		
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_flush_screen(void);


/*rotate value :90 degree*/
#define VM_ROTATE_DEGREE_90				    (90)

/*rotate value :180 degree*/
#define VM_ROTATE_DEGREE_180				(180)

/*rotate value :270 degree*/
#define VM_ROTATE_DEGREE_270				(270)


/******************************************************************************
 * FUNCTION
 *  vm_graphic_rotate
 * DESCRIPTION
 *  rotate image with the appointed angel to the destinate buffer.
 * PARAMETERS
 *  buf : [IN] 	destinate buffer	
 *  x_des : [IN]x offset of destination	
 *  y_des : [IN]y offset of destination	
 *  src_buf : [IN]source buffer	
 *  frame_index :[IN]frame index	
 *  degrees :[IN]the value of clockwise angle,only valid with the value VM_ROTATE_DEGREE_90,VM_ROTATE_DEGREE_180
 *				VM_ROTATE_DEGREE_270. 
 *  RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_rotate(VMBYTE *buf, VMINT x_des, VMINT y_des, 
						VMBYTE *src_buf, VMINT frame_index, VMINT degrees);


/*Mirror direction:x */
#define VM_MIRROR_X							(0)

/*Mirror direction:y */
#define VM_MIRROR_Y							(1)

/******************************************************************************
 * FUNCTION
 *  vm_graphic_mirror
 * DESCRIPTION
 *  mirror the image to the destination with the appointed direction
 * PARAMETERS
 *  buf : [IN] 	destinate buffer	
 *  x_des : [IN] 	x offset of destination	
 *  y_des : [IN] 	y offset of destination	
 *  src_buf : [IN] 	source buffer	
 *  frame_index : [IN] 	frame index	
 *  direction : [IN] 	the mirror direction ,only valid with the value VM_MIRROR_X,VM_MIRROR_Y 
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_mirror(VMBYTE *buf, VMINT x_des, VMINT y_des, VMBYTE *src_buf, VMINT frame_index, VMINT direction);



/******************************************************************************
 * FUNCTION
 *  vm_reg_res_provider
 * DESCRIPTION
 *  APP can use it to register its own resource get function. if the app self-define resource is saved as array, app can operate it by ID using the 
 *  callback function
 * PARAMETERS
 *  fp : resource callback function pointer		
 * RETURNS
 *  void
 *****************************************************************************/
 void vm_reg_res_provider(VMUINT8* (*fp)(VMINT resid, VMINT* len));



/******************************************************************************
 * FUNCTION
 *  vm_graphic_create_layer_ex
 * DESCRIPTION
 *  create layer using varies modes,before create other layers, base layer must be created firstly.
 * PARAMETERS
 *  x : [IN] x offset of layer position	
 *  y : [IN] y offset of layer position		
 *  width : [IN]layer width	
 *  height : [IN] 	layer height	
 *  mode : [IN] 	creation mode
 *  VM_BASE_LAYER: create base layer. if existed, new attribute will override the old.
 *  VM_FAST_LAYER  create fast layer( no need additional memory),if existed, new attribute will override the old.
 *  VM_BUF: create layer using the canvas buffer. the buffer must be gotten from vm_create_canvas. the canvas 
 *  and buffer are mapped automatically. if re-create layer using the same memory , will return error code
 *  VM_CREATE_CANVAS: create a new canvas , at the same time , create a new layer with the canvas buffer.
 *  the canvas and buffer are mapped automatically.
 *  buf : [IN] only valid when mode = VM_BUF, the buffer pointer
 * RETURNS
 *  if succeed, return the layer handle ,otherwise, return error code
 *****************************************************************************/
VM_GDI_HANDLE vm_graphic_create_layer_ex(VMINT x, VMINT y, VMINT width, VMINT height, VMINT trans_color,VMINT mode,VMUINT8 * buf);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_create_layer_cf
 * DESCRIPTION
 *  create layer using varies modes,before create other layers, base layer must be created firstly.
 * PARAMETERS
 *  cf : [IN] color format
 *  x : [IN] x offset of layer position	
 *  y : [IN] y offset of layer position		
 *  width : [IN]layer width	
 *  height : [IN] 	layer height	
 *  mode : [IN] 	creation mode
 *  VM_BASE_LAYER: create base layer. if existed, new attribute will override the old.
 *  VM_FAST_LAYER  create fast layer( no need additional memory),if existed, new attribute will override the old.
 *  VM_BUF: create layer using the canvas buffer. the buffer must be gotten from vm_create_canvas. the canvas 
 *  and buffer are mapped automatically. if re-create layer using the same memory , will return error code
 *  VM_CREATE_CANVAS: create a new canvas , at the same time , create a new layer with the canvas buffer.
 *  the canvas and buffer are mapped automatically.
 *  buf : [IN] only valid when mode = VM_BUF, the buffer pointer
 *  buf_size: [IN] only valid when mode = VM_BUF, the buffer size
 * RETURNS
 *  if succeed, return the layer handle ,otherwise, return error code
 *****************************************************************************/
VM_GDI_HANDLE vm_graphic_create_layer_cf(vm_graphic_color_famat cf, VMINT x, VMINT y, VMINT width, VMINT height, vm_graphic_color_argb* trans_color, VMINT mode, VMUINT8 *buf, VMINT buf_size);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_create_layer_cf_double
 * DESCRIPTION
 *  create layer using varies modes,before create other layers, base layer must be created firstly.
 * PARAMETERS
 *  cf : [IN] color format
 *  x : [IN] x offset of layer position	
 *  y : [IN] y offset of layer position		
 *  width : [IN]layer width	
 *  height : [IN] 	layer height	
 *  mode : [IN] 	creation mode
 *  VM_BASE_LAYER: create base layer. if existed, new attribute will override the old.
 *  VM_FAST_LAYER  create fast layer( no need additional memory),if existed, new attribute will override the old.
 *  VM_BUF: create layer using the canvas buffer. the buffer must be gotten from vm_create_canvas. the canvas 
 *  and buffer are mapped automatically. if re-create layer using the same memory , will return error code
 *  VM_CREATE_CANVAS: create a new canvas , at the same time , create a new layer with the canvas buffer.
 *  the canvas and buffer are mapped automatically.
 *  buf : [IN] only valid when mode = VM_BUF, the buffer pointer
 *  buf_size: [IN] only valid when mode = VM_BUF, the buffer size 
 *  buf1 : [IN] only valid when mode = VM_BUF, the another buffer pointer
 *  buf_size_1: [IN] only valid when mode = VM_BUF, the another buffer size 
 * RETURNS
 *  if succeed, return the layer handle ,otherwise, return error code
 *****************************************************************************/
VM_GDI_HANDLE vm_graphic_create_layer_cf_double(vm_graphic_color_famat cf, VMINT x, VMINT y, VMINT width, VMINT height, vm_graphic_color_argb* trans_color, VMINT mode, VMUINT8 *buf, VMINT buf_size, VMUINT8 *buf1, VMINT buf_size_1);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_layer_toggle_double
 * DESCRIPTION
 *  swap the two buffer of the layer.
 * PARAMETERS
 *  handle : [IN] layer handle
 * RETURNS
 *  if succeed, return success ,otherwise, return error code
 *****************************************************************************/
VM_GDI_RESULT vm_graphic_layer_toggle_double(VMINT handle);



/******************************************************************************
 * FUNCTION
 *  vm_graphic_release_canvas_ex
 * DESCRIPTION
 *  release the canvas handle. if the canvas maps with layer (it means using this canvas buffer to create a layer), the layer will
 * be deleted at the same time.
 * PARAMETERS
 *  hcanvas : [IN] canvas handle 		
 * RETURNS
 *   if succeed, return VM_GDI_SUCCEED ,otherwise, return error code
 *****************************************************************************/
VM_GDI_RESULT  vm_graphic_release_canvas_ex(VMINT hcanvas);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_flatten_canvas
 * DESCRIPTION
 *  merge several canvas display buffer to active layer and release the canvases and them own layers. the canvas buffers must
 *  map with layer, otherwise, their can not be merged. the MAX number of merged canvases is 4.
 * PARAMETERS
 *  hcanvas : [IN] canvas handle array 	
 *  count : [IN] cavas number
 * RETURNS
 *   if succeed, return VM_GDI_SUCCEED ,otherwise, return error code
 *****************************************************************************/
VM_GDI_RESULT  vm_graphic_flatten_canvas(VMINT *hcanvas,VMINT count);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_flatten_canvas
 * DESCRIPTION
 *  merge several canvas display buffer to active layer. the canvas buffers must
 *  map with layer, otherwise, their can not be merged. the MAX number of merged canvases is 4.
 * PARAMETERS
 *  hcanvas : [IN] canvas handle array 	
 *  count : [IN] cavas number
 * RETURNS
 *   if succeed, return VM_GDI_SUCCEED ,otherwise, return error code
 *****************************************************************************/
VM_GDI_RESULT  vm_graphic_flatten_canvas_ex(VMINT *hcanvas,VMINT count);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_flatten_layer
 * DESCRIPTION
 *  merge several layer to active layer and release layers. active layer will not be released. the MAX number of merged layers is 4.
 * PARAMETERS
 *  hhandle : [IN] layer handle array 	
 *  count : [IN] layer number
 * RETURNS
 *   if succeed, return VM_GDI_SUCCEED ,otherwise, return error code
 *****************************************************************************/
VM_GDI_RESULT vm_graphic_flatten_layer(VMINT *hhandle,VMINT count);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_flatten_layer
 * DESCRIPTION
 *  merge several layer to active layer. the MAX number of merged layers is 4.
 * PARAMETERS
 *  hhandle : [IN] layer handle array 	
 *  count : [IN] layer number
 * RETURNS
 *   if succeed, return VM_GDI_SUCCEED ,otherwise, return error code
 *****************************************************************************/
VM_GDI_RESULT vm_graphic_flatten_layer_ex(VMINT *hhandle,VMINT count);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_resize_layer
 * DESCRIPTION
 *  resize layer size. after resize, the layer need to be re-draw. new width and height can not be larger than the origion's.
 * PARAMETERS
 *  handle : [IN] layer handle 	
 *  width : [IN] new layer width
 *  height : [IN] new layer height
 * RETURNS
 *   if succeed, return VM_GDI_SUCCEED ,otherwise, return error code
 *****************************************************************************/
VM_GDI_RESULT  vm_graphic_resize_layer(VMINT handle,VMINT width,VMINT height);




/******************************************************************************
 * FUNCTION
 *  vm_graphic_setpen
 * DESCRIPTION
 *  set pen attribute
 * PARAMETERS
 *  pen : [IN] pen pointer 	
 * RETURNS
 *   if succeed, return VM_GDI_SUCCEED ,otherwise, return error code
 *****************************************************************************/
VM_GDI_RESULT vm_graphic_setpen(vm_graphic_pen *pen);



/******************************************************************************
 * FUNCTION
 *  vm_graphic_getpen
 * DESCRIPTION
 *  get pen attribute
 * PARAMETERS
 *  void
 * RETURNS
 *  pen attribute structure
 *****************************************************************************/
vm_graphic_pen  vm_graphic_getpen(void);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_setcolor
 * DESCRIPTION
 *  set global color
 * PARAMETERS
 *  color : [IN] color pointer 	
 * RETURNS
 *   if succeed, return VM_GDI_SUCCEED ,otherwise, return error code
 *****************************************************************************/
VM_GDI_RESULT vm_graphic_setcolor(vm_graphic_color* color);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_setcolor
 * DESCRIPTION
 *  set global color
 * PARAMETERS
 *  void	
 * RETURNS
 *  return global color
 *****************************************************************************/
vm_graphic_color vm_graphic_getcolor(void);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_setcolor_argb
 * DESCRIPTION
 *  set global color
 * PARAMETERS
 *  color : [IN] color pointer, the color value include a, r, g, b value
 * RETURNS
 *   if succeed, return VM_GDI_SUCCEED ,otherwise, return error code
 *****************************************************************************/
VM_GDI_RESULT vm_graphic_setcolor_argb(vm_graphic_color_argb* color);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_getcolor_argb
 * DESCRIPTION
 *  set global color
 * PARAMETERS
 *  void	
 * RETURNS
 *  return global color, the color value include a, r, g, b value
 *****************************************************************************/
vm_graphic_color_argb vm_graphic_getcolor_argb(void);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_set_pixel_ex
 * DESCRIPTION
 *  draw point on the layer
 * PARAMETERS
 *  handle : [IN] layer handle
 *  x1 : [IN] x offset of start position
 *  y1 : [IN] y offset of start position
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_set_pixel_ex(VMINT handle,VMINT x1,VMINT y1);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_line_ex
 * DESCRIPTION
 * draw line on the layer, not using pen
 * PARAMETERS
 *  handle : [IN] layer handle
 *  x1 : [IN] x offset of start position
 *  y1 : [IN] y offset of start position
 *  x2 : [IN] x offset of end position
 *  y2 : [IN] y offset of end position
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_line_ex(VMINT handle,VMINT x1,VMINT y1,VMINT x2,VMINT y2);




/******************************************************************************
 * FUNCTION
 *  vm_graphic_line_style
 * DESCRIPTION
 * draw line with style. before using this API, vm_graphic_set_pen must be called, otherwise the operation will have no effection
 * PARAMETERS
 *  handle : [IN] layer handle
 *  x1 : [IN] x offset of start position
 *  y1 : [IN] y offset of start position
 *  x2 : [IN] x offset of end position
 *  y2 : [IN] y offset of end position
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_line_style(VMINT handle,VMINT x1,VMINT y1,VMINT x2,VMINT y2);



/******************************************************************************
 * FUNCTION
 *  vm_graphic_roundrect_ex
 * DESCRIPTION
 * draw round rectangle   on the layer. 
 * PARAMETERS
 *  handle : [IN] layer handle
 *  x	: [IN] x offset of start position
 *  y	: [IN] y offset of start position
 *  width : [IN] round rectangle  width
 *  height : [IN] round rectangle  height
 * frame_width : [IN] radius of the rounded angle. the value must less than half of width, if not, the api will have no effect
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_roundrect_ex(VMINT handle, VMINT x, VMINT y, VMINT width, VMINT height, VMINT frame_width);



/******************************************************************************
 * FUNCTION
 *  vm_graphic_rect_ex
 * DESCRIPTION
 * draw rect  on the layer. 
 * PARAMETERS
 *  handle : [IN] layer handle
 *  x	: [IN] x offset of start position
 *  y : [IN] y offset of start position
 *  width : [IN] rect width
 *  height : [IN] rect height
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_rect_ex(VMINT handle, VMINT x, VMINT y, VMINT width, VMINT height);




/******************************************************************************
 * FUNCTION
 *  vm_graphic_ellipse_ex
 * DESCRIPTION
 * draw ellipse  on the layer. 
 * PARAMETERS
 *  handle : [IN] layer handle
 *  x	 : [IN] x offset of start position
 *  y : [IN] y offset of start position
 *  width : [IN] ellipse width
 *  height : [IN] ellipse height
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_ellipse_ex(VMINT handle, VMINT x, VMINT y, VMINT width, VMINT height);




/******************************************************************************
 * FUNCTION
 *  vm_graphic_polygon
 * DESCRIPTION
 * draw polygon  on the layer. 
 * PARAMETERS
 *  handle : [IN] layer handle
 *  point : [IN] point coordination array
 *  npoint : [IN] point number
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_polygon(VMINT handle, vm_graphic_point *point,VMINT npoint);



/******************************************************************************
 * FUNCTION
 *  vm_graphic_fill_roundrect_ex
 * DESCRIPTION
 * draw round rectangle   on the layer. 
 * PARAMETERS
 *  handle : [IN] layer handle
 *  x : [IN] x offset of start position
 *  y : [IN] y offset of start position
 *  width : [IN] round rectangle  width
 *  height : [IN] round rectangle  height
 * frame_width : [IN] radius of the rounded angle. the value must less than half of width, if not, the api will have no effect
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_fill_roundrect_ex(VMINT handle, VMINT x, VMINT y, VMINT width, VMINT height, VMINT  frame_width);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_fill_rect_ex
 * DESCRIPTION
 * draw filled rect  on the layer. 
 * PARAMETERS
 *  handle : [IN] layer handle
 *  x	 : [IN] x offset of start position
 *  y : [IN] y offset of start position
 *  width : [IN] rect width
 *  height : [IN] rect height
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_fill_rect_ex(VMINT handle, VMINT  x, VMINT  y, VMINT  width, VMINT  height);



/******************************************************************************
 * FUNCTION
 *  vm_graphic_fill_ellipse_ex
 * DESCRIPTION
 * draw ellipse  on the layer. 
 * PARAMETERS
 *  handle : [IN] layer handle
 *  x : [IN] x offset of start position
 *  y : [IN] y offset of start position
 *  width : [IN] ellipse width
 *  height : [IN] ellipse height
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_fill_ellipse_ex(VMINT handle, VMINT  x, VMINT  y, VMINT  width, VMINT  height);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_polygon
 * DESCRIPTION
 * draw filled polygon  on the layer. 
 * PARAMETERS
 *  handle : [IN] layer handle
 *  point : [IN] point coordination array
 *  npoint : [IN] point number
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_fill_polygon(VMINT handle, vm_graphic_point *point,VMINT npoints);




/******************************************************************************
 * FUNCTION
 *  vm_graphic_gradient_paint_rect
 * DESCRIPTION
 * draw gradient_paint_rect  on the layer. 
 * PARAMETERS
 *  handle : [IN] layer handle
 *  x1 : [IN] x offset of top left position
 *  y1 : [IN] y offset of top left position
 *  x2 : [IN] x offset of bottom right position
 *  y2 : [IN] y offset of bottom right position
 * color_start : [IN]start color of gradient color
 * color_end : [IN] end colorof gradient color
 * style : [IN] paint style
 * RETURNS
 *  void
 *****************************************************************************/
void vm_graphic_gradient_paint_rect(VMINT handle, VMINT x1, VMINT y1, VMINT x2, VMINT y2, vm_graphic_color color_start, vm_graphic_color color_end,vm_graphic_gp_style style);


/******************************************************************************
 * FUNCTION
 *  vm_graphic_get_layer_clip
 * DESCRIPTION
 * get layer clip region. 
 * PARAMETERS
 *  handle : [IN] layer handle
 *  curcliprect : [OUT] region structure pointer
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
 *****************************************************************************/
VM_GDI_RESULT vm_graphic_get_layer_clip(VMINT handle,clip_rect * curcliprect);



/******************************************************************************
* FUNCTION
*  vm_graphic_set_layer_clip
* DESCRIPTION
* set layer clip region. it will affect the global setting
* PARAMETERS
*  handle : [IN] layer handle
*  x1 : [IN] x offset of top left position
 *  y1 : [IN] y offset of top left position
 *  x2 : [IN] x offset of bottom right position
 *  y2 : [IN] y offset of bottom right position
 
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_graphic_set_layer_clip(VMINT handle,VMINT16 x1,VMINT16 y1,VMINT16 x2,VMINT16 y2);


/******************************************************************************
* FUNCTION
*  vm_graphic_translate_layer
* DESCRIPTION
* move the layer to the new position
* PARAMETERS
*  handle : [IN] layer handle
*  tx	: [IN] x offset of new position
 * ty : [IN] y offset of new position
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_graphic_translate_layer(VMINT handle , VMINT tx, VMINT ty);




/******************************************************************************
* FUNCTION
*  vm_graphic_rotate_layer
* DESCRIPTION
* rotate the layer
* PARAMETERS
*  handle : [IN] layer handle
*  rotatevalue	: [IN] degree of angle,now, valid value is VM_GDI_ROTATE_90,VM_GDI_ROTATE_180 ,VM_GDI_ROTATE_270
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_graphic_rotate_layer(VMINT handle, vm_graphic_rotate_value rotatevalue);



/******************************************************************************
* FUNCTION
*  vm_graphic_load_image_resized
* DESCRIPTION
* resize image to appointed size
* PARAMETERS
*  img_data : [IN] image data buffer pointer
*  img_len : [IN] image length
* width : [IN] image new width
* height : [IN] image new height
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_graphic_load_image_resized(VMUINT8 *img_data, VMINT img_len,VMINT width,VMINT height);


/******************************************************************************
* FUNCTION
*  vm_graphic_load_image_resized_cf
* DESCRIPTION
* resize image to appointed size
* PARAMETERS
*  cf : [IN] color format
*  img_data : [IN] image data buffer pointer
*  img_len : [IN] image length
* width : [IN] image new width
* height : [IN] image new height
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VMINT vm_graphic_load_image_resized_cf(vm_graphic_color_famat cf, VMUINT8 *img_data, VMINT img_len,VMINT width,VMINT height);


/******************************************************************************
* FUNCTION
*  vm_graphic_load_gif_resized_by_percent
* DESCRIPTION
* enlarge gif image
* PARAMETERS
*  img_data : [IN] image data buffer pointer
*  img_len : [IN] image length
* percent	 : [IN] the percent of enlarge
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VMINT vm_graphic_load_gif_resized_by_percent(VMUINT8 *img_data, VMINT img_len,VMINT percent);

/******************************************************************************
* FUNCTION
*  vm_graphic_load_gif_resized_by_percent_cf
* DESCRIPTION
* enlarge gif image
* PARAMETERS
*  cf : [IN] color format
*  img_data : [IN] image data buffer pointer
*  img_len : [IN] image length
* percent	 : [IN] the percent of enlarge
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VMINT vm_graphic_load_gif_resized_by_percent_cf(vm_graphic_color_famat cf, VMUINT8 *img_data, VMINT img_len,VMINT percent);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_load_gif_frame
 * DESCRIPTION
 *  gif image decode, and draw the decoded image frame (from start_frame_index to end_frame_index) to the new-created canvas.
 * PARAMETERS
 *  img : [IN] pointer of source image data
 *  img_len : [IN] image length
 *  start_frame_index : [IN] the first frame of the gif image to be decoded
 *  end_frame_index : [IN] the last frame of the gif image to be decoded
 * RETURNS
 *  the pointer of the canvas's display buffer
 *****************************************************************************/
VMINT vm_graphic_load_gif_frame(VMUINT8 *img_data, VMINT img_len, VMINT start_frame_index, VMINT end_frame_index);

/******************************************************************************
 * FUNCTION
 *  vm_graphic_load_gif_frame_cf
 * DESCRIPTION
 *  gif image decode, and draw the decoded image frame (from start_frame_index to end_frame_index) to the new-created canvas.
 * PARAMETERS
 *  cf : [IN] color format
 *  img : [IN] pointer of source image data
 *  img_len : [IN] image length
 *  start_frame_index : [IN] the first frame of the gif image to be decoded
 *  end_frame_index : [IN] the last frame of the gif image to be decoded
 * RETURNS
 *  the pointer of the canvas's display buffer
 *****************************************************************************/
VMINT vm_graphic_load_gif_frame_cf(vm_graphic_color_famat cf, VMUINT8 *img_data, VMINT img_len, VMINT start_frame_index, VMINT end_frame_index);

/******************************************************************************
* FUNCTION
*  vm_graphic_load_gif_frame_resized
* DESCRIPTION
* resize image to appointed size
* PARAMETERS
*  img_data : [IN] image data buffer pointer
*  img_len : [IN] image length
*  width : [IN] image new width
*  height : [IN] image new height
*  start_frame_index : [IN] the first frame of the gif image to be decoded
*  end_frame_index : [IN] the last frame of the gif image to be decoded
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VMINT vm_graphic_load_gif_frame_resized(VMUINT8 *img_data, VMINT img_len,VMINT width,VMINT height, VMINT start_frame_index, VMINT end_frame_index);

/******************************************************************************
* FUNCTION
*  vm_graphic_load_gif_frame_resized_cf
* DESCRIPTION
* resize image to appointed size
* PARAMETERS
*  cf : [IN] color format
*  img_data : [IN] image data buffer pointer
*  img_len : [IN] image length
*  width : [IN] image new width
*  height : [IN] image new height
*  start_frame_index : [IN] the first frame of the gif image to be decoded
*  end_frame_index : [IN] the last frame of the gif image to be decoded
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VMINT vm_graphic_load_gif_frame_resized_cf(vm_graphic_color_famat cf, VMUINT8 *img_data, VMINT img_len,VMINT width,VMINT height, VMINT start_frame_index, VMINT end_frame_index);

/******************************************************************************
* FUNCTION
*  vm_graphic_load_gif_frame_resized_by_percent
* DESCRIPTION
* enlarge gif image
* PARAMETERS
*  img_data : [IN] image data buffer pointer
*  img_len : [IN] image length
*  percent	 : [IN] the percent of enlarge
*  start_frame_index : [IN] the first frame of the gif image to be decoded
*  end_frame_index : [IN] the last frame of the gif image to be decoded
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VMINT vm_graphic_load_gif_frame_resized_by_percent(VMUINT8 *img_data, VMINT img_len,VMINT percent, VMINT start_frame_index, VMINT end_frame_index);

/******************************************************************************
* FUNCTION
*  vm_graphic_load_gif_frame_resized_by_percent_cf
* DESCRIPTION
* enlarge gif image
* PARAMETERS
*  cf : [IN] color format
*  img_data : [IN] image data buffer pointer
*  img_len : [IN] image length
*  percent	 : [IN] the percent of enlarge
*  start_frame_index : [IN] the first frame of the gif image to be decoded
*  end_frame_index : [IN] the last frame of the gif image to be decoded
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VMINT vm_graphic_load_gif_frame_resized_by_percent_cf(vm_graphic_color_famat cf, VMUINT8 *img_data, VMINT img_len,VMINT percent, VMINT start_frame_index, VMINT end_frame_index);


/******************************************************************************
* FUNCTION
*  vm_graphic_get_blt_layer_count
* DESCRIPTION
* get the MAX layer count that can be drawn
* PARAMETERS
* void
* RETURNS
*  MAX layer count that can be drawn
*****************************************************************************/
VMINT vm_graphic_get_blt_layer_count(void);




/******************************************************************************
* FUNCTION
*  vm_font_set_font_size
* DESCRIPTION
* set font size. Recommended that use font_size_t type to define size. if use number directly, the UI may be diffrent from dot character with vector font
* PARAMETERS
* size : [IN] font size
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_font_set_font_size(VMINT size);


/******************************************************************************
* FUNCTION
*  vm_font_set_font_style
* DESCRIPTION
* set font style . valid only to vector font
* PARAMETERS
* bold : [IN]wether to bold, value:TRUE or FALSE
* italic : [IN]wether to italic, value:TRUE or FALSE
* underline: wether to underline, value:TRUE or FALSE
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_font_set_font_style(VMINT bold,VMINT italic,VMINT underline);



/******************************************************************************
* FUNCTION
*  vm_graphic_textout_to_layer
* DESCRIPTION
* draw text on the layer
* PARAMETERS
* handle: layer handle
* x : [IN]x offset of start position
* y : [IN]y offset of start position
* s : [IN]string pointer
* length : [IN]string length
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_graphic_textout_to_layer (VMINT handle, VMINT x, VMINT y, VMWSTR s, VMINT length);

/******************************************************************************
* FUNCTION
*  vm_graphic_get_string_baseline
* DESCRIPTION
* get the baseline of the string
* PARAMETERS
* string : [IN] string pointer
* RETURNS
*  baseline of the string
*****************************************************************************/
VMINT vm_graphic_get_string_baseline(VMWSTR string);


/******************************************************************************
* FUNCTION
*  vm_graphic_textout_to_layer_by_baseline
* DESCRIPTION
* show the string to the layer according baseline
* PARAMETERS
* handle: layer handle
* x : [IN]x offset of start position
* y : [IN]y offset of start position
* s : [IN] string pointer
* length: [IN] the length of the string
* baseline: [IN]the baseline of the string
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_graphic_textout_to_layer_by_baseline (VMINT handle, VMINT x, VMINT y, VMWSTR s, VMINT length,VMINT baseline);

/******************************************************************************
* FUNCTION
*  vm_graphic_canvas_set_trans_color
* DESCRIPTION
* set canvas transparent color . when use vm_graphic_blt_ex, the color will take effect
* PARAMETERS
* hcanvas : [IN] canvas handle
* trans_color : [IN]transparent color value, -1 means no transparent color
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_graphic_canvas_set_trans_color(VMINT hcanvas, VMINT trans_color);

/******************************************************************************
* FUNCTION
*  vm_graphic_canvas_set_trans_color_argb
* DESCRIPTION
* set canvas transparent color . when use vm_graphic_blt_ex, the color will take effect
* PARAMETERS
* hcanvas : [IN] canvas handle
* trans_color : [IN]transparent color value, NULL means no transparent color, the color value include a, r, g, b value
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_graphic_canvas_set_trans_color_argb(VMINT hcanvas, vm_graphic_color_argb* trans_color);



/******************************************************************************
* FUNCTION
*  vm_graphic_layer_set_trans_color
* DESCRIPTION
* set layer transparent color . 
* PARAMETERS
* hhandle : [IN]layer handle
* trans_color : [IN] transparent color value, -1 means no transparent color
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_graphic_layer_set_trans_color(VMINT hhandle, VMINT trans_color);

/******************************************************************************
* FUNCTION
*  vm_graphic_layer_set_trans_color_argb
* DESCRIPTION
* set layer transparent color . 
* PARAMETERS
* hhandle : [IN]layer handle
* trans_color : [IN] transparent color value, NULL means no transparent color, the color value include a, r, g, b value
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return error code
*****************************************************************************/
VM_GDI_RESULT vm_graphic_layer_set_trans_color_argb(VMINT hhandle, vm_graphic_color_argb* trans_color);


/******************************************************************************
* FUNCTION
*  vm_graphic_is_use_vector_font
* DESCRIPTION
* query current platform whether support vector font . 
* PARAMETERS
* void
* RETURNS
*  if support, return TRUE, otherwise, return FALSE
*****************************************************************************/
VMINT vm_graphic_is_use_vector_font(void);

/******************************************************************************
* FUNCTION
*  vm_graphic_draw_abm_text
* DESCRIPTION
* draw bitmap font according to bitmap array. 
* PARAMETERS
* handle : [IN] layer handle
* x : [IN] x position of the to be drawn string
* y : [IN] y position of the to be drawn string
* color : [IN]the color of font
* font_data : [IN] font array info
* font_width : [IN] character width
* font_height : [IN] character height
* RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return others
*****************************************************************************/
VM_GDI_RESULT vm_graphic_draw_abm_text(VMINT handle, VMINT x, VMINT y, VMINT color,VMUINT8* font_data,VMINT font_width,VMINT font_height);


/******************************************************************************
* FUNCTION
*  vm_graphic_show_theme_background
* DESCRIPTION
* show theme background. 
* PARAMETERS
* void
* RETURNS
* void
*****************************************************************************/
void vm_graphic_show_theme_background(void);


/******************************************************************************
* FUNCTION
*  vm_graphic_show_left_softkey
* DESCRIPTION
* show left softkey. 
* PARAMETERS
* void
* RETURNS
* void
*****************************************************************************/
void vm_graphic_show_left_softkey(void);


/******************************************************************************
* FUNCTION
*  vm_graphic_show_right_softkey
* DESCRIPTION
* show right softkey. 
* PARAMETERS
* void
* RETURNS
* void
*****************************************************************************/
void vm_graphic_show_right_softkey(void);


//========================================================================

/******************************************************************************
* FUNCTION
*  vm_graphic_is_r2l_state
* DESCRIPTION
* 
* PARAMETERS

* RETURNS
*  if yes, return 1, otherwise, return 0
*****************************************************************************/
VMINT vm_graphic_is_r2l_state(void);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_char_num_in_width
 * DESCRIPTION
 *  To get char number in specified width and gap
 *  This function only work for non-complicated langauge.
 *  It means that the language process is not processed in the function.
 * PARAMETERS
 *  String : [IN]        The string content
 *  width : [IN]        The specifed width to display the string.
 *  checklinebreak : [IN]        To check line break or not.
 *  gap                 [IN]        The gap between each character
 * RETURNS
 *  The number of character could be displayed in the specified width.
 *****************************************************************************/
VMUINT vm_graphic_get_char_num_in_width(VMWCHAR* string, VMUINT width, VMINT  checklinebreak, VMUINT gap);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_char_num_in_width_ex
 * DESCRIPTION
 *  To get char number in specified width and gap
 *  This function only work for non-complicated langauge.
 *  It means that the language process is not processed in the function.
 * PARAMETERS
 *  String : [IN]        The string content
 *  width : [IN]        The specifed width to display the string.
 *  checklinebreak : [IN]        To check line break or not.
 *  gap                 [IN]        The gap between each character
 * RETURNS
 *  The number of character could be displayed in the specified width.
 *****************************************************************************/
VMUINT vm_graphic_get_char_num_in_width_ex(VMWCHAR* string, VMUINT width, VMINT  checklinebreak, VMUINT gap);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_draw_gif_image_from_memory
 * DESCRIPTION
 * PARAMETERS
 *  dest_layer_handle   [IN] layer handle
 *  x : [IN] x offset of start position
 *  y : [IN] y offset of start position
 *  img_data : [IN] data pointer
 *  img_len : [IN] length of image data
 *  frameIdx : [IN] frame id
 * RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return others
 *****************************************************************************/
VMINT vm_graphic_draw_gif_image_from_memory(VM_GDI_HANDLE dest_layer_handle,VMINT x,VMINT y,VMUINT8* img_data,VMINT img_len, VMINT frameIdx);

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_draw_image_from_memory
 * DESCRIPTION
 * PARAMETERS
 *  dest_layer_handle   [IN] layer handle
 *  x : [IN] x offset of start position
 *  y : [IN] y offset of start position
 *  img_data : [IN] data pointer
 *  img_len : [IN] length of image data
 * RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return others
 *****************************************************************************/
VMINT vm_graphic_draw_image_from_memory(VM_GDI_HANDLE dest_layer_handle,VMINT x,VMINT y,VMUINT8* img_data,VMINT img_len);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_set_alpha_blending_layer
 * DESCRIPTION
 * PARAMETERS
 *  layer_handle   [IN] layer handle, pass -1 means restore alpha blending layer
 * RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return others
 *****************************************************************************/

VMINT  vm_graphic_set_alpha_blending_layer(VMINT layer_handle);


/*****************************************************************************
 * FUNCTION
 *  vm_get_string_width_height_ex
 * DESCRIPTION
 * PARAMETERS
 *  string   [IN] string pointer
 *  gap : [IN] gap between characters
 *  n : [IN] string length
 *  pWidth : [OUT] width
 *  pHeight : [OUT] height
 *  max_width : [IN] the width for the string
 *  checkLineBreak : [IN] check line break or not
 *  checkCompleteWord : [IN] check complete word or not
 * RETURNS
*  how many character can draw in given width
 *****************************************************************************/

VMUINT vm_get_string_width_height_ex(
        VMWCHAR* string,
        VMINT gap,
        VMINT n,
        VMINT *pWidth,
        VMINT *pHeight,
        VMINT max_width,
        VMUINT8 checkLineBreak,
        VMUINT8 checkCompleteWord);

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_show_truncated_text
 * DESCRIPTION
 * PARAMETERS
 *  dest_layer_handle   [IN] layer handle
 *  x : [IN] offset x
 *  y : [IN] offset y
 *  xwidth : [IN] width for drawing string
 *  st : [IN] string to show
 *  truncated_symbol : [IN] truncated symbol, for example,"..."
 *  bordered : [IN] border or not
 *  color : [IN] color
 * RETURNS
*  Error Message
 *****************************************************************************/


vm_font_engine_error_message_enum vm_graphic_show_truncated_text(VM_GDI_HANDLE dest_layer_handle,
                                    VMINT x,
                                    VMINT y,
                                    VMINT xwidth,
                                    VMWCHAR *st,
                                    VMWCHAR *truncated_symbol,
                                    VMINT bordered,
                                    VMUINT16 color);

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_draw_resized_image_from_memory
 * DESCRIPTION
 * PARAMETERS
 *  dest_layer_handle   [IN] layer handle
 *  x : [IN] x offset of start position
 *  y : [IN] y offset of start position
 *  resized_width : [IN] resized width
 *  resized_height : [IN] resized height
 *  img_data : [IN] data pointer
 *  img_len : [IN] length of image data
 * RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return others
 *****************************************************************************/

VMINT vm_graphic_draw_resized_image_from_memory(VM_GDI_HANDLE dest_layer_handle,VMINT x,VMINT y,VMINT resized_width,VMINT resized_height,VMUINT8* img_data,VMINT img_len);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_draw_resized_gif_image_from_memory
 * DESCRIPTION
 * PARAMETERS
 *  dest_layer_handle   [IN] layer handle
 *  x : [IN] x offset of start position
 *  y : [IN] y offset of start position
 *  resized_width : [IN] resized width
 *  resized_height : [IN] resized height
 *  img_data : [IN] data pointer
 *  img_len : [IN] length of image data
 *  frameIdx : [IN] frame id
 * RETURNS
*  if succeed, return VM_GDI_SUCCEED, otherwise, return others
 *****************************************************************************/

VMINT vm_graphic_draw_resized_gif_image_from_memory(VM_GDI_HANDLE dest_layer_handle,VMINT x,VMINT y,VMINT resized_width,VMINT resized_height,VMUINT8* img_data,VMINT img_len, VMINT frameIdx);

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_set_blt_layer
 * DESCRIPTION
 * PARAMETERS
 *  layer_handles : [IN] the pointer of layer array 
 *  count	: [IN] layer number that  to be flushed. 
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED. otherwise, return error code
 *****************************************************************************/ 

VMINT vm_graphic_set_blt_layer(VMINT* layer_handles, VMINT count);

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_blt_layer
 * DESCRIPTION
 * PARAMETERS
 *  count	: [OUT] layer number that  to be flushed. 
 * RETURNS
 *  layer handles array pointer
 *****************************************************************************/ 

VMINT* vm_graphic_get_blt_layer( VMINT* count);

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_img_property_ex
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *  error code
 *****************************************************************************/ 
VM_GDI_RESULT vm_graphic_get_img_property_ex(VMUINT8 *img_data, VMINT img_len,vm_graphic_imgprop * img_prop);

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_img_property_from_file
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *  error code
 *****************************************************************************/ 
VM_GDI_RESULT vm_graphic_get_img_property_from_file(const VMWSTR filename, vm_graphic_imgprop * img_prop);
	

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_character_height_ex
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *  the character height
 *****************************************************************************/ 

VMINT vm_graphic_get_character_height_ex(VMUWCHAR c);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_highest_char_height_of_all_language
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *  the highest character height of all language
 *****************************************************************************/ 
VMINT vm_graphic_get_highest_char_height_of_all_language(void);

/*****************************************************************************
 * FUNCTION
 *  vm_frm_screen_rotate
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/ 
void vm_frm_screen_rotate(vm_frm_screen_rotate_enum rotation);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_char_height_alllang
 * DESCRIPTION
 * Get maximum char height regardless of language for the font size 
 * PARAMETERS
 *  size   [IN] font size
 * RETURNS
 *  return char height
 *****************************************************************************/
VMINT vm_graphic_get_char_height_alllang(VMINT size);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_draw_image_from_file
 * DESCRIPTION
 * PARAMETERS
 *  dest_layer_handle   [IN] layer handle
 *  x : [IN] x offset of start position
 *  y : [IN] y offset of start position
 *  filename : [IN] file name
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED, otherwise, return others
 *****************************************************************************/
VMINT vm_graphic_draw_image_from_file(VM_GDI_HANDLE dest_layer_handle, VMINT x, VMINT y, const VMWSTR filename);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_draw_resized_image_from_file
 * DESCRIPTION
 * PARAMETERS
 *  dest_layer_handle   [IN] layer handle
 *  x : [IN] x offset of start position
 *  y : [IN] y offset of start position
 *  resized_width : [IN] resized width
 *  resized_height : [IN] resized height
 *  filename : [IN] file name
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED, otherwise, return others
 *****************************************************************************/
VMINT vm_graphic_draw_resized_image_from_file(VM_GDI_HANDLE dest_layer_handle, VMINT x, VMINT y, VMINT resized_width, VMINT resized_height, const VMWSTR filename);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_flush_layer_ex
 * DESCRIPTION
 *  flatten layers to one layer and blt to LCD for some region. 
 * PARAMETERS
 *  layer_handles : [IN] the pointer of layer array 
 *  count	: [IN] layer number that  to be flushed. if the number is larger than max layer count (get by vm_graphic_get_blt_layer_count()), 
 *                 		just use the max layer count
 *  x1 : [IN] x offset of top left position
 *  y1 : [IN] y offset of top left position
 *  x2 : [IN] x offset of bottom right position
 *  y2 : [IN] y offset of bottom right position
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED. otherwise, return error code
 *****************************************************************************/ 
VMINT vm_graphic_flush_layer_ex(VMINT* layer_handles, VMINT count, VMINT x1, VMINT y1, VMINT x2, VMINT y2);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_flush_layer_non_block_ex
 * DESCRIPTION
 *  flatten layers to one layer and blt to LCD for some region with non-blocking way. 
 * PARAMETERS
 *  layer_handles : [IN] the pointer of layer array 
 *  count	: [IN] layer number that  to be flushed. if the number is larger than max layer count (get by vm_graphic_get_blt_layer_count()), 
 *                 		just use the max layer count
 *  x1 : [IN] x offset of top left position
 *  y1 : [IN] y offset of top left position
 *  x2 : [IN] x offset of bottom right position
 *  y2 : [IN] y offset of bottom right position
 * RETURNS
 *  if succeed, return VM_GDI_SUCCEED. otherwise, return error code
 *****************************************************************************/ 
VMINT vm_graphic_flush_layer_non_block_ex(VMINT* layer_handles, VMINT count, VMINT x1, VMINT y1, VMINT x2, VMINT y2);



/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_char_baseline_alllang
 * DESCRIPTION
 * Get maximum char baseline regardless of language for the font size 
 * PARAMETERS
 *  size   [IN] font size
 * RETURNS
 *  return char baseline
 *****************************************************************************/
VMINT vm_graphic_get_char_baseline_alllang(VMINT size);


/*****************************************************************************
 * FUNCTION
 *  vm_graphic_get_layer_buffer_size
 * DESCRIPTION
 * Get buffer size of the layer 
 * PARAMETERS
 *  handle   [IN] layer handle
 * RETURNS
 *  return laeyr buffer size 
 *****************************************************************************/
VMINT vm_graphic_get_layer_buffer_size(VMINT handle); 

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_is_dynamic_switch_cacheable_region
 * DESCRIPTION
 * query whether the memory is dynamic switch cacheable 
 * PARAMETERS
 *  vaddr   [IN] the memory start address
 *  len     [IN] the memory size
 * RETURNS
 *  If the can dynamic switch cacheable, return 1; otherwise, return 0
 *****************************************************************************/
VMINT vm_graphic_is_dynamic_switch_cacheable_region(void * vaddr, VMUINT len);

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_dynamic_switch_cacheable_region
 * DESCRIPTION
 * dynamic switch the memory cacheable attribute 
 * PARAMETERS
 *  vaddr   [IN] the pointer to the memory start address, the memory start address will be changed after switch
 *  len     [IN] the memory size
 *  cacheable [IN] the cacheable attribute. If it is VM_NON_CACHEABLE, switch the memory from cache to non cache; if it is VM_CACHEABLE, switch the memory from non cache to cache
 * NOTE
 *  1. The memory must be dynamic switch cacheable, otherwise ASSERT
 *  2. Only the whole base layer or fast layer buffer can be dynamic switch cacheable
 * RETURNS
 *  Always return 1; if something abnormal, ASSERT directly
 *****************************************************************************/
VMINT vm_graphic_dynamic_switch_cacheable_region(void **vaddr, VMUINT len, VMUINT cacheable);

/*****************************************************************************
 * FUNCTION
 *  vm_graphic_2d_linear_transform
 * DESCRIPTION
 *  hw linear transform.
 * PARAMETERS
 *  src_handle            : [IN]     layer to resize
 *  sx                    : [IN]     x of left-top cornor of resize region
 *  sy                    : [IN]     y of left-top cornor of resize region
 *  sw                    : [IN]     width of resize region
 *  sh                    : [IN]     height of resize region
 *  dx                    : [IN]     x of left-top cornor of output region
 *  dy                    : [IN]     y of left-top cornor of output region
 *  dw                    : [IN]     width of output region
 *  dh                    : [IN]     height of output region
 * RETURNS
 *  void
 *****************************************************************************/
VM_GDI_RESULT vm_graphic_2d_linear_transform(VMINT src_handle, VMINT sx,VMINT sy,VMINT sw,VMINT sh,VMINT dx,VMINT dy,VMINT dw,VMINT dh);

/*****************************************************************************
 * FUNCTION 
 *  vm_graphic_2d_linear_transform_rotate
 * DESCRIPTION
 *  rotate the layer by linear transform.
 * PARAMETERS
 *  src_handle            : [IN]     layer to resize
 *  theta                    : [IN]     rotate angle
 *  sx                    : [IN]     x of left-top cornor of resize region
 *  sy                    : [IN]     y of left-top cornor of resize region
 *  sw                    : [IN]     width of resize region
 *  sh                    : [IN]     height of resize region
 *  dx                    : [IN]     x of left-top cornor of output region
 *  dy                    : [IN]     y of left-top cornor of output region
 *  dw                    : [IN]     width of output region
 *  dh                    : [IN]     height of output region
 * RETURNS
 *  void
 *****************************************************************************/
VM_GDI_RESULT vm_graphic_2d_linear_transform_rotate(VMINT src_handle, VMFLOAT theta, VMINT sx,VMINT sy,VMINT sw,VMINT sh,VMINT dx,VMINT dy,VMINT dw,VMINT dh);

/*****************************************************************************
 * FUNCTION 
 *  vm_graphic_2d_linear_transform_matrix
 * DESCRIPTION
 *  linear transform.
 * PARAMETERS
 *  src_handle            : [IN]     layer to resize
 *  trfmatrix             : [IN]     transform matrix
 *  sx                    : [IN]     x of left-top cornor of resize region
 *  sy                    : [IN]     y of left-top cornor of resize region
 *  sw                    : [IN]     width of resize region
 *  sh                    : [IN]     height of resize region
 *  dx                    : [IN]     x of left-top cornor of output region
 *  dy                    : [IN]     y of left-top cornor of output region
 *  dw                    : [IN]     width of output region
 *  dh                    : [IN]     height of output region
 * RETURNS
 *  void
 *****************************************************************************/
VM_GDI_RESULT vm_graphic_2d_linear_transform_matrix(VMINT src_handle, VMFLOAT *trfmatrix, VMINT sx,VMINT sy,VMINT sw,VMINT sh,VMINT dx,VMINT dy,VMINT dw,VMINT dh);

#ifdef __cplusplus
}
#endif

#endif
