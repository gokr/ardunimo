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
#ifndef LTcpClient_h
#define LTcpClient_h
#include "Arduino.h"
#include "Print.h"
#include "Client.h"
#include "IPAddress.h"


/* DOM-NOT_FOR_SDK-BEGIN */
// partially mimic the behavior of std::shard_ptr
// since we don't have tr1/0x/11 support right now.
class SharedHandle
{
public:
    SharedHandle();
    explicit SharedHandle(VMINT handle);
    SharedHandle(VMINT clientHandle, VMINT serverHandle);
    SharedHandle(const SharedHandle& rhs);
    ~SharedHandle();

    void invalidateHandle();

    SharedHandle& operator =(const SharedHandle& rhs);
    operator bool() const;

    friend class LTcpClient;
    
protected:
    static const VMINT INVALID_HANDLE = -1;
    void releaseHandle();
    void incRef();
    void decRef();
    static boolean releaseTcpHandle(void *userData);

private:    
    VMINT m_handle;
    VMINT m_serverHandle;
    VMINT *m_pSharedCount;
};
/* DOM-NOT_FOR_SDK-END */


//LTcpClient Class
//
// LTcpClient is the base implementation of LWiFiClient and LGPRSClient. 
// You should not use LTcpClient instances directly. Instead, declare instances of LWiFiClient
// or LGPRSClient and use them to connect TCP socket through Wi-Fi and GPRS.
// 
// EXAMPLE:
// <code>
//     LWiFi.begin();
//     LWiFi.connect("open_network");
//     LWiFiClient c;
//     c.connect("www.website.com", 80);
//     LWiFi.end();
// </code>
class LTcpClient : public Client {

public:
  // DESCRIPTION
  //   Constructs a LTcpClient object which can be used to connect to the remote TCP server.
  //  
  // 
  // PARAMETERS
  //    N/A
  LTcpClient();

  /* DOM-NOT_FOR_SDK-BEGIN */
  LTcpClient(const LTcpClient &rhs);
  LTcpClient(VMINT handle);
  LTcpClient(VMINT handle, VMINT serverHandle);
  ~LTcpClient();
  /* DOM-NOT_FOR_SDK-END */

  // DESCRIPTION
  //   Connects to a TCP server.
  // 
  // PARAMETERS
  //   IPAddress: IPAddress object, e.g. IPAddress server (172, 21, 84, 11), that denotes server address
  //   port: TCP port to be connected
  // 
  // RETURNS
  //   1 if connected, 0 otherwise.
  //
  // EXAMPLE
  // <code>
  //     IPAddress server("127.0.0.1");
  //     client.connect(server, 80);  // client is an instance of LWiFiClient or LGPRSClient.
  // </code>
  virtual int connect(IPAddress ip, uint16_t port);

  // DESCRIPTION
  //   Connects to a TCP server.
  // 
  // PARAMETERS
  //   IPAddress: String, e.g. "172.21.84.11", that denotes server address
  //   port: TCP port to be connected
  // 
  // RETURNS
  //   1 if connected, 0 otherwise.
  //
  // EXAMPLE
  // <code>
  //     client.connect("www.somewebsite.com", 80);  // client is an instance of LWiFiClient or LGPRSClient.
  // </code>
  virtual int connect(const char *host, uint16_t port);

  // DESCRIPTION
  //   Writes data to server after connected to one.
  // 
  // PARAMETERS
  //   byte: Single byte to be sent
  // 
  // RETURNS
  //   Total written bytes.
  virtual size_t write(uint8_t);
  

  // DESCRIPTION
  //   Writes data to server after connected to one.
  // 
  // PARAMETERS
  //   byteArray: byteArray to be sent
  //   size: Size of byteArray, in bytes
  // 
  // RETURNS
  //   Total written bytes.
  //
  // EXAMPLE
  // <code>
  //     char *message = "GET /search?q=arduino HTTP/1.0";
  //     client.write((uint8_t*)message, strlen(message));  // client is an instance of LWiFiClient or LGPRSClient.
  // </code>
  virtual size_t write(const uint8_t *buf, size_t size);

  // DESCRIPTION
  //   Queries if there are incoming data from server side and returns the number of byte available for read after connecting to a server.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   0: There is no data available for read.
  //   1: There is data available for read. (The current implementation is not
  //      compatible with the Arduino. A compatible implementation would mean
  //      that the return value is the size of the data available for read, i.e.
  //      >0: Size of the data available for read, in bytes)
  //
  // EXAMPLE
  // <code>
  //     void loop() {
  //         // if there are incoming bytes available
  //         // from the server, read them and print them:
  //         if (client.available()) {
  //               char c = client.read();
  //               Serial.print(c);
  //     }
  // </code>
  virtual int available();

  // DESCRIPTION
  //   Reads the data sent from the server side and returns one single byte if there is no parameter given. If the buffer and buffer size are given, store the data in the buffer passed in.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   The data byte value. -1 is returned if there is no data available.
  //
  // EXAMPLE
  // <code>
  //     int v = client.read();
  //     if (v != -1)
  //     {
  //       Serial.print((char)v);
  //     }
  // </code>
  virtual int read();

  // DESCRIPTION
  //   Reads the data sent from the server side and returns one single byte if there is no parameter given. If the buffer and buffer size are given, store the data in the buffer passed in.
  // 
  // PARAMETERS
  //   buf: uint8_t buffer to store the incoming data
  //   size: Buffer size in bytes
  // 
  // RETURNS
  //   The actual read data in bytes are returned.
  //   >0: Total bytes read
  //   0: There are no data to read
  virtual int read(uint8_t *buf, size_t size);

  // DESCRIPTION
  //   Queries the first unread byte sent from the connected server side.
  //   This byte is not considered as read; therefore this method will return the same byte until read() is called. 
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   The first unread byte sent from server
  virtual int peek();

  // DESCRIPTION
  //   Drops all data sent from server side to this client object.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   N/A
  virtual void flush(); // flush is not currrently supported.

  // DESCRIPTION
  //   Disconnects from the connected TCP server.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   N/A
  virtual void stop();

  // DESCRIPTION
  //   Queries if this client object has been connected to a TCP server.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   1: Currently connected to a server
  //   0: Not connected to a server
  virtual uint8_t connected();

  // DESCRIPTION
  //   An LWiFiClient or LGPRSClient object will evaluate to true if it is connected.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   true: the client object is in connected state.
  //   flase: the client object is not in connected state.
  virtual operator bool();

public:
  friend class LTcpServer;

protected:
  /* DOM-NOT_FOR_SDK-BEGIN */
  SharedHandle m_handle;    // Manages underlying TCP resource handles. Reference counted, copy-constructable.
  VMINT8 m_peekByte;        // buffer to store the peek byte
  boolean m_peekBuffered;   // is the buffer valid or not

  static boolean connectIP(void *userData);
  static void connectCallback(VMINT handle, VMINT event, void *userData);
  static boolean wifiRead(void *userData);
  static boolean wifiWrite(void *userData);
  static boolean wifiPeek(void *userData);
    

  virtual VMINT getAPN() const = 0;
  /* DOM-NOT_FOR_SDK-END */
};

#endif  // LTcpClient_h