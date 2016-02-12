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
#include <Arduino.h>
#include "LTask.h"
#include "vmconn.h"
#include "vmtcp.h"
#include "vmlog.h"
#include "vmsim.h"
#include "vmudp.h"
#include "LUdp.h"

LUDP::LUDP():
	m_port(-1),
	m_sendToPort(-1),
	m_serverHandle(-1),
	m_sendToIP(INADDR_NONE),
	m_recvIP(INADDR_NONE),
	m_recvPort(-1),
	m_writePos(0),
	m_recvPos(0)
{

}

LUDP::~LUDP()
{
	stop();
}

void LUDP::udpCallback(VMINT hdl, VMINT event)
{
	switch(event)
	{
	case VM_UDP_EVT_WRITE:
		break;
	case VM_UDP_EVT_READ:
		break;
	case VM_UDP_EVT_PIPE_BROKEN:
	case VM_UDP_EVT_PIPE_CLOSED:
		vm_log_error("udpCallback error! evt=%d hdl=%d", event, hdl);
		break;
	}
}

boolean LUDP::udpBegin(void* userdata)
{
	LUDP* pThis = (LUDP*)userdata;

	pThis->m_serverHandle = vm_udp_create(pThis->m_port, 
										  pThis->getAPN(), 
										  &udpCallback, 
										  0					// don't loopback
										  );

	if(pThis->m_serverHandle < 0)
	{
		// fail immediately
		pThis->m_serverHandle = -1;
		return true;
	}
	else
	{
		// no need to wait for VM_UDP_EVT_WRITE???
		return true;
	}
}

uint8_t LUDP::begin(uint16_t port)
{
	m_port = port;
	LTask.remoteCall(&udpBegin, this);

	if(m_serverHandle == -1)
	{
		// create failed.
		return 0;
	}
	else
	{
		return 1;
	}
}

boolean LUDP::udpStop(void* userdata)
{
	LUDP* pThis = (LUDP*)userdata;
	vm_udp_close(pThis->m_serverHandle);
	pThis->m_serverHandle = -1;
	return true;
}

void LUDP::stop()
{
	if(m_serverHandle == -1)
		return;

	LTask.remoteCall(&udpStop, this);
	return;
}

int LUDP::beginPacket(IPAddress ip, uint16_t port)
{
	m_sendToPort = port;
	m_sendToIP = ip;

	m_writeBuffer.resize(INIT_WRITE_BUFFER_SIZE);
	m_writePos = 0;

	vm_log_info("beginPacket(IP)");
	return 1;
}

struct LUDPSendContext
{
	LUDP *pThis;
	VMINT sentComplete;
};

boolean LUDP::udpSend(void* userdata)
{
	LUDPSendContext *pCntx = (LUDPSendContext*)userdata;
	LUDP* pThis = pCntx->pThis;
	VMINT remainBuffer = pThis->m_writePos;
	VMUINT8 *pBuf = &pThis->m_writeBuffer[0];

	vm_sockaddr_struct sendto = {0};
	sendto.addr[0] = pThis->m_sendToIP[0];
	sendto.addr[1] = pThis->m_sendToIP[1];
	sendto.addr[2] = pThis->m_sendToIP[2];
	sendto.addr[3] = pThis->m_sendToIP[3];
	sendto.addr_len = 4;
	sendto.port = pThis->m_sendToPort;

	vm_log_info("send packet len:%d to %d.%d.%d.%d:%d",
				remainBuffer,
				sendto.addr[0],
				sendto.addr[1],
				sendto.addr[2],
				sendto.addr[3],
				sendto.port);

	while(remainBuffer > 0)
	{
		VMINT sentBytes = 0;
		sentBytes = vm_udp_sendto(pThis->m_serverHandle,
								  pBuf,
								  remainBuffer,
								  &sendto);
		
		vm_log_info("vm_udp_sendto returns %d", sentBytes);


		if(sentBytes <= 0)
		{
			vm_log_error("vm_udp_sendto sent no content");
			break;
		}	

		pBuf += sentBytes;
		remainBuffer -= sentBytes;
	}

	// check if buffer is completely sent
	if(remainBuffer <= 0)
	{
		pCntx->sentComplete = 1;
	}
	else
	{
		pCntx->sentComplete = 0;
	}

	return true;
}

int LUDP::endPacket()
{
	vm_log_info("endPacket");
	LUDPSendContext cntx;
	cntx.pThis = this;
	cntx.sentComplete = 0;
	LTask.remoteCall(&udpSend, &cntx);
	
	// release buffer
	m_writePos = 0;
	m_writeBuffer.clear();
	
	// reset socket address
	m_sendToIP = INADDR_NONE;
	m_sendToPort = -1;
	return cntx.sentComplete;
}

size_t LUDP::LUDP::write(uint8_t byte)
{
	if(m_writePos >= m_writeBuffer.size())
	{
		m_writeBuffer.resize(m_writeBuffer.size() + INIT_WRITE_BUFFER_SIZE);
	}
	m_writeBuffer[m_writePos] = byte;
	m_writePos++;

	return 1;
}

size_t LUDP::write(const uint8_t *buffer, size_t size)
{
	if((m_writePos + size) >= m_writeBuffer.size())
	{
		m_writeBuffer.resize(m_writeBuffer.size() + size);
	}

	for(size_t i = 0; i < size; ++i)
	{
		m_writeBuffer[m_writePos] = buffer[i];
		m_writePos++;
	}

	return size;
}

boolean LUDP::udpRecv(void* userdata)
{
	LUDP *pThis = (LUDP*)userdata;
	vm_sockaddr_struct recvfrom = {0};

	// allocate buffer for receiving
	pThis->m_recvBuffer.resize(INIT_RECV_BUFFER_SIZE);
	const VMINT receivedSize = vm_udp_recvfrom(pThis->m_serverHandle,
											   &pThis->m_recvBuffer[0],
											   pThis->m_recvBuffer.size(),
											   &recvfrom);

	if(receivedSize > 0)
	{
		// content retrieved
		pThis->m_recvBuffer.resize(receivedSize);
		pThis->m_recvIP = IPAddress(recvfrom.addr[0],
					    			recvfrom.addr[1],
					    			recvfrom.addr[2],
					    			recvfrom.addr[3]);
		pThis->m_recvPort = recvfrom.port;
		pThis->m_recvPos = 0;
	}
	else
	{
		// nothing to read
		pThis->m_recvBuffer.clear();
	}
	
	return true;
}

int LUDP::parsePacket()
{
	if(m_serverHandle == -1)
	{
		return 0;
	}

	// is the receiving buffer has content?
	int remainBytes = available();
	if(remainBytes)
	{
		return remainBytes;
	}

	// is incoming packet ready?
	flush();
	LTask.remoteCall(&udpRecv, this);
	return available();
}

void LUDP::flush()
{
	m_recvBuffer.clear();
	m_recvPos = 0;
	m_recvIP = INADDR_NONE;
	m_recvPort = -1;
}

int LUDP::available()
{
	if(m_recvIP == INADDR_NONE)
		return 0;

	if(m_recvBuffer.size() == 0)
		return 0;

	const int remainBytes = m_recvBuffer.size() - m_recvPos;

	if(remainBytes > 0)
	{
		return remainBytes;
	}	
	else
	{
		return 0;
	}
}

int LUDP::read()
{
	if(!available())
	{
		return -1;
	}

	VMUINT8 byte = m_recvBuffer[m_recvPos];
	m_recvPos++;

	return (int)byte;
}

int LUDP::read(unsigned char* buffer, size_t len)
{
	if(!available() || len <= 0)
	{
		return -1;
	}

	const size_t readLen = std::min(m_recvBuffer.size() - m_recvPos, len);

	memcpy(buffer, &m_recvBuffer[m_recvPos], readLen);
	m_recvPos += readLen;

	return readLen;
}

int LUDP::peek()
{
	if(!available())
	{
		return -1;
	}

	VMUINT8 byte = m_recvBuffer[m_recvPos];
	return (int)byte;
}
