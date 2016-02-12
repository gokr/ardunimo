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

#ifndef _VM_VDOREC_SDK_H
#define _VM_VDOREC_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* msg when record finish */
#define VM_MSG_VDOREC_FINISH        1000

/* msg when file merge done */
#define VM_MSG_VDOREC_FILE_MERGE_DONE      2000

/* video recorder result */
#define VM_RES_VDOREC_SUCCESS                   0      /* Success */
#define VM_RES_VDOREC_FAILED    				(-1)   /* Common failed */
#define VM_RES_VDOREC_REACH_SIZE_LIMIT			(-2)   /* reach max size, mp4 file max size is 2G */
#define VM_RES_VDOREC_REACH_TIME_LIMIT			(-3)   /* reach max time, LINKIT not support this parameter, so there is no limit */
#define VM_RES_VDOREC_DISK_FULL					(-4)   /* disk space full */
#define VM_RES_VDOREC_ERR_STORAGE_TOO_SLOW		(-5)   /* storage too slow */
#define VM_RES_VDOREC_ERR_NO_FRAME_ENCODED      (-6)   /* frame encode error */

#ifndef MAX_APP_NAME_LEN
#define MAX_APP_NAME_LEN					(260)
#endif

/* Video recorder image format */
typedef enum
{
    VM_VDOREC_FORMAT_MPEG4           = 0,      /* MPEG4 */
    VM_VDOREC_FORMAT_H263            = 1,      /* H263 */
    VM_VDOREC_FORMAT_H264            = 2,      /* H264 */
    VM_VDOREC_FORMAT_MJPEG           = 3,      /* MJPEG */
    VM_VDOREC_FORMAT_MAX             = 0x1FFF
} vm_vdorec_format_enum_t;

/* Video recorder image quality */
typedef enum
{
    VM_VDOREC_QUALITY_FINE           = 0,      /* FINE */
    VM_VDOREC_QUALITY_HIGH           = 1,      /* HIGH */
    VM_VDOREC_QUALITY_NORMAL         = 2,      /* NORMAL */
    VM_VDOREC_QUALITY_LOW            = 3,      /* LOW */
    VM_VDOREC_QUALITY_MAX            = 0x1FFF
} vm_vdorec_quality_enum_t;

/* Video record camera id */
enum
{
   VM_VDOREC_MAIN_CAMERA,  /* main camera */
   VM_VDOREC_SUB_CAMERA    /* sub camera */
};

/* Video recorder param */
#define VM_VDOREC_CAMERA_CONTRAST      (1) /* contrast */
#define VM_VDOREC_CAMERA_SHARPNESS     (2) /* sharpness */
#define VM_VDOREC_CAMERA_WB            (3) /* wb */
#define VM_VDOREC_CAMERA_DIGITAL_ZOOM  (4) /* digital zoom */
#define VM_VDOREC_CAMERA_EV_VALUE      (5) /* ev value */

/* Video recorder param contrast */
typedef enum
{
    VM_VDOREC_CONTRAST_LOW=0,   /* low */
    VM_VDOREC_CONTRAST_MEDIUM,  /* medium */
    VM_VDOREC_CONTRAST_HIGH,    /* high */
    VM_VDOREC_CONTRAST_MAX
} VM_VDOREC_CONTRAST_ENUM;

/* Video recorder param sharpness */
typedef enum
{
    VM_VDOREC_SHARPNESS_LOW=0,  /* low */
    VM_VDOREC_SHARPNESS_MEDIUM, /* medium */
    VM_VDOREC_SHARPNESS_HIGH,   /* high */
    VM_VDOREC_SHARPNESS_MAX
} VM_VDOREC_SHARPNESS_ENUM;

/* Video recorder param wb */
typedef enum
{
    VM_VDOREC_WB_AUTO = 0,         /* auto */
    VM_VDOREC_WB_CLOUD,            /* cloud */
    VM_VDOREC_WB_DAYLIGHT,         /* daylight */
    VM_VDOREC_WB_INCANDESCENCE,    /* incandescence */
    VM_VDOREC_WB_FLUORESCENT,      /* fluorescent */
    VM_VDOREC_WB_TUNGSTEN,         /* tungsten */
    VM_VDOREC_WB_MANUAL,           /* manual */
    VM_VDOREC_NO_OF_WB             /* no wb */
} VM_VDOREC_WB_ENUM;

/* Video recorder param zoom */
typedef enum
{
    VM_VDOREC_DZ_TYPE_RANGE,      /* ISP supported digital zoom . (for Raw/YUV sensors) */
    VM_VDOREC_DZ_TYPE_LIST,       /* Sensor supported digial zoom. (for JPEG sensor) */
    VM_VDOREC_DZ_TYPE_MAX
} VM_VDOREC_DIGITAL_ZOOM_TYPE_ENUM;

/* Video recorder param ev */
typedef enum
{
    VM_VDOREC_EV_NEG_4_3 = 0,   /* EV_NEG_4_3 */
    VM_VDOREC_EV_NEG_3_3,       /* EV_NEG_3_3 */
    VM_VDOREC_EV_NEG_2_3,       /* EV_NEG_2_3 */
    VM_VDOREC_EV_NEG_1_3,       /* EV_NEG_1_3 */
    VM_VDOREC_EV_ZERO,          /* EV_ZERO */
    VM_VDOREC_EV_POS_1_3,       /* EV_POS_1_3 */
    VM_VDOREC_EV_POS_2_3,       /* EV_POS_2_3 */
    VM_VDOREC_EV_POS_3_3,       /* EV_POS_3_3 */
    VM_VDOREC_EV_POS_4_3,       /* EV_POS_4_3 */
    VM_VDOREC_EV_NIGHT_SHOT,    /* EV_NIGHT_SHOT */
    VM_VDOREC_NO_OF_EV
} VM_VDOREC_EV_ENUM;

/* Video recorder preview setting structure */
typedef struct
{
    VMUINT16 width;                      		/* Width of the video */
    VMUINT16 height;                     		/* Height of the video */
	VMUINT16 bit_stream_type;					/* image type, refer vm_vdorec_format_enum_t */
	VMUINT16 encode_quality;					/* image quality, refer  vm_vdorec_quality_enum_t */
}vm_vdorec_preview_struct;

/* Video recorder record setting structure */
typedef struct
{
	VMWCHAR fullFileName[MAX_APP_NAME_LEN + 1];	/* full file name to save */
}vm_vdorec_record_struct;


/*****************************************************************************
* FUNCTION
*  vm_vdorec_callback
* DESCRIPTION
*  When record done or file merge done, application will receive this callback
* PARAMETERS
*  msg : [IN] msg id , it should be VM_MSG_VDOREC_FINISH/VM_MSG_VIDEO_FILE_MERGE_DONE
*  VMINT : [INT] please refer the video recorder result 
* RETURNS
*  void
*****************************************************************************/
typedef void (*vm_vdorec_callback)(VMINT msg, VMINT ret);


 /*****************************************************************************
  * FUNCTION
  *  vm_vdorec_start
  * DESCRIPTION
  *  video record start
  * PARAMETERS
  *  camere_id : [IN] camear id, VM_VDOREC_MAIN_CAMERA/VM_VDOREC_SUB_CAMERA
  *  callback : [IN] callback function, please refer vm_vdorec_callback
  * RETURN VALUES
  *  VM_RES_VDOREC_SUCCESS : Succeed to record.
  *  VM_RES_VDOREC_FAILED : Fail to record.
  *****************************************************************************/
VMINT vm_vdorec_power_up(VMUINT16 camere_id, vm_vdorec_callback callback);

/*****************************************************************************
 * FUNCTION
 *	vm_vdorec_preview
 * DESCRIPTION
 *	video record preview start
 * PARAMETERS
 *	para : [IN] video record setting, please refer vm_vdorec_preview_struct
 * RETURN VALUES
 *	VM_RES_VDOREC_SUCCESS : Succeed to record.
 *	VM_RES_VDOREC_FAILED : Fail to record.
 *****************************************************************************/
VMINT vm_vdorec_preview(vm_vdorec_preview_struct* para);

/*****************************************************************************
 * FUNCTION
 *	vm_vdorec_set_param
 * DESCRIPTION
 *	video record set parameters
 * PARAMETERS
 *	param_id : [IN] video record setting, please refer the marco of Video recorder param
 *	value : [IN] value
 * RETURN VALUES
 *	VM_RES_VDOREC_SUCCESS : Succeed to set.
 *	VM_RES_VDOREC_FAILED : Fail to set.
 *****************************************************************************/
VMINT vm_vdorec_set_param(VMUINT32 param_id, VMUINT16 value);

/*****************************************************************************
 * FUNCTION
 *	vm_vdorec_record
 * DESCRIPTION
 *	video record start
 * PARAMETERS
 *	para : [IN] video record setting, please refer vm_vdorec_record_struct
 * RETURN VALUES
 *	VM_RES_VDOREC_SUCCESS : Succeed to record.
 *	VM_RES_VDOREC_FAILED : Fail to record.
 *****************************************************************************/
VMINT vm_vdorec_record(vm_vdorec_record_struct* para);

 /*****************************************************************************
  * FUNCTION
  *  vm_video_close_file
  * DESCRIPTION
  *  To stop video record.
  * PARAMETERS
  *  void
  * RETURN VALUES
  *  VM_RES_VDOREC_SUCCESS : Succeed to stop.
  *  VM_RES_VDOREC_FAILED : Fail to stop.
  *****************************************************************************/
VMINT vm_vdorec_stop(void);

 /*****************************************************************************
  * FUNCTION
  *  vm_video_pause
  * DESCRIPTION
  *  To pause video record.
  * PARAMETERS
  *  void
  * RETURN VALUES
  *  VM_RES_VDOREC_SUCCESS : Succeed to pause.
  *  VM_RES_VDOREC_FAILED : Fail to pause.
  *****************************************************************************/
VMINT vm_vdorec_pause(void);

 /*****************************************************************************
  * FUNCTION
  *  vm_video_resume
  * DESCRIPTION
  *  To resume video record.
  * PARAMETERS
  *  void
  * RETURN VALUES
  *  VM_RES_VDOREC_SUCCESS : Succeed to resume.
  *  VM_RES_VDOREC_FAILED : Fail to resume.
  *****************************************************************************/
VMINT vm_vdorec_resume(void);

/*****************************************************************************
 * FUNCTION
 *	vm_vdorec_power_down
 * DESCRIPTION
 *	video record power down
 * PARAMETERS
 *	void
 * RETURN VALUES
 *	VM_RES_VDOREC_SUCCESS : Succeed to resume.
 *	VM_RES_VDOREC_FAILED : Fail to resume.
 *****************************************************************************/
VMINT vm_vdorec_power_down(void);

/*****************************************************************************
 * FUNCTION
 *  vm_vdorec_save_to_file
 * DESCRIPTION
 *  Save record data to file
 * PARAMETERS
 *  filepath : filepath to save
 *  callback : save result callback
 * RETURN VALUES
 *  N/A
*****************************************************************************/
void vm_vdorec_save_to_file(VMWSTR filepath, vm_vdorec_callback callback);

/*****************************************************************************
 * FUNCTION
 *  vm_vdorec_rtsp_local_save_start
 * DESCRIPTION
 *  Save record data to local file
 * PARAMETERS
 *  filepath : filepath to save
 *  callback : save result callback
 * RETURN VALUES
 *	VM_RES_VDOREC_SUCCESS : Succeed to start.
 *	VM_RES_VDOREC_FAILED : Fail to start.
*****************************************************************************/
VMINT vm_vdorec_rtsp_local_save_start(VMWSTR filepath, vm_vdorec_callback callback);

/*****************************************************************************
 * FUNCTION
 *  vm_vdorec_rtsp_local_save_stop
 * DESCRIPTION
 *  Save record data to file
 * PARAMETERS
 *  void
 * RETURN VALUES
 *	VM_RES_VDOREC_SUCCESS : Succeed to stop.
 *	VM_RES_VDOREC_FAILED : Fail to stop.
*****************************************************************************/
VMINT vm_vdorec_rtsp_local_save_stop(void);

#ifdef __cplusplus
}
#endif

#endif  /*_VM_VDOREC_H*/

