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


#ifndef __GATT_UUID_H__
#define __GATT_UUID_H__
#include "LGATT.h"
#include <Printable.h>
#include "vmbtgatt.h"

// This class facilitates handling UUIDs used by LGATTClient, LGATTServerClass and LGATTService classes.
class LGATTUUID : public Printable {

public:
    // Description: This function represents the default constructor that creates an invalid UUID.                                          
   
    LGATTUUID();

    // Description: This function represents the constructor that initializes a LGATTUUID object from 16-bit Bluetooth UUIDs.
    // Parameters
    //    uuid :  The 16-bit UUID in Bluetooth specifications, e.g. 0x1810 for blood Pressure Service. Please see
    //            https://www.bluetooth.org/en-us/specification/assigned-numbers for assigned 16-bit UUIDs.                                     
    LGATTUUID(uint16_t uuid);

    // Description: This function represents the constructor that initializes a LGATTUUID object from 128-bit uuid strings.
    // Parameters
    //    uuid :  The UUID string in canonical form, e.g.&quot;9D6EB1F1-F16D-5B84-5640-E5FF491FA020&quot;.         
    LGATTUUID(const char *uuid);

    // Description: This function represents an overloaded comparison operator to compare two UUID objects.                                           
    bool operator==(const LGATTUUID& uuid) const;

    // Description: This function represents an overloaded comparison operator to compare an UUID object to a canonical form UUID string.             
    bool operator==(const char *uuid) const;

    // Description: This function represents an overloaded index operator to allow getting and setting individual octets of the UUID.
    // Parameters
    //    index :  Index into elements of the raw UUID bytes.                  
    uint8_t operator[](int index) const;

    // Description: This function represents an overloaded index operator to allow getting and setting individual octets of the UUID.
    // Parameters
    // index :  Index into elements of the raw UUID bytes.                  
    uint8_t& operator[](int index);

    // Description: This function represents an overloaded assignment operators to allow initialization of LGATTUUID objects from 128-bit uuid strings.
    // Parameters
    //    uuid :  The UUID string in canonical form, e.g.&quot;9D6EB1F1-F16D-5B84-5640-E5FF491FA020&quot;.
    // Example
    // <code>
    //   LGATTUUID customUUID;
    //   customUUID = &quot;9D6EB1F1-F16D-5B84-5640-E5FF491FA020&quot;;
    // </code>                                                            
    LGATTUUID& operator=(const char *uuid);

    // Description: This function represents an overloaded assignment operators to allow initialization of LGATTUUID objects from 16-bit Bluetooth UUIDs.
    // Parameters
    //    uuid :  The 16-bit UUID in Bluetooth specifications, e.g. 0x1810 for blood Pressure Service. Please see https://www.bluetooth.org/en-us/specification/assigned-numbers
    //            for assigned 16-bit UUIDs.
    // Example
    // <code>
    //    LGATTUUID bloodPressureUUID;
    //    customUUID = 0x1810;
    // </code>                                                                
    LGATTUUID& operator=(uint16_t uuid);

    /* DOM-NOT_FOR_SDK-BEGIN */
    LGATTUUID(const VM_BT_UUID &uuid);
    const VM_BT_UUID* operator&() const { return &_uuid; }
    LGATTUUID& operator=(const VM_BT_UUID &uuid);
    virtual size_t printTo(Print& p) const;
    /* DOM-NOT_FOR_SDK-END */
private:
    void str2uuid(uint8_t *uuid_dst, const char *uuid) const;

    VM_BT_UUID _uuid;
};

#endif /* __GATT_UUID_H__ */

