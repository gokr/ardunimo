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
#ifndef ludp_h
#define ludp_h

#include <Udp.h>
#include <vector>

#define UDP_TX_PACKET_MAX_SIZE 24

//LUDP Class
//
// LUDP is the base implementation of LWiFiUDP and LGPRSUDP. 
// You should not use LUDP instances directly. Instead, declare instances of LWiFiUDP
// or LGPRSUDP and use them to perform UDP socket operations.
//
// Unlike LTcpClient and LTcpServer, a LUDP instance can send to and receive from multiple addresses. 
// To achieve this, beginPacket() should be called first to assign remote address and port, followed by write() and finally endPacket().
// Receiving packets works in a similar way. parsePacket() should be called first. After parsePacket() returns non-zero value, 
// methods read(), available(), remoteIP() and remotePort() becomes meaningful.
// Each call to parsePacket() method starts the processing of a new incoming packet, which may have different retrun values from methods like remoteIP() and remotePort().
// 
// EXAMPLE:
// <code>
//     LWiFi.begin();
//     LWiFiUDP u;
//     u.begin(1234);  // host UDP port on 1234
//     u.beginPacket(IPAddress(127.0.0.1), 123);  // start sending UDP datagram to 127.0.0.1 port 123
//     u.write(0);  // the content is a single byte of value 0
//     u.endPacket();  // actually send the packet
// </code>
class LUDP : public UDP {
  /* DOM-NOT_FOR_SDK-BEGIN */
protected:
  uint16_t m_port; // local port to listen on
  VMINT m_serverHandle;

  IPAddress m_sendToIP; // remote IP address for outgoing packet whilst it's being processed
  uint16_t m_sendToPort; // remote port for the outgoing packet whilst it's being processed
  std::vector<VMUINT8> m_writeBuffer;
  VMINT m_writePos;

  IPAddress m_recvIP; // remote IP address for outgoing packet whilst it's being processed
  uint16_t m_recvPort; // remote port for the outgoing packet whilst it's being processed
  std::vector<VMUINT8> m_recvBuffer;
  VMINT m_recvPos;

  static const VMINT INIT_WRITE_BUFFER_SIZE = 32;
  static const VMINT INIT_RECV_BUFFER_SIZE = 1024;  // typical MTU of web is 512 bytes, 1KB buffer should be sufficient

  static boolean udpBegin(void* userdata);
  static boolean udpStop(void* userdata);
  static boolean udpSend(void* userdata);
  static boolean udpRecv(void* userdata);
  static void udpCallback(VMINT hdl, VMINT event);

protected:
  // child class shoudl return proper APN enum
  virtual VMINT getAPN() const = 0;
  /* DOM-NOT_FOR_SDK-END */

public:

  // DESCRIPTION
  //   Constructor. LUDP cannot be instantiated directly. Use LWiFiUDP or LGPRSUDP instead.
  //
  // EXAMPLE
  // <code>
  //     LWiFiUDP u;
  //     u.begin(1234);   // start UDP on port 1234
  // </code>
  LUDP();

  // DESCRIPTION
  //   Destructor. LUDP will close resources when it is destroyed.
  //
  // EXAMPLE
  // <code>
  //     do{
  //        LWiFiUDP u;
  //        u.begin(1234);   // start UDP on port 1234
  //     }while(0);
  //     // LWiFiUDP will release the resource
  // </code>
  ~LUDP();

  // DESCRIPTION
  //   Initializes UDP function, and start listening on specified local port.
  // 
  // PARAMETERS
  //   port: the port number to listening for incoming UDP datagram
  // 
  // RETURNS
  //   >= 1 if succeeded
  //   <= 0 if failed
  //
  // EXAMPLE
  // <code>
  //     udp.begin(1234);   // start UDP on port 1234
  // </code>
  virtual uint8_t begin(uint16_t port);

  // DESCRIPTION
  //   Stop listening for UDP datagram and uninitializes UDP module.
  // 
  // PARAMETERS
  //   N/A
  //
  // EXAMPLE
  // <code>
  //     udp.begin(1234);   // start UDP on port 1234
  //     udp.stop();  // stops UDP
  // </code>
  virtual void stop();  

  // DESCRIPTION
  //   Start constructing an UDP datagrams to a remote host specified by IP address and port.
  //   Call write() subsequently to construct the datagram content.
  //   Then call endPacket() to actually send it.
  // 
  // PARAMETERS
  //   ip: the IP address of the remote host
  //   port: the port on the remote host
  // 
  // RETURNS
  //   1 if succeeded, 0 if failed.
  //
  // EXAMPLE
  // <code>
  //     udp.begin(1234);   // start UDP on port 1234
  //     udp.beginPacket(IPAddress(127, 0, 0, 1), 56);  // start a packet sending to IP 127.0.0.1 on port 56.
  //     udp.write(0);  // write a byte of value 0 to the packet
  //     udp.endPacket();  // actually send the packet.
  // </code>
  virtual int beginPacket(IPAddress ip, uint16_t port);

  // DESCRIPTION
  //   Start constructing an UDP datagrams to a remote host specified by URL address and port.
  //   Call write() subsequently to construct the datagram content.
  //   Then call endPacket() to actually send it.
  // 
  // PARAMETERS
  //   host: URL of the remote host
  //   port: the port on the remote host
  // 
  // RETURNS
  //   1 if succeeded, 0 if failed.
  //
  // EXAMPLE
  // <code>
  //     udp.begin(1234);   // start UDP on port 1234
  //     udp.beginPacket("www.somewebsite.com", 56);  // start a packet sending to www.somewebsite.com on port 56.
  //     udp.write(0);  // write a byte of value 0 to the packet
  //     udp.endPacket();  // actually send the packet.
  // </code>
  virtual int beginPacket(const char *host, uint16_t port) = 0;

  // DESCRIPTION
  //   Send the datagram after calling beginPacket() and write().
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   1 if succeeded, 0 if failed.
  //
  // EXAMPLE
  // <code>
  //     udp.begin(1234);   // start UDP on port 1234
  //     udp.beginPacket("www.somewebsite.com", 56);  // start a packet sending to www.somewebsite.com on port 56.
  //     udp.write(0);  // write a byte of value 0 to the packet
  //     udp.endPacket();  // actually send the packet.
  // </code>
  virtual int endPacket();

  // DESCRIPTION
  //   Append 1 single byte into the datagram
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   1 if succeeded, 0 if failed.
  virtual size_t write(uint8_t);

  // DESCRIPTION
  //   Append a buffer into the datagram.
  // 
  // PARAMETERS
  //   buffer: the buffer to be appended
  //   size: size of the buffer
  // RETURNS
  //   1 if succeeded, 0 if failed.
  virtual size_t write(const uint8_t *buffer, size_t size);
  
  using Print::write;

  // DESCRIPTION
  //   Check if there are incoming UDP datagrams. read() should be then used to actually read the data from packet.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   size of the datagram packet, in bytes. 0 is returned if there is no incoming packet.
  //
  // EXAMPLE
  // <code>
  //     if(udp.parsePacket()){
  //     Serial.println("packet received");
  //     // read the packet, byte by byte
  //     int v = udp.read();
  //     while(v != -1){
  //         Serial.print((char)v);
  //         v = udp.read();
  //     }
  // </code>
  virtual int parsePacket();

  // DESCRIPTION
  //   Number of remaining bytes in the current packet. Only meaningful after parsePacket() returns non-zero.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   size of the remaining data, in bytes.
  virtual int available();

  // DESCRIPTION
  //   Read 1 byte from current packet after calling parsePacket();
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   value of the data byte. -1 is returned if there is no more data available.
  virtual int read();

  // DESCRIPTION
  //   Read up to len bytes from current packet after calling parsePacket();
  // 
  // PARAMETERS
  //   buffer: output buffer to be read into
  //   len: maximum allowed length of buffer
  // 
  // RETURNS
  //   number of bytes read into buffer
  virtual int read(unsigned char* buffer, size_t len);

  /* DOM-NOT_FOR_SDK-BEGIN */
  // Read up to len characters from the current packet and place them into buffer
  // Returns the number of characters read, or 0 if none are available
  virtual int read(char* buffer, size_t len) { return read((unsigned char*)buffer, len); };
  /* DOM-NOT_FOR_SDK-END */

  // Return the next byte from the current packet without moving on to the next byte

  // DESCRIPTION
  //   return the value of next available byte from current packet. The byte remains in the packet.
  // 
  // PARAMETERS
  //   N/A
  // 
  // RETURNS
  //   value of the data byte. -1 is returned if there is no data available.
  virtual int peek();

  // DESCRIPTION
  //   Stop processing current packet.
  // 
  // PARAMETERS
  //   N/A
  virtual void flush();

  // DESCRIPTION
  //   retrieve the sender IP address of the current packet started by parsePacket()
  // 
  // RETURNS
  //   sender address of the current incoming packet.
  virtual IPAddress remoteIP() { return m_recvIP; };

  // DESCRIPTION
  //   retrieve the sender port of the current packet started by parsePacket()
  // 
  // RETURNS
  //   sender port of the current incoming packet.
  virtual uint16_t remotePort() { return m_recvPort; };
};

#endif
