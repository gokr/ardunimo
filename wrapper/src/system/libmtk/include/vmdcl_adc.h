#ifndef __VM_DCL_ADC_H__
#define __VM_DCL_ADC_H__
 

/*Define the dev for ADC module. Used in dcl_open*/
typedef enum
{
	VM_DCL_ADC_START = VM_DCL_ADC_GROUP_START,
	VM_DCL_ADC
}VM_DCL_ADC_DEV_T;

/* DCL_CTRL_CMD for ADC */
typedef enum
{
   VM_ADC_CMD_CREATE_OBJECT = 0x901, /* Get logic channel */
   VM_ADC_CMD_MODIFY_PARAM, /* Set measure parameters */
   VM_ADC_CMD_SEND_START, /* start to measure */
   VM_ADC_CMD_SEND_STOP, /* stop measure */
   VM_ADC_CMD_GET_CHANNEL /* get physical channel */
}VM_DCL_ADC_CTRL_CMD_T;

/* ADC event id */
typedef enum
{
   VM_ADC_GET_RESULT = VM_ADC_EVENTS_START /* Get logic channel */
}VM_DCL_ADC_EVENT_T;


/* For VM_ADC_CMD_CREATE_OBJECT command. */
typedef struct
{
   VMUINT32 u4Period;				/* Measurement period (Uint is in Tick) */
   VMUINT32 u4Sapid;
   VM_DCL_MODULE_TYPE_T u1OwnerId;				/* Indicate the module to for ADC driver to notify the result */
   VMUINT8 u1AdcChannel;			/* To be measured physical ADC channel */
   VMUINT8 u1EvaluateCount;		/* Measurement count */
   VMBOOL fgSendPrimitive;		/* Whether to send message to owner module or NOT */
}vm_adc_ctrl_create_object_t; 

/* For VM_ADC_CMD_MODIFY_PARAM command. */
typedef struct
{
   VMUINT32 u4Period;				/* Measurement period (Uint is in Tick) */
   VMUINT8 u1EvaluateCount;		/* Measurement count */
} vm_adc_ctrl_modify_param_t;

/* For VM_ADC_CMD_SEND_START command. */
typedef struct
{
   VM_DCL_MODULE_TYPE_T u1OwnerId;				/* Indicate the module to for ADC driver to notify the result */
} vm_adc_ctrl_send_start_t;

/* For VM_ADC_CMD_SEND_STOP command. */
typedef struct
{

   VM_DCL_MODULE_TYPE_T u1OwnerId;				/* Indicate the module to for ADC driver to notify the result */
} vm_adc_ctrl_send_stop_t;

/*ADC measure result */
typedef struct {
	VMUINT8 	ref_count;
	VMUINT16 	msg_len;			/* LOCAL_PARA_HDR */
	double         adc_value; /* Indicate the measure raw data */
	VMINT32 		adc_handle;
	VMINT32 		volt; /* Indicate the measure data (volt) */
	VMUINT8 		adc_sche_id;
}vm_bmt_adc_measure_done_conf_struct; 

/* For VM_ADC_CMD_GET_CHANNEL command. */
typedef enum {
   VM_VBAT_ADC_CHANNEL = 0,
   VM_VISENSE_ADC_CHANNEL,
   VM_VBATTMP_ADC_CHANNEL,
   VM_BATTYPE_ADC_CHANNEL,
   VM_VCHARGER_ADC_CHANNEL,
   VM_PCBTMP_ADC_CHANNEL,
   VM_AUX_ADC_CHANNEL,
   VM_CHR_USB_ADC_CHANNEL,
   VM_OTG_VBUS_ADC_CHANNEL,
   VM_RFTMP_ADC_CHANNEL,
   VM_DCL_XP_ADC_CHANNEL,
   VM_DCL_YP_ADC_CHANNEL,
   VM_DCL_YM_ADC_CHANNEL,
   VM_DCL_XM_ADC_CHANNEL,    
   VM_MAX_ADC_CHANNEL
} VM_ADC_CHANNEL_TYPE_ENUM;

/* For VM_ADC_CMD_GET_CHANNEL command. */
typedef struct
{
   VMUINT8    u1AdcPhyCh;
   VMUINT16   u2AdcName;
}vm_adc_ctrl_get_physical_channel_t; 



#endif



