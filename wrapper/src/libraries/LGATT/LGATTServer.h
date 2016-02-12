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


#ifndef __LGATT_SERVER_H__
#define __LGATT_SERVER_H__

#include "LGATT.h"
#include <LGATTUUID.h>

#define MAX_SERVICES 8 // This can be enlarged according to your specified profile.
#define MAX_QUEUE_NODES 40

typedef uint32_t LGATT_PERMISSION; // This represents the permission of the characteristic or descriptor.
                                     
#define LGATT_PERM_READ                   (1 << 0) // The bit 0.
#define LGATT_PERM_READ_ENCRYPTED         (1 << 1) // The bit 1.
#define LGATT_PERM_READ_ENC_MITM          (1 << 2) // The bit 2.
#define LGATT_PERM_WRITE                  (1 << 4) // The bit 3.
#define LGATT_PERM_WRITE_ENCRYPTED        (1 << 5) // The bit 4.
#define LGATT_PERM_WRITE_ENC_MITM         (1 << 6) // The bit 5.
#define LGATT_PERM_WRITE_SIGNED           (1 << 7) // The bit 6.
#define LGATT_PERM_WRITE_SIGNED_MITM      (1 << 8) // The bit 7.

// These represent profile types. To identify your attribute type please refer to LGATTServiceInfo for more information.                      
  
typedef enum
{
    TYPE_UNKNOW = (0),      // This is reserved, do not use.
    TYPE_SERVICE,           // This denotes a service entry in LGATTServiceInfo.
    TYPE_CHARACTERISTIC,    // This denotes a characteristic entry in LGATTServiceInfo.
    TYPE_DESCRIPTOR,        // This denotes a descriptor entry in LGATTServiceInfo.
    TYPE_END                // This denotes the end of the array of LGATTServiceInfo.
} ard_decl_type_enum;


// DESCRIPTION: This is a structure that defines GATT service, characteristic and descriptor.
//   
// A GATT service is defined by an array of LGATTServiceInfo, the first
// array elements must be of type TYPE_SERVICE, followed by elements of
// type TYPE_CHARACTERISTIC or type TYPE_DESCRIPTOR. The last element in
// the array must be of type TYPE_END.
//
// Please see LGATTServerClass.loadService() for more details.          
 typedef struct
{
    ard_decl_type_enum          type; 		 // Type of this entry can be TYPE_SERVICE, TYPE_CHARACTERISTIC, TYPE_DESCRIPTOR, or TYPE_END.
    uint8_t                     uuid[37];  // The UUID string of this entry in canonical form representation, e.g. "123e4567-e89b-12d3-a456-426655440000" plus the terminating NULL character. Please see http://en.wikipedia.org/wiki/Universally_unique_identifier#Definition for details.
    uint8_t                     isprimary; // This entry is valid only if it's type TYPE_SERVICE. Set value to 1 if this service is a primary service of the GATT profile which is discovered by primary service. 
    LGATT_CHAR_PROPERTIES    prop; 				// This is the bit field flag representing properties of a characteristic or descriptor. Multiple properties can be OR-ed. This entry is valid only if it's type TYPE_SERVICE or TYPE_DESCRIPTOR.
    LGATT_PERMISSION         permission;  // This is the bit field flag representing access permissions of this characteristic or descriptor. This entry is valid only if it's tyep TYPE_SERVICE or TYPE_DESCRIPTOR.
    int32_t                     trigged;  // This is reserved and it must be 0.
} LGATTServiceInfo;

/* DOM-NOT_FOR_SDK-BEGIN */
class LGATTData
{
public:
    LGATTData(){}
    ~LGATTData(){}
    void *_srv;
};
/* DOM-NOT_FOR_SDK-END */

// DESCRIPTION:
//     This represents information about a characteristic or a descriptor.
struct LGATTAttributeData : LGATTData
{
    uint16_t handle; // This is the handle of the attribute and it is required in LGATTServer.sendIndication().                            
                    
    LGATTUUID uuid;  // This is the attribute UUID.
                      
    boolean failed;  // This represents if the transaction failed or not.
    LGATTAttributeData() : handle(0), failed(0)
    {
        //memset(this, 0, sizeof(LGATTAttributeData));
    }
};

/* DOM-NOT_FOR_SDK-BEGIN */
// This represents a structure for connection or disconnection.
struct LGATTConnection : LGATTData
{
    LGATTAddress addr; // This is the Bluetooth 4.0 address.
    boolean connected; // This indicates whether it has got a connection or lost a connection.
    LGATTConnection()
    {
        memset(this, 0, sizeof(LGATTConnection));
    }
};

struct LGATTReadRequest;
struct LGATTWriteRequest;

enum gatts_evt
{
    GATTS_EVENT_NONE,
    GATTS_EVENT_ON_CONNETION, 
    GATTS_EVENT_ON_CHAR_ADDED, 
    GATTS_EVENT_ON_DESC_ADDED, 
    GATTS_EVENT_ON_READ, 
    GATTS_EVENT_ON_WRITE 
};

struct gatts_q_node
{
    int32_t evt; 
    void *service; 
    LGATTData *data; 
    gatts_q_node(){}
    gatts_q_node(gatts_evt e, void *s);
    ~gatts_q_node();
};
/* DOM-NOT_FOR_SDK-END */

// This class inherits and implements callbacks to define a GATT service.
class LGATTService : public _LTaskClass 
{   
    friend boolean gattServiceRemoteCallHandler(void *userdata);
    friend class LGATTServerClass;
    friend class GATTServer;
    friend class GATTService;
    enum
    {
        ACTION_BEGIN,
        ACTION_SEND,
        ACTION_SEND_ACK,
        ACTION_END,
    };
    
// This class represents the constructor.
public:
      /* DOM-NOT_FOR_SDK-BEGIN */
    LGATTService();
    virtual ~LGATTService();
    /* DOM-NOT_FOR_SDK-END */
    
// Method
public:

      /* DOM-NOT_FOR_SDK-BEGIN */
      
    boolean begin(const LGATTUUID &uuid, int32_t index, int32_t timeout = 20);
    void end();
    // DESCRIPTION:
    //    This class sends ACK to the central device and it must be called in onRead/onWrite.
    // PARAMETERS
    //    value: Attribute value, refer to LGATTAttributeValue
    //    attr_handle: attribute handle 
    //    failed: ACK to Central, confirm to Central if the data has been properly received. 
    //    trans_id: Current transaction id. Refer to LGATTWriteRequest or LGATTReadRequest
    // RETURNS
    //    true: success
    //    false: fail
      boolean sendResponse(const LGATTAttributeValue &value, uint16_t attr_handle, boolean failed, uint16_t trans_id); 
    
    /* DOM-NOT_FOR_SDK-END */
    
    // DESCRIPTION: 
    // 		This function sends notifications or indications to central device.
    // PARAMETERS
    //    value :        Attribute value, refer to LGATTAttributeValue 
    //    attr_handle :  Attribute handle that is passed in
    //                   onCharacteristicAdded() 
    //    needConfirm :  Asks Central for a response if it is set to true. For a
    //                   protocol if it is set to true it means indication, for
    //                   false - notify.
    // RETURNS
    //    true: success
    //    false: fail                                                        
    boolean sendIndication(const LGATTAttributeValue &value, uint16_t attr_handle, boolean needConfirm);

protected:
    // DESCRIPTION:
    //    You need to override this method in order to define a GATT service.
    //    This function is called immediately upon calling LGATTServer.begin(),
    //    and it must return an array of LGATTServiceInfo beginning
    //    with the type TYPE_SERVICE, followed by elements of TYPE_CHARACTERISTIC or 
    //    TYPE_DESCRIPTOR, and it must be terminated with an element of TYPE_END.
    // PARAMETERS
    //    index: The index of this object in LGATTServer.begin(). For example, 
    //           LGATTServer.begin(2, &serviceA, &serviceB)
    //           the loadService() of serviceA will receive 0 as index, while serviceB receives 1 as index.
    //      
    // RETURNS
    //    Pointer pointing to the beginning of an array of LGATTServiceInfo. This array must be valid until LGATTServerClass.end() is called.
    //    Returning NULL will fail LGATTServer.begin().
      // EXAMPLE
      //        <code>
    //            static LGATTServiceInfo g_my_gatt_service[] =
    //            {
    //                {TYPE_SERVICE, "6e400001-b5a3-f393-e0a9-e50e24dcca9e", TRUE, 0, 0, 0},
    //                {TYPE_CHARACTERISTIC, "6e400002-b5a3-f393-e0a9-e50e24dcca9e", FALSE, VM_GATT_CHAR_PROP_WRITE, VM_GATT_PERM_WRITE, 0},
    //                {TYPE_CHARACTERISTIC, "6e400003-b5a3-f393-e0a9-e50e24dcca9e", FALSE, VM_GATT_CHAR_PROP_NOTIFY | VM_GATT_CHAR_PROP_INDICATE, VM_GATT_PERM_READ, 0},
    //                {TYPE_DESCRIPTOR, "00002902-0000-1000-8000-00805f9b34fb", FALSE, VM_GATT_CHAR_PROP_NOTIFY, VM_GATT_PERM_READ | VM_GATT_PERM_WRITE, 0},
    //                {TYPE_END, 0, 0, 0, 0, 0}
    //            };
    //
    //            LGATTServiceInfo *LGATTUT::loadService(int32_t index)
    //            {
    //                return g_my_gatt_service;
    //            }
    //         </code>
    //    This defines a service of UUID 6e400001-b5a3-f393-e0a9-e50e24dcca9e with two characteristics and one descriptor.
    //    This array must be valid until LGATTServerClass.end() is called, therefore you should avoid getting a return of an array declared in the local scope.
    //    It is recommended to return a globally, statically defined array like the example above instead.
    virtual LGATTServiceInfo *onLoadService(int32_t index) = 0;
    
    // DESCRIPTION:
    //    You need to override this function to receive handles for each characteristic when
    //    characteristics are added.
    // PARAMETERS
    //    data: Information of the characteristic added. Refer to LGATTAttributeData.
    // RETURNS
    //    true: success
    //    false: fail
    virtual boolean onCharacteristicAdded(LGATTAttributeData &data);
    
    // DESCRIPTION:
    //    You need to override this method to receive handles for each descriptor when
    //    descriptors are added.
    // PARAMETERS
    //    data: Information of the descriptor added. Refer to LGATTAttributeData.
    // RETURNS
    //    true: success
    //    false: fail
    virtual boolean onDescriptorAdded(LGATTAttributeData &data);
    
    // DESCRIPTION:
    //    This function is called when the state of connections from the central device has changed.
    // PARAMETERS
    //    addr: The address of the central device. Refer to LGATTAddress.
    //    connected: true means a connection has established, false means the central device has disconnected.
    // RETURNS
    //    true: success
    //    false: fail
    virtual boolean onConnection(const LGATTAddress &addr, boolean connected);

    // DESCRIPTION:
    //    You need to override this method to handle a read request coming from central device.
    //    Always respond to the request by calling request.ackOk() or request.ackFail()
    //    before this function returns. Otherwise it will lead to an undefined behavior.
    // PARAMETERS
    //    request: An object representing the read request. Refer to LGATTReadRequest.
    // RETURNS
    //    true: success
    //    false: fail
    virtual boolean onRead(LGATTReadRequest &request);

    // DESCRIPTION:
    //    You need to override this method to handle a write action coming from the central device.
    //    You may store sendData or ACK after onRead() returns,
    //    Always respond the write request by calling ackOK() and ackFail() 
    //    before this function returns. Otherwise it will lead to an undefined behavior.
    // PARAMETERS
    //    request: refer to LGATTWriteRequest
    // RETURNS
    //    true: success
    //    false: fail
    virtual boolean onWrite(LGATTWriteRequest &request);

private:

    void *_gatts_srv_ctx;             // The gatts_srv_ctx_t.
    LGATTServiceInfo *_gatts_service; // The current service.
    
    // The current action.
    uint8_t _action;
    boolean _result;

    // The uuid.
    uint8_t _uuid[16];

    // The data.
    LGATTAttributeValue *_value;
    boolean _confirm_failed;
    uint16_t _attr_handle;
    uint16_t _trans_id;
    
    
};

// You can use the LGATTServer singleton macro to access its methods instead of instantiating this class directly.                    
 class LGATTServerClass : _LTaskClass
{
    friend boolean gattServerRemoteCallHandler(void *userdata);
    friend class GATTServer;
    enum
    {
        ACTION_BEGIN,
        ACTION_END,
        ACTION_HANDLE_EVENTS,
    };
// Method
public:
    // DESCRIPTION: 
    //     This function initializes Bluetooth 4.0 module and sets up a profile. 
    // PARAMETERS
    //    service_nums :  Number of services of your profile.
    //    ...: Objects of LGATTService
    // RETURNS
    //    true: success
    //    false: fail
    // Example
    // <code>
    // #include <LGATTSUart.h>
    // #include <LGATTSABC.h>
    // LGATTSUart uart;
    // LGATTUT abc;
    // 
    // void setup() {
    //   // put your setup code here, to run once:
    //   LGATTServer.begin(2, &uart, &abc);
    // }
    // </code>                                                                    
    boolean begin(int32_t service_nums, ...);
    
    // DESCRIPTION: 
    //     This function ejects the attached Bluetooth 4.0 peripherals, frees the resources and stops firing Bluetooth 4.0 events.
    // RETURNS
    //     None                                                                 
    void end();
    
    // DESCRIPTION: 
    //   This function handles events for Bluetooth 4.0, it will work through all the request that have been added to the event queue.
    //   You can override LGATTService if you need to get a corresponding event.
    // RETURNS
    //    None
    // Example
    //  <code>
    // #include <LGATTSUart.h>
    // #include <LGATTSABC.h>
    //   
    //  LGATTSUart uart;
    //  LGATTUT abc;
    // 
    //  void setup() {
    //    // put your setup code here, to run once:
    //    LGATTServer.begin(g_gatts_uuid, 2, &uart, &abc);
    //  }
    // 
    //  void loop() {
    //   // put your main code here, to run repeatedly:
    //   delay(1000);
    //   LGATTServer.handleEvents();
    // }
    // </code>                                                                  
    void handleEvents();
    
    /* DOM-NOT_FOR_SDK-BEGIN */
    static LGATTServerClass &getServer();
    /* DOM-NOT_FOR_SDK-END */  
private:
    // The message queue.   
    boolean enQ(gatts_q_node *node);
    boolean deQ();
    gatts_q_node *frQ();
    gatts_q_node *_cq[MAX_QUEUE_NODES];
    int32_t _fr, _ba;
    uint32_t _size;

    LGATTServerClass();
    virtual ~LGATTServerClass();
    
    // This function indicates it has delegated the services. 
    LGATTService *_gatts_service[MAX_SERVICES];
    boolean _result;

    // This function represents the current action.     
    uint8_t _action;

    // The singleton.  
    static LGATTServerClass *_server;

};

// This class represents a read request from the central device.
// It also provides method to send the attribute value back to the central device.
class LGATTReadRequest : public LGATTData
{
public:

    uint16_t trans_id;      // This function represents the transaction ID.                       
    LGATTAddress bd;        // This function represents the Bluetooth 4.0 address.                       
    uint16_t attr_handle;   // The function represents the attribute handle.                            
    uint16_t offset;        // This function offsets into the data buffer, in bytes. For example, if
                            // the characteristic is 20 bytes long and the central device requests a
                            // 10 bytes offset, then the service should call ackOk with value buffer
                            // starting with buffer[10].                                            
                              
    /* DOM-NOT_FOR_SDK-BEGIN */
    LGATTReadRequest()
    {
        memset(this, 0, sizeof(LGATTReadRequest));
    }
        /* DOM-NOT_FOR_SDK-END */
        
        // You can call this method in onRead() and callback to fail the read request.
    boolean ackFail()
    {
        // sendAck(fail)      
        LGATTAttributeValue value;
        value.len = 0;
        return ((LGATTService *)_srv)->sendResponse(value, this->attr_handle, 1, this->trans_id); // ACK
    }

        // You can call this method in onRead() and callback to send the value of the attribute
        // back to central device.
    boolean ackOK(const LGATTAttributeValue &value)
    {
        return ((LGATTService *)_srv)->sendResponse(value, this->attr_handle, 0, this->trans_id); // ACK
    }
}; 

// This class represents a write request from central device.
// It also provides method to send the write operation result to the central device.
class LGATTWriteRequest : public LGATTData
{
public:
    uint16_t trans_id;           // The transaction ID.                               
    LGATTAddress bd;             // The Bluetooth 4.0 address.                                   
    uint16_t attr_handle;        // The attribute handle.                                 
    LGATTAttributeValue value;   // The attribute value of the central device.                               
    uint16_t offset;             // This offsets the data buffer from the central device.                                   
    boolean need_rsp;            // This indicates whether it is required to respond to remote device or not.                                                                
                                   
    
    /* DOM-NOT_FOR_SDK-BEGIN */
    LGATTWriteRequest()
    {
        memset(this, 0, sizeof(LGATTWriteRequest));
    }
    /* DOM-NOT_FOR_SDK-END */
    
    // You can call this method in onWrite() and callback to respond a failed result to central device.
    boolean ackFail()
    {
        // The sendAck(fail)      
        LGATTAttributeValue value;
        value.len = 0;
        return ((LGATTService *)_srv)->sendResponse(value, this->attr_handle, 1, this->trans_id); // ACK
    }

    // You can call this method in onWrite() and callback to respond a success result to central device.
    boolean ackOK()
    {
        // The sendAck(OK)
        LGATTAttributeValue value;
        value.len = 0;
        return ((LGATTService *)_srv)->sendResponse(value, this->attr_handle, 0, this->trans_id); // ACK
    }

};

// You can use the LGATTServer singleton to access GATT server's functionality.
#define LGATTServer LGATTServerClass::getServer()

#endif

