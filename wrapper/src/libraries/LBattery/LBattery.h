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


#ifndef _LBATTERY_H
#define _LBATTERY_H

#include "LTask.h"


// LBattery class interface, With this library, you can get battery infomation like charging status and battery level
class LBatteryClass  : public _LTaskClass {

// Constructor / Destructor
public:
	LBatteryClass() { };

// Method
public:
	// DESCRIPTION
	//     Get the level of the attached battery. The return value may be 0, 33, 66, 100
	// RETURNS
	//     Percentage of battery level
	int level();
	
	// DESCRIPTION
	//     Charging or not.
	// RETURNS
	//     true: in charging state, false: not in charging state
	boolean isCharging();

private:
	int m_level;
	boolean m_charging;
};

extern LBatteryClass LBattery;

#endif
