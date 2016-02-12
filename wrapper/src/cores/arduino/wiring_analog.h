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

#ifndef _WIRING_ANALOG_
#define _WIRING_ANALOG_

#ifdef __cplusplus
extern "C" {
#endif

/* DOM-NOT_FOR_SDK-BEGIN */
/*
 * \brief SAM3 products have only one reference for ADC
 */
typedef enum _eAnalogReference
{
  AR_DEFAULT,
} eAnalogReference ;

#define PWM_SOURCE_CLOCK_13MHZ 0x00
#define PWM_SOURCE_CLOCK_32KHZ 0x01

#define PWM_CLOCK_DIV1 0x00
#define PWM_CLOCK_DIV2 0x01
#define PWM_CLOCK_DIV4 0x02
#define PWM_CLOCK_DIV8 0x03

/*
 * \brief Configures the reference voltage used for analog input (i.e. the value used as the top of the input range).
 * This function is kept only for compatibility with existing AVR based API.
 *
 * \param ulMmode Should be set to AR_DEFAULT.
 */
extern void analogReference( eAnalogReference ulMode ) ;

/*
 * \brief Set the resolution of analogRead return values. Default is 10 bits (range from 0 to 1023).
 *
 * \param res
 */
extern void analogReadResolution(int res);

/*
 * \brief Set the resolution of analogWrite parameters. Default is 8 bits (range from 0 to 255).
 *
 * \param res
 */
extern void analogWriteResolution(int res);

extern void analogOutputInit( void ) ;
/* DOM-NOT_FOR_SDK-END */

 /*****************************************************************************
 * FUNCTION
 *  analogWrite
 * DESCRIPTION
 *  Outputs analog value(PWM wave)to the assigned analog output pin.
 * PARAMETERS
 *  ulPin : [IN] Analog output pin number; 3, 9
 *  ulValue : [IN] duty cycle,0~1023
 * RETURNS
 * void
 * EXAMPLE
 * <code>
 * uint32_t analogPin = 9;
 * void setup()
 * {}
 * void loop()
 * {
 *     analogWrite(analogPin,128);
 * }
 * </code> 
*****************************************************************************/
extern void analogWrite( uint32_t ulPin, uint32_t ulValue );

 /*****************************************************************************
 * FUNCTION
 *  analogWriteAdvance
 * DESCRIPTION
 *  Outputs analog value (PWM wave) to the assigned analog output pin.
 *  Note: Only the analog output pins D3 and D9 support analog output.
 *  You can define your own PWM output wave accuracy (max. 13-bit) and frequency in this function.
 *  The wave accuracy and frequency can be setup by following below steps:
 *      1. Decide accuracy first. If you need 0 ~ N levels, set cycle to N.
 *      2. Next, decide frequency. If cycle = N, sourceClock = PWM_SOURCE_CLOCK_13MHZ and clockDivider = WM_CLOCK_DIV1, the frequency will be 13MHz/(N+1).
 *          if cycle = N, sourceClock = PWM_SOURCE_CLOCK_32KHZ and clockDivider = PWM_CLOCK_DIV8, the frequency will be 32kHz / (8 * (N+1))
 *      3. If the frequency is too high or too low, adjust sourceClock and clockDivider adjust the frequency.
 * PARAMETERS
 *  ulPin : [IN] analog output pin number; 3, 9
 *  ulClock : [IN] define base clock frequency, can be PWM_SOURCE_CLOCK_13MHZ or PWM_SOURCE_CLOCK_32KHZ
 *  ulDiv : [IN] define clock frequency divider, can be PWM_CLOCK_DIV1, PWM_CLOCK_DIV2, PWM_CLOCK_DIV4 or PWM_CLOCK_DIV8
 *  ulCycle : [IN] the cycle, between 0 and 8191
 *  ulDuty : [IN] the duty cycle,between 0 and 8191, but must be smaller than cycle
 * EXAMPLE
 * <code>
 * uint32_t pwmPin = 9;    // use Digital pin D9
 * 
 * int cycle = 9;                      // Divide output into 9+1 = 10 portions
 * int sourceClock = PWM_SOURCE_CLOCK_13MHZ;   //
 * int divider = PWM_CLOCK_DIV8;       // The PWM frequency will be 13MHz / 8 / 10 = 162.5KHz
 * 
 * int duty = 0;
 * int offset = 1;
 * 
 * void setup()
 * {
 *     pinMode(pwmPin, OUTPUT);
 * }
 * 
 * void loop()
 * {
 *     analogWriteAdvance(pwmPin, sourceClock, divider, cycle, duty);
 * 
 *     duty += offset;
 *     if (duty == cycle)
 *     {
 *         offset = -1;
 *     }
 *     else if(duty == 0)
 *     {
 *         offset = 1;
 *     }
 *     delay(1000);
 * }
 * </code> 
*****************************************************************************/
extern void analogWriteAdvance(uint32_t pin, uint32_t sourceClock, uint32_t clockDivider, uint32_t cycle, uint32_t dutyCycle);

/*****************************************************************************
 * FUNCTION
 *  analogRead
 * DESCRIPTION
 *  Reads the value of an specified analog input pin. It will map input votages 0 to 5 volts into integer values 0 to 1023.
 * PARAMETERS
 *  ulPin : [IN] Analog input pin number to be read;A0,A1 or A2
 * RETURNS
 * uint32_t:0 to 1023
 * EXAMPLE
 * <code>
 * uint32_t analogPin = A0;
 * uint32_t readVal = 0;
 * void setup()
 * {
 *     Serial.begin(9600);
 * }
 * void loop()
 * {
 *     readVal = analogRead(analogPin);
 *     Serial.println(readVal);
 * }
 * </code> 
*****************************************************************************/
extern uint32_t analogRead( uint32_t ulPin ) ;

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_ANALOG_ */
