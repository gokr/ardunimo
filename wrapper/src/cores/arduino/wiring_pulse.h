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

#ifndef _WIRING_PULSE_
#define _WIRING_PULSE_

#ifdef __cplusplus
 extern "C" {
#endif

#include <avr/pgmspace.h>
 
//DESCRIPTION
// Duration of acquiring voltage (HIGH or LOW) of a pin. The accuracy is us; range is approx. 10us to 3 mins.
//EXAMPLE
// <code>
// #define BUTTON   13
// unsigned long duration;
// void setup()
// {
//     pinMode(BUTTON, INPUT);
// }
// void loop()
// {
//     duration = pulseIn(BUTTON, HIGH);
// }
// </code> 
uint32_t pulseIn(
  uint32_t ulPin,     // [IN] Pin number measured
  uint32_t ulState,   // [IN] Voltage type measured (HIGH or LOW)
  uint32_t ulTimeout = 1000000L  // [IN] The longest time allowed by the function before the measurement starts; unit: us (If not set, default will be 1s.)
  ) ;


#ifdef __cplusplus
}
#endif

#endif /* _WIRING_PULSE_ */
