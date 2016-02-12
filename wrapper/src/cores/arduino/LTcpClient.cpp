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
#include "LTcpClient.h"
#include "vmconn.h"
#include "vmtcp.h"
#include "vmlog.h"

#define APN_ID VM_TCP_APN_WIFI

SharedHandle::SharedHandle():
	m_handle(INVALID_HANDLE),
	m_serverHandle(INVALID_HANDLE),
	m_pSharedCount(NULL)
{
}

SharedHandle::SharedHandle(VMINT handle):
	m_handle(handle),
	m_serverHandle(INVALID_HANDLE),
	m_pSharedCount(new VMINT(1))
{
	vm_log_info("SharedHandle create: c:%d, s:%d", m_handle, m_serverHandle);
}

SharedHandle::SharedHandle(VMINT clientHandle, VMINT serverHandle):
	m_handle(clientHandle),
	m_serverHandle(serverHandle),
	m_pSharedCount(new VMINT(1))
{
	vm_log_info("SharedHandle create: c:%d, s:%d", m_handle, m_serverHandle);
}

SharedHandle::SharedHandle(const SharedHandle& rhs):
	m_handle(rhs.m_handle),
	m_serverHandle(rhs.m_serverHandle),
	m_pSharedCount(rhs.m_pSharedCount)
{
	incRef();
}
	
SharedHandle::~SharedHandle()
{
	decRef();
}

void SharedHandle::invalidateHandle()
{
	m_handle = INVALID_HANDLE;
	m_serverHandle = INVALID_HANDLE; 
}

SharedHandle& SharedHandle::operator =(const SharedHandle& rhs)
{
	decRef();
	m_handle = rhs.m_handle;
	m_serverHandle = rhs.m_serverHandle;
	m_pSharedCount = rhs.m_pSharedCount;
	incRef();

	return *this;
}

SharedHandle::operator bool() const
{
	return (m_handle != INVALID_HANDLE);
}

boolean SharedHandle::releaseTcpHandle(void *userData)
{
	SharedHandle *pThis = (SharedHandle*)userData;
	vm_log_info("SharedHandle release: c=%d, s=%d", pThis->m_handle, pThis->m_serverHandle);
	if (pThis->m_serverHandle != -1)
	{
		VMINT ret = vm_soc_svr_close_client(pThis->m_handle);
	}
	else
	{
		vm_tcp_close(pThis->m_handle);
	}
	return true;
}

void SharedHandle::releaseHandle()
{
	if(m_handle == INVALID_HANDLE)
	{
		invalidateHandle();
		return;
	}
	
	LTask.remoteCall(&releaseTcpHandle, (void*)this);
	invalidateHandle();
}

void SharedHandle::incRef()
{
	if(m_pSharedCount != NULL)
	{
		(*m_pSharedCount)++;
	}
}

void SharedHandle::decRef()
{
	if(m_pSharedCount == NULL)
	{
		return;
	}
	
	if(*m_pSharedCount)
		*m_pSharedCount -= 1;

	if(*m_pSharedCount <= 0)
	{
		releaseHandle();
		delete m_pSharedCount;
		m_pSharedCount = NULL;
	}
}

LTcpClient::LTcpClient():
	m_handle(),
	m_peekByte(-1),
	m_peekBuffered(false)
{

}

LTcpClient::LTcpClient(const LTcpClient &rhs):
	m_handle(rhs.m_handle),
	m_peekByte(-1),
	m_peekBuffered(false)
{
}

LTcpClient::LTcpClient(VMINT handle):
	m_handle(handle),
	m_peekByte(-1),
	m_peekBuffered(false)
{
}

LTcpClient::LTcpClient(VMINT handle, VMINT serverHandle):
	m_handle(handle, serverHandle),
	m_peekByte(-1),
	m_peekBuffered(false)
{
}

LTcpClient::~LTcpClient()
{
}

struct LTcpConnectContext
{
	const char *ipAddr;
	VMINT port;
	LTcpClient *pInstance;
};

void LTcpClient::connectCallback(VMINT handle, VMINT event, void *userData)
{
	LTcpClient *pThis = (LTcpClient*)userData;
	vm_log_info("connectCallback handle=%d event=%d userData=%d", handle, event, userData);
	switch(event)
	{
	case VM_TCP_EVT_CONNECTED:
		pThis->m_handle = SharedHandle(handle);
		LTask.post_signal();
		break;
	case VM_TCP_EVT_CAN_WRITE:
		break;
	case VM_TCP_EVT_CAN_READ:
		break;
	case VM_TCP_EVT_PIPE_BROKEN:
		pThis->m_handle.invalidateHandle();
		LTask.post_signal();
		break;
	case VM_TCP_EVT_HOST_NOT_FOUND:
		pThis->m_handle.invalidateHandle();
		LTask.post_signal();
		break;
	case VM_TCP_EVT_PIPE_CLOSED:
		pThis->m_handle.invalidateHandle();
		LTask.post_signal();
		break;
	}
	return;
}

boolean LTcpClient::connectIP(void *userData)
{
	LTcpConnectContext *pContext = (LTcpConnectContext*)userData;
	// async api
	vm_log_info("connectIP, IP=%s, port=%d", pContext->ipAddr, pContext->port);
	VMINT clientHandle = vm_tcp_connect_ex(pContext->ipAddr, 
										   pContext->port, 
										   pContext->pInstance->getAPN(),
										   pContext->pInstance,
										   &connectCallback);
	vm_log_info("vm_tcp_connect returns %d", clientHandle);
	return false;
}

int LTcpClient::connect(IPAddress ip, uint16_t port)
{
	vm_log_info("connect(IPAddress)");
	char ipAddr[50] = {0};
	sprintf(ipAddr, 
			"%d.%d.%d.%d", 
			ip[0],
			ip[1], 
			ip[2], 
			ip[3]);
	vm_log_info("connect to %s", ipAddr);
	return connect(ipAddr, port); 
}

int LTcpClient::connect(const char *host, uint16_t port)
{
	vm_log_info("LTcpClient::connect(char) to %s:%d", host, port);

	if(connected())
	{
		vm_log_info("LTcpClient::connect() while already connected. stop() first.");
		stop();
	}
	
	LTcpConnectContext context;
	context.ipAddr = host;
	context.port = port;
	context.pInstance = this;
	LTask.remoteCall(&connectIP, &context);	
	return connected();
}

struct LTcpReadWriteContext
{
	VMINT handle;
	VMINT serverHandle;
	void *buf;
	VMINT len;
	VMINT lenProcessed;	// bytes read or written
	LTcpClient *pInst;

	LTcpReadWriteContext():
		handle(-1),
		serverHandle(-1),
		buf(NULL),
		len(0),
		lenProcessed(0),
		pInst(NULL)
	{

	}
};

boolean LTcpClient::wifiWrite(void *userData)
{
	vm_log_info("wifiWrite");
	LTcpReadWriteContext *pContext = (LTcpReadWriteContext*)userData;
	if (pContext->serverHandle != -1)
	{
		pContext->lenProcessed = vm_soc_svr_send(pContext->serverHandle,
												 pContext->handle, 
												 pContext->buf, 
												 pContext->len);
	}
	else
	{
		pContext->lenProcessed = vm_tcp_write(pContext->handle, 
											  pContext->buf, 
											  pContext->len);
	}
	
	vm_log_info("wifiWrite wrote %d", pContext->lenProcessed);
	return true;
}

size_t LTcpClient::write(uint8_t b)
{
	vm_log_info("wifiWrite arduino (byte)");
	LTcpReadWriteContext c;
	c.handle = m_handle.m_handle;
	c.serverHandle = m_handle.m_serverHandle;
	c.buf = &b;
	c.len = 1;
	c.pInst = this;
	LTask.remoteCall(&wifiWrite, &c);

	vm_log_info("written %d bytes", c.lenProcessed);
	return c.lenProcessed;
}

size_t LTcpClient::write(const uint8_t *buf, size_t size)
{
	vm_log_info("wifiWrite arduino (buffered)");
	LTcpReadWriteContext c;
	c.handle = m_handle.m_handle;
	c.serverHandle = m_handle.m_serverHandle;
	c.buf = (void*)buf;
	c.len = size;
	c.pInst = this;
	LTask.remoteCall(&wifiWrite, &c);

	vm_log_info("written %d bytes", c.lenProcessed);
	return c.lenProcessed;
}

int LTcpClient::available()
{
	return (peek() == -1) ? 0 : 1;
}

boolean LTcpClient::wifiRead(void *userData)
{
	LTcpReadWriteContext *pContext = (LTcpReadWriteContext*)userData;
	LTcpClient *pThis = pContext->pInst;

	pContext->lenProcessed = 0;
	
	// parameter check
	if(pContext->len <= 0)
	{	
		return true;
	}

	vm_log_info("wifiRead len=%d", pContext->len);

	// check peek state
	if(pThis->m_peekBuffered)
	{	
		// insert the peeked byte
		*((VMINT8*)pContext->buf) = pThis->m_peekByte;
		pContext->buf = (VMINT8*)pContext->buf + 1;
		pContext->lenProcessed += 1;
		pContext->len--;
		// clear peek state
		pThis->m_peekByte = -1;
		pThis->m_peekBuffered = false;
	}

	VMINT readResult = VM_TCP_READ_EOF;
	
	// actually read from TCP socket
	if (pContext->serverHandle != -1)
	{
		readResult = vm_soc_svr_read(pContext->serverHandle,
									 pContext->handle, 
									 pContext->buf, 
									 pContext->len);
	}
	else
	{
		readResult = vm_tcp_read(pContext->handle, 
								 pContext->buf, 
								 pContext->len);
	}

	if (readResult > 0)
	{
		pContext->lenProcessed += readResult;
	}
	
	if (readResult == VM_TCP_READ_EOF)
	{
		// we may cache a peek byte even if the socket is disconnected
		vm_log_info("wifiRead socket disconnected");
	}
	
	vm_log_info("wifiRead %d bytes", pContext->lenProcessed);
	return true;
}

int LTcpClient::read()
{
	// read a single byte
	LTcpReadWriteContext c;
	uint8_t ret = 0;
	c.handle = m_handle.m_handle;
	c.serverHandle = m_handle.m_serverHandle;
	c.buf = &ret;
	c.len = 1;
	c.pInst = this;
	LTask.remoteCall(&wifiRead, &c);
	if(c.lenProcessed > 0)
	{
		return (int)ret;
	}
	else
	{
		// if no data available, return -1
		return -1;
	}	
}

int LTcpClient::read(uint8_t *buf, size_t size)
{
	// read a single byte
	LTcpReadWriteContext c;
	uint8_t ret = 0;
	c.handle = m_handle.m_handle;
	c.serverHandle = m_handle.m_serverHandle;
	c.buf = buf;
	c.len = size;
	c.pInst = this;
	vm_log_info("wifiRead call with buf=%d, size=%d", c.buf, c.len);
	LTask.remoteCall(&wifiRead, &c);
	vm_log_info("LTcpClient::read return %d", c.lenProcessed);
	return c.lenProcessed;
}

boolean LTcpClient::wifiPeek(void *userData)
{
	LTcpClient *pThis = (LTcpClient*)userData;

	if(pThis->m_peekBuffered)
	{
		return true;
	}

	// read and store the peeked byte
	LTcpReadWriteContext cntx;
	cntx.buf = &pThis->m_peekByte;
	cntx.len = sizeof(pThis->m_peekByte);
	cntx.handle = pThis->m_handle.m_handle;
	cntx.serverHandle = pThis->m_handle.m_serverHandle;
	cntx.lenProcessed = 0;
	cntx.pInst = pThis;
	if(!wifiRead(&cntx))
	{
		vm_log_error("read fail in wifiPeek");
	}

	if (cntx.lenProcessed > 0)
	{
		pThis->m_peekBuffered = true;
	}
	else
	{
		pThis->m_peekBuffered = false;
	}

	return true;
}

int LTcpClient::peek()
{
	// peek() must return -1 when there is no data to read
	if (m_handle == -1)
	{
		vm_log_info("peek() with invalid handle, return -1");
		return -1;
	}

	LTask.remoteCall(&wifiPeek, this);

	if (m_peekBuffered)
	{
		return (int)m_peekByte;
	}
	else
	{
		return -1;
	}
}

void LTcpClient::stop()
{
	// release reference to handle
	m_handle = SharedHandle();
}

uint8_t LTcpClient::connected()
{
	return bool(m_handle);
}

LTcpClient::operator bool()
{
	return connected();
}

void LTcpClient::flush()
{
	// both read() and write() are inherently flush()ed.
	// so we simply return here.
	return;
}

VMINT LTcpClient::getAPN() const
{
	vm_log_error("LTcpClient::getAPN called. return -1");
	return -1;
}

