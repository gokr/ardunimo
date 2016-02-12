/*
  Copyright (c) 2014 MediaTek Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License.

  This library is distributed with hope that it will be useful,
  but WITHOUT ANY WARRANTY or the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU Lesser General Public License for more details.
*/


#ifndef __LGATT_H__
#define __LGATT_H__

#include <Arduino.h>
#include "LTask.h"
#include "vmlog.h"

//#define PARAM_HEAD \
//    void *reg_ctx; \
//    void *conn_ctx
//
//
//struct PARAM_OUT
//{
//    PARAM_HEAD;
//    
//};

/* DOM-NOT_FOR_SDK-BEGIN */

#define GATTS_REMOTE_CALL(a, f, d) \
    _action = a; \
    remoteCall(f, d)

#define REMOTE_RETURN(s, ret) \
    s->_result = ret; \
    s->post_signal()

#define SRV_CTX(s) \
    ((gatts_srv_ctx_t *)s->_gatts_srv_ctx)

/* DOM-NOT_FOR_SDK-END */
    
typedef uint32_t LGATT_CHAR_PROPERTIES; /***********************************************************************
                                          * This represents the characteristic properties or the descriptor. The
                                          * meaning of each bit in this property is defined by bit-flag, i.e.
                                          * LGATT_CHAR_PROP_READ, LGATT_CHAR_PROP_EXT, etc.                     
                                          ***********************************************************************/
#define LGATT_CHAR_PROP_BROADCAST         0x01 /****************************************************************
                                                 * The bit position in LGATT_CHAR_PROPERTIES that represents the
                                                 * broadcast.                                                   
                                                 ****************************************************************/
#define LGATT_CHAR_PROP_READ              0x02 /*********************************************************************
                                                 * The bit position in LGATT_CHAR_PROPERTIES that represents the Read
                                                 *********************************************************************/
#define LGATT_CHAR_PROP_WRITE_WO_RESPONSE 0x04 /****************************************************************************
                                                 * The bit position in LGATT_CHAR_PROPERTIES that represents the &quot;Write
                                                 * Without Response&quot;.                                                  
                                                 ****************************************************************************/
#define LGATT_CHAR_PROP_WRITE             0x08 /***********************************************************************
                                                 * The bit position in LGATT_CHAR_PROPERTIES that represents the Write.
                                                 ***********************************************************************/
#define LGATT_CHAR_PROP_NOTIFY            0x10 /************************************************************************
                                                 * The bit position in LGATT_CHAR_PROPERTIES that represents the Notify.
                                                 ************************************************************************/
#define LGATT_CHAR_PROP_INDICATE          0x20 /**************************************************************************
                                                 * The bit position in LGATT_CHAR_PROPERTIES that represents the Indicate.
                                                 **************************************************************************/
#define LGATT_CHAR_PROP_SIGNED_WRITE      0x40 /***********************************************************************
                                                 * The bit position in LGATT_CHAR_PROPERTIES that represents the Signed
                                                 * Write.                                                              
                                                 ***********************************************************************/
#define LGATT_CHAR_PROP_EXT               0x80 /****************************************************************
                                                 * The bit position in LGATT_CHAR_PROPERTIES that represents the
                                                 * extension.                                                   
                                                 ****************************************************************/


#define LGATT_BD_ADDR_SIZE 6 // This is the address size of a Bluetooth 4.0 device.
#define LGATT_ATT_MAX_VALUE_LEN 23 // This is the attribute MTU and it is the maximum number of bytes that a single read and write operation can transmit. If the characteristic is more than 23 bytes, then offset must be used in onRead() and onWrite().

// This represents address structure for Bluetooth 4.0 devices.
typedef struct
{
    uint8_t addr[LGATT_BD_ADDR_SIZE]; // Address of a Bluetooth 4.0 device. The structure of the address represents a 12-digit hexadecimal value.
}LGATTAddress;

// This represents value of a GATT attribute.
typedef struct
{
    uint16_t len; // This is the valid length of the value array. The maximum length of the value array is LGATT_ATT_MAX_VALUE_LEN in bytes.
    uint8_t value[LGATT_ATT_MAX_VALUE_LEN]; // The array of attribute value.
}LGATTAttributeValue;

/* DOM-NOT_FOR_SDK-BEGIN */
#if defined(__LINKIT_ONE_DEBUG__)
//#define APP_LOG(...) Serial.printf(__VA_ARGS__); \
//    Serial.println();
#define APP_LOG(...) vm_log_debug(__VA_ARGS__);
#else
#define APP_LOG(...)
#endif
/* DOM-NOT_FOR_SDK-END */

#endif
