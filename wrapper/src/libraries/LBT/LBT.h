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
#ifndef LBT_H
#define LBT_H

#if defined(__LINKIT_ONE_DEBUG__)
#define LBT_DEBUG
#endif

#include <Arduino.h>
#include "LTask.h"
#include "vmbtcm.h"
#include <stdint.h>

#define LBT_DEVICE_NAME_LENGTH  56

#define LBT_PIN_CODE_BUFFER_SIZE (20)

struct BTBase
{
    _LTaskClass *ptr;
};

struct LBTAddress
{
	uint8_t lap[3];
	uint8_t uap;
	uint8_t nap[2];
};

typedef struct
{
	LBTAddress address;
	char name[56];
} LBTDeviceInfo;

#define LBT_SERIAL_BUFFER_SIZE (1024*6)

class LBTRingBuffer
{
  public:
    uint8_t _aucBuffer[LBT_SERIAL_BUFFER_SIZE] ;
    int _iHead ;
    int _iTail ;

  public:
    LBTRingBuffer( void ) ;
    void store_char( uint8_t c ) ;
} ;
#endif //#ifndef LBT_H
