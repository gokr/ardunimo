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

#ifndef _VM_VIDEO_SDK_H
#define _VM_VIDEO_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"
#include "vmmm.h"

/**
 *	operation succeed
 */
#define VM_VIDEO_SUCCESS    (0)
/**
 *	operation fail
 */
#define VM_VIDEO_FAILED    (-1)


/**
 *	data not enough
 */
#define VM_VIDEO_PROGRESSIVE_FILE_NOT_ENOUGH   	-101




/**
 *	file open failed
 */
#define VM_VIDEO_ERR_OPEN_FILE_FAILED           		-103

/**
 *	file size too large
 */
#define VM_VIDEO_ERR_FILE_TOO_LARGE             		-104

/**
 *	snapshot failed
 */
#define VM_VIDEO_ERR_SNAPSHOT_FAILED            		-105

/**
 *	play failed
 */
#define VM_VIDEO_ERR_PLAY_FAILED                		-106



/**
 *	snapshot failed for disk full
 */
#define VM_VIDEO_ERR_SNAPSHOT_DISK_FULL         	-107

/**
 *	snapshot failed for disk read-only
 */
#define VM_VIDEO_ERR_SNAPSHOT_WRITE_PROTECTION  -108

/**
 *	invalid resoulution
 */
#define VM_VIDEO_ERR_INVALID_RESOULTION         	-109   

/**
 *	unsupported format
 */
#define VM_VIDEO_ERR_UNSUPPORTED_FORMAT         	-110

/**
 *	memory insufficient
 */
#define VM_VIDEO_ERR_MEMORY_INSUFFICIENT        	-111

/**
 *	DRM prohibited
 */
#define VM_VIDEO_ERR_DRM_PROHIBITED             		-112     

/**
 *	DRM during usage
 */
#define VM_VIDEO_ERR_DRM_DURATION_USED          	-113

/**
 *	framerate too high
 */
#define VM_VIDEO_ERR_FRAMERATE_TOO_HIGH         	-114



/**
 *	one grade darker than N4
 */
#define VM_VIDEO_BRIGHTNESS_N5              0	
/**
 *	one grade darker than N3
 */
#define VM_VIDEO_BRIGHTNESS_N4              1    
/**
 *	one grade darker than N2
 */
#define VM_VIDEO_BRIGHTNESS_N3              2	
/**
 *	one grade darker than N1
 */
#define VM_VIDEO_BRIGHTNESS_N2              3	
/**
 *	one grade darker than 0
 */
#define VM_VIDEO_BRIGHTNESS_N1              4		
/**
 *	default brightness
 */
#define VM_VIDEO_BRIGHTNESS_0                5  
/**
 *	one grade brighter than 0
 */
#define VM_VIDEO_BRIGHTNESS_P1              6	
/**
 *	one grade brighter than P1
 */
#define VM_VIDEO_BRIGHTNESS_P2              7	
/**
 *	one grade brighter than P2
 */
#define VM_VIDEO_BRIGHTNESS_P3              8	
/**
 *	one grade brighter than P3
 */
#define VM_VIDEO_BRIGHTNESS_P4              9	
/**
 *	one grade brighter than P4
 */
#define VM_VIDEO_BRIGHTNESS_P5              10	


/**
 *	one grade lower than N4
 */
#define VM_VIDEO_CONTRAST_N5                0	
/**
 *	one grade lower than N3
 */
#define VM_VIDEO_CONTRAST_N4                1	
/**
 *	one grade lower than N2
 */
#define VM_VIDEO_CONTRAST_N3                2	
/**
 *	one grade lower than N1
 */
#define VM_VIDEO_CONTRAST_N2                3	
/**
 *	one grade lower than 0
 */
#define VM_VIDEO_CONTRAST_N1                4	
/**
 *	default contrast
 */
#define VM_VIDEO_CONTRAST_0                 5	
/**
 *	one grade higher than 0
 */
#define VM_VIDEO_CONTRAST_P1                6	
/**
 *	one grade higher than P1
 */
#define VM_VIDEO_CONTRAST_P2                7	
/**
 *	one grade higher than P2
 */
#define VM_VIDEO_CONTRAST_P3                8	
/**
 *	one grade higher than P3
 */
#define VM_VIDEO_CONTRAST_P4                9	
/**
 *	one grade higher than P4
 */
#define VM_VIDEO_CONTRAST_P5                10	


/**
 *	rotate 0 degree
 */
#define VM_VIDEO_LCD_ROTATE_0            0
/**
 *	rotate 90 degree
 */
#define VM_VIDEO_LCD_ROTATE_90           1
/**
 *	rotate 180 degree
 */
#define VM_VIDEO_LCD_ROTATE_180          2
/**
 *	rotate 270 degree
 */
#define VM_VIDEO_LCD_ROTATE_270          3

/* Video track type enum */
typedef enum
{
    VM_VIDEO_TRACK_NONE,   
    VM_VIDEO_TRACK_AV,     /* Video has both audio and video tracks */
    VM_VIDEO_TRACK_A_ONLY, /* Video has audio track only */
    VM_VIDEO_TRACK_V_ONLY  /* Video has video track only */
} vm_video_track_enum;


/* Max length of content info */
#define VM_VIDEO_MAX_CONTENT_INFO_LEN   80


/* Video information structure */
typedef struct
{
    VMUINT16 width;                      /* Width of the video */
    VMUINT16 height;                     /* Height of the video */
    VMUINT32 total_frame_count;          /* Total framecount of the video */
    VMUINT64 total_time_duration;        /* Total time duration of the video */
    vm_video_track_enum track;     
    VMINT handle;                        /* Handle of the opened video file */
    VMINT is_seekable;                  /* Is this video seekable */
    VMUINT8 aud_channel_no;              /* Audio channel count information */
    VMUINT16 aud_sample_rate;            /* Audio sample rate information */

    VMINT is_drm_streaming;             /* Is this is a drm streaming file */
    VMUINT drm_handle;                  /* DRM handle of this video */

    VMWCHAR title_desc[VM_VIDEO_MAX_CONTENT_INFO_LEN+1];       /* Title information */
    VMWCHAR artist_desc[VM_VIDEO_MAX_CONTENT_INFO_LEN+1];      /* Artist information */
    VMWCHAR album_desc[VM_VIDEO_MAX_CONTENT_INFO_LEN+1];       /* Album information */
    VMWCHAR author_desc[VM_VIDEO_MAX_CONTENT_INFO_LEN+1];      /* Author information */
    VMWCHAR copyright_desc[VM_VIDEO_MAX_CONTENT_INFO_LEN+1];   /* Copyright information */
    VMWCHAR date_desc[VM_VIDEO_MAX_CONTENT_INFO_LEN+1];        /* Date information */
} vm_video_info_struct;





/*****************************************************************************
* FUNCTION
*  vm_video_open_result_callback
* DESCRIPTION
*  When open a file in async mode, if there is any error or indication (open succeefully) from media-task, MDI-Video module will invoke this callback function and pass the result to MMI appliactions.
*  MMI application should handle this kind of error.
* PARAMETERS
*  ret : [IN] The result in MDI_RESULT enum type.
*  video_info : [OUT] video information of this opened file, it will contain valid data if the open operation is succeeded.
* RETURNS
*  void
*****************************************************************************/
typedef void (*vm_video_open_result_callback)(VMINT ret, vm_video_info_struct *video_info);


/*****************************************************************************
* FUNCTION
*  vm_video_finish_callback
* DESCRIPTION
*  When playing a video, if there is any error or indication (finished playing) from media-task, MDI-Video module will invoke this callback function and pass the result to MMI applications.
*  MMI application should handle this kind of error.
* PARAMETERS
*  ret: [IN] The result in MDI_RESULT enum type.
* RETURNS
*  void
*****************************************************************************/
typedef void (*vm_video_finish_callback) (VMINT ret);



 /*****************************************************************************
  * FUNCTION
  *  vm_video_open_file
  * DESCRIPTION
  *  To open video file (non-blocking open).
  * PARAMETERS
  *  filename : [IN] Videe clip's full file name
  *  open_result_callback : [IN] Open file result callback function
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to open video file, need to wait callback function when open operation is finished.
  *  VM_VIDEO_ERR_DRM_PROHIBITED : Fail to open video file due to drm is prohibited.
  *  VM_VIDEO_ERR_MEMORY_INSUFFICIENT : Fail to open video file due to memory is insufficient.
  *  VM_VIDEO_ERR_FRAMERATE_TOO_HIGH : Fail to open video file due to file is too large.
  *  VM_VIDEO_ERR_INVALID_RESOULTION : Fail to open video file due to framerate is too high.
  *  VM_VIDEO_ERR_OPEN_FILE_FAILED : Fail to open video file.
  *****************************************************************************/
 VMINT vm_video_open_file(
                    const VMWSTR filename,
                    vm_video_open_result_callback open_result_callback);


 /*****************************************************************************
  * FUNCTION
  *  vm_video_close_file
  * DESCRIPTION
  *  To close video file.
  * PARAMETERS
  *  void
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to close video file.
  *  VM_VIDEO_FAILED : Fail to close video file.
  *****************************************************************************/
 VMINT vm_video_close_file(void);


 /*****************************************************************************
  * FUNCTION
  *  vm_video_open_buffer
  * DESCRIPTION
  *  To open video clip from buffer.
  * PARAMETERS
  *  file_buffer : [IN] Video clip file buffer
  *  buffer_len : [IN] Video clip's buffer size
  *  info : [OUT] Video clip's info
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to open video buffer, need to wait callback function when open operation is finished.
  *  VM_VIDEO_ERR_MEMORY_INSUFFICIENT : Fail to open video buffer due to memory is insufficient.
  *  VM_VIDEO_ERR_FRAMERATE_TOO_HIGH : Fail to open video buffer due to framerate is too high.
  *  VM_VIDEO_ERR_OPEN_FILE_FAILED : Fail to open video file.
  *****************************************************************************/
  VMINT vm_video_open_buffer(
                    const VMUSTR buffer,
                    const VMUINT buffer_len,
                    vm_video_info_struct *info);
 
                    
 /*****************************************************************************
  * FUNCTION
  *  vm_video_close_buffer
  * DESCRIPTION
  *  To close video clip from buffer
  * PARAMETERS
  *  void
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to close video clip buffer.
  *  VM_VIDEO_FAILED : Fail to close video clip buffer.
  *****************************************************************************/
 VMINT vm_video_close_buffer(void);


/*****************************************************************************
* FUNCTION
*  mdi_video_ply_play
* DESCRIPTION
*  To start play opened video.
* PARAMETERS
*  player_layer_handle : [IN] Layer handle of playback layer.
*  base_layer_handle : [IN] Layer handle of tool component layer.
*  repeat_count : [IN] Repeat how many times.
*  is_play_audio : [IN] To play audio or not.
*  audio_path : [IN] Audio output path.
*  play_finish_callback : [IN] Callback function.
* RETURN VALUES
*  VM_VIDEO_SUCCESS : Succeed to start play.
*  VM_VIDEO_ERR_DRM_PROHIBITED : Fail to start play due to drm check is prohibited.
*  MDI_RES_VDOPLY_PROGRESSIVE_FILE_NOT_ENOUGH : Fail to start play due to the download data is not enough for progressive playback.
*  VM_VIDEO_PROGRESSIVE_FILE_NOT_ENOUGH : Fail to start play due to it is stopped due to stop time is reached.
*  VM_VIDEO_ERR_PLAY_FAILED : Fail to start play.
*****************************************************************************/
 VMINT vm_video_play(
                    VMUINT player_layer_handle,
                    VMUINT base_layer_handle,
                    VMUINT16 repeat_count, 
                    VMINT is_play_audio,
                    VMINT audio_path, 
                    vm_video_finish_callback play_finish_callback);


/*****************************************************************************
 * FUNCTION
 *  vm_video_stop
 * DESCRIPTION
 *  To stop video playing.
 * PARAMETERS
 *  void
 * RETURN VALUES
 *  VM_VIDEO_SUCCESS : Succeed to stop player.
 *  VM_VIDEO_FAILED : Fail to stop player due to it is already stopped.
 *****************************************************************************/
 VMINT vm_video_stop(void);


 /*****************************************************************************
  * FUNCTION
  *  vm_video_pause
  * DESCRIPTION
  *  To pause video playing.
  * PARAMETERS
  *  void
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to pause.
  *  VM_VIDEO_FAILED : Fail to pause.
  *****************************************************************************/
VMINT vm_video_pause(void);


 /*****************************************************************************
  * FUNCTION
  *  vm_video_resume
  * DESCRIPTION
  *  To resume video playing.
  * PARAMETERS
  *  void
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to resume.
  *  VM_VIDEO_FAILED : Fail to resume.
  *****************************************************************************/
VMINT vm_video_resume(void);


 /*****************************************************************************
  * FUNCTION
  *  vm_video_seek_and_getframe
  * DESCRIPTION
  *  To seek video and get seek frame.
  * PARAMETERS
  *  time : [IN] Seek time stamp.
  *  player_layer_handle : [IN] Get frame on this layer.
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to seek.
  *  VM_VIDEO_FAILED : Fail to seek.
  *****************************************************************************/
 VMINT vm_video_seek_and_getframe(VMUINT64 time, VMUINT player_layer_handle);


 /*****************************************************************************
  * FUNCTION
  *  vm_video_snapshot
  * DESCRIPTION
  *  To snapshot video and save as jpeg file.
  * PARAMETERS
  *  layer_handle : [IN] Video play layer.
  *  file_name : [IN] Filename for jpeg.
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to snapshot.
  *  VM_VIDEO_ERR_SNAPSHOT_DISK_FULL : Fail to snapshot due to disk is full.
  *  VM_VIDEO_ERR_SNAPSHOT_WRITE_PROTECTION : Fail to snapshot due to the disk is in write protection mode.
  *  VM_VIDEO_ERR_SNAPSHOT_FAILED : Fail to snapshot.
  *****************************************************************************/
 VMINT vm_video_snapshot(VMUINT player_layer_handle, VMWSTR file_name);



 /*****************************************************************************
  * FUNCTION
  *  vm_video_set_brightness
  * DESCRIPTION
  *  To set brightness parameter for video player.
  * PARAMETERS
  *  brightness : [IN] Brightness value
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to set brightness parameter to video player.
  *  VM_VIDEO_FAILED : Fail to set brightness parameter to video player.
  *****************************************************************************/
 VMINT vm_video_set_brightness(VMUINT16 brightness);


 /*****************************************************************************
  * FUNCTION
  *  vm_video_set_contrast
  * DESCRIPTION
  *  To set contrast parameter to video player.
  * PARAMETERS
  *  contrast : [IN] Contrast value
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to set EV parameter to video player.
  *  VM_VIDEO_FAILED : Fail to set EV parameter to video player.
  *****************************************************************************/
 VMINT vm_video_set_contrast(VMUINT16 contrast);



 /*****************************************************************************
  * FUNCTION
  *  vm_video_get_cur_play_time
  * DESCRIPTION
  *  To get current play time.
  * PARAMETERS
  *  cur_play_time : [OUT] Current play time.
  * RETURNS
  *  result of get play time
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to set EV parameter to video player.
  *  VM_VIDEO_FAILED : Fail to set EV parameter to video player.
  *****************************************************************************/
 VMINT vm_video_get_cur_play_time(VMUINT64 *cur_play_time); 


 /*****************************************************************************
  * FUNCTION
  *  vm_video_play_stream_from_rtsp_link
  * DESCRIPTION
  *  launch native Video Player to play specified RTSP link
  * PARAMETERS
  *  url : [IN] RTSP URL link encoding with UCS2 format.
  * RETURNS
  *  result of launch video player applicaiton
  * RETURN VALUES
  *  VM_VIDEO_SUCCESS : Succeed to launch video player application
  *  VM_VIDEO_FAILED : Fail to launch video player application.
  *****************************************************************************/
VMINT vm_video_play_stream_from_rtsp_link(VMWSTR url);
	
/*****************************************************************************
 * FUNCTION
 *  vm_video_play_stream_from_sdp_file
 * DESCRIPTION
 *  launch native Video Player to play specified sdp file
 * PARAMETERS
 *  filename : [IN] sdp file name encoding with UCS2 format.
 *  is_short : [IN] is 8.3 format file name or not.
 * RETURNS
 *  result of launch video player applicaiton
 * RETURN VALUES
 *  VM_VIDEO_SUCCESS : Succeed to launch video player application
 *  VM_VIDEO_FAILED : Fail to launch video player application.
 *****************************************************************************/
VMINT vm_video_play_stream_from_sdp_file(VMWSTR filename, VMUCHAR is_short);


/*****************************************************************************
 * FUNCTION
 *  vm_video_play_by_filepath
 * DESCRIPTION
 *  launch native Video Player to play specified file path
 * PARAMETERS
 *  filename : [IN] file name encoding with UCS2 format.
 * RETURNS
 *  result of launch video player applicaiton
 * RETURN VALUES
 *  VM_VIDEO_SUCCESS : Succeed to launch video player application
 *  or else failure.
 *****************************************************************************/
VMINT vm_video_play_by_filepath(VMWSTR filename);

/*****************************************************************************
 * FUNCTION
 *  vm_video_is_support_rtsp_link_play
 * DESCRIPTION
 *  support rstp play or not
 * PARAMETERS
 *  
 * RETURNS
 *  
 * RETURN VALUES
 *  TRUE : support rtsp play
 *  FALSE : not support
 *****************************************************************************/
VMBOOL vm_video_is_support_rtsp_link_play(void);

/*****************************************************************************
 * FUNCTION
 *  vm_video_is_support_sdp_file_play
 * DESCRIPTION
 *  support sdp file play or not
 * PARAMETERS
 *  
 * RETURNS
 *  
 * RETURN VALUES
 *  TRUE : support sdp file play
 *  FALSE : not support
 *****************************************************************************/
VMBOOL vm_video_is_support_sdp_file_play(void);

#ifdef __cplusplus
}
#endif

#endif  /*_VM_VIDEO_H*/
