/*
 Copyright (c) 2011 Arduino.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 

 Modified 20 Aug 2014 by MediaTek Inc.
 */

#include "Arduino.h"
#include "vmdcl.h"
#include "vmlog.h"
#include "vmdcl_adc.h"
#include "vmdcl_pwm.h"
#include "vmdcl_gpio.h"
#include "vmthread.h"
#include "vmsys.h"

#ifdef __cplusplus
extern "C" {
#endif

static int _readResolution = 10;
static int _writeResolution = 8;

static VM_SIGNAL_ID signalid = 0;
static uint32_t adc_result = 0;

#define PWM_RESOLUTION		8

#ifdef __LINKIT_V1__
#define ADC_PIN_NUM 4
#else
#define ADC_PIN_NUM 3
#endif

typedef struct _ADCPinDescription
{
  uint32_t ulPin;
  uint32_t channel;
}ADCPinDescription;

ADCPinDescription g_ADCPinArray[ADC_PIN_NUM] = 
{
	{ 14, 12 },
	{ 15, 15 },
#ifdef __LINKIT_V1__
	{ 16, 13 },
	{ 17, 14 }
#else
	{ 16, 13 }
#endif
};

/**/
void analogReadResolution(int res) {
	_readResolution = res;
}

void analogWriteResolution(int res) {
	_writeResolution = res;
}

static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to) {
	if (from == to)
		return value;
	if (from > to)
		return value >> (from-to);
	else
		return value << (to-from);
}

long mapVolt(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

eAnalogReference analog_reference = AR_DEFAULT;

void analogReference(eAnalogReference ulMode)
{
	analog_reference = ulMode;//only for compatiable, nouse.
}

void adcCallback(void* parameter, VM_DCL_EVENT event, VM_DCL_HANDLE device_handle)
{
	VM_DCL_CB_ILM_DATA_T *data;
	vm_bmt_adc_measure_done_conf_struct * result;

	if(parameter!=NULL) 
	  {
		data = (VM_DCL_CB_ILM_DATA_T*)parameter;
		result = (vm_bmt_adc_measure_done_conf_struct *)(data->vm_local_para_ptr);

		if( result != NULL )
		{ 
			double *p;

			p =(double*)&(result->adc_value);

			adc_result = (unsigned int)*p;
			//vm_log_info("analogRead_callback:the result is:adc_result=%d;",adc_result);
		}
	 }
	
	 vm_signal_post(signalid);

}

uint32_t findADCChannel(uint32_t ulPin)
{
	int i;
	
	for(i = 0; i<ADC_PIN_NUM; i++)
	{
		if(g_ADCPinArray[i].ulPin == ulPin)
			return g_ADCPinArray[i].channel;
	}
	return 0;
}

uint32_t analogRead(uint32_t ulPin)
{
	int32_t status = 0;
	VM_DCL_HANDLE adc_handle;
	
	vm_adc_ctrl_send_start_t start_data;
	vm_adc_ctrl_send_stop_t stop_data;

	
	if(!changePinType(ulPin, PIO_ANALOG, &adc_handle))
	{
		//vm_log_info("analogRead : changePinType failed");
		return;
	}
	
	if(adc_handle == VM_DCL_HANDLE_INVALID)
	{	
		vm_adc_ctrl_create_object_t obj_data;

		adc_handle = vm_dcl_open(VM_DCL_ADC,0);
		setPinHandle(ulPin, adc_handle);
		
		status = vm_dcl_registercallback(adc_handle,VM_ADC_GET_RESULT ,(VM_DCL_CALLBACK)adcCallback,(void *)NULL);
	
		obj_data.u1OwnerId = vm_dcl_get_ownerid();
		obj_data.u1AdcChannel = findADCChannel(ulPin);
		obj_data.u4Period = 1;
		obj_data.u1EvaluateCount = 1;
		obj_data.fgSendPrimitive = 1;
		status = vm_dcl_control(adc_handle,VM_ADC_CMD_CREATE_OBJECT,(void *)&obj_data);
		//vm_log_info("analogRead : adc_handle=%d, status = %d",adc_handle, status);

	}
	
	signalid = vm_signal_init();
	
	start_data.u1OwnerId = vm_dcl_get_ownerid();
	status = vm_dcl_control(adc_handle,VM_ADC_CMD_SEND_START,(void *)&start_data);

	vm_signal_wait(signalid);
	vm_signal_deinit(signalid);
	
	stop_data.u1OwnerId = vm_dcl_get_ownerid();
	status = vm_dcl_control(adc_handle,VM_ADC_CMD_SEND_STOP,(void *)&stop_data);

	adc_result = mapResolution(adc_result, 10, _readResolution);
	
	if(adc_result>906)
		adc_result = 906;
		
	adc_result = mapVolt(adc_result, 0, 906, 0, 1023);

	return adc_result;

}

void analogOutputInit(void) {
	return;
}

void analogWrite(uint32_t ulPin, uint32_t ulValue) {
	
	VM_DCL_HANDLE pwm_handle;

	if(ulPin == 9)
       {    
		VM_PWM_SET_CLOCK_T pwm_clock;
		VM_PWM_SET_COUNTER_THRESHOLD_T pwm_config_adv;

    		if(!changePinType(ulPin, PIO_PWM, &pwm_handle))
			return;

		if(pwm_handle == VM_DCL_HANDLE_INVALID)
		{
			pwm_handle = vm_dcl_open(VM_DCL_PWM4,vm_dcl_get_ownerid());
			vm_dcl_control(pwm_handle,VM_PWM_CMD_START,0);
			setPinHandle(ulPin, pwm_handle);
		}
		
		pwm_config_adv.counter = 1022;
		pwm_config_adv.threshold = ulValue;
		pwm_clock.source_clk = 0;
		pwm_clock.source_clk_div =3;
		vm_dcl_control(pwm_handle,VM_PWM_CMD_SET_CLK,(void *)(&pwm_clock));
		vm_dcl_control(pwm_handle,VM_PWM_CMD_SET_COUNTER_AND_THRESHOLD,(void *)(&pwm_config_adv));
	}
	else if(ulPin == 3)
       {    
		VM_PWM_SET_CLOCK_T pwm_clock;
		VM_PWM_SET_COUNTER_THRESHOLD_T pwm_config_adv;

    		if(!changePinType(ulPin, PIO_PWM, &pwm_handle))
			return;

		if(pwm_handle == VM_DCL_HANDLE_INVALID)
		{
			pwm_handle = vm_dcl_open(VM_DCL_PWM1,vm_dcl_get_ownerid());
			vm_dcl_control(pwm_handle,VM_PWM_CMD_START,0);
			setPinHandle(ulPin, pwm_handle);
		}
		
		pwm_config_adv.counter = 1022;
		pwm_config_adv.threshold = ulValue;
		pwm_clock.source_clk = 0;
		pwm_clock.source_clk_div =3;
		vm_dcl_control(pwm_handle,VM_PWM_CMD_SET_CLK,(void *)(&pwm_clock));
		vm_dcl_control(pwm_handle,VM_PWM_CMD_SET_COUNTER_AND_THRESHOLD,(void *)(&pwm_config_adv));
	}
	else
	{
		pinMode(ulPin, OUTPUT);

		if (ulValue < 128)
			digitalWrite(ulPin, LOW);
		else
			digitalWrite(ulPin, HIGH);
	}

}


void analogWriteAdvance(uint32_t ulPin, uint32_t ulClock, uint32_t ulDiv, uint32_t ulCycle, uint32_t ulDuty )
{
	VM_DCL_HANDLE pwm_handle;
	
	if(ulPin == 9)
	{    
		VM_PWM_SET_CLOCK_T pwm_clock;
		VM_PWM_SET_COUNTER_THRESHOLD_T pwm_config_adv;
		
		if(!changePinType(ulPin, PIO_PWM, &pwm_handle))
			return;
		
		if(pwm_handle == VM_DCL_HANDLE_INVALID)
		{
			pwm_handle = vm_dcl_open(VM_DCL_PWM4,vm_dcl_get_ownerid());
			vm_dcl_control(pwm_handle,VM_PWM_CMD_START,0);
			setPinHandle(ulPin, pwm_handle);
		}
		
		pwm_clock.source_clk = ulClock;
		pwm_clock.source_clk_div = ulDiv;
		pwm_config_adv.counter = ulCycle;
		pwm_config_adv.threshold = ulDuty;
		vm_dcl_control(pwm_handle,VM_PWM_CMD_SET_CLK,(void *)(&pwm_clock));
		vm_dcl_control(pwm_handle,VM_PWM_CMD_SET_COUNTER_AND_THRESHOLD,(void *)(&pwm_config_adv));
	}
	if(ulPin == 3)
	{    
		VM_PWM_SET_CLOCK_T pwm_clock;
		VM_PWM_SET_COUNTER_THRESHOLD_T pwm_config_adv;
		
		if(!changePinType(ulPin, PIO_PWM, &pwm_handle))
			return;
		
		if(pwm_handle == VM_DCL_HANDLE_INVALID)
		{
			pwm_handle = vm_dcl_open(VM_DCL_PWM1,vm_dcl_get_ownerid());
			vm_dcl_control(pwm_handle,VM_PWM_CMD_START,0);
			setPinHandle(ulPin, pwm_handle);
		}
		
		pwm_clock.source_clk = ulClock;
		pwm_clock.source_clk_div = ulDiv;
		pwm_config_adv.counter = ulCycle;
		pwm_config_adv.threshold = ulDuty;
		vm_dcl_control(pwm_handle,VM_PWM_CMD_SET_CLK,(void *)(&pwm_clock));
		vm_dcl_control(pwm_handle,VM_PWM_CMD_SET_COUNTER_AND_THRESHOLD,(void *)(&pwm_config_adv));
	}
}

#ifdef __cplusplus
}
#endif
