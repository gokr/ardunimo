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

#ifndef VMCAMERA_SDK_H_
#define VMCAMERA_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"
#include "vmgraph.h"

typedef VMINT VM_CAMERA_HANDLE;

/* camera id */
typedef enum 
{
	VM_CAMERA_MAIN_ID = 1,
	VM_CAMERA_MAIN_LOW_RESOURCE_ID
}VM_CAMERA_ID;

/* The maximum number of af zone */
#define VM_CAMERA_AF_ZONE_MAX_NO 5         

/* camera result */
typedef enum
{
	VM_CAM_PREVIEW_START_DONE = 1,		/* preview success */
	VM_CAM_PREVIEW_START_ABORT,			/* preview abort */
	VM_CAM_PREVIEW_STOP_DONE,			/* stop preview done */
	VM_CAM_PREVIEW_STOP_ABORT,			/* stop preview failed */
	VM_CAM_PREVIEW_FRAME_RECEIVED,		/* receive data */
	VM_CAM_CAPTURE_DONE,					/* capture success */
	VM_CAM_CAPTURE_ABORT				/* capture abort */
}VM_CAMERA_MESSAGE;

/* camera status */
typedef enum
{
	VM_CAM_READY_STATUS = 1,				/* create camera success status */
	VM_CAM_STARTING_PREVIEW_STATUS,	/* starting preview status */
	VM_CAM_STOPPING_PREVIEW_STATUS,	/* stopping preview status */
	VM_CAM_PREVIEW_STATUS,				/* preview status	*/
	VM_CAM_CAPTURING_STATUS				/* capturing status	*/
}VM_CAMERA_STATUS;


/* operation success */
#define VM_CAM_SUCCESS								(0)

/* no memory */
#define VM_CAM_ERR_NOMEMORY						(-1)

/* not support operation in this status */
#define VM_CAM_ERR_OPERATE_BAD_STATUS			(-2)

/* wrong parameters */
#define VM_CAM_ERR_BAD_PARAM						(-3)

/* invalid handle */
#define VM_CAM_ERR_INVALID_CAM_HANDLE			(-4)

/* linkit not support operation */
#define VM_CAM_ERR_UNSUPPORT_OPERATION			(-5)

/* instance has been created */
#define VM_CAM_ERR_CAM_INSTANCE_CREATED			(-6)

/* not register callback function */
#define VM_CAM_ERR_NOT_REGISTER_NOTIFY			(-7)

/* invalid camera id */
#define VM_CAM_ERR_INVALID_CAM_ID				(-8)

/* internal error */
#define VM_CAM_ERR_CAM_INTERNAL_ERROR			(-9)

/* not support camera feature */
#define VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE	(-10)

/* not support under background run */
#define VM_CAM_OPERATION_IN_PROCESS_STATUS		(-11)


#define VM_CAM_XENONFLASH_CHARGING            1001
#define VM_CAM_ERR_FAILED                     -1001
#define VM_CAM_ERR_DISK_FULL                  -1002
#define VM_CAM_ERR_WRITE_PROTECTION           -1003
#define VM_CAM_ERR_NO_DISK                    -1004
#define VM_CAM_ERR_HW_NOT_READY               -1005
#define VM_CAM_ERR_MEMORY_NOT_ENOUGH          -1006
#define VM_CAM_ERR_PREVIEW_FAILED             -1007
#define VM_CAM_ERR_CAPTURE_FAILED             -1008
#define VM_CAM_ERR_ROOT_DIR_FULL              -1009
#define VM_CAM_ERR_XENONFLASH_TIMEOUT         -1010
#define VM_CAM_ERR_XENONFLASH_LOW_BATTERY     -1011
#define VM_CAM_ERR_CBM_BEARER_ERROR           -1012
#define VM_CAM_ERR_SAVE_FAILED                -1013



#define VM_CAMERA_ROTATE_0    0
#define VM_CAMERA_ROTATE_90   1
#define VM_CAMERA_ROTATE_180  2
#define VM_CAMERA_ROTATE_270  3

typedef void (*vm_camera_rotate_callback)(VMUINT8 rotate);

/* pixel format */
typedef enum
{
	PIXTEL_RGB565 = 1,
	PIXTEL_BGR565,
	PIXTEL_RGB888,
	PIXTEL_BGR888,
	PIXTEL_ARGB8888,
	PIXTEL_ABGR8888,
	PIXTEL_UYUV422
}PIXTEL_FORMAT_T;

typedef enum
{
    VM_RAWDATA_RGB565 = 0,
    Vm_RAWDATA_YUV420
}ROW_DATA_FORMAT_T;


/* frame raw data */
typedef struct vm_cam_frame_raw_data_t
{
	VMUINT 				row_pixel;				/* pixels per row */
	VMUINT 				col_pixel;				/* pixels per column */
	ROW_DATA_FORMAT_T 	format;			        /* pixel format	*/
	void* 				buffer;			        /* buffer */
	VMINT				buffer_size;			/* buffer size */
}vm_cam_frame_raw_data_t;


/* frame data */
typedef struct vm_cam_frame_data_t
{
	VMUINT 				row_pixel;				/* pixels per row */
	VMUINT 				col_pixel;				/* pixels per column */
	PIXTEL_FORMAT_T 	pixtel_format;			/* pixel format	*/
	void* 				pixtel_data;				/* data */
	VMINT				reserved;				/* no use */
}vm_cam_frame_data_t;

/* capture data */
typedef struct vm_cam_capture_data_t
{
	VMCHAR 				mime_type[32];			/* data type */
	VMUINT8*			data;					/* data */
	VMUINT				data_size;				/* data size */
	VMINT				reserved;				/* no use */
}vm_cam_capture_data_t;

/* notify data */
typedef struct vm_cam_notify_data_t
{
	VM_CAMERA_HANDLE 		handle;					/* camera handle */
	VM_CAMERA_MESSAGE 	cam_message;			/* message type */
	VM_CAMERA_STATUS 		cam_status;				/* curent status */
}vm_cam_notify_data_t;

/* callback function */
typedef void (*VM_CAMERA_STATUS_NOTIFY)(const vm_cam_notify_data_t* notify_data, void* user_data);
/* camera size */
typedef struct vm_cam_size_t
{
	VMUINT width;
	VMUINT height;
}vm_cam_size_t;

/* camera size */
typedef struct vm_cam_origin_t
{
	VMUINT x;
	VMUINT y;
}vm_cam_origin_t;


/* AF zone structure */
typedef struct
{
	VMUINT af_zone_w;		/* Width */
	VMUINT af_zone_h;		/* Height */
	VMUINT af_zone_x;		/* Offset x */
	VMUINT af_zone_y;		/* Offset y */
}vm_camera_af_zone_struct;


/* AF window structure */
typedef struct
{
	VMUINT af_active_zone; 	/* Active zone */
	vm_camera_af_zone_struct af_zone[VM_CAMERA_AF_ZONE_MAX_NO];	/* AF zone array */
}vm_camera_af_window_struct;

/* The result of af */
typedef enum 
{
    VM_AF_SEARCH_STATUS_IDLE=0,                /* Idle */
    VM_AF_SEARCH_STATUS_BUSY,                  /* Busy */
    VM_AF_SEARCH_STATUS_FOUND_FAIL,            /* Failed */
    VM_AF_SEARCH_STATUS_FOUND_SUCCESS,         /* Success */
    VM_AF_SEARCH_STATUS_FOUND_NOFOCUS,         /* No focus */
    VM_AF_SEARCH_STATUS_SWITCH_MACRO           /* Switch to marco */   
}vm_af_result_enum;

/* af struct */
typedef struct
{
	vm_af_result_enum af_result;	/* AF result */
	VMUINT af_success_zone;			/* AF success zone */
}vm_camera_af_result_struct;

typedef void (*vm_camera_af_ind_callback) (vm_camera_af_result_struct result_ind, void* user_data);

/* camera parameter setting struct */
typedef struct
{
	unsigned int preview_x;       /* preview x */
 	unsigned int preview_y;       /* preview y */
 	unsigned int preview_width;   /* preview width */					
	unsigned int preview_height;  /* preview height */
	unsigned int preview_layer;   /* preview layer handle */						
	void* preview_layer_buffer;	  /* preview layer buffer */

	unsigned int osd_x;           /* osd x */
	unsigned int osd_y;           /* osd y */
	unsigned int osd_width;       /* osd width */					
	unsigned int osd_height;      /* osd height */	
	unsigned int osd_layer;	      /* osd ayer handle */						
	void* osd_layer_buffer;	      /* osd layer buffer */				

    VMUINT16 af_operation_mode;   /* af mode */
    VMUINT16 af_range;			  /* af range */			
}vm_camera_para_struct;

void vm_camera_sensor_driver_install(void* func_install1,void* func_install2);

/*****************************************************************************
 * FUNCTION
 *    vm_create_camera_instance
 * DESCRIPTION
 *  create camera instance and get the handle, you can use the handle to do other operation,
 *  if you don't need use this instance, please use vm_release_camera_instance to release it.
 * PARAMETERS
 *  camera_id : [IN] camera's id, you can refer the VM_CAMERA_ID.
 *  handle_ptr : [OUT] camera's handle. 
 * RETURNS
 *  create camera instance success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : create success.
 *  VM_CAM_ERR_NOMEMORY : there is no enough memory.
 *  VM_CAM_ERR_INVALID_CAM_ID : camera id is wrong.
 *  VM_CAM_ERR_CAM_INSTANCE_CREATED : camera instance is in use.
 *  VM_CAM_ERR_CAM_INTERNAL_ERROR : preview size is not support.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
 *  VM_CAM_OPERATION_IN_PROCESS_STATUS : after LINKIT, when application is in background status
 *                                        not allow to create camera.
 * EXAMPLE
 * <code>
 * VM_CAM_READY_STATUS      VM_CAM_STARTING_PREVIEW_STATUS      VM_CAM_PREVIEW_STATUS      VM_CAM_STOPPING_PREVIEW_STATUS      VM_CAM_CAPTURING_STATUS
 *			| vm_camera_preview_start		                                                                                     			
 *			------------------------------->								
 *											|VM_CAM_PREVIEW_START_DONE																				 
 *											-------------------------------->																
 *											|								|																
 *				VM_CAM_PREVIEW_START_ABORT	|								|																
 *			<--------------------------------								|vm_camera_preview_stop													 							 
 *			|																------------------------------->													 
 *			|																|	VM_CAM_PREVIEW_STOP_ABORT	|														 
 *			|																<-------------------------------													 
 *			|	 																							|								
 *			|																	VM_CAM_PREVIEW_STOP_DONE	|				 				
 *			<------------------------------------------------------------------------------------------------												 
 *			|								 								|								 			 					
 *			|																|vm_camera_capture											
 *			|								 								--------------------------------------------------------------->
 *			|																			 VM_CAM_CAPTURE_DONE/VM_CAM_CAPTURE_ABORT			|
 *			<-------------------------------------------------------------------------------------------------------------------------------
 *			|vm_camera_capture																												|
 *			------------------------------------------------------------------------------------------------------------------------------->
 *			|																			VM_CAM_CAPTURE_DONE/VM_CAM_CAPTURE_ABORT			|
 *			<-------------------------------------------------------------------------------------------------------------------------------
 * </code>
*****************************************************************************/
VMINT vm_create_camera_instance(VM_CAMERA_ID camera_id, 
	VM_CAMERA_HANDLE* handle_ptr);

/*****************************************************************************
 * FUNCTION
 *    vm_release_camera_instance
 * DESCRIPTION
 *  release camera instance, after vm_create_camera_instance, when application exit or not use camera, 
 *  please invole this function to release it.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 * RETURNS
 *  release camera instance success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : release success.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to release camera instance.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_release_camera_instance(VM_CAMERA_HANDLE handle);

/*****************************************************************************
 * FUNCTION
 *    vm_get_camera_status
 * DESCRIPTION
 *  get camera's current status.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  cam_status : [OUT] camera's status, please refer struct VM_CAMERA_STATUS. 
 * RETURNS
 *  get camera's success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get status success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_get_camera_status(VM_CAMERA_HANDLE handle, VM_CAMERA_STATUS* cam_status);





/*****************************************************************************
 * FUNCTION
 *    vm_camera_register_notify
 * DESCRIPTION
 *  register callback function, system will invoke this function when camera's status changes.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  notify_callback : [IN] application's callback function.
 *  user_data : [IN] user data use as parameter for callback function, if no need, set to NULL.
 * RETURNS
 *  register success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : register success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_register_notify(VM_CAMERA_HANDLE handle, VM_CAMERA_STATUS_NOTIFY notify_callback, void* user_data);





/*****************************************************************************
 * FUNCTION
 *    vm_camera_get_support_preview_size
 * DESCRIPTION
 *  get camera's support preview size.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  cam_size_list : [OUT] camera's support preview size list.
 *  list_size : [OUT] camera's support preview size list size. 
 * RETURNS
 *  get camera's success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get status success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_CAM_INTERNAL_ERROR : preview size is not support.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
 * EXAMPLE
 * <code>
 * void app_set_preview_size(void)
 * {
 *	vm_cam_size_t* ptr = NULL;
 *	VMUINT size = 0, i = 0;
 * 	if (vm_camera_get_support_preview_size(camera_handle, &ptr, &size) == VM_CAM_SUCCESS)
 *	{
 *		vm_cam_size_t my_cam_size;
 *		
 *		for (i = 0; i < size; i++)
 *		{
 *			my_cam_size.width  = (ptr + i)->width;
 *			my_cam_size.height =(ptr + i) ->height;
 *		}
 *		vm_camera_set_preview_size(camera_handle, &my_cam_size);
 *	}
 * }
 * </code>
*****************************************************************************/
VMINT vm_camera_get_support_preview_size(VM_CAMERA_HANDLE handle, const vm_cam_size_t** cam_size_list, VMUINT* list_size);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_set_preview_size
 * DESCRIPTION
 *  set camera's preview size.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  preview_size : [IN] preview size to set.
 * RETURNS
 *  set camera's preview size success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get status success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_CAM_INTERNAL_ERROR : preview size is not support.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to set camera's preview size.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_set_preview_size(VM_CAMERA_HANDLE handle, const vm_cam_size_t* preview_size);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_set_preview_fps
 * DESCRIPTION
 *  set camera's preview frame number per second, the max is 30, if not set the default is the max number.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  fps : [IN] frame number, the max is 30, if this is bigger than 30, it will change to 30.
 * RETURNS
 *  set preview frame number success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : set frame number success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_CAM_INTERNAL_ERROR : preview size is not support.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to set camera's preview size.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_set_preview_fps(VM_CAMERA_HANDLE handle, VMUINT fps);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_preview_start
 * DESCRIPTION
 *  start to preview.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 * RETURNS
 *  start preview success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : start preview success.
 *  VM_CAM_ERR_NOT_REGISTER_NOTIFY : not register callback function.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to start preview.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
 *  VM_CAM_OPERATION_IN_PROCESS_STATUS : after LINKIT SDK, when application is in background status
 *                                        not allow to create camera.
*****************************************************************************/
VMINT vm_camera_preview_start(VM_CAMERA_HANDLE handle);
 
/*****************************************************************************
 * FUNCTION
 *    vm_camera_preview_stop
 * DESCRIPTION
 *  stop preview.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 * RETURNS
 *  stop preview success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : stop preview success.
 *  VM_CAM_ERR_NOT_REGISTER_NOTIFY : not register callback function.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to set camera's preview size.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_preview_stop(VM_CAMERA_HANDLE handle);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_get_frame
 * DESCRIPTION
 *  get camera's one frame.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  frame_data : [OUT] the frame data. 
 * RETURNS
 *  get frame success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get status success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to get frame.
 *  VM_CAM_ERR_CAM_INTERNAL_ERROR : pixtel format is not support, now support BGR565,BGR888,ABGR8888.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
 * EXAMPLE
 * <code>
 * void cam_message_callback(vm_cam_notify_data_t* notify_data, void* user_data)
 * {
 * 	if (notify_data != NULL)
 *    {
 *		vm_cam_frame_data_t frame;
 *		
 *		switch (notify_data->cam_message)
 *		{
 *		case VM_CAM_PREVIEW_SOPT_DONE:
 *			// 
 *			break;
 *		case VM_CAM_PREVIEW_FRAME_RECEIVED:
 *			if (vm_camera_get_frame(cam_handle, &frame) == VM_CAM_SUCCESS)
 *			{

 *				VMUINT app_frame_data_size = 0;
 *				VMUINT8* app_frame_data = NULL;
 *				
 *				if (frame.pixtel_format == PIXTEL_RGB565 || frame.pixtel_format == PIXTEL_BGR565)
 *					app_frame_data_size = row_pixel * col_pixel * 2;
 *				else if (frame.pixtel_format == PIXTEL_RGB888 || frame.pixtel_format == PIXTEL_BGR888)
 *					app_frame_data_size = row_pixel * col_pixel * 3;
 *				else
 *					app_frame_data_size = row_pixel * col_pixel * 4;
 *
 *				if ((app_frame_data = vm_malloc(app_frame_data_size)) != NULL)
 *				{
 *					memcpy(app_frame_data, frame.pixtel_data, app_frame_data_size);
 *				}
 *				else
 *				{
 *					// if (frame.rgbformat == screen format)
 *					// {
 *					//     copy frame.pixtel_data to screen buffer;
 *					//     flush screen buffer;
 *					//  }
 *				}
 *				
 *			}
 *			break;
 *		case ......
 *    		}
 *	}
 * }
 * </code>
*****************************************************************************/
VMINT vm_camera_get_frame(VM_CAMERA_HANDLE handle, vm_cam_frame_data_t* frame_data);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_get_raw_data_frame
 * DESCRIPTION
 *  get raw dat use application's memory.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  frame_data : [IN] please refer vm_cam_frame_raw_data_t
 * RETURNS
 *  get raw data success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get raw data success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to set capture size.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
 *  VM_CAM_ERR_DISK_FULL            Disk full
 *  VM_CAM_ERR_WRITE_PROTECTION     Disk write protection
 *  VM_CAM_ERR_NO_DISK              No disk
 *  VM_CAM_ERR_CAPTURE_FAILED       Capture failed
*****************************************************************************/
VMINT vm_camera_get_raw_data_frame(VM_CAMERA_HANDLE handle, vm_cam_frame_raw_data_t* frame_data);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_get_support_capture_size
 * DESCRIPTION
 *  get camera's support capture size.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  cam_size_list : [OUT] camera's support capture size list.
 *  list_size : [OUT] camera's support capture size list size. 
 * RETURNS
 *  get camera's success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get status success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_CAM_INTERNAL_ERROR : capture size is not support.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
 * EXAMPLE
 * <code>
 * void app_set_capture_size(void)
 * {
 *	vm_cam_size_t* ptr = NULL;
 *	VMUINT size = 0, i = 0;
 * 	if (vm_camera_get_support_capture_size(camera_handle, &ptr, &size) == VM_CAM_SUCCESS)
 *	{
 *		vm_cam_size_t my_cam_size;
 *		
 *		for (i = 0; i < size; i++)
 *		{
 *			my_cam_size.width  = (ptr + i)->width;
 *			my_cam_size.height =(ptr + i) ->height;
 *		}
 *		vm_camera_set_capture_size(camera_handle, &my_cam_size);
 *	}
 * }
 * </code>
*****************************************************************************/
VMINT vm_camera_get_support_capture_size(VM_CAMERA_HANDLE handle, const vm_cam_size_t** cam_size_list, VMUINT* list_size);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_set_capture_size
 * DESCRIPTION
 *  set camera's capture size.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  size : [IN] capture size to set.
 * RETURNS
 *  set camera's capture size success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get max capture size success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to set capture size.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_set_capture_size(VM_CAMERA_HANDLE handle, const vm_cam_size_t* size);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_capture
 * DESCRIPTION
 *  capture a image.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 * RETURNS
 *  capture success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : capture a image success.
 *  VM_CAM_ERR_NOT_REGISTER_NOTIFY : not register callback function.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to capture a image.
 *  VM_CAM_ERR_NOMEMORY : there is no enough memory.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_capture(VM_CAMERA_HANDLE handle);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_get_capture_data
 * DESCRIPTION
 *  get capture data.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  capture_data : [OUT] capture data.
 * RETURNS
 *  get camera's capture data success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get capture data success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to get get data.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_get_capture_data(VM_CAMERA_HANDLE handle, vm_cam_capture_data_t* capture_data);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_get_focus_zone
 * DESCRIPTION
 *  get focuse zone.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  zone : [OUT] zone data.
 * RETURNS
 *  success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get capture data success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to get get data.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_get_focus_zone(VM_CAMERA_HANDLE handle, vm_camera_af_window_struct* zone);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_start_autofocus_process
 * DESCRIPTION
 *  start auto focuse process
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  af_callback : [IN] callback function.
 *  user_data : [IN] user data.
  * RETURNS
 *  success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get capture data success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to get get data.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_start_autofocus_process(VM_CAMERA_HANDLE handle, vm_camera_af_ind_callback af_callback, void* user_data);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_stop_autofocus_process
 * DESCRIPTION
 *  stop auto foucs process.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 * RETURNS
 * stop auto focus success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get capture data success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to get get data.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_stop_autofocus_process(VM_CAMERA_HANDLE handle);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_update_parameter
 * DESCRIPTION
 *  update parameter.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  para : [OUT] capture data.
 * RETURNS
 *  update parameter success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get capture data success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to get get data.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_update_parameter(VM_CAMERA_HANDLE handle, vm_camera_para_struct* para);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_get_default_parameter
 * DESCRIPTION
 *  get default parameter.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  para : [OUT] camera data.
 * RETURNS
 *  get parameter success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get capture data success.
 *  VM_CAM_ERR_BAD_PARAM : parameter is wrong.
 *  VM_CAM_ERR_INVALID_CAM_HANDLE : camera's handle is wrong.
 *  VM_CAM_ERR_OPERATE_BAD_STATUS : bad status to get get data.
 *  VM_CAM_ERR_UNSPPUORT_CAMERA_FEATURE : not support camera function.
*****************************************************************************/
VMINT vm_camera_get_default_parameter(VM_CAMERA_HANDLE handle, vm_camera_para_struct* para);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_get_osd_layer_buffer
 * DESCRIPTION
 *  get osd layer buffer.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  osd : [OUT] osd layer width and height.
 * RETURNS
 *  layer buffer pointer
 * RETURN VALUES
 *  NULL : error
*****************************************************************************/
void* vm_camera_get_osd_layer_buffer(VM_CAMERA_HANDLE handle, vm_cam_size_t* osd);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_get_osd_layer_handle
 * DESCRIPTION
 *  get osd layer handle.
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 * RETURNS
 *  handle id
 * RETURN VALUES
 *  0 : error
*****************************************************************************/
VMINT vm_camera_get_osd_layer_handle(VM_CAMERA_HANDLE handle);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_set_camera_id
 * DESCRIPTION
 *  get capture data.
 * PARAMETERS
 *  camera_id : [IN] please refer VM_CAMERA_ID
 * RETURNS
 *  set camera's id success or not.
 * RETURN VALUES
 *  VM_CAM_SUCCESS : get capture data success.
 *  other : error
*****************************************************************************/
VMINT vm_camera_set_camera_id(VMUINT16 camera_id);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_get_main_camera_id
 * DESCRIPTION
 *  get main camera id
 * PARAMETERS
 *  
 * RETURNS
 *  main camera id
 * RETURN VALUES
 *  -1 : error
*****************************************************************************/
VMINT vm_camera_get_main_camera_id(void);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_get_sub_camera_id
 * DESCRIPTION
 *  get sub camera id
 * PARAMETERS
 *  
 * RETURNS
 *  sub camera id
 * RETURN VALUES
 *  -1 : error
*****************************************************************************/
VMINT vm_camera_get_sub_camera_id(void);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_is_support_dual_camera
 * DESCRIPTION
 *  support dual camera or not
 * PARAMETERS
 *  
 * RETURNS
 *  
 * RETURN VALUES
 *  1 : support
 * 0: not support
*****************************************************************************/
VMINT vm_camera_is_support_dual_camera(void);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_register_rotation_callback
 * DESCRIPTION
 *  register ratate callback function
 * PARAMETERS
 *  callback
 * RETURNS
*****************************************************************************/
void vm_camera_register_rotation_callback(vm_camera_rotate_callback callback);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_set_capture_rotation
 * DESCRIPTION
 *  set capture rotation
 * PARAMETERS
 *  rotate
 * RETURNS
*****************************************************************************/
void vm_camera_set_capture_rotation(VMUINT8 rotate);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_update_para_image_size
 * DESCRIPTION
 *  update image size
 * PARAMETERS
 *  image_width: image width
 *  image_height: image height
 * RETURNS
*****************************************************************************/
void vm_camera_update_para_image_size(VMUINT16 image_width, VMUINT16 image_height);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_set_auto_detect_mode
 * DESCRIPTION
 *  set auto detect mode
 * PARAMETERS
 *  mode: TRUE or FALSE
 *  
 * RETURNS
*****************************************************************************/
void vm_camera_set_auto_detect_mode(VMBOOL mode);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_set_lcd_update
 * DESCRIPTION
 *  set lcd update or not
 * PARAMETERS
 *  update: TRUE or FALSE
 *  
 * RETURNS
*****************************************************************************/
void vm_camera_set_lcd_update(VMBOOL update);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_enable_osd_layer
 * DESCRIPTION
 *  use new layer as osd layer or not
 * PARAMETERS
 *  mode: TRUE or FALSE
 *  
 * RETURNS
*****************************************************************************/
void vm_camera_enable_osd_layer(VMBOOL enable);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_is_horizontal_sensor
 * DESCRIPTION
 * is horizontal sensor or not
 * PARAMETERS
 *  
 * RETURNS
 *  
 * RETURN VALUES
 *  1 : horizontal
 * 0: not horizontal
*****************************************************************************/
VMINT vm_camera_is_horizontal_sensor(void);


/*****************************************************************************
 * FUNCTION
 *  vm_camera_set_capture_disable_jaia
 * DESCRIPTION
 *  Enable/disable capture with JAIA 
 * PARAMETERS
 *  is_disable          : [IN]        enable[FALSE]/disable[TRUE]
 * RETURNS
 *  void
 *****************************************************************************/
void vm_camera_set_capture_disable_jaia(VMBOOL is_disable);


/*****************************************************************************
 * FUNCTION
 *    vm_camera_rotate_osd_layer
 * DESCRIPTION
 *  rotate osd layer
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 * RETURNS
 *  success or not
 * RETURN VALUES
 *  FALSE
 *  TRUE
*****************************************************************************/
VMBOOL vm_camera_rotate_osd_layer(VM_CAMERA_HANDLE handle, vm_graphic_rotate_value rotatevalue);

/*****************************************************************************
 * FUNCTION
 *    vm_camera_set_preview_origin
 * DESCRIPTION
 *  set preview origin point
 * PARAMETERS
 *  handle : [IN] camera's handle which is created by vm_create_camera_instance.
 *  origin : [IN] origin point.
 * RETURNS
 *  success or not
 * RETURN VALUES
 *  FALSE
 *  TRUE
*****************************************************************************/
VMINT vm_camera_set_preview_origin(VM_CAMERA_HANDLE handle, const vm_cam_origin_t* origin);

/*****************************************************************************
 * FUNCTION
 *  vm_camera_use_anonymous_memory
 * DESCRIPTION
 *  use/no use anonymous memory 
 * PARAMETERS
 *  mode          : [IN]        no use[FALSE]/use[TRUE]
 * RETURNS
 *  void
 *****************************************************************************/
void vm_camera_use_anonymous_memory(VMBOOL mode);

#ifdef __cplusplus
}
#endif

#endif /* VMCAMERA_SDK_H_ */

