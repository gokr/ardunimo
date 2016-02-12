/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 * Modified 20 Aug 2014 by MediaTek Inc.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include "variant.h"
#include "vmdcl_spi.h"
#include <stdio.h>

// SPI clock is 1/4 of system clock
#define SPI_CLOCK_DIV4 0x00
// SPI clock is 1/16 of system clock
#define SPI_CLOCK_DIV16 0x01
// SPI clock is 1/64 of system clock
#define SPI_CLOCK_DIV64 0x02
// SPI clock is 1/128 of system clock
#define SPI_CLOCK_DIV128 0x03
// SPI clock is 1/2 of system clock
#define SPI_CLOCK_DIV2 0x04
// SPI clock is 1/8 of system clock
#define SPI_CLOCK_DIV8 0x05
// SPI clock is 1/32 of system clock
#define SPI_CLOCK_DIV32 0x06

// SPI data transfer mode 0
#define SPI_MODE0 0x02
// SPI data transfer mode 1
#define SPI_MODE1 0x00
// SPI data transfer mode 2
#define SPI_MODE2 0x03
// SPI data transfer mode 3
#define SPI_MODE3 0x01

// SPI class interface, is used to control SPI port for users to conduct data communication between the processor and all kinds of peripheral devices.
class SPIClass {
	
// Constructor / Destructor 
public: 
    SPIClass(void);
    
// Method  
public:  
//DESCRIPTION
// Sends a byte of data to slave and receives a byte of data from the slave at the same time.
//RETURNS
// Data returned from slave to master
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
//
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin();    
// }
// void loop()
// {
//     byte ret_val;
//     digitalWrite(SS_PIN, LOW);
//     ret_val = SPI.transfer(100);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code> 
    byte transfer(
        uint8_t _data  // [IN] Data sent from master to slave
    );

//DESCRIPTION
// Initlize SPI, setting up the mode and initial status of pins.
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
// 
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin();    
// }
// void loop()
// {
//     byte ret_val;
//     digitalWrite(SS_PIN, LOW);
//     ret_val = SPI.transfer(100);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code> 
    void begin(void);
// 
//DESCRIPTION
// Disables SPI data transmission.
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
// int value = 0;
//
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin();    
// }
// void loop()
// {
//     for (value = 0; value < 255; value++)
//     {
//         digitalWrite(SS_PIN, LOW);
//         SPI.transfer(value);
//         digitalWrite(SS_PIN, HIGH);
//         delay(1000);
//     }
//     SPI.end();
// }
// </code> 
    void end(void);

//DESCRIPTION
// Sets up order of data transmission, can be MSBFIRST (MSB first) or LSBFIRST (LSB first)
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
//
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin(); 
//     SPI.setBitOrder(MSBFIRST); 
// }
// void loop()
// {
//     byte ret_val;
//     digitalWrite(SS_PIN, LOW);
//     ret_val = SPI.transfer(100);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code> 
    void setBitOrder(
        BitOrder bit_order // [IN] Data transmission order (MSBFIRST or LSBFIRST)
        );

//DESCRIPTION
// Sets up SPI data transmission mode.
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
//
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin(); 
//     SPI.setDataMode(SPI_MODE1); 
// }
// void loop()
// {
//     byte ret_val;
//     digitalWrite(SS_PIN, LOW);
//     ret_val = SPI.transfer(100);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code>
    void setDataMode(
        uint8_t mode  // [IN] SPI data transmission mode (SPI_MODE0 ~ SPI_MODE3)
        );

//DESCRIPTION
// Sets up clock divider to control the speed of data transmission. 
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
// 
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin(); 
//     SPI.setClockDivider(SPI_CLOCK_DIV8); 
// }
// void loop()
// {
//     byte ret_val;
//     digitalWrite(SS_PIN, LOW);
//     ret_val = SPI.transfer(100);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code>
    void setClockDivider(
        uint8_t clock_div  // [IN] Clock divider (SPI_CLOCK_DIV2 ~ SPI_CLOCK_DIV128)
        );
  
//DESCRIPTION
// write block memory to slave, and size need to be 2^X. 
//RETURNS
// size to write, 0 means failed
//EXAMPLE
// <code>
// #include <SPI.h>
// #define SS_PIN    10
// 
// void setup()
// {
//     pinMode(SS_PIN, OUTPUT);
//     SPI.begin(); 
//     SPI.setClockDivider(SPI_CLOCK_DIV8); 
// }
// void loop()
// {
//     byte ret_val;
//     uint8_t mem[64];
//     //    //    memset(mem, 0, 64);
//     digitalWrite(SS_PIN, LOW);
//     SPI.write(mem, 64);
//     digitalWrite(SS_PIN, HIGH);
//     delay(1000);
// }
// </code>
    uint32_t write(
        uint8_t* _data,   // [IN]  the porint of data sent from master to slave
        uint32_t size   //     [IN] data size to send
        );
  private:

    // SPI config data
    vm_spi_config_para_t conf_data;

    // SPI handle
    VM_DCL_HANDLE spi_handle;

    // Specify a SPI mode. 
    vm_spi_mode_t  spi_data;

    // write buffer
    VMUINT8 write_buff;

    // write buffer length
    VMUINT32 write_len;

    // read buffer
    VMUINT8 read_buff;

    // read buffer length
    VMUINT32 read_len;

    uint32_t write_2x(uint8_t* _data,uint32_t size);

};

//the SPI object
extern SPIClass SPI;

#endif
