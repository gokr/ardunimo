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
#ifndef VMSTATUSBAR_SDK_H
#define VMSTATUSBAR_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"
#include "vmpromng.h"

#ifndef MAX_APP_NAME_LEN
#define MAX_APP_NAME_LEN					(260)
#endif

/*****************************************************************************
* FUNCTION
 *    vm_pmng_apply_to_run_in_fg
 * DESCRIPTION
 *  apply to foreground running for background running application by specified mode.
 * PARAMETERS
 *  notify_type : [IN]  notification mode, refer to VM_FG_NOTIFY_TYPE
 * EXAMPLE                                   [this TAG is optional]
  * <code>
  * vm_pmng_apply_to_run_in_fg(VM_NOTIFY_TYPE_SOUND);    //by sound mode
  * </code>
 *  
*****************************************************************************/
VMINT vm_pmng_apply_to_run_in_fg(VMINT notify_type);

/* DOM-NOT_FOR_SDK-BEGIN */
void vm_graphic_status_icon_bar_hide_callback(void);
void vm_graphic_show_status_icon_bar(void);
void vm_graphic_reset_status_icon_bar(void);

typedef struct mmi_mre_data
{
    VMUWSTR  	subText;    
    VMUWSTR	timeText;   
    VMUSTR 	imageBuffer;    
}mmi_mre_data;

typedef enum mmi_mre_image_type
{
	MRE_IMAGE_TYPE_INVALID = 0,
	MRE_IMAGE_TYPE_BMP = 1,
	MRE_IMAGE_TYPE_GIF = 3,
	MRE_IMAGE_TYPE_JPG = 9,
	MRE_IMAGE_TYPE_PNG = 19,
}mmi_mre_image_type;


typedef struct vm_status_bar_icon_t
{
        VMINT 			                   icon_id; 				                      /**< ICON ID */
        VMINT		                   pHandle;				                    /**< ICON Handle */
        VMINT                          b_used;
        VMWCHAR                        fullFilename[MAX_APP_NAME_LEN + 1];		/**< full file name of bg running app */	
        VMUSTR                         image_buffer_show;                     /**< ICON Show Image */
        VMUSTR                         image_buffer_blink;                    /**< ICON BlinkImage */
        mmi_mre_data*                  ncenter_cell_buf;
        struct vm_status_bar_icon_t*   pNext; 		                            /**< next icon */
}vm_status_bar_icon_t;
/* DOM-NOT_FOR_SDK-END */

typedef enum 
{
    VM_ICON_SHOW=1 ,				    	    /**< icon image is show */
    VM_ICON_BLINK,					    	    /**< icon image is blink */
    VM_ICON_NCENTER_CELL,			        /**< icon image is notification-center cell */	    	
    VM_ICON_HIDE					    	      /**< icon image is hide */
}VM_ICON_STATUS_TYPE;

typedef struct vm_status_bar_icon_image_info
{
    VMUINT8                 image_type;             /**< image type such as BMP|PNG|JPEG|GIF    */
    VMUINT                  image_frame_num;        /**< how many frame does Image have         */
    VMUINT                  image_size;		          /**< image size                             */
    VMUINT                  image_width;	    	    /**< image width                            */
    VMUINT                  image_height;	          /**< image height                           */
    VMUSTR                 image_data_buf;          /**< pointer to image data buf              */
}VM_ICON_STATUS_ICON_IMAGE_INFO;

typedef struct vm_status_bar_new_message_info
{
    VMUWSTR                  us_subText;               /**< sub text        */
    VMUWSTR                  us_timeText;              /**< time text       */
    VMINT                       subText_lenth;         /**< sub text lenth  */
    VMINT                       timeText_lenth;        /**< time text lenth */
    VM_ICON_STATUS_ICON_IMAGE_INFO* 	 uc_imageBuffer; /**< image data buf  */
}VM_NEW_MESSAGE_INFO;

/*****************************************************************************
* FUNCTION
 *    vm_graphic_show_status_icon_bar
 * DESCRIPTION
 *  normally MRE application is full screen ,this api will show status bar in
 *  application's screen
 * PARAMETERS
 *  NULL
 * EXAMPLE                                   [this TAG is optional]
  * <code>
  * vm_statusbar_new_message(&new_message);
  * </code>
 *  
*****************************************************************************/
void vm_graphic_show_status_icon_bar(void);

/*****************************************************************************
* FUNCTION
 *    vm_graphic_reset_status_icon_bar
 * DESCRIPTION
 *  after called vm_graphic_show_status_icon_bar(),status bar will be shown.
 *  vm_graphic_reset_status_icon_bar() will hide status bar again.
 * PARAMETERS
 *  NULL
 * EXAMPLE                                   [this TAG is optional]
  * <code>
  * vm_statusbar_new_message(&new_message);
  * </code>
 *  
*****************************************************************************/
void vm_graphic_reset_status_icon_bar(void);

/*****************************************************************************
* FUNCTION
 *    vm_statusbar_new_message
 * DESCRIPTION
 *  notify statusbar has a new message coming,detail will be in paramater of 
 *  new_message_info.
 * PARAMETERS
 *  new_message_info : [IN]  new message content
 * EXAMPLE                                   [this TAG is optional]
  * <code>
  * VM_NEW_MESSAGE_INFO new_message;
  *	new_message.us_subText     = XXXX;
  * new_message.us_timeText    = XXXX;
  * new_message.subText_lenth  = XXXX;
  * new_message.timeText_lenth = XXXX;
  * new_message.uc_imageBuffer = XXXX;
  * vm_statusbar_new_message(&new_message);
  * </code>
 *  
*****************************************************************************/
VMINT vm_statusbar_new_message(VM_NEW_MESSAGE_INFO* new_message_info);

/*****************************************************************************
* FUNCTION
 *    vm_statusbar_set_image
 * DESCRIPTION
 *  set image of statusbar.
 * PARAMETERS
 *  Status_type : [IN]  notification mode, refer to VM_ICON_STATUS_TYPE
 *   VM_ICON_SHOW				    	          // icon image will be show 
 *   VM_ICON_BLINK					    	      // icon image will be blink
 *   VM_ICON_NCENTER_CELL			          // icon image will be show on N-center cell
 *   VM_ICON_HIDE					    	        // icon image will be hide
 *	image_info : [IN]  information of image.  
 *   image_type;		  // image type.
 *   image_frame_num;  // image frame number it should be 1,if it is a static image.
 *   image_size;       // size of image.
 *   image_width;      // width of image.
 *   image_height;     // height of image
 *   image_data_buf;   // image resource buffer.
 * EXAMPLE                                   [this TAG is optional]
  * <code>
  * VM_ICON_STATUS_ICON_IMAGE_INFO image_icon_info;
  * image_icon_info.image_type      = XXXX;
  * image_icon_info.image_frame_num = XXXX;
  * image_icon_info.image_size      = XXXX;
  * image_icon_info.image_width     = XXXX;
  * image_icon_info.image_height    = XXXX;
  * image_icon_info.image_data_buf  = XXXX;
  * vm_statusbar_set_image(VM_ICON_SHOW,&image_icon_info);
  * </code>
 *  
*****************************************************************************/
VMINT vm_statusbar_set_image(VM_ICON_STATUS_TYPE Status_type ,VM_ICON_STATUS_ICON_IMAGE_INFO*image_info);

/*****************************************************************************
* FUNCTION
 *    vm_statusbar_set_image_ex
 * DESCRIPTION
 *  set image of statusbar, and you can decide which notify type will be used.
 * PARAMETERS
 *  Status_type : [IN]  notification mode, refer to VM_ICON_STATUS_TYPE
 *   VM_ICON_SHOW				    	          // icon image will be show 
 *   VM_ICON_BLINK					    	      // icon image will be blink
 *   VM_ICON_NCENTER_CELL			          // icon image will be show on N-center cell
 *   VM_ICON_HIDE					    	        // icon image will be hide
 *	image_info : [IN]  information of image.  
 *   image_type;		  // image type.
 *   image_frame_num;  // image frame number it should be 1,if it is a static image.
 *   image_size;       // size of image.
 *   image_width;      // width of image.
 *   image_height;     // height of image
 *   image_data_buf;   // image resource buffer.
 *	notify_type : [IN]	type of notification.
 *		VM_NOTIFY_TYPE_DEFAULT      // by default mode (follow engine control)
 *		VM_NOTIFY_TYPE_SOUND		// by sound mode
 *		VM_NOTIFY_TYPE_VIBRATILITY	// by vibration mode
 * EXAMPLE                                   [this TAG is optional]
  * <code>
  * VM_ICON_STATUS_ICON_IMAGE_INFO image_icon_info;
  * image_icon_info.image_type      = XXXX;
  * image_icon_info.image_frame_num = XXXX;
  * image_icon_info.image_size      = XXXX;
  * image_icon_info.image_width     = XXXX;
  * image_icon_info.image_height    = XXXX;
  * image_icon_info.image_data_buf  = XXXX;
  * vm_statusbar_set_image(VM_ICON_SHOW,&image_icon_info,VM_NOTIFY_TYPE_DEFAULT);
  * </code>
 *  
*****************************************************************************/
VMINT vm_statusbar_set_image_ex(
			VM_ICON_STATUS_TYPE status_type,
			VM_ICON_STATUS_ICON_IMAGE_INFO *image_info,
			VMINT notify_type);

/******************************************************************************
 * FUNCTION
 *	vm_statusbar_get_height
 * DESCRIPTION
 *	get the height of statusbar.
 * PARAMETER
 *	void
 * RETURNS
 *	the height (in pixels) of statusbar.
 ******************************************************************************/
VMINT vm_statusbar_get_height(void);

#ifdef __cplusplus
}
#endif 

#endif /* VMSTATUSBAR_SDK_H */
