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

#ifndef _WIRING_
#define _WIRING_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 */
extern void init( void ) ;

/*****************************************************************************
 * FUNCTION
 *  millis
 * DESCRIPTION
 *  Time from returning to LinkIt to enable the current program to the present(unit:ms).
 * PARAMETERS
 *  none
 * RETURNS
 * uint32_t:Time from LinkIt enabling the current program to the present in ms.
 * EXAMPLE
 * <code>
 * uint32_t t;
 * void setup()
 * {
 * 
 * }
 * void loop()
 * {
 *     t = millis();
 *     delay(2000);
 * }
 * </code> 
*****************************************************************************/
extern uint32_t millis( void ) ;

/*****************************************************************************
 * FUNCTION
 *  micros
 * DESCRIPTION
 *  Time from returning to LinkIt to enable the current program to the present(unit:us)
 * PARAMETERS
 *  none
 * RETURNS
 * uint32_t:Time from LinkIt enabling the current program to the present in us.
 * EXAMPLE
 * <code>
 * uint32_t t;
 * void setup()
 * {
 * 
 * }
 * void loop()
 * {
 *     t = micros();
 *     delay(2000);
 * }
 * </code> 
*****************************************************************************/
extern uint32_t micros( void ) ;

/*****************************************************************************
 * FUNCTION
 *  delay
 * DESCRIPTION
 *  Pauses the program by setting up parameter to designate time to pause(unit:ms)
 * PARAMETERS
 *  dwMs: Time to pause in ms
 * EXAMPLE
 * <code>
 * int led = 13;
 * void setup()
 * {
 *     pinMode(led,OUTPUT);
 * }
 * void loop()
 * {
 *     digitalWrite(led,HIGH);
 *     delay(1000);
 *     digitalWrite(led,LOW);
 *     delay(1000);
 * }
 * </code> 
*****************************************************************************/
extern void delay( uint32_t dwMs ) ;

/*****************************************************************************
 * FUNCTION
 *  delayMicroseconds
 * DESCRIPTION
 *  Pauses the program by setting up parameter to designate time to pause(unit:us)
 * PARAMETERS
 *  usec: Time to pause in us
 * EXAMPLE
 * <code>
 * int led = 13;
 * void setup()
 * {
 *     pinMode(led,OUTPUT);
 * }
 * void loop()
 * {
 *     digitalWrite(led,HIGH);
 *     delayMicroseconds(1000);
 *     digitalWrite(led,LOW);
 *     delayMicroseconds(1000);
 * }
 * </code> 
*****************************************************************************/
void delayMicroseconds(uint32_t usec);

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_ */
