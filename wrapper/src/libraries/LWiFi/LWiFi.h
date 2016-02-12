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

#ifndef LWiFi_h
#define LWiFi_h

#include "Arduino.h"
#include "IPAddress.h"
#include "vmnwsetting.h"
#include "vmconn.h"
#include "WString.h"

class LWiFiConnectContext;

//LWiFiLoginInfo enum
enum LWiFiEncryption
{
  LWIFI_OPEN, // Open networks
  LWIFI_WEP,  // WEP encrypted networks
  LWIFI_WPA,  // WPA1 and WPA2 networks
};

//LWiFiLoginInfo enum
enum LWifiStatus
{
  LWIFI_STATUS_DISABLED,          // the LWiFi module is not enabled. use LWiFi.begin() to enable it.
  LWIFI_STATUS_DISCONNECTED,      // the LWiFi module is not connect to any AP, or the connection is lost due to bad signal strength
  LWIFI_STATUS_CONNECTED,         // the LWiFi module is connected to an AP
};

//LWiFiLoginInfo Class
// 
// This class is used as parameter for LWiFiClass.connect
// See the documentation of LWiFiClass.connect instead.
class LWiFiLoginInfo
{
  /* DOM-NOT_FOR_SDK-BEGIN */
public:
  LWiFiEncryption m_enc;
  String m_password;
  String m_username;
  
public:

  // connect to Open network
  LWiFiLoginInfo();

  // Set entryption type and password
  LWiFiLoginInfo(LWiFiEncryption enc, const String &password);

  // Set encryption type, password, and user name
  LWiFiLoginInfo(LWiFiEncryption enc, const String &password, const String &username);

  /* DOM-NOT_FOR_SDK-END */
};

//LWifiClass Class
// 
// LWifiClass exposes the WiFi AP scan and connect function of the LinkIt ONE board.
// Use LWiFi singleton object to access the actual functions. Do not declare LWiFiClass instances.
// After connected to an Wi-Fi access point, use LWiFiClient object to create TCP socket;
// or use LWiFiUDP object to create an UDP socket.
// 
// EXAMPLE:
// <code>
//     LWiFi.begin();
//     int nearbyAccessPointCount = LWiFi.scanNetworks();
//     LWiFi.end();
// </code>
class LWiFiClass
{
public:

  /* DOM-NOT_FOR_SDK-BEGIN */
  LWiFiClass();
  /* DOM-NOT_FOR_SDK-END */

  // DESCRIPTION
  //  turn on and initializes the WiFi module
  //
  // PARAMETERS
  //  N/A
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // turn on Wi-Fi module
  //     LWiFi.end();     // turn off Wi-Fi module
  // </code>
  void begin();

  // DESCRIPTION
  //  uninitialize and turn off the WiFi module
  //
  // PARAMETERS
  //  N/A
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // turn on Wi-Fi module
  //     LWiFi.end();     // turn off Wi-Fi module
  // </code>
  void end();

  // DESCRIPTION
  //  Start Wifi connection for OPEN networks
  //
  // PARAMETERS
  //  ssid: Pointer to the SSID string.
  // 
  // RETURNS
  // > 0: Succeed
  // <= 0: Fail
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // turn on Wi-Fi module
  //     LWiFi.connect("open_network_ssid");
  //     LWiFi.end();     // turn off Wi-Fi module
  // </code>
  int connect(const char* ssid);

  // DESCRIPTION
  //  Start Wifi connection to networks
  //  The login information are stored in loginInfo.
  //
  // PARAMETERS
  //  ssid: Pointer to the SSID string.
  //  loginInfo: an LWiFiKey that stores login information
  //
  // RETURNS
  // > 0: Succeed
  // <= 0: Fail
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // turn on Wi-Fi module
  //     LWiFi.connect("wep_network_ssid", LWiFiLoginInfo(LWIFI_WEP, "wep_password"));
  //     LWiFi.end();     // turn off Wi-Fi module
  // </code>
  int connect(const char* ssid, const LWiFiLoginInfo &loginInfo);

  // DESCRIPTION
  //  Start Wifi connection with WEP encryption.
  //  Configure a key into the device. The key type (WEP-40, WEP-104)
  //  is determined by the size of the key (5 bytes for WEP-40, 13 bytes for WEP-104).
  //
  // PARAMETERS
  //  ssid: Pointer to the SSID string.
  //  key_idx: The key index to set. Valid values are 0-3.
  //  key: Key input buffer.
  //
  // RETURNS
  // > 0: Succeed
  // <= 0: Fail
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // turn on Wi-Fi module
  //     LWiFi.connectWEP("wifi_ap_ssid", "mypassword");
  //     LWiFi.end();     // turn off Wi-Fi module
  // </code>
  int connectWEP(const char* ssid, const char* key);

  // DESCRIPTION
  //  Start Wifi connection with WPA/WPA-2 passphrase
  //
  // PARAMETERS
  //  ssid: Pointer to the SSID string.
  //  passphrase: Passphrase. Valid characters in a passphrase
  //              must be between ASCII 32-126 (decimal).
  //
  // RETURNS
  // > 0: Succeed
  // <= 0: Fail
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // turn on Wi-Fi module
  //     LWiFi.connectWPA("wifi_ap_ssid", "mypassword");
  //     LWiFi.end();     // turn off Wi-Fi module
  // </code>
  int connectWPA(const char* ssid, const char *passphrase);
 
  // DESCRIPTION
  //  Start Wifi connection with the configuration set from Smart phone
  //
  // PARAMETERS
  //  void
  // RETURNS
  // > 0: Succeed
  // <= 0: Fail
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // turn on Wi-Fi module
  //     LWiFi.connectSmart();
  //     LWiFi.end();     // turn off Wi-Fi module
  // </code>

  int connectSmart(void);

  // DESCRIPTION
  //  Disconnect from the WiFi AP
  //
  // RETURNS
  //  currently it always returns 0
  //
  // EXAMPLE
  // <code>
  //     LWiFi.begin();   // turn on Wi-Fi module
  //     LWiFi.connectWPA("wifi_ap_ssid", "mypassword");  // connect to an WPA-encrypted AP
  //     LWifi.disconnect();  // disconnect from the AP
  //     LWiFi.end();     // turn off Wi-Fi module
  // </code>
  int disconnect(void);

  // DESCRIPTION
  //  Get the interface MAC address.
  //
  // RETURNS
  //  pointer to uint8_t array with length VM_WLAN_LOC_MAC_ADDR_LEN
  //  which is defined as 6 bytes.
  //
  // EXAMPLE
  // <code>
  //     Serial.begin(115200);
  //     LWiFi.begin();
  //     uint8_t macAddress[VM_WLAN_WNDRV_MAC_ADDRESS_LEN] = {0};
  //     LWiFi.macAddress(macAddress);
  //     Serial.print("MAC Address is:");
  //     for(int i = 0; i < VM_WLAN_WNDRV_MAC_ADDRESS_LEN; ++i)
  //     {
  //       Serial.print(macAddress[i], HEX);
  //       Serial.print(":");
  //     }
  //     Serial.println();
  // </code>
  uint8_t* macAddress(uint8_t* mac);

  // DESCRIPTION
  //  Get the interface IP address.
  //
  // RETURNS
  //  Ip address value
  IPAddress localIP();

  // DESCRIPTION
  //  Get the interface subnet mask address.
  //
  // RETURNS
  //  subnet mask address value
  IPAddress subnetMask();

  // DESCRIPTION
  //  Get the gateway ip address.
  //
  // RETURNS
  //  gateway ip address value
  IPAddress gatewayIP();

  // DESCRIPTION
  //  Return the current SSID associated with the network
  //
  // RETURNS
  //  ssid string
  char* SSID();

  // DESCRIPTION
  //  Return the current BSSID associated with the network.
  //  It is the MAC address of the Access Point
  //
  // RETURNS
  //  pointer to uint8_t array with length WL_MAC_ADDR_LENGTH which is 6 bytes long.
  uint8_t* BSSID(uint8_t* bssid);

  // DESCRIPTION
  //  Return the current RSSI /Received Signal Strength in dBm)
  //  associated with the network
  //
  // RETURNS
  //  signed value in dB. A smaller (negative) value indicates weaker signal
  int32_t RSSI();

  // DESCRIPTION
  //  Start scan WiFi networks available
  //
  // RETURNS
  //  Number of discovered networks
  // 
  // EXAMPLE
  // <code>
  //     Serial.begin();
  //     int numOfAP = LWiFi.scanNetworks();
  //     Serial.print("number of WiFi AP found:");
  //     Serial.println(numOfAP);
  // </code>
  int8_t scanNetworks();

  // DESCRIPTION
  //  Return the SSID discovered during the network scan.
  //
  // PARAMETERS
  //  networkItem: specify from which network item want to get the information
  //
  // RETURNS
  //  ssid string of the specified item on the networks scanned list
  char*	SSID(uint8_t networkItem);

  // DESCRIPTION
  //  Return the RSSI of the networks discovered during the scanNetworks
  //
  // PARAMETERS
  //  networkItem: specify from which network item want to get the information
  //
  // RETURNS
  //  signed value of RSSI of the specified item on the networks scanned list
  int32_t RSSI(uint8_t networkItem);

  // DESCRIPTION
  //  Return Connection status.
  //
  // RETURNS
  //  one of the value defined in LWifiStatus.
  //  It can be
  //    LWIFI_STATUS_DISABLED: the LWiFi module is not enabled. use LWiFi.begin() to enable it.
  //    LWIFI_STATUS_DISCONNECTED: the LWiFi module is not connect to any AP, or the connection is lost due to bad signal strength
  //    LWIFI_STATUS_CONNECTED: the LWiFi module is connected to an AP
  LWifiStatus status();

  // DESCRIPTION
  //  Resolve the given hostname to an IP address.
  //
  // PARAMETERS
  //  param aHostname: Name to be resolved
  //  param aResult: IPAddress structure to store the returned IP address
  //
  // RETURNS
  //  1 if aIPAddrString was successfully converted to an IP address,
  //  else error code
  int hostByName(const char* aHostname, IPAddress& aResult);

  /* DOM-NOT_FOR_SDK-BEGIN */
  friend class LWiFiClient;
  friend class LWiFiServer;
  /* DOM-NOT_FOR_SDK-END */

public:
  /* DOM-NOT_FOR_SDK-BEGIN */
  char m_macAddress[VM_WLAN_LOC_MAC_ADDR_LEN];
  vm_wlan_ip_info_struct m_ipInfo;  // IP info after being connected
  vm_wlan_conned_ap_info_struct m_apInfo;  // This stores BSSID and RSSI of connectd AP
  vm_wlan_cfg_ap_struct m_apParam;  // This stores SSID for connected AP
  vm_wlan_scan_result_struct m_scanInfo;  // Info of scanned APs
  VMINT m_lastError;

private:
  int wifiConnectImpl(LWiFiConnectContext &context);
  /* DOM-NOT_FOR_SDK-END */
};

// use this LWiFi singleton to access the Wi-Fi functionality
extern LWiFiClass LWiFi;

#endif // #ifndef LWiFi_h
