/*
 * digital I/O for Arduino Due
 * Copyright (c) 2011 Cristian Maglie <c.maglie@bug.st>.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Modified 20 Aug 2014 by MediaTek Inc.
 */
#ifndef _WIRING_DIGITAL_
#define _WIRING_DIGITAL_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

//DESCRIPTION
// Sets up modes for assigned pins.
//
// There are 16 pins on LinkIt ONE used as digital I/O, they are D0 ~ D13 
// and D18/D19, particularly D18/D19 are shared with Wire/I2C.
//
//
//
// LinkIt One supports 3 pin modes:
//
//  * INPUT mode is used for reading voltage (HIGH or LOW) or sensor. In INPUT mode when 
//    the circuit is at high impedance, similar to serially connecting a big resistance in 
//    the circuit, the pin can read accurate voltage value. However, this pin may not have 
//    enough voltage to activate peripheral devices, e.g. LED.
//  * INPUT_PULLUP mode is similar to INPUT mode, used for reading voltage of sensor. However 
//    in this mode, the pin is often at high voltage when the sensor is disabled and turns to 
//    low voltage when the sensor is enabled, which is opposite to its behavior in INPUT mode.
//  * OUTPUT mode is used for controlling peripheral devices. In OUTPUT mode when the circuit 
//    is at low impedance, the pin has enough voltage to activate or control other devices but 
//    cannot read the voltage of sensor.
//
//EXAMPLE
// <code>
// #define LED  13
// void setup()
// {
//     pinMode(LED, OUTPUT);
// }
// void loop()
// {
//     digitalWrite(LED, HIGH);
//     delay(3000);
//     digitalWrite(LED, LOW);
//     delay(3000);
// }
// </code> 
extern void pinMode(
  uint32_t dwPin,   // [IN] Pin number that needs to be set with a mode
  uint32_t dwMode   // [IN] Mode of pin (INPUT, INPUT_PULLUP or OUTPUT)
  ) ;

//DESCRIPTION
// Sets assigned pins to high voltage (3.3V) or low voltage (0V).
//
// There are 16 pins on LinkIt ONE used as digital I/O, they are D0 ~ D13 and D18/D19, particularly D18/D19 are shared with Wire/I2C.
//EXAMPLE
// <code>
// #define LED  13
// void setup()
// {
//     pinMode(LED, OUTPUT);
// }
// void loop()
// {
//     digitalWrite(LED, HIGH);
//     delay(3000);
//     digitalWrite(LED, LOW);
//     delay(3000);
// }
// </code> 
extern void digitalWrite(
  uint32_t dwPin,   // [IN] Pin number that needs to be set with a value
  uint32_t dwVal    // [IN] HIGH or LOW
   ) ;
 
//DESCRIPTION
// Reads voltage of assigned pin, HIGH or LOW.
//
// There are 16 pins on LinkIt ONE used as digital I/O, they are D0 ~ D13 and D18/D19, particularly D18/D19 are shared with Wire/I2C.
//RETURNS
// HIGH or LOW
//EXAMPLE
// <code>
// #define LED     13
// #define BUTTON  8
// void setup()
// {
//     pinMode(LED, OUTPUT);
//     pinMode(BUTTON, INPUT);
// }
// void loop()
// {
//     int n= digitalRead(BUTTON);
//     if (n == HIGH)
//     {
//         digitalWrite(LED, LOW);
//     }
//     else
//     {
//         digitalWrite(LED, HIGH);
//     }
//     delay(2000);
// }
// </code> 
extern int digitalRead( 
  uint32_t ulPin   // [IN] Pin number that needs to read voltage
  ) ;

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_DIGITAL_ */
