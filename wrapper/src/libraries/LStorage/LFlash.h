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


#ifndef _LINKITFLASH_h
#define _LINKITFLASH_h

#include "LStorage.h"

// Class of LinkIt Flash support 
class LFlashClass : public LDrive
{
/* DOM-NOT_FOR_SDK-BEGIN */	
// Constructor / Destructor    
public:
    LFlashClass(void);
    ~LFlashClass(void);
/* DOM-NOT_FOR_SDK-END */	

	// DESCRIPTION
	//  Initialzes the Flash module
	// RETURNS
	//  true if succeed, false if failed
    virtual boolean begin();
    
};

// The global LFlash object. Use it to manipulate Flash
extern LFlashClass LFlash;

#endif

