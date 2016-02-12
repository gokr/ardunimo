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


#ifndef __LGATT_CLIENT_H__
#define __LGATT_CLIENT_H__

#include "LGATT.h"
#include "LTask.h"
#include <LGATTUUID.h>

#define MAX_GATT_CLIENT 10
#define MAX_BLE_SERCHED_DEV 10
#define MAX_BLE_SERVICES 20


/* DOM-NOT_FOR_SDK-BEGIN */

// This represents the Bluetooth 4.0 device's UUID structure.
typedef struct 
{
   uint8_t uu[16]; // The UUID array.
}lgatt_uuid_struct;


typedef enum {
    LGATTC_STATUS_DISABLED = 0, // This represents it's not connected.
    LGATTC_STATUS_ENABLING,     // This represents it's connecting.
    LGATTC_STATUS_ENABLED,      // This represents it's connected.
    LGATTC_STATUS_DISABLING,    // This represents it's disconnecting.
}lgatt_client_status;

typedef struct
{
    LGATTUUID _serviceUUID;
    boolean   _isPrimary;
    LGATTUUID _charUUID;
    LGATTAttributeValue _attrValue;
}lgatt_notification_data;

// This represents the Bluetooth 4.0 GATT client context structure.
typedef struct
{
    void *reg_ctx; 							// The register context.
    void *conn_ctx; 						// The connection context.
    lgatt_client_status state;  // The connection status.
    lgatt_uuid_struct uuid;     // The device UUID.
    uint32_t _searched_ble_dev_nums;
    uint32_t _timeout;
    LGATTAddress _address;
    
    LGATTUUID _currServiceUUID;
    boolean   _isPrimary;
    LGATTUUID _currCharUUID;
    LGATTUUID _currDescUUID;
    LGATTAttributeValue _currAttrValue;
    boolean _isEnableNotification;
    int32_t _tid;
    lgatt_notification_data _currNotificationData;
}lgatt_client_cntx;


// This represents the Bluetooth 4.0 GATT client operation result.
typedef enum
{
    LGATT_STATUS_SUCCESS= 0, // The represents success.
    LGATT_STATUS_FAILED = 1, // This represents failed.
}lgatt_os_status;


// This represents the Bluetooth 4.0 connection context structure.
typedef struct
{
    void *reg_ctx;  // The register context.
    void *conn_ctx; // The connection context.
}lgatt_conn_struct;

// This represents the Bluetooth 4.0 GATT UUID structure.
typedef struct
{
    uint8_t len;      // The length of GATT UUID.
    uint8_t uuid[16]; // The UUID array.
}lgatt_bt_uuid;

// This represents the Bluetooth 4.0 GATT attribute structure.
typedef struct
{
    lgatt_bt_uuid uuid; // The Bluetooth 4.0 GATT UUID.
    uint8_t inst;       // The instance ID.
}lgatt_att_uuid;

// This represents the Bluetooth 4.0 service context structure.
typedef struct
{
    lgatt_att_uuid uuid; // The Bluetooth 4.0 attribute.
    uint8_t is_primary; // The primary flag.
}lgatt_svc_uuid;

// This represents the Bluetooth 4.0 GATT characteristic structure.
typedef struct
{
    lgatt_svc_uuid svc_uuid; // The Bluetooth 4.0 service context.
    lgatt_att_uuid ch_uuid; // The Bluetooth 4.0 attribute context.
}lgatt_char_struct;

// This represents the Bluetooth 4.0 GATT descriptor structure.
typedef struct
{
    lgatt_svc_uuid svc_uuid;   // The Bluetooth 4.0 service context. 
    lgatt_att_uuid ch_uuid;    // The Bluetooth 4.0 characteristic context.
    lgatt_att_uuid descr_uuid; // The Bluetooth 4.0 descriptor context.
}lgattc_descr_struct;


// This represents the Bluetooth 4.0 GATT register callback structure.
typedef struct
{
    lgatt_os_status *status;     // The register result.
    lgatt_uuid_struct *app_uuid; // The service device UUID.
}lgatt_register_client_struct;

// This represents the Bluetooth 4.0 GATT connection callback structure.
typedef struct
{
    boolean connected;    // The connection result.
    LGATTAddress bd_addr; // The service device address.
}lgatt_connection_struct;

// This represents the Bluetooth 4.0 GATT search complete callback structure.
typedef struct
{
    lgatt_os_status status; // The search result.
}lgatt_search_complete_struct;

// This represents the Bluetooth 4.0 GATT search result callback structure.
typedef struct
{
    lgatt_svc_uuid uuid[MAX_BLE_SERVICES]; // The Bluetooth 4.0 service context.
    int32_t service_uuid_num;              // The number of Bluetooth 4.0 service.
}lgatt_search_result_struct;

// This represents the Bluetooth 4.0 GATT get characteristic callback structure.
typedef struct
{
    lgatt_os_status status;           // The result of get characteristic.
    lgatt_char_struct ch;             // The content of characteristic.
    lgatt_att_uuid start_char_uuid;   // The Bluetooth 4.0 attribute context.
    LGATT_CHAR_PROPERTIES properties; // The properties of GATT characteristic.
}lgatt_get_characteristic_struct;


// This represents the Bluetooth 4.0 GATT get descriptor callback structure.
typedef struct
{
    lgatt_os_status status;    // The result of get descriptor.
    lgattc_descr_struct descr; // The content of descriptor.
    lgatt_att_uuid start_descr_uuid;
}lgatt_get_descriptor_struct;

// This represents the Bluetooth 4.0 GATT read characteristic callback structure.
typedef struct
{
    lgatt_os_status status;    // The result of read characteristic.
    lgatt_char_struct ch;      // The content of characteristic.
    LGATTAttributeValue value; // The attribute value.
}lgatt_read_characteristic_struct;

// This represents the Bluetooth 4.0 GATT write characteristic callback structure.
typedef struct
{
    lgatt_os_status *status;    // The result of write characteristic.
    lgatt_char_struct *ch;      // The content of characteristic.
    LGATTAttributeValue *value; // The attribute value.
}lgatt_write_characteristic_struct;


// This represents the Bluetooth 4.0 GATT read descriptor callback structure.
typedef struct
{
    lgatt_os_status status;    // The result of read descriptor.
    lgattc_descr_struct descr; // The content of descriptor.
    LGATTAttributeValue value; // The attribute value.
}lgatt_read_descriptor_struct;


// This represents the Bluetooth 4.0 GATT write descriptor callback structure
typedef struct
{
    lgatt_os_status *status;    // The result of write descriptor.
    lgattc_descr_struct *descr; // The content of descriptor.
    LGATTAttributeValue *value; // The attribute value.
}lgatt_write_descriptor_struct;


// This represents the Bluetooth 4.0 GATT read remote rssi callback structure.
typedef struct
{
    lgatt_os_status status; // The result of read remote rssi.
    LGATTAddress bd_addr;   // The service device address.
    int32_t rssi;           // The rssi value.
}lgatt_read_remote_rssi_struct;

// This represents the Bluetooth 4.0 GATT callback functions structure.
typedef struct
{
    // This represents the Bluetooth 4.0 connection context structure.
    lgatt_conn_struct conn;
    
    // This represents the Bluetooth 4.0 GATT register callback.
    //lgatt_register_client_struct register_client;

    // This represents the Bluetooth 4.0 GATT connection callback.
    lgatt_connection_struct connection;

    // This represents the Bluetooth 4.0 GATT search complete callback.
    lgatt_search_complete_struct search_complete;

    // This represents the Bluetooth 4.0 GATT search result callback.
    lgatt_search_result_struct search_result;

    // This represents the Bluetooth 4.0 GATT get characteristic callback.
    lgatt_get_characteristic_struct characteristic;

    // This represents the Bluetooth 4.0 GATT get descriptor callback.
    lgatt_get_descriptor_struct descriptor;

    // This represents the Bluetooth 4.0 GATT read characteristic callback.
    lgatt_read_characteristic_struct read_characteristic;

    // This represents the Bluetooth 4.0 GATT write characteristic callback.
    //lgatt_write_characteristic_struct write_characteristic;

    // This represents the Bluetooth 4.0 GATT read descriptor callback.
    lgatt_read_descriptor_struct read_descriptor;

    // This represents the Bluetooth 4.0 GATT write descriptor callback.
    //lgatt_write_descriptor_struct write_descriptor;

    // This represents the Bluetooth 4.0 GATT read remote rssi callback.
    lgatt_read_remote_rssi_struct read_remote_rssi;

}lgatt_callback_data_struct;

/* DOM-NOT_FOR_SDK-END */

//  This represents the information of a remote Bluetooth 4.0 peripheral device.
typedef struct
{
    LGATTAddress bd_addr; // Address of Bluetooth 4.0 device.
    int32_t rssi;         // Received signal strength indication.
    uint8_t eir_len;      // Length of equipment identity register.
    uint8_t eir[256];         // Content of equipment identity register.
}LGATTDeviceInfo;

//   You can use this class to read and write GATT attributes and receive notifications.
//	 This class instantiates an object to scan for nearby Bluetooth 4.0 peripheral devices.
//   It also provides functionality to connect to one Bluetooth 4.0 peripheral device
//   and enumerate all the GATT service the peripheral device provides.
//   
class LGATTClient : public _LTaskClass
{   
public:
    // This function represents the constructor.
     
    LGATTClient();
    
    // This represents the Destructor.
     
    virtual ~LGATTClient(){}

    // Description: This function initializes Bluetooth 4.0 GATT Client.
    // Parameters
    //    uuid :  The reference of LGATTUUID object.
    // Returns
    //    true:  success
    //    false: failure
    // \EXAMPLE                                                         
    boolean begin(const LGATTUUID& uuid);

    // DESCRIPTION
    //    The LGATTClient scan function scans for Bluetooth 4.0 devices. The maximum number of
    //    Bluetooth 4.0 devices that can be captured by the scan function is 10. The
    //    scan function will return an integer value indicating the number of devices scanned or 
    //    a timeout message, which ever comes first.
    // PARAMETERS
    //    timeout: The timeout value in seconds
    // RETURNS
    //    The number of Bluetooth 4.0 devices that have been capture by scan().
    //    The max is 10.
    // EXAMPLE
    //    <code>
    //    int32_t numOfDevice = scan(20); // timeout is set to 10 seconds.
    //    </code> 
    int32_t scan(uint32_t timeout);

    
    // Description: This function retrieves the device information from the scan result.
    // Parameters
    //    index:  This is the index of the scanned devices and ranges from 0 to
    //            scan() - 1.<p /> 
    //    info :  The object reference of LGATTDeviceInfo.
    // Returns
    //    true:  success
    //    false: failure
    // Example
    //  
    // <code>
    //   LGATTDeviceInfo info;
    //   boolean ret = getScanResult(1, info);
    //</code>                                                               
    boolean getScanResult(int index,
                          LGATTDeviceInfo& info
                         ); 

    // Description: This function connects to a Bluetooth 4.0 device.
    // Parameters
    //    deviceAddress :  The Bluetooth 4.0 address to be connected to.
    // Returns
    //    true:  success
    //    false: failure
    // Example
    // 
    // <code>
    //    LGATTAddress address;
    //    address.addr[0] = 0x0A;
    //    address.addr[1] = 0x1B;
    //    address.addr[2] = 0x2C;
    //    address.addr[3] = 0x3D;
    //    address.addr[4] = 0x4E;
    //    address.addr[5] = 0x5G;
    //    boolean ret = connect(address);
    // </code>                                                       
    boolean connect(const LGATTAddress& deviceAddress);

    // Description: This function disconnects from a Bluetooth 4.0 device.
    // Parameters
    //    deviceAddress :  The address of a Bluetooth 4.0 device.
    // Returns
    //    true:  success
    //    false: failure
    // Example
    // 
    // <code>
    //    LGATTAddress address;
    //    address.addr[0] = 0x0A;
    //    address.addr[1] = 0x1B;
    //    address.addr[2] = 0x2C;
    //    address.addr[3] = 0x3D;
    //    address.addr[4] = 0x4E;
    //    address.addr[5] = 0x5G;
    //    boolean ret = disconnect(address);
    // </code>                                                            
    boolean disconnect(const LGATTAddress& deviceAddress);

    // Description: This function enables or disables notifications.
    // Parameters
    //    enable :             If it is true, enable the notification; or disable the notification if enable is false. 
    //    serviceUUID :        The UUID of the service provided by a Bluetooth 4.0 devices. 
    //    isPrimary :          It specifies if this service is primary. 
    //    characteristicUUID : The UUID of characteristic.
    // Returns
    //    true:  success
    //    false: failure
    // Example
    // 
    // <code>
    //    None
    // </code>                                                                 
    boolean setupNotification(boolean enableOrNot, 
                               const LGATTUUID& serviceUUID, 
                               boolean isPrimary, 
                               const LGATTUUID& characteristicUUID
                              );
    

    // Description: This function queries the attribute value from the notification of a connected Bluetooth 4.0 device.
    // Parameters
    //    serviceUUID :       The UUID of the service provided by a Bluetooth 4.0 device. 
    //    isPrimary :         It specifies if this service is primary.
    //    characteristicUUID :The UUID of characteristic. 
    //    value :             The attribute value of current notification.
    // Returns
    //    true:  success
    //    false: failure
    // Example
    // 
    // <code>
    //    None
    // </code>                                                                  
    boolean queryNotification(const LGATTUUID& serviceUUID, 
                              boolean isPrimary, 
                              const LGATTUUID& characteristicUUID,
                              LGATTAttributeValue& value
                             );

    // Description: This function gets number of services provided by a connected Bluetooth 4.0 device.
    // Returns
    //    uint32_t: The number of services.                            
    uint32_t getServiceCount();
        
    // Description: This function gets the information of a service.
    // Parameters
    //     index :        The index of services. The max is the return value of getServiceCount(). 
    //     serviceUUID :  The UUID of the service provided by a Bluetooth 4.0 device. 
    //     isPrimary :    It indicates if this service is primary.
    // Returns
    //     true:  success
    //     false: failure
    // Example
    // 
    // <code>
    //    None
    // </code>
    // int getCharacteristicNumber(const LGATTUUID &amp;serviceUUID, boolean isPrimary);
    boolean getServiceInfo(int index, 
                           LGATTUUID& serviceUUID, 
                           boolean& isPrimary
                          );
        
    // Description: This function gets the information of a characteristic.
    // Parameters
    //    serviceUUID :         The UUID of the service provided by a Bluetooth 4.0 device. 
    //    isPrimary :           It specifies if this service is primary. 
    //    characteristicUUID :  The UUID of the characteristic. 
    //    properties :          The properties of the specified characteristic, please refer to LGATT_CHAR_PROPERTIES.
    // Returns
    //    true:  success
    //    false: failure
    // Example
    //  
    // <code>
    // None
    // </code>                                                              
    boolean getCharacteristicInfo(const LGATTUUID& serviceUUID, 
                                  boolean isPrimary, 
                                  LGATTUUID& characteristicUUID, 
                                  LGATT_CHAR_PROPERTIES& properties
                                 );

    // Description: This function gets the descriptor from a specified characteristic.
    // Parameters
    //    serviceUUID :         The UUID of the service provided by a Bluetooth 4.0 device. 
    //    isPrimary :           It specifies if this service is primary. 
    //    characteristicUUID :  The UUID of the characteristic. 
    //    descriptorUUID :      The uuis of the descriptor.
    // Returns
    //    true:  success
    //    false: fail
    // Example
    // 
    // <code>
    // None
    // </code>                                                              
    boolean getDescriptorInfo(const LGATTUUID& serviceUUID, 
                              boolean isPrimary, 
                              const LGATTUUID& characteristicUUID,
                              LGATTUUID& descriptorUUID 
                             );

    // Description: This function reads the service characteristic provided by a Bluetooth 4.0 device.
    // Parameters
    // serviceUUID :         The UUID of the service provided by a Bluetooth 4.0 device.<p /> 
    // isPrimary :           It specifies if this service is primary.<p /> 
    // characteristicUUID :  The UUID of the characteristic.<p /> 
    // attrValue :           The attribute value, which is obtained from the remote Bluetooth 4.0 device if succeed.
    // Returns
    //    true:  success
    //    false: failure
    // Example
    //
    // <code>
    //    None
    // </code>                                                                
    boolean readCharacteristic(const LGATTUUID& serviceUUID,
                               boolean isPrimary, 
                               const LGATTUUID& characteristicUUID,
                               LGATTAttributeValue& attrValue);

    
    // Description: This function writes the service characteristic provided by a Bluetooth 4.0 device.
    // Parameters
    //    serviceUUID :         The UUID of the service provided by a Bluetooth 4.0 device. 
    //    isPrimary :           It specifies if this service is primary.
    //    characteristicUUID :  The UUID of the characteristic. 
    //    attrValue :           The attribute value, which is written to the remote Bluetooth 4.0 device if succeed.
    // Returns
    //    true:  success
    //    false: failure
    // Example
    // 
    // <code>
    //    None
    // </code>                                                              
    boolean writeCharacteristic(const LGATTUUID& serviceUUID,
                                boolean isPrimary, 
                                const LGATTUUID& characteristicUUID,
                                const LGATTAttributeValue& attrValue);

    // Description: This function reads the descriptor from the service provided by a Bluetooth 4.0 device.
    // Parameters
    //    serviceUUID :         The UUID of the service provided by a Bluetooth 4.0 device. 
    //    isPrimary :           It specifies if this service is primary. 
    //    characteristicUUID :  The UUID of the characteristic. 
    //    descriptorUUID :      The UUID of the descriptor. 
    //    attrValue :           The attribute value, which is obtained from the remote Bluetooth 4.0 device if succeed.
    // Returns
    //    true:  success
    //    false: failure
    // Example
    // 
    // <code>
    //    None
    // </code>                                                              
    boolean readDescriptor(const LGATTUUID& serviceUUID,
                           boolean isPrimary, 
                           const LGATTUUID& characteristicUUID,
                           const LGATTUUID& descriptorUUID,
                           LGATTAttributeValue& attrValue);

    // Description: This function writes the descriptor to a service.
    // Parameters
    //    serviceUUID :         The UUID of the service provided by a Bluetooth 4.0 device. 
    //    isPrimary :           It specifies if this service is primary. 
    //    characteristicUUID :  The UUID of the characteristic. 
    //    descriptorUUID :      The UUID of the descriptor. 
    //    attrValue :           The attribute value, which is written to the remote Bluetooth 4.0 device if succeed.
    // Returns
    //    true:  success
    //    false: failure
    // Example
    // 
    // <code>
    //    Please refer to the example of begin().
    // </code>                                                              
    boolean writeDescriptor(const LGATTUUID& serviceUUID,
                            boolean isPrimary, 
                            const LGATTUUID& characteristicUUID,
                            const LGATTUUID& descriptorUUID,
                            const LGATTAttributeValue& attrValue);
    
    // Description: This function reads the signal strength of the remote device.
    // Parameters
    //    address :  The address of the remote device, which could be obtained during the scan. 
    //    rssi :     The signal strength of the remote device.
    // Returns
    //    true:  success
    //    false: failure
    // Example
    // 
    // <code>
    //    None
    // </code>                                                             
    boolean readRemoteRSSI(const LGATTAddress &address, int32_t& rssi);

    // DESCRIPTION
    //    When this function is called, it will turn off the Bluetooth and release the resources (memory) occupied by the LGATT Client object.
    // RETURNS
    //    true:  success
    //    false: failure
    // EXAMPLE
    //    <code>
    //       None.
    //    </code> 
    boolean end();
    
    /* DOM-NOT_FOR_SDK-BEGIN */
    lgatt_callback_data_struct cb_data;
    lgatt_client_cntx _cntx;
    boolean _return_value;
    int32_t scan_ret;
    /* DOM-NOT_FOR_SDK-END */
};


#endif
