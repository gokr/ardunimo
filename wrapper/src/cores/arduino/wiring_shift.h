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

#ifndef _WIRING_SHIFT_
#define _WIRING_SHIFT_

#ifdef __cplusplus
 extern "C" {
#endif

//DESCRIPTION
// Reads data of a byte by bits on the assigned pin. 
// Every bit of data is read from the data pin. 
// You can select to combine the read 8-bit data into a byte from MSB or LSB. 
// Every clock cycle (meaning the clock goes through a complete high voltage and low voltage) reads a bit of data; every bit of data is read when the clock signal is at high voltage.
//RETURNS
// Data read (one byte)
//EXAMPLE
// <code>
// #define DATA  13
// #define CLOCK 15
// void setup()
// {
//     pinMode(DATA, INPUT);
//     pinMode(CLOCK, OUTPUT);
// }
// void loop()
// {
//     byte data;
//     data = shiftIn(DATA, CLOCK, LSBFIRST);
//     delay(1000);
// }
// </code> 
extern uint32_t shiftIn(
  uint32_t ulDataPin,  // [IN] Data input pin, for reading every bit of data
  uint32_t ulClockPin, // [IN] Clock pin. Periodically switches between high voltage and low voltage when dataPin outputs data
  uint32_t ulBitOrder  // [IN] Data input order. Can be MSBFIRST (MSB first) or LSBFIRST (LSB first)
   ) ;


//DESCRIPTION
// Outputs a byte of data by bits on the assigned pin. 
// Every bit of data is outputted from the data pin. 
// You can select to start output from MSB or LSB of the data. 
// Every clock cycle (meaning the clock goes through a complete high voltage and low voltage) outputs a bit of data.
//EXAMPLE
// <code>
// #define DATA  13
// #define CLOCK 15
// void setup()
// {
//     pinMode(DATA, INPUT);
//     pinMode(CLOCK, OUTPUT);
// }
// void loop()
// {
//     shiftOut(DATA, CLOCK, LSBFIRST, 100);
//     delay(1000);
// }
// </code> 
extern void shiftOut(
  uint32_t ulDataPin,   // [IN] Data output pin, for outputting every bit of data
  uint32_t ulClockPin,  // [IN] Clock pin. Periodically switches between high voltage and low voltage when dataPin outputs data
  uint32_t ulBitOrder,  // [IN] Data output order. Can be MSBFIRST (MSB first) or LSBFIRST (LSB first)
  uint32_t ulVal        // [IN] Value to be outputted by bits (one byte)
  ) ;


#ifdef __cplusplus
}
#endif

#endif /* _WIRING_SHIFT_ */
