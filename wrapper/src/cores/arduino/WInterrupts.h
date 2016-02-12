/*
  Copyright (c) 2014 MediaTek Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License..

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU Lesser General Public License for more details.
*/


#ifndef _WIRING_INTERRUPTS_
#define _WIRING_INTERRUPTS_

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

// Definitions Interrupt callback type
typedef void (*callback_ptr)(void);

/*****************************************************************************
* FUNCTION
 *    attachInterrupt
 * DESCRIPTION
 *  Sets up Interrupt Service Routine (ISR).
 *  When an interrupt arrives, the ISR will be called automatically. This interrupt service cannot preempt execution. 
 *  When the next interrupt arrives, it will wait for ISR to finish the previous interrupt before its execution starts. 
 *  There are two external interrupts on LinkIt One development board, interrupt 0 (at pin 2) and interrupt 1 (at pin 3). 
 * PARAMETERS
 *  pin       :         [IN]      Interrupt id, should be 0, and 1; 0 corresponds to pin2 (D2), 1 corresponds to pin3 (D3).
 *  callback  :        [IN]      Interrupt callback
 *  mode       :     [IN]      Interrupt trigger mode, it should be RISING/FALLING/CHANGE
 * Example
 * <code>
 *
 * int pin = 13;
 * volatile int state = LOW;
 *  
 * void setup()
 * {
 *   pinMode(pin, OUTPUT);
 *   attachInterrupt(0, blink, RISING);
 * }
 *  
 * void loop()
 * {
 *   digitalWrite(pin, state);
 * }
 *  
 * void blink()
 * {
 *   state = !state;
 * }
 *
 * </code>
 *****************************************************************************/
void attachInterrupt(uint32_t pin, callback_ptr callback, uint32_t mode);

/*****************************************************************************
* FUNCTION
 *    detachInterrupt
 * DESCRIPTION
 *  Disables ISR.
 * PARAMETERS
 *  pin       :         [IN]      Interrupt id, should be 0, and 1
 *****************************************************************************/
void detachInterrupt(uint32_t pin);

/*****************************************************************************
 * <GROUP Core_Int>
 * FUNCTION
 *    interrupts
 * DESCRIPTION
 *  Enables interrupt (after it is disabled by noInterrupts()).
 *  By default, interrupts make some essential tasks executed in background. Disabling interrupts 
 *  will make some communication functions unable to work normally and external interaction ignored. 
 *  Therefore, please pay particular attention when using this function and enable the interrupt again as soon as possible
 * Example
 * <code>
 *
 * void setup() {}
 *  
 * void loop()
 * {
 *   noInterrupts();
 *   // critical, time-sensitive code here
 *   interrupts();
 *   // other code here
 * }
 *
 * </code>
 *****************************************************************************/
void interrupts(void);


/*****************************************************************************
 * <GROUP Core_Int>
 * FUNCTION
 *    noInterrupts
 * DESCRIPTION
 *  Disables interrupt (which can be enabled again by interrupts()).
 *****************************************************************************/
void noInterrupts(void );

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_INTERRUPTS_ */
