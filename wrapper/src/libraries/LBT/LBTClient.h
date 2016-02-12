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

#ifndef LBTCLIENT_H
#define LBTCLIENT_H

#include "LTask.h"
#include "LBT.h"

struct LBTClientBeginContext : BTBase
{
    void* name;
    boolean result;
    LBTClientBeginContext():
        name(NULL),
        result(false)
    {

    }
};

struct LBTClientConnectContext : BTBase
{
    LBTAddress* address;
    boolean result;
    boolean is_set_pin;
    LBTClientConnectContext():
        address(NULL),
        result(false)
    {

    }
};

struct LBTClientScanContext : BTBase
{
    size_t time_out;
    size_t number;

    LBTClientScanContext():
        time_out(20),
        number(0)
    {

    }
};

struct LBTClientGetDeviceInfoContext : BTBase
{
    size_t index;
    LBTDeviceInfo* device_info;
    boolean result;

    LBTClientGetDeviceInfoContext():
        index(0),
        device_info(NULL),
        result(false)
    {

    }
};

struct LBTClientReadWriteContext : BTBase
{
    void *buf;
    VMUINT len;
    VMINT lenProcessed;	// bytes read or written

	LBTClientReadWriteContext():
		buf(NULL),
		len(1),
		lenProcessed(0)
	{

	}
};


// LBTClient class interface
class LBTClientClass  : public _LTaskClass, public Stream {

public:
	LBTRingBuffer *_rx_buffer;
	uint8_t _pincode_buffer[LBT_PIN_CODE_BUFFER_SIZE];
// Constructor
public:
	LBTClientClass(LBTRingBuffer* pRx_buffer);

// Method
public:

    // DESCRIPTION
    //    init BT module and setup a SPP client instance
    // RETURNS
    //    true: success
    //    false: fail
	// EXAMPLE
	// <code>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else 
    //   {
    //       Serial.println("Bluetooth Client begin successfully");
    //   }
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
    boolean begin(void);

    // DESCRIPTION
    //    close corresponding SPP client instance and end BT module
    // RETURNS
    //    None
	// EXAMPLE
	// <code>
    // #include <LBTClient.h>
    //       
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // don't do anything else
    //       while(true);
    //   } 
    //   else
    //   {
    //       Serial.println("Bluetooth Client begin successfully");
    //   }
    //  
    //   LBTClient.end();
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
    void end(void);

    // DESCRIPTION
    //    connect SPP server with BT address
    // PARAMETERS
    //    address: refer to LBTAddress type
    //    pinCode: BT2.0 pincode, if you set it as const string, LinkOne can communicate BT2.0 device.
    // RETURNS
    //    true: success
    //    false: fail
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begin successfully");
    //       // start scan, at most scan 15 seconds
    //       int num = LBTClient.scan(15);
    //  
    //       if(num > 0)
    //       {
    //           LBTDeviceInfo info = {0};
    //           if( LBTClient.getDeviceInfo(0, &info) )
    //           {
    //               bool conn_result = LBTClient.connect(info.address);//bool conn_result = LBTClient.connect(info.address, "1234");
    //               if( !conn_result )
    //               {
    //                   Serial.println("Cannot connect to Spp Server successfully");
    //                   // don't do anything else
    //                   while(true);
    //               }
    //               else
    //               {
    //                  Serial.println("Connect to Spp Server successfully");
    //               }
    //           }
    //           else
    //           {
    //               Serial.println("Device index not correct");
    //               // don't do anything else
    //               while(true);
    //           }
    //       } 
    //   }
    // }
	// </code> 
    boolean connect(
            LBTAddress &address,  //[IN] BT address to connect
            const char* pinCode = NULL //[IN] BT2.0 set pincode
        );

    // DESCRIPTION
    //    connect SPP server with BT address on spencified BT address
    // PARAMETERS
    //    MACAddr: string format (const char *), the format is like "12:34:56:ab:cd:ef".
    //    pinCode: BT2.0 pincode, if you set it as const string, LinkOne can communicate BT2.0 device.
    // RETURNS
    //    true: success
    //    false: fail
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begin successfully");
    //       // start scan, at most scan 15 seconds
    //       int num = LBTClient.scan(15);
    //  
    //       if(num > 0)
    //       {
    //           LBTDeviceInfo info = {0};
    //           bool conn_result = LBTClient.connect("12:34:56:ab:cd:ef");//bool conn_result = LBTClient.connect("12:34:56:ab:cd:ef", "1234");
    //           if( !conn_result )
    //           {
    //               Serial.println("Cannot connect to Spp Server successfully");
    //               // don't do anything else
    //               while(true);
    //           }
    //           else
    //           {
    //              Serial.println("Connect to Spp Server successfully");
    //           }
    //       } 
    //   }
    // }
	// </code> 
    boolean connect(
            const char *MACAddr,  //[IN] BT address to connect
            const char* pinCode = NULL //[IN] BT2.0 set pincode
        );
    // DESCRIPTION
    //    check if any SPP server is conneccted
    // RETURNS
    //    true: yes
    //    false: no
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //      
    // LBTDeviceInfo info = {0};
    //  
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begin successfully");
    //       // start scan, at most scanned 15 seconds
    //       int num = LBTClient.scan(15);
    //  
    //       if(num > 0)
    //       {
    //           if( LBTClient.getDeviceInfo(0, &info) )
    //           {
    //               Serial.println("Get device info of interested server");
    //           }
    //           else
    //           {
    //               Serial.println("Device index not correct");
    //               // don't do anything else
    //               while(true);
    //           }
    //       }
    //   }
    // }
	// </code> 
    boolean connected(void);

    // DESCRIPTION
    //    scan BT devices around, at most scanned 10 devices
    // RETURNS
    //    number of devices scanned
	// EXAMPLE
	// <code>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begin successfully");
    //       // start scan, at most scanned 15 seconds
    //       int num = LBTClient.scan(15);
    //       Serial.print("Scaned Device number:");
    //       Serial.println(num);
    //   }
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
    int scan(
            size_t time_out = 20   // [IN] time out duration in seconds of the scan process
        );

    // DESCRIPTION
    //    get scanned device information
    // RETURNS
    //    true: success
    //    false : fail. Possible reasons are index not reasonable or never scanned before
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begin successfully");
    //       // start scan, at most scanned 15 seconds
    //       int num = LBTClient.scan(15);
    //       Serial.print("Scaned Device number:");
    //       Serial.println(num);
    //  
    //       for(int i = 0; i < num; ++i)
    //       {
    //           LBTDeviceInfo info = {0};
    //           bool success = LBTClient.getDeviceInfo(i, &info);
    //           if( success )
    //           {
    //               Serial.print("Device");
    //               Serial.println(i);
    //               Serial.print("   name:");
    //               Serial.println(info.name);
    //           }        
    //       }
    //   }
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
	boolean getDeviceInfo(
            size_t index,    // [IN] device index of the scanned result
            LBTDeviceInfo* dev_info    // [OUT] device info acquired
        );

    // DESCRIPTION
    //    read data from SPP server
    // RETURNS
    //    number of bytes read
    //    0 for no data to read
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begin successfully");
    //       // start scan, at most scanned 15 seconds
    //       int num = LBTClient.scan(15);
    //  
    //       if(num > 0)
    //       {
    //           LBTDeviceInfo info = {0};
    //           if( LBTClient.getDeviceInfo(0, &info) )
    //           {
    //               bool conn_result = LBTClient.connect(info.address);
    //               if( !conn_result )
    //               {
    //                   Serial.println("Cannot connect to Spp Server successfully");
    //                   // don't do anything else
    //                   while(true);
    //               }
    //               else
    //               {
    //                  Serial.println("Connect to Spp Server successfully");
    //               }
    //           }
    //           else
    //           {
    //               Serial.println("Device index not correct");
    //               // don't do anything else
    //               while(true);
    //           }
    //       }
    //   }
    // }
    //  
    // void loop()
    // {
    //     char buffer[10];
    //     int read_size = LBTClient.read((uint8_t*)buffer, 10);
    //     if(read_size > 0)
    //     {
    //         Serial.print("size read: ");
    //         Serial.println(read_size);
    //         Serial.println(buffer);
    //     }
    // }
	// </code> 

        int read(void);

    // DESCRIPTION
    //    write data to SPP server
    // RETURNS
    //    number of bytes written
    //    0 for no buffer to write
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTClient.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTClient.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Client successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Client begin successfully");
    //       // start scan, at most scanned 15 seconds
    //       int num = LBTClient.scan(15);
    //  
    //       if(num > 0)
    //       {
    //           LBTDeviceInfo info = {0};
    //           if( LBTClient.getDeviceInfo(0, &info) )
    //           {
    //               bool conn_result = LBTClient.connect(info.address);
    //               if( !conn_result )
    //               {
    //                   Serial.println("Cannot connect to Spp Server successfully");
    //                   // don't do anything else
    //                   while(true);
    //               }
    //               else
    //               {
    //                  Serial.println("Connect to Spp Server successfully");
    //               }
    //           }
    //           else
    //           {
    //               Serial.println("Device index not correct");
    //               // don't do anything else
    //               while(true);
    //           }
    //       }
    //   }
    // }
    //  
    // void loop()
    // {
    //     char* buffer = "LinkIt BT Client";
    //     int write_size = LBTClient.write((uint8_t*)buffer, strlen(write_buf));
    //     if(write_size > 0)
    //     {
    //         Serial.print("write read: ");
    //         Serial.println(write_size);
    //     }
    //}
	// </code> 

    size_t write(
            const uint8_t* buf,    // [IN] daat to write
            size_t size = 1    // [IN] size of the buffer
        );
        
 // get the number of bytes(characters)avaiable for reading from the serial port.
 //
 // RETURNS
 // the bumbers of bytes available to read        
    int available(void);
    
 // returns the next byte of incoming serial data without removing it from the 
 //  internal serial buffer
 //
 // RETURNS
 // the first byte of incoming serial data available, -1 if no data is available   
    int peek(void);
    
 //  waits for the transmission of outgoing serial data to complete
    void flush(void);
    
// write a char 
//
// RETURNS
// 1 for write success, 0 for write fail   
    size_t write(const uint8_t data  //[IN] input char
                );
                
    using Print::write;
        
    void post_signal_write();
    void post_signal_read();

private:
    int m_post_write;
    VM_SIGNAL_ID m_signal_write;
    int m_post_read;
    VM_SIGNAL_ID m_signal_read;

};

// the LBTClientClass object
extern LBTClientClass LBTClient;

#endif //#ifndef LBTCLIENT_H
