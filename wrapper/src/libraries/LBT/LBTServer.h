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


#ifndef LBTSERVER_H
#define LBTSERVER_H

#include "LTask.h"
#include "LBT.h"



struct LBTServerBeginContext : BTBase
{
    void* name;
    boolean result;
    boolean is_set_pin;
    LBTServerBeginContext():
        name(NULL),
        result(false)
    {

    }
};

struct LBTServerAcceptContext : BTBase
{
    size_t time_out;
    boolean result;
    LBTAddress *address;

    LBTServerAcceptContext():
        time_out(20),
        result(false),
        address(NULL)
    {

    }
};

struct LBTServerGetHostDeviceInfoContext : BTBase
{
    LBTDeviceInfo* device_info;
    boolean result;

    LBTServerGetHostDeviceInfoContext():
        device_info(NULL),
        result(false)
    {

    }
};

struct LBTServerReadWriteContext : BTBase
{
    void *buf;
    VMINT len;
    VMINT lenProcessed;	// bytes read or written

	LBTServerReadWriteContext():
		buf(NULL),
		len(1),
		lenProcessed(0)
	{

	}
};


// LBTServer class interface
class LBTServerClass  : public _LTaskClass,public Stream{
public:
	LBTRingBuffer *_rx_buffer;
	uint8_t _pincode_buffer[LBT_PIN_CODE_BUFFER_SIZE];
// Constructor
public:
	LBTServerClass(LBTRingBuffer* pRx_buffer);

// Method
public:

    // DESCRIPTION
    //    init BT module and setup a SPP server instance
    // PARAMETERS
    //    name: device name to set 
    //    pinCode: BT2.0 pincode, if you set it as const string, LinkOne can communicate BT2.0 device.
    // RETURNS
    //    true: success
    //    false: fail
	// EXAMPLE
	// <code>
    // #include <LBTServer.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin((uint8_t*)"LBTServer"); //bool success = LBTServer.begin((uint8_t*)"BTServer",(uint8_t*)"1234");
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begin successfully");
    //   }
    // }
    //  
    // void loop()
    // {
    //   
    // }
    // 
	// </code> 
    boolean begin(
           const uint8_t* name = NULL,   //[IN] device name to set
           const uint8_t* pinCode = NULL //[IN] BT2.0 pincode
        );

    // DESCRIPTION
    //    close corresponding SPP server instance and end BT module
    // RETURNS
    //    None
	// EXAMPLE
	// <code>
    // #include <LBTServer.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begin successfully");
    //   }
    //   
    //   LBTServer.end();
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
    void end(void);

    // DESCRIPTION
    //    accept SPP client's connection request. 
    //    returns as long as the connection is made or timeout
    // PARAMETERS
    //    time_out: timeout for accept action.
    // RETURNS
    //    true: success
    //    false: fail
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTServer.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begin successfully");
    //   }
    //  
    //   // waiting for Spp Client to connect
    //   bool connected = LBTServer.accept(20);
    //  
    //   if( !connected )
    //   {
    //       Serial.println("No connection request yet");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Connected");
    //   }
    // }
    //  
    // void loop()
    // {
    //  
    // }
	// </code> 
    boolean accept(
            size_t time_out = 20  //[IN] time out duration while waiting for SPP client's connection request
        );
        
    // DESCRIPTION
    //    accept SPP client's connection request on spencified BT address.
    //    returns as long as the connection is made or timeout
    // PARAMETERS
    //    time_out: timeout for accept action.
    //    MACAddr: string format (const char *), the format is like "12:34:56:ab:cd:ef".
    // RETURNS
    //    true: success
    //    false: fail
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTServer.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begin successfully");
    //   }
    //  
    //   // waiting for Spp Client to connect
    //   bool connected = LBTServer.accept(20, "12:34:56:ab:cd:ef");
    //  
    //   if( !connected )
    //   {
    //       Serial.println("No connection request yet");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Connected");
    //   }
    // }
    //  
    // void loop()
    // {
    //  
    // }
	// </code> 
    boolean accept(
            size_t time_out,  //[IN] time out duration while waiting for SPP client's connection request
            const char *MACAddr // [IN] string format (const char *), the format is like "12:34:56:ab:cd:ef".
            );

    // DESCRIPTION
    //    check if any SPP client is conneccted
    // RETURNS
    //    true: yes
    //    false: no
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTServer.h>
    //   
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begin successfully");
    //   }
    //  
    // }
    //  
    // void loop()
    // {
    // ¡¡¡¡ if(!LBTServer.connected())
    //     {
    //        // waiting for Spp Client to connect
    //        bool connected = LBTServer.accept(20);
    //  
    //        if( !connected )
    //        {
    //            Serial.println("No connection request yet");
    //            // don't do anything else
    //            while(true);
    //        }
    //        else
    //        {
    //            Serial.println("Connected");
    //        }
    //     }
    //     else
    //     {
    //         char buffer[10];
    //         int read_size = LBTServer.read((uint8_t*)buffer, 10);
    //         if(read_size > 0)
    //         {
    //             Serial.print("size read: ");
    //             Serial.println(read_size);
    //             Serial.println(buffer);
    //         }
    //     }
    // }
	// </code> 
    boolean connected(void);

    // DESCRIPTION
    //    get scanned device information
    // RETURNS
    //    true: success
    //    false : fail. Possible reasons are index not reasonable or never scanned before
	// EXAMPLE
	// <code>
	// #include <LBT.h>
    // #include <LBTServer.h>
    //  
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin("LBTServer");
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begin successfully");
    //       LBTDeviceInfo info = {0};
    //       bool success = LBTServer.getHostDeviceInfo(i, &info);
    //       if( success )
    //       {
    //           Serial.print("Device name:" );
    //           Serial.println(info.name);
    //       }
    //   }
    // }
    //  
    // void loop()
    // {
    //   
    // }
	// </code> 
	boolean getHostDeviceInfo(
            LBTDeviceInfo* dev_info    // [OUT] device info acquired
        );

    // DESCRIPTION
    //    read data from SPP client
    // RETURNS
    //    number of bytes read
    //    0 for no data to read
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTServer.h>
    //  
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begin successfully");
    //   }
    //  
    //   // waiting for Spp Client to connect
    //   bool connected = LBTServer.accept(20);
    //  
    //   if( !connected )
    //   {
    //       Serial.println("No connection request yet");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Connected");
    //   }
    // }
    //  
    // void loop()
    // {
    //     char buffer[10];
    //     int read_size = LBTServer.read((uint8_t*)buffer, 10);
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
    //    write data to SPP client
    // RETURNS
    //    number of bytes written
    //    0 for write fail
	// EXAMPLE
	// <code>
    // #include <LBT.h>
    // #include <LBTServer.h>
    //  
    // void setup()
    // {
    //   Serial.begin(9600);
    //   bool success = LBTServer.begin();
    //   if( !success )
    //   {
    //       Serial.println("Cannot begin Bluetooth Server successfully");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Bluetooth Server begin successfully");
    //   }
    //  
    //   // waiting for Spp Client to connect
    //   bool connected = LBTServer.accept(20);
    //  
    //   if( !connected )
    //   {
    //       Serial.println("No connection request yet");
    //       // don't do anything else
    //       while(true);
    //   }
    //   else
    //   {
    //       Serial.println("Connected");
    //   }
    // }
    //  
    // void loop()
    // {
    //     char* buffer = "LinkIt BT Server";
    //     int write_size = LBTServer.write((uint8_t*)buffer, strlen(buffer));
    //     if(write_size > 0)
    //     {
    //         Serial.print("Size written: ");
    //         Serial.println(write_size);
    //     }
    // }
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

// the LBTServerClass object
extern LBTServerClass LBTServer;

#endif //#ifndef LBTSERVER_H
