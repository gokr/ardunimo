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

#ifndef _WIRING_MATH_
#define _WIRING_MATH_

/*****************************************************************************
 * <GROUP Core_Math>
 * FUNCTION
 *    map
 * DESCRIPTION
 *   Re-maps a number from one range to another. 
 *   That is, a value of fromLow would get mapped to toLow, a value of fromHigh to toHigh, values in-between to values in-between, etc. 
 * PARAMETERS
 *   value: the number to map 
 *   fromLow: the lower bound of the value's current range 
 *   fromHigh: the upper bound of the value's current range 
 *   toLow: the lower bound of the value's target range 
 *   toHigh: the upper bound of the value's target range 
 * RETURNS
 *   The mapped value. 
 * RETURN VALUES  
 *   long
 *****************************************************************************/
extern long map(long value, long fromLow, long fromHigh, long toLow, long toHigh);

/*****************************************************************************
 * FUNCTION
 *    random
 * DESCRIPTION
 *   The random function generates pseudo-random numbers. 
 * PARAMETERS
 *   max: upper bound of the random value, exclusive 
 * RETURNS
 *   a random number limit to max-1 (long) 
 * RETURN VALUES  
 *  long
 *****************************************************************************/
extern long random(long max) ;

/*****************************************************************************
 * FUNCTION
 *    random
 * DESCRIPTION
 *   The random function generates pseudo-random numbers. 
 * PARAMETERS
 *   min: lower bound of the random value, inclusive (optional) 
 *   max: upper bound of the random value, exclusive 
 * RETURNS
 *   a random number between min and max-1 (long) 
 * RETURN VALUES  
 *  long
 *****************************************************************************/
extern long random(long min, long max) ;

/*****************************************************************************
 * FUNCTION
 *    randomSeed
 * DESCRIPTION
 *   randomSeed() initializes the pseudo-random number generator, causing it to start at an arbitrary point in its random sequence. 
 * PARAMETERS
 *   dwSeed: pass a number to generate the seed. 
 * RETURNS
 *   no returns 
 * RETURN VALUES
 *  long
 *****************************************************************************/
extern void randomSeed( uint32_t dwSeed ) ;

extern uint16_t makeWord( uint16_t w ) ;
extern uint16_t makeWord( uint8_t h, uint8_t l ) ;

#define word(...) makeWord(__VA_ARGS__)


#endif /* _WIRING_MATH_ */
