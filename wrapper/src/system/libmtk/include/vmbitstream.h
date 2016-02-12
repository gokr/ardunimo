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

#ifndef _VM_BITSTREAM_SDK_H
#define _VM_BITSTREAM_SDK_H
/* SDK header file */

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"


#define VM_BITSTREAM_SUCCEED                   0
#define VM_BITSTREAM_BUFFER_OVERFLOW           8001
#define VM_BITSTREAM_BUFFER_UNDERFLOW          8002
#define VM_BITSTREAM_EVENT_NONE                8003
#define VM_BITSTREAM_EVENT_DATA_REQUEST        8004
#define VM_BITSTREAM_EVENT_ERROR               8005
#define VM_BITSTREAM_RECOVER                   8006
#define VM_BITSTREAM_INTERRUPT                 8100
#define VM_BITSTREAM_INTERRUPT_RESUME          8101

#define VM_BITSTREAM_ERR_FAILED                -8001
#define VM_BITSTREAM_ERR_INVALID_RESOULTION    -8002
#define VM_BITSTREAM_ERR_UNSUPPORTED_FORMAT    -8003
#define VM_BITSTREAM_ERR_INVALID_BITSTREAM     -8004
#define VM_BITSTREAM_ERR_MEMORY_INSUFFICIENT   -8005
#define VM_BITSTREAM_ERR_INSUFFICIENT_MEMORY   -8006  /* MED memory is not enough, should check MED memory scenario */
#define VM_BITSTREAM_ERR_INVALID_FORMAT        -8007  /* there is some error while decoding the frame, the frame may not be a valid one */
#define VM_BITSTREAM_NOT_SUPPORTED             -8008  /* Something which is not supported by Bitstream API, e.g. incorrect invoking sequence, features not available */
#define VM_BITSTREAM_INVALID_PARAMETER         -8009  /* The parameter passed through the API is invalid */

#define VM_BITSTREAM_FAILED                    -1


/* format type */
typedef enum
{
    VM_BITSTREAM_CODEC_TYPE_NONE,  /* No type */
    VM_BITSTREAM_CODEC_TYPE_SILENT, /* To play silence frame for video only file */
    VM_BITSTREAM_CODEC_TYPE_AMR,   /* AMR */
    VM_BITSTREAM_CODEC_TYPE_AMRWB, /* Wideband AMR */
    VM_BITSTREAM_CODEC_TYPE_AAC,   /* AAC */
    VM_BITSTREAM_CODEC_TYPE_DAF,   /* DAF */
    VM_BITSTREAM_CODEC_TYPE_MP4A,  /* Mpeg-4 audio */
    VM_BITSTREAM_CODEC_TYPE_MP4AG,
	VM_BITSTREAM_CODEC_TYPE_WAV,	/* RAW data wav */
	VM_BITSTREAM_CODEC_TYPE_ADPCM, /* compressed wav*/
	VM_BITSTREAM_CODEC_TYPE_PCM,	/*RAW data, for input data strengh calculation*/
	VM_BITSTREAM_CODEC_TYPE_TOTAL	/* Total codec type */
} vm_bitstream_codec_type_enum;

typedef enum
{
    VM_BITSTREAM_SAMPLE_FREQ_8000,   /* 8000  */
    VM_BITSTREAM_SAMPLE_FREQ_11025,  /* 11025 */
    VM_BITSTREAM_SAMPLE_FREQ_16000,  /* 16000 */
    VM_BITSTREAM_SAMPLE_FREQ_22050,  /* 22050 */
    VM_BITSTREAM_SAMPLE_FREQ_24000,  /* 24000 */
    VM_BITSTREAM_SAMPLE_FREQ_32000,  /* 32000 */
    VM_BITSTREAM_SAMPLE_FREQ_44100,  /* 44100 */
    VM_BITSTREAM_SAMPLE_FREQ_48000,  /* 48000 */
    VM_BITSTREAM_SAMPLE_FREQ_TOTAL   /* Total sample frequency number */
    
} vm_bitstream_sample_freq_enum;

/* bitstream aduio configuration structure*/
typedef struct
{ 
    vm_bitstream_codec_type_enum vm_codec_type;                                 
} vm_bitstream_audio_cfg_struct;

/* PCM bitstream aduio configuration structure*/
typedef struct
{ 
    vm_bitstream_codec_type_enum vm_codec_type;
	VMBOOL isStereo;                              /* FALSE: mono, TRUE: stereo*/ 
    VMUINT8 bitPerSample;                         /* 8 or 16, commonly use 16 bits*/
    vm_bitstream_sample_freq_enum sampleFreq;    /* 8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000*/
} vm_bitstream_pcm_audio_cfg_struct;

/* buffer status */
typedef struct
{
    VMUINT total_buf_size;
    VMUINT free_buf_size;
} vm_bitstream_audio_buffer_status;

/* paly audio parameters */
typedef struct
{	
    VMUINT 	start_time;
    VMUINT8 	volume;
    VMUINT8 	audio_path;
} vm_bitstream_audio_start_param;

/* callback function */
typedef void (*vm_bitstream_audio_result_callback)(VMINT handle, VMINT result);


/* Bitstream record quality */
typedef enum
{
    VM_BITSTREAM_RECORD_QUALITY_LOW,   /* Low quality */
    VM_BITSTREAM_RECORD_QUALITY_MED,   /* Reserved */
    VM_BITSTREAM_RECORD_QUALITY_HIGH,  /* High quality */
    VM_BITSTREAM_RECORD_QUALITY_BEST,  /* Reserved */

    /* For VM_BITSTREAM_CODEC_TYPE_AMR only */
    VM_BITSTREAM_RECORD_AMR_4_75,      /* AMR 4.75 kbit/s */
    VM_BITSTREAM_RECORD_AMR_5_15,      /* AMR 5.15 kbit/s */
    VM_BITSTREAM_RECORD_AMR_5_9,       /* AMR 5.9  kbit/s */
    VM_BITSTREAM_RECORD_AMR_6_7,       /* AMR 6.7  kbit/s */
    VM_BITSTREAM_RECORD_AMR_7_4,       /* AMR 7.4  kbit/s */
    VM_BITSTREAM_RECORD_AMR_7_95,      /* AMR 7.95 kbit/s */
    VM_BITSTREAM_RECORD_AMR_10_2,      /* AMR 10.2 kbit/s */
    VM_BITSTREAM_RECORD_AMR_12_2       /* AMR 12.2 kbit/s */
}vm_bitstream_rec_quality_enum;

/* Get type of bitstream recorder */
typedef enum
{ 
    VM_BITSTREAM_RECORD_GET_LENGTH, /* Get the length of recorded data(VMUINT16*) */
    VM_BITSTREAM_RECORD_GET_DATA,    /* Get recorded data(VMUINT16*) */
    VM_BITSTREAM_RECORD_GET_STRENGTH /* Get current data strengh value*/
}vm_bitstream_record_get_type_enum;

/* Set type of bitstream recorder */
typedef enum
{ 
    VM_BITSTREAM_RECORD_SET_PAUSE,  /* Pause bitstream record */
    VM_BITSTREAM_RECORD_SET_RESUME,  /* Resume bitstream record */
    VM_BITSTREAM_RECORD_SET_CB_THRESHOLD /* Set callback threshold: default is 200 (words), pass the address of a VMUINT32 to data_p*/
}vm_bitstream_record_set_type_enum;

typedef struct
{ 
    VMUINT16 codec_type;  /* vm_bitstream_codec_type_enum */
    VMUINT16 quality;     /* vm_bitstream_rec_quality_enum */
}vm_bitstream_record_cfg_struct;


/* ======================== BitStream Audio ============================= */

/*****************************************************************************
 * FUNCTION
 *    vm_bitstream_audio_open
 * DESCRIPTION
 *  open bitstream audio.
 * PARAMETERS
 *  handle : [OUT] bitstream handle.
 *  audio_type : [IN] current type, support ARM,AAC,MP3.
 *  callback : [IN] callback function.
 * RETURNS
 *  open success or not.
 * RETURN VALUES
 *	VM_BITSTREAM_SUCCEED : open success.
 *  VM_BITSTREAM_FAILED : open failed.
*****************************************************************************/
VMINT vm_bitstream_audio_open(
	VMINT* handle,
	vm_bitstream_audio_cfg_struct *audio_type,
	vm_bitstream_audio_result_callback callback);


/*****************************************************************************
 * FUNCTION
 *    vm_bitstream_audio_open_pcm
 * DESCRIPTION
 *  open pcm type bitstream audio.
 * PARAMETERS
 *  handle : [OUT] bitstream handle.
 *  audio_type : [IN] current type, support PCM.
 *  callback : [IN] callback function.
 * RETURNS
 *  open success or not.
 * RETURN VALUES
 *	VM_BITSTREAM_SUCCEED : open success.
 *  VM_BITSTREAM_FAILED : open failed.
*****************************************************************************/
VMINT vm_bitstream_audio_open_pcm(
	VMINT* handle,
	vm_bitstream_pcm_audio_cfg_struct *audio_type,
	vm_bitstream_audio_result_callback callback);


/*****************************************************************************
 * FUNCTION
 *    vm_bitstream_audio_finished
 * DESCRIPTION
 *  tell driver no data to put any more.
 * PARAMETERS
 *  handle : [IN] bitstream handle which is getted by vm_bitstream_audio_open.
 * RETURNS
 *  close success or not.
 * RETURN VALUES
 *	VM_BITSTREAM_SUCCEED : finished success.
 *  VM_BITSTREAM_FAILED : finished failed.
*****************************************************************************/
VMINT vm_bitstream_audio_finished(VMINT handle);


/*****************************************************************************
 * FUNCTION
 *    vm_bitstream_audio_close
 * DESCRIPTION
 *  close bitstream audio.
 * PARAMETERS
 *  handle : [IN] bitstream handle which is getted by vm_bitstream_audio_open.
 * RETURNS
 *  close success or not.
 * RETURN VALUES
 *	VM_BITSTREAM_SUCCEED : close success.
 *  VM_BITSTREAM_FAILED : close failed.
*****************************************************************************/
VMINT vm_bitstream_audio_close(VMINT handle);


/*****************************************************************************
 * FUNCTION
 *    vm_bitstream_audio_get_buffer_status
 * DESCRIPTION
 *  get data buffer status include free buffer and total buffer size
 * PARAMETERS
 *  handle : [IN] bitstream handle.
 *  status : [OUT] the status of buffer, please refer the stucture of vm_bitstream_audio_buffer_status.
 * RETURNS
 *  get status success or not.
 * RETURN VALUES
 *	VM_BITSTREAM_SUCCEED : get status success.
 *  VM_BITSTREAM_FAILED : get status failed.
*****************************************************************************/
VMINT vm_bitstream_audio_get_buffer_status(
	VMINT handle, 
	vm_bitstream_audio_buffer_status *status);


/*****************************************************************************
 * FUNCTION
 *    vm_bitstream_audio_put_data
 * DESCRIPTION
 *  put audio data to buffer.
 * PARAMETERS
 *  handle : [IN] bitstream handle.
 *  buffer : [IN] buffer data to put.
 *  buffer_size : [IN] data buffer size.
 *  written : [OUT] the real data size to put.
 * RETURNS
 *  put data to buffer success or not.
 * RETURN VALUES
 *	VM_BITSTREAM_SUCCEED : put data success.
 *  VM_BITSTREAM_FAILED : put data failed.
*****************************************************************************/
VMINT vm_bitstream_audio_put_data(
	VMINT 	handle,
	VMUINT8 *buffer,
	VMUINT 	buffer_size,
	VMUINT 	*written);


/*****************************************************************************
 * FUNCTION
 *    vm_bitstream_audio_start
 * DESCRIPTION
 *  start to play audio.
 * PARAMETERS
 *  handle : [IN] bitstream handle.
 *  para : [IN] audio paremeters,refer the structure of vm_bitstream_audio_start_param.
 * RETURNS
 *  play audio success or not.
 * RETURN VALUES
 *	VM_BITSTREAM_SUCCEED : play audio success.
 *  VM_BITSTREAM_FAILED : play audio failed.
*****************************************************************************/
VMINT vm_bitstream_audio_start(
	VMINT handle,
	vm_bitstream_audio_start_param *para);


/*****************************************************************************
 * FUNCTION
 *    vm_bitstream_audio_stop
 * DESCRIPTION
 *  stop play audio.
 * PARAMETERS
 *  handle : [IN] bitstream handle.
 * RETURNS
 *  stop audio success or not.
 * RETURN VALUES
 *	VM_BITSTREAM_SUCCEED : stop audio success.
 *  VM_BITSTREAM_FAILED : stop audio failed.
*****************************************************************************/
VMINT vm_bitstream_audio_stop(VMINT handle);


/*****************************************************************************
 * FUNCTION
 *    vm_bitstream_audio_get_play_time
 * DESCRIPTION
 *  get current play time.
 * PARAMETERS
 *  handle : [IN] bitstream handle.
 *  current_time : [OUT] current play time(ms).
 * RETURNS
 *  get current play time success or not.
 * RETURN VALUES
 *	VM_BITSTREAM_SUCCEED : get time success.
 *  VM_BITSTREAM_FAILED : get time failed.
*****************************************************************************/
VMINT vm_bitstream_audio_get_play_time(
	VMINT handle,
	VMUINT* current_time);


/*****************************************************************************
 * FUNCTION
 *    vm_bitstream_audio_register_interrupt_callback
 * DESCRIPTION
 *  register interrupt callback.
 * PARAMETERS
 *  callback : [IN] callback function pointer.
 * RETURNS
 *  handle of register function
 * RETURN VALUES
 *  0 :  failed.
*****************************************************************************/
VMINT vm_bitstream_audio_register_interrupt_callback(vm_bitstream_audio_result_callback callback);


/*****************************************************************************
 * FUNCTION
 *    vm_bitstream_audio_clear_interrupt_callback
 * DESCRIPTION
 *  clear the interrupt callback.
 * PARAMETERS
 *  handle : [IN] handle from vm_bitstream_audio_register_interrupt_callback.
*****************************************************************************/
void vm_bitstream_audio_clear_interrupt_callback(VMINT handle);


VMINT vm_bitstream_record_open(VMINT* handle_p,vm_bitstream_record_cfg_struct* cfg_p,vm_bitstream_audio_result_callback callback);
VMINT vm_bitstream_record_close(VMINT handle);
VMINT vm_bitstream_record_start(VMINT handle);
VMINT vm_bitstream_record_stop(VMINT handle);
VMINT vm_bitstream_record_get(VMINT handle,vm_bitstream_record_get_type_enum get_type,void* data_p,VMUINT16* data_len_p);
VMINT vm_bitstream_record_set(VMINT handle,vm_bitstream_record_set_type_enum set_type,void* data_p,VMUINT16 data_len);

#ifdef __cplusplus
}
#endif

#endif /* _VM_BITSTREAM_SDK_H */
