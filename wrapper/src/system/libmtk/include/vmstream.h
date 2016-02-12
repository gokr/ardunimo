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

#ifndef VMSTREAM_SDK_H_
#define VMSTREAM_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

#define VM_STREAM_MAX_PROXY_ADDR_LEN (63)
#define VM_STREAM_MAX_IP_LEN 4

/* stream scenario enum */
typedef enum
{
    VM_STREAM_DECODER,                 // not used
    VM_STREAM_QVGA,                    // not used
    VM_STREAM_PREVIEW,                 // not used
    VM_STREAM_CIF,                     // not used
    VM_STREAM_INFO,                    // not used
    VM_STREAM_MPEG4_DECODER,           // not used
    VM_STREAM_DECODER_N_SUBTITLE,      // not used
    VM_STREAM_UPTO_QVGA,               // not used
    VM_STREAM_UPTO_CIF,                // not used
    VM_STREAM_QVGA_MPEG4SP,            // not used
    VM_STREAM_MAX_SCENARIO = 0xFF
}vm_stream_scenario_enum;

/* stream connect struct */
typedef struct
{
    VMUINT8   session_id;				// not used
    VMUINT16  request_id;				// not used
    VMUINT32  net_id;					// not used
    VMUINT8   type; 					// not used
    VMBOOL    use_proxy;				// not used
    VMUINT8   proxy_addr[VM_STREAM_MAX_PROXY_ADDR_LEN];		// not used
    VMUINT16  proxy_port;				// not used	
    VMUINT16  lowest_udp_port;			// not used	
    VMUINT16  highest_udp_port;			// not used
    vm_stream_scenario_enum scenario;	// not used
    VMUINT16  prefer_transport; 		// not used
    VMUINT8	  host_ip[VM_STREAM_MAX_IP_LEN];	// remote IP, format is like host_ip[0] = 127; host_ip[1] = 0; host_ip[2] = 0; host_ip[3] = 1 
    VMUINT8	  local_ip[VM_STREAM_MAX_IP_LEN];	// local IP , format is like local_ip[0] = 127; host_ip[1] = 0; host_ip[2] = 0; host_ip[3] = 1 
    VMUINT16  host_port;						// remote port	
    VMUINT16  local_port;						// local port

}vm_stream_connect_struct;

/* volume type */
typedef enum
{
    VM_STREAM_VOLUME_MIC,                         /* microphone */
    VM_STREAM_VOLUME_MEDIA,                       /* Multi-Media */
    VM_STREAM_MAX_VOLUME_TYPE
}vm_stream_volume_enum;

/* Audio volume level enum for 7 level volume */
typedef enum
{
    VM_STREAM_VOL_0,      /* Volume level 0 (Not mute) */
    VM_STREAM_VOL_1,      /* Volume level 1 */
    VM_STREAM_VOL_2,      /* Volume level 2 */
    VM_STREAM_VOL_3,      /* Volume level 3 */
    VM_STREAM_VOL_4,      /* Volume level 4 */
    VM_STREAM_VOL_5,      /* Volume level 5 */
    VM_STREAM_VOL_6,      /* Volume level 6 */
    VM_STREAM_VOL_NUM     /* Total volume level */
}vm_stream_mic_vol_enum;

/* Audio volume level enum for 16 level volume */
typedef enum
{
    VM_STREAM_VOL_EX_0,   /* Volume level 0 (Not mute) */
    VM_STREAM_VOL_EX_1,   /* Volume level 1 */
    VM_STREAM_VOL_EX_2,   /* Volume level 2 */
    VM_STREAM_VOL_EX_3,   /* Volume level 3 */
    VM_STREAM_VOL_EX_4,   /* Volume level 4 */
    VM_STREAM_VOL_EX_5,   /* Volume level 5 */
    VM_STREAM_VOL_EX_6,   /* Volume level 6 */
    VM_STREAM_VOL_EX_7,   /* Volume level 7 */
    VM_STREAM_VOL_EX_8,   /* Volume level 8 */
    VM_STREAM_VOL_EX_9,   /* Volume level 9 */
    VM_STREAM_VOL_EX_10,  /* Volume level 10 */
    VM_STREAM_VOL_EX_11,  /* Volume level 11 */
    VM_STREAM_VOL_EX_12,  /* Volume level 12 */
    VM_STREAM_VOL_EX_13,  /* Volume level 13 */
    VM_STREAM_VOL_EX_14,  /* Volume level 14 */
    VM_STREAM_VOL_EX_15,  /* Volume level 15 */
    VM_STREAM_VOL_EX_NUM  /* Total volume level */
}vm_stream_media_vol_enum;



/*****************************************************************************
 * FUNCTION
 *  vm_stream_connect
 * DESCRIPTION
 *  connect by remote device external IP/port and current device local IP/port 
 * PARAMETERS
 *  connect_info : [IN] please refer the structure vm_stream_connect_struct
 * RETURNS
 *  stream handle / failure
 *****************************************************************************/ 
VMINT vm_stream_connect(vm_stream_connect_struct connect_info);


/*****************************************************************************
 * FUNCTION
 *  vm_stream_disconnect
 * DESCRIPTION
 *  disconnect session 
 * PARAMETERS
 *  session_id : [IN] not used, default: 0
 * RETURNS
 *  stream handle / failure
 *****************************************************************************/ 
VMINT vm_stream_disconnect(VMUINT8 session_id);

/*****************************************************************************
 * FUNCTION
 *  vm_stream_set_volume
 * DESCRIPTION
 *  set loudspeaker volume  
 * PARAMETERS
 *  type : [IN]please refer vm_stream_volume_enum
 *  value : [IN] volume level refer vm_stream_mic_vol_enum/vm_stream_media_vol_enum
 * RETURNS
 *  
 *****************************************************************************/ 
void vm_stream_set_volume(vm_stream_volume_enum type, VMUINT value);

#ifdef __cplusplus
}
#endif

#endif /* VMSTREAM_SDK_H_ */
