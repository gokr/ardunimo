/*
 * TwoWire.h - TWI/I2C library for Arduino Due
 * Copyright (c) 2011 Cristian Maglie <c.maglie@bug.st>.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Modified 20 Aug 2014 by MediaTek Inc.
 */

extern "C" {
#include <string.h>
#include <stdlib.h> 
#include <inttypes.h>  
#include "vmsys.h" 
#include "vmdcl.h" 
#include "vmdcl_i2c.h" 
#include "vmlog.h"
}

#include "Wire.h"

VM_DCL_HANDLE i2c_handle = -1;                 /* Declare a VM_DCL_HANDLE variable. */

TwoWire::TwoWire() :
	 rxBufferIndex(0), rxBufferLength(0), txAddress(0), txBufferLength(0), 
     srvBufferIndex(0), srvBufferLength(0), status(UNINITIALIZED), bytes_per_transfer(0), num_transfer(0), bytes_per_read(0), num_read(0){
	// Empty
}

void TwoWire::begin(void) {
	
	if(!changePinType(18, PIO_I2C, &i2c_handle))
		return;

	if(i2c_handle == VM_DCL_HANDLE_INVALID)
	   i2c_handle = vm_dcl_open(VM_DCL_I2C,0); 
	else
	   i2c_handle = g_APinDescription[18].ulHandle;

	if(VM_DCL_HANDLE_INVALID == i2c_handle)	 
	{	  	
		vm_log_info("begin, failed to get i2c_handle.");	
	}	

	setPinHandle(18, i2c_handle);

	status = MASTER_IDLE;
}
	
void TwoWire::begin(uint8_t address) {
    //status = SLAVE_IDLE;// can not porting use dcl
    begin();
}

void TwoWire::begin(int address) {
	begin((uint8_t) address);// can not porting use dcl
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {

	// perform blocking read into buffer
	int readed = 0;
	VM_DCL_STATUS ret = 0;
	vm_i2c_ctrl_config_t conf_data;
	vm_i2c_ctrl_single_read_t  read_data;
	vm_i2c_ctrl_cont_read_t read_data_2;
	vm_i2c_ctrl_write_and_read_t read_and_write_data;
	
      if(i2c_handle==-1)
      {
          return 0;
      }
	
      if (quantity > BUFFER_LENGTH)
      {   
          quantity = BUFFER_LENGTH;
      }

    if (sendStop == 1)
    {
        if (txBufferLength != 0)
        {
            // write_and_read
            if ((num_transfer != 1) || (num_read != 0))
            {
                rxBufferLength = 0;
                bytes_per_read = 0;
                num_read = 0;
                return 0;
            }
            else
            {
                conf_data.Reserved0 = (VM_DCL_I2C_OWNER)0;
                conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
                conf_data.fgGetHandleWait = 0;
                conf_data.Reserved1 = 0;
                conf_data.u1DelayLen = 0;
                conf_data.u1SlaveAddress = address<<1;
                conf_data.u4FastModeSpeed = 100;
                conf_data.u4HSModeSpeed = 0;
                ret = vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
                read_and_write_data.pu1InData= &(rxBuffer[0]);
                read_and_write_data.u4InDataLen= quantity;
                read_and_write_data.pu1OutData = &(txBuffer[0]);
                read_and_write_data.u4OutDataLen = txBufferLength;
                
                ret = vm_dcl_control(i2c_handle,VM_I2C_CMD_WRITE_AND_READ,(void *)&read_and_write_data);
                rxBufferIndex = 0;
                rxBufferLength = quantity;
                bytes_per_transfer = 0;
                num_transfer = 1;
                txBufferLength = 0;
            }
        }
        else
        {    
            if (num_read == 0)
            {
            	conf_data.Reserved0 = (VM_DCL_I2C_OWNER)0;
            	conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
            	conf_data.fgGetHandleWait = 0;
            	conf_data.Reserved1 = 0;
            	conf_data.u1DelayLen = 0;
            	conf_data.u1SlaveAddress = address<<1;
            	conf_data.u4FastModeSpeed = 100;
            	conf_data.u4HSModeSpeed = 0;
            	ret = vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
            	read_data.pu1Data = &(rxBuffer[0]);
            	read_data.u4DataLen = quantity;
            	ret = vm_dcl_control(i2c_handle,VM_I2C_CMD_SINGLE_READ,(void *)&read_data);
            	rxBufferIndex = 0;
            	rxBufferLength = quantity;
            }
            else
            {
                num_read++;
                rxBufferLength += quantity;
                if ((bytes_per_read != quantity) || (rxBufferLength > BUFFER_LENGTH))
                {
                    rxBufferLength = 0;
                    bytes_per_read = 0;
                    num_read = 0;
                    return 0;
                }
                
                conf_data.Reserved0 = (VM_DCL_I2C_OWNER)0;
            	conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
            	conf_data.fgGetHandleWait = 0;
            	conf_data.Reserved1 = 0;
            	conf_data.u1DelayLen = 0;
            	conf_data.u1SlaveAddress = address<<1;
            	conf_data.u4FastModeSpeed = 100;
            	conf_data.u4HSModeSpeed = 0;
            	ret = vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
            	read_data_2.pu1Data = &(rxBuffer[0]);
            	read_data_2.u4DataLen = quantity;
                read_data_2.u4TransferNum = num_read;
            	ret = vm_dcl_control(i2c_handle,VM_I2C_CMD_CONT_READ,(void *)&read_data_2);
            	rxBufferIndex = 0;
            }
        }
        
        bytes_per_read = 0;
        num_read = 0;
        
    }
    else if (sendStop == 0)
    {
        if (txBufferLength != 0)
        {
            // before cont_read, please call endTransmission() to send data in txBuffer
            rxBufferLength = 0;
            bytes_per_read = 0;
            num_read = 0;
            return 0;
        }
        
        if (rxBufferLength == 0)
        {
            bytes_per_read = quantity;
            num_read = 1;
            rxBufferLength = quantity;
        }
        else
        {
            rxBufferLength += quantity;
            if ((bytes_per_read != quantity) || (rxBufferLength > BUFFER_LENGTH))
            {
                rxBufferLength = 0;
                bytes_per_read = 0;
                num_read = 0;
                return 0;
            }
            // conut the number of repeated start signal
            num_read++;
        }
    }

	return quantity;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity) {
	return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity) {
	return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop) {
	return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) sendStop);
}

void TwoWire::beginTransmission(uint8_t address) {
	if(i2c_handle==-1)
	{
		vm_log_info("[TwoWire]beginTransmission:i2c handle is invalid,return");
		return;
	}
	status = MASTER_SEND;

	// save address of target and empty buffer
	txAddress = address<<1;

    // frist transfer
    if (txBufferLength == 0)
    {
        bytes_per_transfer = 0;
        num_transfer = 1;
    }
    else
    {
        // conut the number of repeated start signal
        num_transfer++;
    }

    rxBufferLength = 0;
    bytes_per_read = 0;
    num_read = 0;
}

void TwoWire::beginTransmission(int address) {
	beginTransmission((uint8_t) address);
}

uint8_t TwoWire::endTransmission(uint8_t sendStop) {
	vm_i2c_ctrl_config_t conf_data;
	vm_i2c_ctrl_single_write_t write_data;
    vm_i2c_ctrl_cont_write_t cont_write_data;
	VM_DCL_STATUS ret = 0;
	uint8_t result = 0;

    // in idle state, user cannot write buffer, must to invoke the beginTransmission(..) before write buffer
    status = MASTER_IDLE; 
            
	if(i2c_handle==-1)
	{
        bytes_per_transfer = 0;
        num_transfer = 1;
        txBufferLength = 0;
        return 4; // other error
	}
    
    if (BUFFER_LENGTH < txBufferLength)
    {
        bytes_per_transfer = 0;
        num_transfer = 1;
        txBufferLength = 0;
        return 1; // data too long to fit in transmit buffer
    }
    else if(0 < txBufferLength)
    {

        if (sendStop == 0)
        {
            // frist transfer
            if (num_transfer == 1)
            {
                bytes_per_transfer = txBufferLength;
                
                if (BUFFER_LENGTH == txBufferLength)
                {
                    bytes_per_transfer = 0;
                    num_transfer = 1;
                    txBufferLength = 0;
                    return 1; // data too long to fit in transmit buffer
                }
            }
            else if (num_transfer > 1)
            {
                // check the API sequence error
                if (txBufferLength != (num_transfer * bytes_per_transfer))
                {
                    vm_log_info("[TwoWire]endTransmission, txBufferLength = %d, num_transfer = %d, bytes_per_transfer = %d", txBufferLength, num_transfer, bytes_per_transfer);
                    bytes_per_transfer = 0;
                    num_transfer = 1;
                    txBufferLength = 0;
                    return 4; // other error
                }
            }
            else
            {
                bytes_per_transfer = 0;
                num_transfer = 1;
                txBufferLength = 0;
                return 4; // other error
            }
        }
        else if (sendStop == 1)
        {
            // no repeated start signal
            if (num_transfer == 1)
            {
                conf_data.Reserved0 =  (VM_DCL_I2C_OWNER)0;
                conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
                conf_data.fgGetHandleWait = 0;
                conf_data.Reserved1 = 0;
                conf_data.u1DelayLen = 0;
                conf_data.u1SlaveAddress = txAddress;

                conf_data.u4FastModeSpeed = 100;
                conf_data.u4HSModeSpeed = 0;
                ret = vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
                
            
                write_data.pu1Data = &(txBuffer[0]);
                write_data.u4DataLen = txBufferLength;
                ret = vm_dcl_control(i2c_handle,VM_I2C_CMD_SINGLE_WRITE,(void *)&write_data);
            }
            else if (num_transfer > 1)
            {
                conf_data.Reserved0 =  (VM_DCL_I2C_OWNER)0;
                conf_data.eTransactionMode = VM_DCL_I2C_TRANSACTION_FAST_MODE;
                conf_data.fgGetHandleWait = 0;
                conf_data.Reserved1 = 0;
                conf_data.u1DelayLen = 0;
                conf_data.u1SlaveAddress = txAddress;

                conf_data.u4FastModeSpeed = 100;
                conf_data.u4HSModeSpeed = 0;
                ret = vm_dcl_control(i2c_handle,VM_I2C_CMD_CONFIG,(void *)&conf_data);
                
            
                cont_write_data.pu1Data = &(txBuffer[0]);
                cont_write_data.u4DataLen = txBufferLength;
                cont_write_data.u4TransferNum = num_transfer;
                ret = vm_dcl_control(i2c_handle,VM_I2C_CMD_CONT_WRITE,(void *)&cont_write_data);
            }
            else
            {
                bytes_per_transfer = 0;
                num_transfer = 1;
                txBufferLength = 0;
                return 4; // other error
            }
            
            bytes_per_transfer = 0;
            num_transfer = 1;
            txBufferLength = 0;
        }
        else
        {
            bytes_per_transfer = 0;
            num_transfer = 1;
            txBufferLength = 0;
            return 4; // other error
        }
    }
    
    if (ret == 5 || ret == 0)
    {
        result = 0; //success
    }
    else if (ret == 1)
    {
        result = 1; // data too long to fit in transmit buffer
    }
    else if (ret == 4)
    {
        result = 2; // received NACK on transmit of address
    }
    else if (ret == 3)
    {
        result = 3; // received NACK on transmit of date
    }
    else
    {
        result = 4; // other error
    }
    
    return result;
}

//	This provides backwards compatibility with the original
//	definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void)
{
	return endTransmission(true);
}

size_t TwoWire::write(uint8_t data) {
	if (status == MASTER_SEND) {
		if (txBufferLength >= BUFFER_LENGTH)
			return 0;
		txBuffer[txBufferLength++] = data;
		return 1;
	} else {
		if (srvBufferLength >= BUFFER_LENGTH)
			return 0;
		srvBuffer[srvBufferLength++] = data;
		return 1;
	}
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
	if (status == MASTER_SEND) {
		for (size_t i = 0; i < quantity; ++i) {
			if (txBufferLength >= BUFFER_LENGTH)
				return i;
			txBuffer[txBufferLength++] = data[i];
		}
	} else {
		for (size_t i = 0; i < quantity; ++i) {
			if (srvBufferLength >= BUFFER_LENGTH)
				return i;
			srvBuffer[srvBufferLength++] = data[i];
		}
	}
	return quantity;
}

int TwoWire::available(void) {
	return rxBufferLength - rxBufferIndex;
}

int TwoWire::read(void) {
	if (rxBufferIndex < rxBufferLength)
		return rxBuffer[rxBufferIndex++];
	return -1;
}

int TwoWire::peek(void) {
	if (rxBufferIndex < rxBufferLength)
		return rxBuffer[rxBufferIndex];
	return -1;
}

void TwoWire::flush(void) {
	// Do nothing, use endTransmission(..) to force
	// data transfer.
}

void TwoWire::onReceive(void(*function)(int)) {
	onReceiveCallback = function;
}

void TwoWire::onRequest(void(*function)(void)) {
	onRequestCallback = function;
}

void TwoWire::onService(void) {
	// Retrieve interrupt status
}
// Preinstantiate Objects //////////////////////////////////////////////////////
TwoWire Wire = TwoWire();

