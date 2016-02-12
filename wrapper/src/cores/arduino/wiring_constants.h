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

#ifndef _WIRING_CONSTANTS_
#define _WIRING_CONSTANTS_

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/* DOM-NOT_FOR_SDK-BEGIN */
#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#ifndef C2NIM
#define true 0x1
#define false 0x0
#endif

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886   //弧度转角度
#define RAD_TO_DEG 57.295779513082320876798154814105  //角度转弧度
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

enum BitOrder {
	LSBFIRST = 0,
	MSBFIRST = 1
};

//      LOW 0
//      HIGH 1
#define CHANGE 2
#define FALLING 3
#define RISING 4

#define DEFAULT 1
#define EXTERNAL 0

// The following should instead fall back on Nim's stdlib
#ifndef C2NIM

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif // abs
/* DOM-NOT_FOR_SDK-END */

#ifndef min
/*****************************************************************************
 * <GROUP Core_Math>
 * FUNCTION
 *    min
 * DESCRIPTION
 *  Calculates the minimum of two numbers. 
 * PARAMETERS
 *  x: the first number, any data type 
 *  y: the second number, any data type 
 * RETURNS
 *  The smaller of the two numbers. 
 * RETURN VALUES  
 *  depend on input value
 *****************************************************************************/
#define min(a,b) ((a)<(b)?(a):(b))
#endif // min

#ifndef max
/*****************************************************************************
 * <GROUP Core_Math>
 * FUNCTION
 *    max
 * DESCRIPTION
 *  Calculates the maximum of two numbers. 
 * PARAMETERS
 *  x: the first number, any data type 
 *  y: the second number, any data type 
 * RETURNS
 *  The larger of the two numbers. 
 * RETURN VALUES  
 *  depend on input value
 *****************************************************************************/
#define max(a,b) ((a)>(b)?(a):(b))
#endif // max

/*****************************************************************************
 * <GROUP Core_Math>
 * FUNCTION
 *    abs
 * DESCRIPTION
 *  Computes the absolute value of a number. 
 * PARAMETERS
 * x: the number 
 * RETURNS
 *  x: if x is greater than or equal to 0. 
 * -x: if x is less than 0. 
 * RETURN VALUES  
 *  depend on input value
 *****************************************************************************/
#define abs(x) ((x)>0?(x):-(x))

/*****************************************************************************
 * <GROUP Core_Math>
 * FUNCTION
 *    constrain
 * DESCRIPTION
 *  Constrains a number to be within a range. 
 * PARAMETERS
 * x: the number to constrain, all data types 
 * a: the lower end of the range, all data types 
 * b: the upper end of the range, all data types 
 * RETURNS
 * x: if x is between a and b 
 * a: if x is less than a 
 * b: if x is greater than b 
 * RETURN VALUES  
 *  depend on input value
 *****************************************************************************/
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

/* DOM-NOT_FOR_SDK-BEGIN */
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))    //四舍五入
#define radians(deg) ((deg)*DEG_TO_RAD)  // 角度转弧度
#define degrees(rad) ((rad)*RAD_TO_DEG)  //弧度转角度
#define sq(x) ((x)*(x))  //平方


/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
 * FUNCTION
 *  lowByte
 * DESCRIPTION
 *  Extracts the high-order (leftmost) byte of a word (or the second lowest byte of a larger data type). 
 * PARAMETERS
 *  x: a value of any type 
 * RETURNS
 *  byte 
 * RETURN VALUES  
 *  depend on input value
 *****************************************************************************/
#define lowByte(w) ((uint8_t) ((w) & 0xff)) 

/*****************************************************************************
 * FUNCTION
 *  highByte
 * DESCRIPTION
 *  Extracts the high-order (leftmost) byte of a word (or the second lowest byte of a larger data type). 
 * PARAMETERS
 *  x: a value of any type 
 * RETURNS
 *  byte
 * RETURN VALUES  
 *  depend on input value
 *****************************************************************************/
#define highByte(w) ((uint8_t) ((w) >> 8)) 

/*****************************************************************************
 * FUNCTION
 *  bitRead
 * DESCRIPTION
 *  Reads a bit of a number. 
 * PARAMETERS
 *  x: the number from which to read 
 *  n: which bit to read, starting at 0 for the least-significant (rightmost) bit 
 * RETURNS
 *  the value of the bit (0 or 1). 
 * RETURN VALUES  
 *  depend on input value
 *****************************************************************************/
#define bitRead(value, bit) (((value) >> (bit)) & 0x01) 

/*****************************************************************************
 * FUNCTION
 *  bitSet
 * DESCRIPTION
 *  Sets (writes a 1 to) a bit of a numeric variable. 
 * PARAMETERS
 *  x: the numeric variable whose bit to set 
 *  n: which bit to set, starting at 0 for the least-significant (rightmost) bit 
 * RETURNS
 *  none 
 *****************************************************************************/
#define bitSet(value, bit) ((value) |= (1UL << (bit)))

/*****************************************************************************
 * FUNCTION
 *  bitClear
 * DESCRIPTION
 *  Clears (writes a 0 to) a bit of a numeric variable. 
 * PARAMETERS
 *  x: the numeric variable whose bit to clear 
 *  n: which bit to clear, starting at 0 for the least-significant (rightmost) bit 
 * RETURNS
 *  none 
 *****************************************************************************/
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))

/*****************************************************************************
 * FUNCTION
 *  bitWrite
 * DESCRIPTION
 *  Writes a bit of a numeric variable. 
 * PARAMETERS
 *  x: the numeric variable to which to write 
 *  n: which bit of the number to write, starting at 0 for the least-significant (rightmost) bit 
 *  b: the value to write to the bit (0 or 1) 
 * RETURNS
 *  the value of the bit 
 * RETURN VALUES  
 *  depend on input value
 *****************************************************************************/
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

/* DOM-NOT_FOR_SDK-BEGIN */
typedef unsigned int word;
/* DOM-NOT_FOR_SDK-END */

/*****************************************************************************
 * FUNCTION
 *  bit
 * DESCRIPTION
 *  Computes the value of the specified bit (bit 0 is 1, bit 1 is 2, bit 2 is 4, etc.).  
 * PARAMETERS
 *  b: the bit whose value to compute 
 * RETURNS
 *  the value of the bit 
 * RETURN VALUES  
 *  depend on input value
 *****************************************************************************/
#define bit(b) (1UL << (b))

#define _BV(bit) (1 << (bit))

/* DOM-NOT_FOR_SDK-BEGIN */
// TODO: to be checked
typedef uint8_t boolean ;
typedef uint8_t byte ;
/* DOM-NOT_FOR_SDK-END */

#endif

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* _WIRING_CONSTANTS_ */
