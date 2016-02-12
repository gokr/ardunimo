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

#ifndef _UART_CLASS_
#define _UART_CLASS_

#include "HardwareSerial.h"
#include "RingBuffer.h"
#include "vmdcl.h"
#include "vmdcl_gpio.h"
#include "vmdcl_sio.h"
#include <chip.h>

// UARTClass is designed for LinkIt One board connecte with other hardware device through UART
// LinkIt One has 2 serial ports: Serial and Serial1. Serial communicates on USB port, Serial1
// on pins0(RX) and pins1(TX).
class UARTClass : public HardwareSerial
{
  protected:
    RingBuffer *_rx_buffer ;
  protected:
    int _usbNum ;
    VM_DCL_HANDLE uart_handle;

  public:
    UARTClass( int usbNum, RingBuffer* pRx_buffer ) ;
    
// Method
  public:
  	
 //  sets the data rate in bits per sencond for serial data transmission
 //
 // EXAMPLE
 //<code>
 //void setup()
 //{
 //    Serial.begin(115200);
 //}
 //void loop()
 //{
 //    //handle code
 //}
 //</code> 
void begin( const uint32_t dwBaudRate //[IN] in bits per sencond(baud rate)
          ) ;

 //  disables serial communication, allowing the RX and TX pins to be used for 
 //  general input and output
void end( void ) ;

 //  get the number of bytes(characters)avaiable for reading from the serial port.
 //
 // RETURNS
 // the bumbers of bytes available to read
 //
 // EXAMPLE
 //<code>
 //int numberscomingBytes = 0;
 //void setup()
 //{
 //    Serial.begin(115200);
 //}
 //void loop()
 //{
 //    if(Serial.available()>0)
 //    {
 //        numberscomingBytes = Serial.read();
 //        Serial.print(numberscomingBytes);
 //    }
 //}
 //</code> 
int available( void ) ;

 //  returns the next byte of incoming serial data without removing it from the 
 //  internal serial buffer
 //
 // RETURNS
 // the first byte of incoming serial data available, -1 if no data is available
int peek( void ) ;

 //  reads incoming serial data
 //
 // RETURNS
 // the first byte of incoimng serial data avaiable, -a if no data is available
 //
 // EXAMPLE
 //<code>
 //int incomingdata = 0;
 //void setup()
 //{
 //    Serial.begin(9600);  
 //}
 //void loop()
 //{
 //    if (Serial.available() > 0)
 //    {
 //        incomingdata = Serial.read();
 //        Serial.print("received data: ");
 //        Serial.println(incomingdata, DEC);
 //    }
 //}
 //</code> 
int read( void ) ;

 //  waits for the transmission of outgoing serial data to complete
void flush( void ) ;

// write a char 
//
// RETURNS
// the number of write
size_t write( const uint8_t c //[IN] input char
            ) ;
    
    friend void UartIrqHandler(void* parameter, VM_DCL_EVENT event, VM_DCL_HANDLE device_handle);
    
    // pull in write(str) and write(buf, size) from Print
    using Print::write ; 
    	
// Check if the serail port is ready. 
//
// For Serial (USB port), it will check DTR signal to know that if the USB CDC 
// serial connection is established or not (i.e. return true if PC side application
// opens the corresponding COM port, and return false if the application closes the port).
//
// For Serial1, it will always return true.
// RETURNS
// For Serial:
// * true: DTR is 1, PC application has opened the COM port.
// * false: DTR is 0, no application open the COM port.
// For Serial1:
// * always return true
// EXAMPLE
//<code>
//void setup() 
//{
//    Serial.begin(9600);
//    while (!Serial)
//    {
//        ; // wait for serial port to connect. 
//    }
//}
//</code> 
    operator bool(); 
};

// the UARTClass object, Serial on USB port
extern UARTClass Serial;

// the UARTClass object, Serial1 on pins0(RX) and pins1(TX)
extern UARTClass Serial1;

#endif // _UART_CLASS_
