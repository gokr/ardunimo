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

#ifdef __cplusplus
extern "C" {
#endif

boolean no_interrupt = 1;

uint32_t millis( void )
{
// todo: ensure no interrupts
    return vm_get_tick_count() ;
}

// Interrupt-compatible version of micros
// Theory: repeatedly take readings of SysTick counter, millis counter and SysTick interrupt pending flag.
// When it appears that millis counter and pending is stable and SysTick hasn't rolled over, use these 
// values to calculate micros. If there is a pending SysTick, add one to the millis counter in the calculation.
uint32_t micros( void )
{
	return vm_ust_get_current_time(); 
}

// original function:
// uint32_t micros( void )
// {
//     uint32_t ticks ;
//     uint32_t count ;
// 
//     SysTick->CTRL;
//     do {
//         ticks = SysTick->VAL;
//         count = GetTickCount();
//     } while (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk);
// 
//     return count * 1000 + (SysTick->LOAD + 1 - ticks) / (SystemCoreClock/1000000) ;
// }


void delay( uint32_t ms )
{
    vm_thread_sleep(ms);
}

void delayMicroseconds(uint32_t usec){
   VMUINT32 timeStop; 
   VMUINT32 timeStart; 
   VMUINT32 Freq = 0; 
    
    timeStart = vm_ust_get_current_time(); 
    while( Freq  < usec) 
    { 
        timeStop = vm_ust_get_current_time();
        Freq = timeStop - timeStart + 1;
    }
}
void interrupts(void)
{
    no_interrupt = 1;
}

void noInterrupts(void )
{
    no_interrupt = 0;
}

boolean noStopInterrupts(void)
{
	return no_interrupt;
}

#ifdef __cplusplus
}
#endif
