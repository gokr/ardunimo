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

#ifndef VMMM_SDK_H_
#define VMMM_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/* driver name length */
#define DRV_NAME_LEN	(4)

/* record file name length */
#define REC_NAME_LEN	(50)

/* directory length */
#define DIR_NAME_LEN	(200)

/* file name length */
#define MAX_NAME_LEN	(260)

/* wide char file name length */
#define MAX_WNAME_LEN		(260 * sizeof(VMWCHAR))

/* default volume */
#define DEFAULT_VOLUME			3

/* path to play */
#define VM_DEVICE_SPEAKER 			0
#define VM_DEVICE_MICROPHONE	 	1
#define VM_DEVICE_SPEAKER2 		4
#define VM_DEVICE_LOUDSPEAKER 	5
#define VM_DEVICE_SPEAKER_BOTH 	6
#define VM_DEVICE_BT_HEADSET 		8

/* media type */
typedef enum
{
	VM_FORMAT_NONE = -1,  
    	VM_FORMAT_AMR = 3,
    	VM_FORMAT_MP3 = 5,
    	VM_FORMAT_AAC = 6,
   	VM_FORMAT_WAV = 13,
   	VM_FORMAT_MIDI = 17,
   	VM_FORMAT_IMELODY = 18,
   	VM_FORMAT_OTHER = 100,
	VM_FORMAT_MAX
}vm_format_enum;

/* ======================= record ====================== */


/* record success */
#define VM_RECORD_SUCCEED		(1)

/* record failed */
#define VM_RECORD_FAILED		(0)

/* callback function pointer */
typedef void(*vm_recorder_callback)(VMINT result);

typedef void (*vm_audio_result_callback)(VMINT handle, VMINT result);

/*****************************************************************************
 * FUNCTION
 *    vm_record_start
 * DESCRIPTION
 *  start record.
 * PARAMETERS
 *  drv_name : [IN] driver name.
 *  dir_name : [IN] directory name.
 *  rec_name : [IN] record file name.
 *  format : [IN] record file format, VM_FORMAT_AMR and VM_FORMAT_WAV.
 *  full_rec_file_wname : [OUT] the real file name, maybe different with rec_name.
 *  vm_record_cb : [IN] callback function.
 * RETURNS
 *  start record success or not.
 * RETURN VALUES
 *  VM_RECORD_FAILED : start record failed.
 *  VM_RECORD_SUCCEED : start record success.
*****************************************************************************/
VMINT vm_record_start(VMSTR drv_name, VMSTR dir_name, VMSTR rec_name, VMUINT8 format, VMWSTR full_rec_file_wname, vm_recorder_callback vm_record_cb);

/*****************************************************************************
 * FUNCTION
 *    vm_record_pause
 * DESCRIPTION
 *  record pause.
 * RETURNS
 *  record pause success or not.
 * RETURN VALUES
 *  VM_RECORD_FAILED : record pause failed.
 *  VM_RECORD_SUCCEED : record pause success.
*****************************************************************************/
VMINT vm_record_pause(void);

/*****************************************************************************
 * FUNCTION
 *    vm_record_resume
 * DESCRIPTION
 *  record resume.
 * RETURNS
 *  record resume success or not.
 * RETURN VALUES
 *  VM_RECORD_FAILED : record resume failed.
 *  VM_RECORD_SUCCEED : record resume success.
*****************************************************************************/
VMINT vm_record_resume(void);

/*****************************************************************************
 * FUNCTION
 *    vm_record_stop
 * DESCRIPTION
 *  stop record.
 * RETURNS
 *  stop record success or not.
 * RETURN VALUES
 *  VM_RECORD_FAILED : stop record failed.
 *  VM_RECORD_SUCCEED : stop record success.
*****************************************************************************/
VMINT vm_record_stop(void);


/* ===================== audio ========================== */


/* audio operation success */
#define VM_AUDIO_SUCCEED 	(0)

/* audio operation failed */
#define VM_AUDIO_FAILED	(-1)

/* stop play audio */
#define VM_AUDIO_RESULT_STOP			1

/* pause audio */
#define VM_AUDIO_RESULT_PAUSE			2

/* resume audio */
#define VM_AUDIO_RESULT_RESUME			3

/* play end */ 
#define	VM_AUDIO_RESULT_END_OF_FILE		5

/* demo end time */
#define	VM_AUDIO_RESULT_DEMO_END		6

/* interruptted by others */
#define	VM_AUDIO_RESULT_INTERRUPT		7

/* resume from interruptting */
#define	VM_AUDIO_RESULT_INTERRUPT_RESUME		8


/*****************************************************************************
 * FUNCTION
 *    vm_audio_play_file
 * DESCRIPTION
 *  play file use default volume(3) and path(VM_DEVICE_SPEAKER2).
 * PARAMETERS
 *  filename : [IN] file name to play.
 *  f : [IN] callback function.
 * RETURNS
 *  play a file success or not.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : play a file failed.
 *  VM_AUDIO_SUCCEED : play a file success.
*****************************************************************************/
VMINT vm_audio_play_file(VMWSTR filename, void (*f)(VMINT result));

/*****************************************************************************
 * FUNCTION
 *    vm_audio_play_file_ex
 * DESCRIPTION
 *  play file use default volume(3) but set start time and path.
 * PARAMETERS
 *  filename : [IN] file name to play.
 *  start_time : [IN] start time to play.
 *  path : [IN] play path.            
 *	               VM_DEVICE_SPEAKER         Tone, Keypad sound to play on audio device. 
 *                 VM_DEVICE_MICROPHONE      Microphone sound to send on audio device. 
 *                 VM_DEVICE_SPEAKER2        Earphone, carkit 
 *                 VM_DEVICE_LOUDSPEAKER     Loudspeaker for free sound 
 *                 VM_DEVICE_SPEAKER_BOTH    Output from earphone and loud speaker 
 *                 VM_DEVICE_BT_HEADSET      Used to be OR bitwise with above audio output devices 
 *  f : [IN] callback function.
 * RETURNS
 *  play a file success or not.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : play a file failed.
 *  VM_AUDIO_SUCCEED : play a file success.
*****************************************************************************/
VMINT vm_audio_play_file_ex(VMWSTR filename, VMUINT start_time, VMUINT path, void (*f)(VMINT result));

/*****************************************************************************
 * FUNCTION
 *    vm_audio_play_bytes
 * DESCRIPTION
 *  play buffer use default volume(3) but set start time and path.
 * PARAMETERS
 *  audio_data : [IN] audio buffer to play.
 *  len : [IN] buffer length.
 *  format : [IN] buffer format, only support mp3 and aac.
 *  start_time : [IN] start time to play.
 *  path : [IN] play path.            
 *	               VM_DEVICE_SPEAKER         Tone, Keypad sound to play on audio device. 
 *                 VM_DEVICE_MICROPHONE      Microphone sound to send on audio device. 
 *                 VM_DEVICE_SPEAKER2        Earphone, carkit 
 *                 VM_DEVICE_LOUDSPEAKER     Loudspeaker for free sound 
 *                 VM_DEVICE_SPEAKER_BOTH    Output from earphone and loud speaker 
 *                 VM_DEVICE_BT_HEADSET      Used to be OR bitwise with above audio output devices 
 *  f : [IN] callback function.
 * RETURNS
 *  play buffer success or not.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : play buffer failed.
 *  VM_AUDIO_SUCCEED : play buffer success.
*****************************************************************************/
VMINT vm_audio_play_bytes(void *audio_data, VMUINT len, VMUINT8 format, VMUINT start_time, VMUINT path, void (*f)(VMINT result));


/*****************************************************************************
 * FUNCTION
 *    vm_audio_play_bytes_no_block
 * DESCRIPTION
 *  play buffer use default volume(3) but set path, this is no block function.
 * PARAMETERS
 *  audio_data : [IN] audio buffer to play.
 *  len : [IN] buffer length.
 *  format : [IN] buffer format, only support mp3 and aac.
 *  path : [IN] play path.            
 *	               VM_DEVICE_SPEAKER         Tone, Keypad sound to play on audio device. 
 *                 VM_DEVICE_MICROPHONE      Microphone sound to send on audio device. 
 *                 VM_DEVICE_SPEAKER2        Earphone, carkit 
 *                 VM_DEVICE_LOUDSPEAKER     Loudspeaker for free sound 
 *                 VM_DEVICE_SPEAKER_BOTH    Output from earphone and loud speaker 
 *                 VM_DEVICE_BT_HEADSET      Used to be OR bitwise with above audio output devices 
 *  f : [IN] callback function.
 * RETURNS
 *  play buffer success or not.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : play buffer failed.
 *  VM_AUDIO_SUCCEED : play buffer success.
*****************************************************************************/
VMINT vm_audio_play_bytes_no_block(void *audio_data, VMUINT len, VMUINT8 format, VMUINT path, void (*f)(VMINT result));


/*****************************************************************************
 * FUNCTION
 *    vm_audio_pause
 * DESCRIPTION
 *  pause audio.
 * PARAMETERS
 *  f : [IN] callback function.
 * RETURNS
 *  pause success or not.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : pause failed.
 *  VM_AUDIO_SUCCEED : pause success.
*****************************************************************************/
VMINT vm_audio_pause(void (*f)(VMINT result));

/*****************************************************************************
 * FUNCTION
 *    vm_audio_resume
 * DESCRIPTION
 *  resume audio.
 * PARAMETERS
 *  f : [IN] callback function.
 * RETURNS
 *  resume success or not.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : resume failed.
 *  VM_AUDIO_SUCCEED : resume success.
*****************************************************************************/
VMINT vm_audio_resume(void (*f)(VMINT result));

/*****************************************************************************
 * FUNCTION
 *    vm_audio_stop
 * DESCRIPTION
 *  stop audio.
 * PARAMETERS
 *  f : [IN] callback function.
 * RETURNS
 *  stop success or not.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : stop failed.
 *  VM_AUDIO_SUCCEED : stop success.
*****************************************************************************/
VMINT vm_audio_stop(void (*f)(VMINT result));

/*****************************************************************************
 * FUNCTION
 *    vm_audio_stop_all
 * DESCRIPTION
 *  stop  all audios.
 * PARAMETERS
 *  
 * RETURNS
 *  stop success or not.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : stop failed.
 *  VM_AUDIO_SUCCEED : stop success.
*****************************************************************************/
VMINT vm_audio_stop_all(void);

/*****************************************************************************
 * FUNCTION
 *    vm_audio_duration
 * DESCRIPTION
 *  get file time.
 * PARAMETERS
 *  filename : [IN] file name to get time.
 * RETURNS
 *  time timer or failed.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : get time failed.
 *  Other : audio time.
*****************************************************************************/
VMINT vm_audio_duration(VMWSTR filename);

/*****************************************************************************
 * FUNCTION
 *    vm_audio_bytes_duration
 * DESCRIPTION
 *  get buffer time.
 * PARAMETERS
 *  audio_data : [IN] audio buffer to play.
 *  len : [IN] buffer length.
 *  format : [IN] buffer format, support mp3,aac,midi,amr.
 * RETURNS
 *  buffer timer or failed.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : play buffer failed.
 *  Other : buffer time.
*****************************************************************************/
VMINT vm_audio_bytes_duration(void *audio_data, VMUINT len, VMUINT8 format);


/*****************************************************************************
 * FUNCTION
 *    vm_audio_get_time
 * DESCRIPTION
 *  get current play time.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : play buffer failed.
 *  Other : current play time.
*****************************************************************************/
VMINT vm_audio_get_time(void);

/*****************************************************************************
 * FUNCTION
 *    vm_set_volume
 * DESCRIPTION
 *  set play volume.
 * PARAMETERS
 *  volume : [IN] volume to set, range is 0-6.
*****************************************************************************/
void vm_set_volume(VMINT volume);


/* ========================== midi ============================ */

/* midi operation success */
#define VM_MIDI_SUCCEED 	(0)

/* midi operation failed */
#define VM_MIDI_FAILED		(-1)

/* play count once time */
#define VM_MIDI_PLAY_MAX	9

/* midi paly start */
#define VM_STATE_MIDI_START		1

/* midi paly end */
#define VM_STATE_MIDI_STOP			2


/*****************************************************************************
 * FUNCTION
 *    vm_midi_set_type
 * DESCRIPTION
 *  set midi play format.
 * PARAMETERS
 *  type : [IN] resource id.
 * RETURNS
 *  set midi type
 * RETURN VALUES
*****************************************************************************/
void vm_midi_set_type(VMINT type);

/* DOM-NOT_FOR_SDK-BEGIN */
/*****************************************************************************
 * FUNCTION
 *    vm_midi_play
 * DESCRIPTION
 *  play midi, phase out now, please use vm_midi_paly_by_tytes
 * PARAMETERS
 *  resid : [IN] resource id.
 *  repeat : [IN] repeat count.
 *  f : [IN] callback function.
 * RETURNS
 *  if play success return midi handle, else return VM_MIDI_FAILED.
 * RETURN VALUES
 *  VM_MIDI_FAILED : play midi failed.
 *  Other : midi handle.
*****************************************************************************/
VMINT vm_midi_play(VMINT resid, VMINT repeat, void (*f)(VMINT handle, VMINT event));

/*****************************************************************************
 * FUNCTION
 *    vm_midi_play_ex
 * DESCRIPTION
 *  play midi, phase out now, please use vm_midi_paly_by_tytes_ex
 * PARAMETERS
 *  resid : [IN] resource id.
 *  start_time : [IN] time to play.
 *  repeat : [IN] repeat count.
 *  path : [IN] play path.            
 *	               VM_DEVICE_SPEAKER         Tone, Keypad sound to play on audio device. 
 *                 VM_DEVICE_MICROPHONE      Microphone sound to send on audio device. 
 *                 VM_DEVICE_SPEAKER2        Earphone, carkit 
 *                 VM_DEVICE_LOUDSPEAKER     Loudspeaker for free sound 
 *                 VM_DEVICE_SPEAKER_BOTH    Output from earphone and loud speaker 
 *                 VM_DEVICE_BT_HEADSET      Used to be OR bitwise with above audio output devices 
 *  f : [IN] callback function.
 * RETURNS
 *  if play success return midi handle, else return VM_MIDI_FAILED.
 * RETURN VALUES
 *  VM_MIDI_FAILED : play midi failed.
 *  Other : midi handle.
*****************************************************************************/
VMINT vm_midi_play_ex(VMINT resid, VMUINT start_time, VMINT repeat, VMUINT path, void (*f)(VMINT handle, VMINT event));
/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
 * FUNCTION
 *    vm_midi_play_by_bytes
 * DESCRIPTION
 *  play buffer.
 * PARAMETERS
 *  midibuf : [IN] buffer data.
 *  len : [IN] buffer length.
 *  repeat : [IN] repeat count.
 *  f : [IN] callback function.
 * RETURNS
 *  if play success return midi handle, else return VM_MIDI_FAILED.
 * RETURN VALUES
 *  VM_MIDI_FAILED : play midi failed.
 *  Other : midi handle.
*****************************************************************************/
VMINT vm_midi_play_by_bytes( VMUINT8 * midibuf, VMINT len, VMINT repeat, void (*f)(VMINT handle, VMINT event) );

/*****************************************************************************
 * FUNCTION
 *    vm_midi_play_ex
 * DESCRIPTION
 *  play midi.
 * PARAMETERS
 *  midibuf : [IN] buffer data.
 *  len : [IN] buffer length.
 *  start_time : [IN] time to play.
 *  repeat : [IN] repeat count.
 *  path : [IN] play path.            
 *	               VM_DEVICE_SPEAKER         Tone, Keypad sound to play on audio device. 
 *                 VM_DEVICE_MICROPHONE      Microphone sound to send on audio device. 
 *                 VM_DEVICE_SPEAKER2        Earphone, carkit 
 *                 VM_DEVICE_LOUDSPEAKER     Loudspeaker for free sound 
 *                 VM_DEVICE_SPEAKER_BOTH    Output from earphone and loud speaker 
 *                 VM_DEVICE_BT_HEADSET      Used to be OR bitwise with above audio output devices 
 *  f : [IN] callback function.
 * RETURNS
 *  if play success return midi handle, else return VM_MIDI_FAILED.
 * RETURN VALUES
 *  VM_MIDI_FAILED : play midi failed.
 *  Other : midi handle.
*****************************************************************************/
VMINT vm_midi_play_by_bytes_ex( VMUINT8 * midibuf, VMINT len, VMUINT start_time, VMINT repeat, VMUINT path, void (*f)(VMINT handle, VMINT event) );

/*****************************************************************************
 * FUNCTION
 *    vm_midi_pause
 * DESCRIPTION
 *  pause audio.
 * PARAMETERS
 *  handle : [IN] play handle.
 * RETURNS
 *  pause success or not.
 * RETURN VALUES
 *  0 : resume success.
 *  others : resume failed.
*****************************************************************************/
VMINT vm_midi_pause(VMINT handle);

/*****************************************************************************
 * FUNCTION
 *    vm_midi_resume
 * DESCRIPTION
 *  resume audio.
 * PARAMETERS
 *  handle : [IN] play handle.
 * RETURNS
 *  resume success or not.
 * RETURN VALUES
 *  0 : resume success.
 *  others : resume failed.
*****************************************************************************/
VMINT vm_midi_resume(VMINT handle);

/*****************************************************************************
 * FUNCTION
 *    vm_midi_get_time
 * DESCRIPTION
 *  get play time.
 * PARAMETERS
 *  handle : [IN] play handle.
 *  current_time : [OUT] play time.
 * RETURNS
 *  get play time success or not.
 * RETURN VALUES
 *  0 : resume success.
 *  others : resume failed.
*****************************************************************************/
VMINT vm_midi_get_time(VMINT handle, VMUINT *current_time);

/*****************************************************************************
 * FUNCTION
 *    vm_midi_stop
 * DESCRIPTION
 *  stop midi.
 * PARAMETERS
 *  handle : [IN] play handle.
 * RETURNS
 *  stop success or not.
 * RETURN VALUES
 *  VM_MIDI_SUCCEED : stop success.
 *  VM_MIDI_FAILED : stop failed.
*****************************************************************************/
void vm_midi_stop(VMINT handle);

/*****************************************************************************
 * FUNCTION
 *    vm_midi_stop_all
 * DESCRIPTION
 *  stop all opened midi.
 * EXAMPLE
*****************************************************************************/
void vm_midi_stop_all(void);

/*****************************************************************************
 * FUNCTION
 *    vm_set_key_tone_on
 * DESCRIPTION
 *  set key tone on.
*****************************************************************************/
void vm_set_key_tone_on(void);

/*****************************************************************************
 * FUNCTION
 *    vm_set_key_tone_off
 * DESCRIPTION
 *  set key tone off.
*****************************************************************************/
void vm_set_key_tone_off(void);

/* key tone type */
typedef enum
{
	VM_KEY_TONE_ENABLED = 0,		 /* Not Disable all key tone */
    	VM_KEY_VOL_TONE_DISABLED,		/* Disable VOL_UP VOL_DOWN key tone */
    	VM_KEY_VOL_UP_DOWN_TONE_DISABLED,		/* Disable VOL_UP, VOL_DOWN, UP_ARROW, DOWN_ARROW key tone */
    	VM_KEY_RIGHT_LEFT_ARROW_TONE_DISABLED,	/* Disable LEFT ARROW, RIGHT ARROW */
    	VM_KEY_TONE_DISABLED,		/* Disable all key tone */
    	VM_KEY_TONE_INVALID
} vm_kbd_tone_state_enum;

/*****************************************************************************
 * FUNCTION
 *    vm_get_key_tone_state
 * DESCRIPTION
 *  get current key tone states.
 * RETURNS
 *  key tone states, please refer the struct of vm_kbd_tone_state_enum.
*****************************************************************************/
vm_kbd_tone_state_enum vm_get_key_tone_state(void);

/*****************************************************************************
 * FUNCTION
 *    vm_set_key_tone_state
 * DESCRIPTION
 *  set key tone states.
 * PARAMETERS
 *  key_tone_state : [IN] key tone states to set.
 * RETURNS
 *  set key tone states success or not.
 * RETURN VALUES
 *  FALSE : set key tone states failed.
 *  TRUE : set key tone states success.
*****************************************************************************/
VMINT vm_set_key_tone_state(vm_kbd_tone_state_enum key_tone_state);


/* DOM-NOT_FOR_SDK-BEGIN */
/*****************************************************************************
 * FUNCTION
 *    vm_set_ringtone
 * DESCRIPTION
 *  set file as ringtone, phase out now, please use the interface of vm_settings_set_tone
 * PARAMETERS
 *  filepath : [IN] the path for setting ringtone.
 * RETURNS
 *  set ringtone success or not.
 * RETURN VALUES
 *  >0 : the slot of set ringtone
 *  VM_KURO_FAILED : set ringtone error
*****************************************************************************/
VMINT vm_set_ringtone(VMWSTR filepath);
/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
* FUNCTION
*  vm_audio_resume_bg_play
* DESCRIPTION
*  resume background audio
*****************************************************************************/
void vm_audio_resume_bg_play(void);

/*****************************************************************************
* FUNCTION
*  vm_audio_suspend_bg_play
* DESCRIPTION
*  suspend background audio
*****************************************************************************/
void vm_audio_suspend_bg_play(void);


typedef void (*vm_audio_mixed_callback_p) (VMINT handle, VMINT result, void* user_data);

typedef struct
{
    void*                   data;         /* String data. */
    VMINT32                 data_len;     /* The length of string data. Don't care if using file name */
    vm_format_enum          format;       /* Audio format, please refer vm_format_enum */
    VMINT8                  repeats;      /* Repate times */
    VMINT8                  output_path;  /* Output path. Use VM_DEVICE_SPEAKER2 for default setting */
    VMBOOL                  async_mode;   /* Async mode, if this is TRUE, play and stop will be asynchronous */
    vm_audio_mixed_callback_p callback;     /* Callback function */
    void*                   user_data;    /* User data */
} vm_auido_mixed_open_struct;


/*****************************************************************************
 * FUNCTION
 *    vm_audio_mixed_set_speedup_mode
 * DESCRIPTION
 *  Speed mode, if this is TRUE, play and stop will speed up, but this will use on mixed channel,
 * Example : if the paltformat support 5 channels to mixed, if you set this is TRUE , application
 * only can use 4 channels to play
 * PARAMETERS
 *  mode : [IN] TRUE
 * RETURNS
 * RETURN VALUES
*****************************************************************************/
void vm_audio_mixed_set_speedup_mode(VMBOOL mode);

/*****************************************************************************
 * FUNCTION
 *    vm_audio_mixed_open
 * DESCRIPTION
 *  this function support mixed audio's play,  support format is VM_FORMAT_WAV,VM_FORMAT_MIDI,VM_FORMAT_IMELODY, 
 *  other audio format only can play, but could not mixed.
 * PARAMETERS
 *  mixed_play : [IN] open parameters, please refer vm_auido_mixed_open_struct.
 * RETURNS
 *  if open success , it will return handle, else return VM_AUDIO_FAILED.
 * RETURN VALUES
 *  VM_AUDIO_FAILED : mixed play open failed.
 *  Other : play handle.
*****************************************************************************/
VMINT vm_audio_mixed_open(vm_auido_mixed_open_struct* mixed_open);


/*****************************************************************************
 * FUNCTION
 *    vm_audio_mixed_play
 * DESCRIPTION
 *  play the audio
 * PARAMETERS
 *  handle : [IN] play parameters, please refer vm_auido_mixed_play_struct.
 * RETURNS
 *  play success or not.
 * RETURN VALUES
 *  VM_AUDIO_SUCCEED : mixed play success.
 *  Other : play failed.
*****************************************************************************/
VMINT vm_audio_mixed_play(VMINT handle);


/*****************************************************************************
 * FUNCTION
 *    vm_audio_mixed_pause
 * DESCRIPTION
 *  pause audio.
 * PARAMETERS
 *  handle : [IN] audio handle, get from vm_audio_mixed_open
 * RETURNS
 *  pause success or not.
 * RETURN VALUES
 *  VM_AUDIO_SUCCEED : resume success.
 *  others : resume failed.
*****************************************************************************/
VMINT vm_audio_mixed_pause(VMINT handle);

/*****************************************************************************
 * FUNCTION
 *    vm_audio_mixed_resume
 * DESCRIPTION
 *  resume audio.
 * PARAMETERS
 *  handle : [IN]  audio handle, get from vm_audio_mixed_open
 * RETURNS
 *  resume success or not.
 * RETURN VALUES
 *  VM_AUDIO_SUCCEED : resume success.
 *  others : resume failed.
*****************************************************************************/
VMINT vm_audio_mixed_resume(VMINT handle);


/*****************************************************************************
 * FUNCTION
 *   vm_audio_mixed_set_start_time
 * DESCRIPTION
 *  set start time to play.
 * PARAMETERS
 *  handle : [IN] audio handle, get from vm_audio_mixed_open
 *  current_time : [IN] start time.
 * RETURNS
 *  set start time success or not.
 * RETURN VALUES
 *  VM_AUDIO_SUCCEED : set time success.
 *  others : set time failed.
*****************************************************************************/
VMINT vm_audio_mixed_set_start_time(VMINT handle, VMUINT start_time);


/*****************************************************************************
 * FUNCTION
 *   vm_audio_mixed_get_time
 * DESCRIPTION
 *  get current play time.
 * PARAMETERS
 *  handle : [IN] audio handle, get from vm_audio_mixed_open
 *  current_time : [OUT] play time.
 * RETURNS
 *  get play time success or not.
 * RETURN VALUES
 *  VM_AUDIO_SUCCEED : get time success.
 *  others : get time failed.
*****************************************************************************/
VMINT vm_audio_mixed_get_time(VMINT handle, VMUINT *current_time);

/*****************************************************************************
 * FUNCTION
 *   vm_audio_mixed_stop
 * DESCRIPTION
 *  stop the opened audio.
 * PARAMETERS
 *  handle : [IN] audio handle, get from vm_audio_mixed_open
 * RETURNS
*****************************************************************************/
void vm_audio_mixed_stop(VMINT handle);

/*****************************************************************************
 * FUNCTION
 *   vm_audio_mixed_close
 * DESCRIPTION
 *  close the opened audio.
 * PARAMETERS
 *  handle : [IN] audio handle, get from vm_audio_mixed_open
 * RETURNS
*****************************************************************************/
void vm_audio_mixed_close(VMINT handle);


/*****************************************************************************
 * FUNCTION
 *   vm_audio_mixed_close_all
 * DESCRIPTION
 *  close all opened mixed audio.
 * EXAMPLE
*****************************************************************************/
void vm_audio_mixed_close_all(void);


/*****************************************************************************
 * FUNCTION
 *    vm_audio_register_interrupt_callback
 * DESCRIPTION
 *  register interrupt callback, when audio was interrupted it will invoke this callback
 * PARAMETERS
 *  callback : [IN] callback function pointer
 * RETURNS
 *  handle of the app
 * RETURN VALUES
 *  0 : error
 *  other : handle of the app
*****************************************************************************/
VMINT vm_audio_register_interrupt_callback(vm_audio_result_callback callback);


/*****************************************************************************
 * FUNCTION
 *    vm_audio_clear_interrupt_callback
 * DESCRIPTION
 *  clear interrupt callback
 * PARAMETERS
 *  handle : [IN] get from vm_audio_register_interrupt_callback
 * RETURNS
 *  
*****************************************************************************/
void vm_audio_clear_interrupt_callback(VMINT handle);

/*****************************************************************************
 * FUNCTION
 *    vm_audio_play_beep
 * DESCRIPTION
 *  when other app use audio play, application can use this to play notification tone
 * PARAMETERS
 *  
 * RETURNS
 *  
*****************************************************************************/
void vm_audio_play_beep(void);


/*****************************************************************************
 * FUNCTION
 *    vm_audio_is_app_playing
 * DESCRIPTION
 *  this is to check if there is other applications are palying
 * PARAMETERS
 *  
 * RETURNS
 *  TRUE: other application is playing
 *  FLASE: no there is palying
*****************************************************************************/
VMBOOL vm_audio_is_app_playing(void);


/*****************************************************************************
 * FUNCTION
 *    vm_audio_terminate_background_play
 * DESCRIPTION
 *  terminate background play , if the LINKIT appliction is audio player, please use it.
 * PARAMETERS
*****************************************************************************/
void vm_audio_terminate_background_play(void);


/*****************************************************************************
 * FUNCTION
 *    vm_get_volume
 * DESCRIPTION
 *  get current volume
 * PARAMETERS
 *  
 * RETURNS
 *  volume value
 *  
*****************************************************************************/
VMINT vm_get_volume(void);


/*****************************************************************************
 * FUNCTION
 *    vm_audio_is_calling
 * DESCRIPTION
 *  quer is calling now
 * PARAMETERS
 *  
 * RETURNS
 *  TRUE or FALSE
 *  
*****************************************************************************/
VMINT vm_audio_is_calling(void);


/*****************************************************************************
 * FUNCTION
 *    vm_audio_set_volume_type
 * DESCRIPTION
 *  set volume type, media or ring,  media only cosmos project support
 * PARAMETERS
 *  type 0-ring 1-media
 * RETURNS
 *  TRUE or FALSE
 *  
*****************************************************************************/
VMINT vm_audio_set_volume_type(VMINT type);

/*****************************************************************************
 * FUNCTION
 *    vm_audio_set_sph_volume
 * DESCRIPTION
 *  set speech volume
 * PARAMETERS
 *  volume
 * RETURNS
 *  
*****************************************************************************/
void vm_audio_set_sph_volume(VMINT volume);

/*****************************************************************************
 * FUNCTION
 *    vm_audio_get_sph_mode_volume
 * DESCRIPTION
 *  get speech volume
 * PARAMETERS
 *  void
 * RETURNS
 *  volume value
*****************************************************************************/
VMINT vm_audio_get_sph_mode_volume(void);

#ifdef __cplusplus
}
#endif

#endif /* VMMM_SDK_H_ */
