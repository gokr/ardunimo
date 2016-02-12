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

#ifndef VMGPS_SDK_H_
#define VMGPS_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vmsys.h"

/*GPS open result status*/
typedef enum{
	VM_GPS_OPEN_MEMORY_LESS = -2	,		/*memory not enough*/
	VM_GPS_OPEN_RES_LESS = -1	,			/*lack of resource*/
	VM_GPS_OPEN_SUCCESS = 0,				/*Open successfully, need waiting callback */
	VM_GPS_OPEN_ALREADY_OPEN = 1			/*Already open*/
} vm_gps_open_state_enum;

/*GPS close result status*/
typedef enum{
	VM_GPS_CLOSE_FAILED = -1,				/*Close failed*/
	VM_GPS_CLOSE_SUCCESS = 0,				/*Close successfully*/
	VM_GPS_CLOSE_STILL_APP_USE_DATA = 1		/*GPS information still used by other application*/
} vm_gps_close_state_enum;

/*GPS set mode result status*/
typedef enum{
	VM_GPS_SET_MODE_NOT_OPEN = -1,		/*GPS not opened, please open it first*/
	VM_GPS_SET_MODE_CLOSE_SUCCESS = 0,	/*set mode successfully*/
	VM_GPS_SET_PARAM_SUCCESS = 1	/*set mode successfully*/
} vm_gps_setmode_state_enum;

/*GPS type. This type dependent your GPS chip. 3336 only support VM_GPS_ONLY. */
typedef enum
{
    VM_GPS_ONLY,		/* GPS_ONLY */
    VM_GPS_GLONASS,	/* GPS+GLONASS */
    VM_GPS_BEIDOU,		/* GPS+BEIDOU */
    VM_GPS_TYPE_END
} vm_gps_type_enum;

#define VM_MAX_GPGGA_SENTENCE_LENGTH 100
#define VM_MAX_GPGSA_SENTENCE_LENGTH 80
#define VM_MAX_GPRMC_SENTENCE_LENGTH 100
#define VM_MAX_GPVTG_SENTENCE_LENGTH 80
#define VM_MAX_GPGSV_SENTENCE_LENGTH 400
#define VM_MAX_GLGSV_SENTENCE_LENGTH 400
#define VM_MAX_BDGSV_SENTENCE_LENGTH 400
#define VM_MAX_BDGSA_SENTENCE_LENGTH 80
#define VM_MAX_GLGSA_SENTENCE_LENGTH 80
#define VM_MAX_GPACC_SENTENCE_LENGTH 80

/*GPS data structure */
typedef struct
{
    VMUINT8  GPGGA[VM_MAX_GPGGA_SENTENCE_LENGTH+1];     /* GGA data */
    VMUINT8  GPGSA[VM_MAX_GPGSA_SENTENCE_LENGTH+1];     /* GSA data */
    VMUINT8  GPRMC[VM_MAX_GPRMC_SENTENCE_LENGTH+1];     /* RMC data */
    VMUINT8  GPVTG[VM_MAX_GPVTG_SENTENCE_LENGTH+1];     /* VTG data */
    VMUINT8  GPGSV[VM_MAX_GPGSV_SENTENCE_LENGTH+1];     /* GSV data */
    VMUINT8  GLGSV[VM_MAX_GLGSV_SENTENCE_LENGTH+1];     /* GLONASS GSV data */
    VMUINT8  GLGSA[VM_MAX_GLGSA_SENTENCE_LENGTH+1];     /* GLONASS GSA data */
    VMUINT8  BDGSV[VM_MAX_BDGSV_SENTENCE_LENGTH+1];     /* BD GSV data */
    VMUINT8  BDGSA[VM_MAX_BDGSA_SENTENCE_LENGTH+1];     /* BD GSA data */
    VMUINT8  GPACC[VM_MAX_BDGSA_SENTENCE_LENGTH+1];     /* ACC data */
} vm_gps_sentence_info;

/*GPS start mode status. Only for test.*/
typedef enum
{
    VM_GPS_START_MODE_NULL,
    VM_GPS_HOT_START,       /* To test GPS hot start */
    VM_GPS_WARM_START,      /* To test GPS warm start */
    VM_GPS_COLD_START,      /* To test GPS cold start */
    VM_GPS_FULL_START,      /* To test GPS full start */
    VM_GPS_START_TYPE_END
}vm_gps_mode_enum;

/*GPS start set parameter*/
typedef enum
{
    VM_GPS_CMD_SET_LOCATION_REPORT_PERIOD = 1,         /* Set GPS positioning period of normal mode. The minimun is 1s. */
   	VM_GPS_CMD_SET_LOCATION_REPORT_PREIOD_SLEEP_WORK,  /* Set GPS positioning period of low power mode (Sleep First Mode). GPS will power off firstly in positioning cycle. And then willl auto power on to get position before period timer out.*/
    VM_GPS_CMD_SET_LOCATION_REPORT_PREIOD_WROK_SLEEP,  /* Set GPS positioning period of low power mode (Work First Mode). GPS will power on to get position. And then will power off for low power. After period timer out will power on again. */
    VM_GPS_CMD_SET_ASSIST_DATA_FOR_FAST_FIXED,         /* Set GPS assist data for ast fixed. */
	  VM_GPS_CMD_SET_EPO_AUTO_DOWNLOAD,		           /* Set GPS EPO download on or off, default is off. */
	  VM_GPS_CMD_GET_EPO_AUTO_DOWNLOAD_SETTING ,		   /* Get GPS EPO download setting. */
	  VM_GPS_CMD_SET_AGPS_ON_OFF,
	  VM_GPS_CMD_SET_SUPL_PROFILE,
    VM_GPS_CMD_SET_END
} vm_gps_set_param_enum;

/*GPS assist data*/
typedef struct 
{
  VMUINT16      u2YEAR ;             /* > 2000 */
  VMUINT8       u1MONTH;             /* 1~12 */
  VMUINT8       u1DAY;               /* 1~31*/
  VMUINT8       u1HOUR;              /* 0~23*/
  VMUINT8       u1MIN;               /* 0~59*/ 
  VMUINT8       u1SEC;               /* 0~59*/ 
  double	Latitude;				/* reserved */
  double	Longitude;				/* reserved */
  double	Altitude;               /* reserved */
}vm_gps_assist_data_cfg;

#define VM_GPS_AGPS_MAX_PROFILE_ADDR_LEN 64

typedef struct 
{
	VMWCHAR addr[VM_GPS_AGPS_MAX_PROFILE_ADDR_LEN]; // AGPS server addr
	VMUINT32 port; // AGPS server port
}vm_gps_agps_server_cfg;

/*GPS callback message*/
typedef enum
{
	VM_GPS_OPEN_CNF,   /* GPS open confirm msg, data is the result of success of not */
	VM_GPS_SET_MODE_CNF,   /* GPS set mode  confirm msg, data is the result of success of not */
    VM_GPS_CLOSE_CNF,  /* GPS close  confirm msg, data is the result of success of not, LINKIT app cannot receive this msg now */
    VM_GPS_SENTENCE_DATA,  /* GPS data receive msg, the data is the GPS sentence data, refer vm_gps_sentence_info */
    VM_GPS_SET_PARAM_CNF /* GPS set parameter  confirm msg, data is the result of success of not */
}vm_gps_msg_type_enum;


typedef void (*VM_GPS_CAlLBACK_FUNC)(VMINT msg, void* data);

/*****************************************************************************
* FUNCTION
 *    vm_gps_open
 * DESCRIPTION
 *  Open GPS. This funtion will also open UART port. 
 * PARAMETERS
 *  period                          [IN]      period of update data, must be 1, now
 *  call_back                     [IN]       callback function, will be invoked when get the message of vm_gps_msg_type_enum.
 * RETURNS
 *  result of open operation.
 * RETURN VALUES  
 *  VM_GPS_OPEN_SUCCESS : Open successfully.
 *  VM_GPS_OPEN_ALREADY_OPEN : Already open.
 *  VM_GPS_OPEN_MEMORY_LESS : memory not enough
 *  VM_GPS_OPEN_RES_LESS : lack of resource
 *
 * Example
 * <code>
 *
 *	vm_gps_sentence_info g_info
 *
 *	static void vm_gps_callback(VMINT msg, void* data)
 *	{
 *		switch(msg)
 *		{
 *		case VM_GPS_OPEN_CNF:
 *			{
 *				VMINT result = (VMINT)data;
 *				if(result == 0)
 *				{
 *					// open success
 *					// if need you can set mode
 *					// vm_gps_set_mode();
 *				}
 *				else
 *				{
 *					// open failed
 *				}
 *			}
 *			break;
 *		case VM_GPS_CLOSE_CNF:
 *			// app cannot receive this msg now, ignore this.
 *			break;
 *		case VM_GPS_SET_MODE_CNF:
 *			{
 *				VMINT result = (VMINT)data;
 *				if(result == 0)
 *					// set mode success
 *				else
 *					// set mode failed
 *			}
 *			break;
 *		case VM_GPS_SENTENCE_DATA:
 *			{
 *				// copy data
 *				memcpy(&g_info, (vm_gps_sentence_info*)data, sizeof(vm_gps_sentence_info));
 *				
 *				//  deal with the data
 *			}
 *			break;
 *		}
 *	}
 *
 *	int vm_gps_test(void)
 *	{
 *		VMINT result;
 *		result = vm_gps_open( 1, VM_GPS_ONLY, vm_gps_callback);
 *		
 *		if(result == VM_GPS_OPEN_SUCCESS)
 *		{
 *			// this is first time to open GPS, need to get the message VM_GPS_OPEN_CNF
 *		}
 *		else if(result == VM_GPS_OPEN_ALREADY_OPEN)
 *		{
 *			// GPS had been opened before, can get data, no need to wait VM_GPS_OPEN_CNF
 *			// if need you can set mode
 *			// vm_gps_set_mode();
 *		}
 *		else
 *		{
 *			// open failed
 *		}
 *	}
 *
 *
 * void handle_sysevt(VMINT message, VMINT param)
 * {
 *	 switch (message)
 *	 {
 *		 case VM_MSG_CREATE: 
 *			{
 *			 	VMINT result;
 *				result = vm_gps_open( 1, VM_GPS_ONLY, vm_gps_callback);
 *				
 *				if(result == VM_GPS_OPEN_SUCCESS)
 *				{
 *					// this is first time to open GPS, need to get the message VM_GPS_OPEN_CNF
 *				}
 *				else if(result == VM_GPS_OPEN_ALREADY_OPEN)
 *				{
 *					// GPS had been opened before, can get data, no need to wait VM_GPS_OPEN_CNF
 *					// if need you can set mode
 *					// vm_gps_set_mode();
 *				}
 *				else
 *				{
 *					// open failed
 *				}
 *			}
 *			 break;
 *		 case VM_MSG_QUIT:
 *			 vm_gps_close();
 *			 break;
 *			 break;
 *		 }
 *	 }
 * }
 *
 * </code>
 *****************************************************************************/
VMINT vm_gps_open(VMUINT period, vm_gps_type_enum type, VM_GPS_CAlLBACK_FUNC callback);

/*****************************************************************************
* FUNCTION
 *    vm_gps_close
 * DESCRIPTION
 *  Close GPS. This funtion will close GPS if there is no other application use GPS. 
 * RETURNS
 *  result of close operation.
 * RETURN VALUES   
 *  VM_GPS_CLOSE_SUCCESS : Close successfully.
 *  VM_GPS_CLOSE_STILL_APP_USE_DATA : GPS information still used by other application
 *  VM_GPS_CLOSE_FAILED : Close failed.
 *
 * Example
 * <code>
 * please refer vm_gps_open
 * </code>
*****************************************************************************/
VMINT vm_gps_close(void);

/*****************************************************************************
* FUNCTION
 *    vm_gps_set_mode
 * DESCRIPTION
 *  set GPS start mode. This API is only for test. Please don't use it in normal usage.
 * PARAMETERS
 *  mode                          [IN]      start mode of GPS, please refer vm_gps_mode_enum type
 * RETURNS
 *  result of close operation.
 * RETURN VALUES   
 *  VM_GPS_SET_MODE_CLOSE_SUCCESS : set mode successfully.
 *  VM_GPS_SET_MODE_NOT_OPEN : GPS not opened, need open it.
 *
 * Example
 * <code>
 * please refer vm_gps_open
 * </code>
*****************************************************************************/
VMINT vm_gps_set_mode(vm_gps_mode_enum mode);

/*****************************************************************************
* FUNCTION
 *    vm_gps_set_param
 * DESCRIPTION
 *  set GPS parameter 
 * PARAMETERS
 *  mode                          [IN]      set parameter of GPS, please refer vm_gps_param_enum type
 *  value                          [IN]      parameter value
 * RETURNS
 *  result of the operation.
 * RETURN VALUES   
 *  0 : set mode successfully.
 *  -1 : GPS not opened, need open it.
 *
 * Example
 * <code>
 *
 * void set_param(void)
 * {
 *    // If you need set gps assist data.
 *    vm_gps_assist_data_cfg cfg;
 *	cfg.u2YEAR = 2000;
 *	cfg.u1MONTH = 7;
 *	cfg.u1DAY = 22;
 *	cfg.u1HOUR = 10;
 *	cfg.u1MIN = 10;
 *	cfg.u1SEC = 10;
 *	vm_gps_set_param(VM_GPS_CMD_SET_ASSIST_DATA_FOR_FAST_FIXED, &cfg);
 *     
 *    // If you need set GPS normal mode and positioning period.
 *    vm_gps_set_param(VM_GPS_CMD_SET_LOCATION_REPORT_PERIOD, 1);
 *   // If you need set GPS low power mode (Sleep first mode) and  positioning period.
 *    vm_gps_set_param(VM_GPS_CMD_SET_LOCATION_REPORT_PREIOD_SLEEP_WORK, 60);
 *   // If you need set GPS low power mode (Work first mode) and  positioning period.
 *    vm_gps_set_param(VM_GPS_CMD_SET_LOCATION_REPORT_PREIOD_WROK_SLEEP, 60);
 * }
 *
 * </code>
*****************************************************************************/
VMINT vm_gps_set_param(vm_gps_set_param_enum param, VMUINT32 value);

#ifdef __cplusplus
}
#endif 

#endif /* VMGPS_SDK_H_ */

