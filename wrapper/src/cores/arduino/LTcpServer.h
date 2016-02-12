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
#ifndef LTcpServer_h
#define LTcpServer_h
#include "Arduino.h"	
#include "Print.h"
#include "Client.h"
#include "Server.h"
#include <vector>

class LTcpClient;

//LTcpServer Class
//
// LTcpServer is the base implementation of LWiFiServer and LGPRSServer. 
// You should not use LTcpServer instances directly. Instead, declare instances of LWiFiServer
// or LGPRSServer and use them to host TCP port through Wi-Fi and GPRS.
// 
// EXAMPLE:
// <code>
//     LWiFi.begin();
//     LWiFi.connect("open_network");
//     LWiFiServer server(80);
//     server.begin();  // start listening on port 80 via Wi-Fi network
// </code>
class LTcpServer : public Server {
public:

  /* DOM-NOT_FOR_SDK-BEGIN */	
  VMINT m_port;		// server port
  VMINT m_handle;   // server handle;
  /* DOM-NOT_FOR_SDK-END */	

public:

  // DESCRIPTION
  //   Creates a TCP server port on the device that can be connected by remote TCP clients.
  //   Call LTcpServer.begin() to start the server port.
  // 
  // PARAMETERS
  //   port: uint16_t port number. Click here to learn more about common TCP port definitions.
  // 
  // RETURNS
  //   N/A
  LTcpServer(uint16_t port);

  // DESCRIPTION
  //   Starts listening to a TCP port that accepts client connections.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   N/A
  void begin();

  // DESCRIPTION
  //   Close all
  //   Stops listening to a TCP port that accepts client connections.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   N/A
  void end();

  // DESCRIPTION
  //   Writes data to all clients connected to this server object.
  // 
  // PARAMETERS
  //   byte: Write a single byte to all connected clients.
  // 
  // RETURNS
  //   Actual written bytes.
  //   Since this counts all bytes written to all connected clients, this value can be bigger than the size parameter passed to this method.
  virtual size_t write(uint8_t);

  // DESCRIPTION
  //   Writes data to all clients connected to this server object.
  // 
  // PARAMETERS
  //   buf: Write an array of bytes to all connected clients.
  //   size: buf size in bytes
  // 
  // RETURNS
  //   Actual written bytes.
  //   Since this counts all bytes written to all connected clients, this value can be bigger than the size parameter passed to this method.
  virtual size_t write(const uint8_t *buf, size_t size);

  // DESCRIPTION
  //   returns the IP address of the server. An IP address is only valid after begin() is called.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   IP address of the server  
  IPAddress serverIP();

  using Print::write;

protected:
  /* DOM-NOT_FOR_SDK-BEGIN */
  // DESCRIPTION
  //   This is the internal implementation of available(). 
  //   Since we cannot return different class objects in different child class implementations, we return hClient/hServer handle
  //   instead and use these handles to create LWiFiClient / LGPRSClient objects in child class implementations.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   An pointer to LTcpClient object representing the connection between this server object and the remote client.
  //   This object will turn to false if there is no incoming connection.
  void availableImpl(VMINT& hClient, VMINT& hServer);
  /* DOM-NOT_FOR_SDK-END */

protected:
  /* DOM-NOT_FOR_SDK-BEGIN */
  virtual VMINT getAPN() const = 0;
  
  static boolean initServer(void *userData);
  static boolean deinitServer(void *userData);
  static boolean acceptConnection(void *userData);
  static void serverCallback(VMINT handle, VMINT event, VMINT param, void *user_data);
  static boolean wifiServerWrite(void *userData);
  
  std::vector<VMINT> m_clients;
  /* DOM-NOT_FOR_SDK-END */	
};

#endif
