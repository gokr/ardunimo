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
#include "LWiFi.h"
#include "vmhttp.h"
#include "vmlog.h"
#include "vmtcp.h"

LWiFiLoginInfo::LWiFiLoginInfo():
  m_enc(LWIFI_OPEN),
  m_password(NULL)
{
}

LWiFiLoginInfo::LWiFiLoginInfo(LWiFiEncryption enc, const String &password):
  m_enc(enc),
  m_password(password)
{
}

LWiFiLoginInfo::LWiFiLoginInfo(LWiFiEncryption enc, const String &password, const String &username):
  m_enc(enc),
  m_password(password),
  m_username(username)
{
}

struct LWiFiContext
{
  VM_SIGNAL_ID sig;

  LWiFiContext()
  {
    sig = vm_signal_init();
  }

  ~LWiFiContext()
  {
    vm_signal_deinit(sig);
    sig = 0;
  }
};

LWiFiClass::LWiFiClass()
{
  memset(&m_apInfo, 0, sizeof(m_apInfo));
  memset(&m_ipInfo, 0, sizeof(m_ipInfo));
  memset(&m_scanInfo, 0, sizeof(m_scanInfo));
  memset(&m_apParam, 0, sizeof(m_apParam));
}

static void onWiFiEnabled(void *userData, vm_wlan_req_res_enum result);

static void onWifiInitialized(void *userData, vm_wlan_req_res_enum result)
{
  if (result != VM_WLAN_REQ_RES_DONE)
  {
    vm_log_error("onWifiInitialized: result error code %d", result);
  }
  LTask.post_signal();
}

boolean wifiInitialize(void *userData)
{
  // enable WiFi (as mobile station) and wait for callback
  if (VM_WLAN_SET_MODE_STA != vm_wlan_mode_get())
  {
    vm_wlan_mode_set(VM_WLAN_SET_MODE_STA, &onWifiInitialized, NULL);
    return false;
  }

  // already initialized
  return true;
}

void LWiFiClass::begin()
{
  LTask.remoteCall(&wifiInitialize, NULL);
  return;
}

static void onWifiUninitialized(void *userData, vm_wlan_req_res_enum result)
{
  if (result != VM_WLAN_REQ_RES_DONE)
  {
    vm_log_error("onWifiUninitialized: result error code %d", result);
  }
  LTask.post_signal();
}

boolean wifiUnitinialize(void *userData)
{
  // enable WiFi (as mobile station) and wait for callback
  if (VM_WLAN_SET_MODE_OFF != vm_wlan_mode_get())
  {
    vm_wlan_mode_set(VM_WLAN_SET_MODE_OFF, &onWifiUninitialized, NULL);
    return false;
  }

  // already initialized
  return true;
}

void LWiFiClass::end()
{
  LTask.remoteCall(&wifiUnitinialize, NULL);
  return;
}

//------------------------------------
//	Begin() connection methods
//------------------------------------
struct LWiFiConnectContext
{
  vm_wlan_ap_info_struct apInfo;
  vm_wlan_conned_ap_info_struct connectedInfo;
  vm_wlan_ip_info_struct ipInfo;
  vm_wlan_conn_res_struct result;
  bool isWaitApInfo;
  LWiFiConnectContext()
  {
    memset(&apInfo, 0, sizeof(apInfo));
    memset(&ipInfo, 0, sizeof(ipInfo));
    memset(&result, 0, sizeof(result));
    memset(&connectedInfo, 0, sizeof(connectedInfo));
    isWaitApInfo = false;
  }

  ~LWiFiConnectContext()
  {
  }
};

static void onWifiConnected(void *user_data, vm_wlan_conn_res_struct *conn_res)
{
  vm_log_info("onWifiConnected (MMI)");
  LWiFiConnectContext *pContext = (LWiFiConnectContext*)user_data;

  // connect result
  pContext->result = *conn_res;

  vm_log_info("onWifiConnected result=%d", conn_res->result);

  if (VM_WLAN_RESULT_SUCCESS != pContext->result.result)
  {
    vm_log_info("FAILED ret=%d cause=%d", conn_res->result, conn_res->cause);
    // connect fail,
    // wakeup Arduino thread directly
    LTask.post_signal();
  }
  else
  {
    // connect OK,
    // retrieve AP & IP info.
    // in DHCP case, we may need to wait for IP ready
    vm_wlan_get_connected_ap_info((void*)&pContext->connectedInfo, VM_WLAN_AP_INFO_ALL);

    // We should then wait for IP info, which will be callbacked
  }
  return;
}

static void onWiFiIPReady(void *userData, vm_wlan_noti_struct *noti)
{
  vm_log_info("onWiFiIPReady notify_type=%d", noti->type);
  LWiFiConnectContext *pContext = (LWiFiConnectContext*)userData;

  if (VM_WLAN_NOTI_IP_AVAILABLE == noti->type)
  {
    vm_wlan_get_ip_info(&pContext->ipInfo);
    VMUINT8 *ip_addr = pContext->ipInfo.ip_addr;
    vm_log_info("get localIP address = %d, %d, %d, %d",
                ip_addr[0],
                ip_addr[1],
                ip_addr[2],
                ip_addr[3]);

    // unregister to prevent receiving duplicated data
    vm_wlan_dereg_noti(VM_WLAN_NOTI_IP_AVAILABLE, &onWiFiIPReady, pContext);

    // IP ready,
    // notify Arduino thread to wake up
    pContext->result.result = VM_WLAN_RESULT_SUCCESS;
    LTask.post_signal();
  }
}

static void onWiFiSnifferOff(void *userData, vm_wlan_sniffer_res_enum res)
{
    LWiFiConnectContext *pContext = (LWiFiConnectContext*)userData;

    if(VM_WLAN_SNIFFER_SUCCESS == res)
    {
        pContext->isWaitApInfo = false;
        onWiFiEnabled(pContext, VM_WLAN_REQ_RES_DONE);
    }
    else
    {
        vm_log_info("vm_wlan_sniffer_off fails, result=%d", res);
        pContext->result.result = VM_WLAN_RESULT_FAILED;
        LTask.post_signal();
    }
}

static void onWiFiSnifferOn(void *userData, vm_wlan_sniffer_on_res_struct *res)
{
    LWiFiConnectContext *pContext = (LWiFiConnectContext*)userData;

    vm_log_info("onWiFiSnifferOn result=%d, cb_type=%d", res->result, res->cb_type);
    if(VM_WLAN_SNIFFER_SUCCESS == res->result)
    {
        if(VM_WLAN_SNIFFER_ON_RES == res->cb_type)
        {
            
        }
        else if(VM_WLAN_SNIFFER_ON_AP_INFO == res->cb_type)
        {
            vm_wlan_prof_struct prof;
            memset(&prof, 0, sizeof(vm_wlan_prof_struct));
            memcpy(&prof, &(res->profile), sizeof(vm_wlan_prof_struct));
            pContext->apInfo.auth_mode = prof.auth_mode;
            strncpy((char*)pContext->apInfo.ssid, (char*)prof.ssid, VM_WLAN_PROF_MAX_SSID_LEN);
            strncpy((char*)pContext->apInfo.password, (char*)prof.password, VM_WLAN_PROF_PSWD_MAX_LEN);
            
            vm_log_info("auth_mode: %d", res->profile.auth_mode);            
            vm_log_info("ssid: %s", (char*)pContext->apInfo.ssid);
            vm_log_info("password: %s", (char*)pContext->apInfo.password);
            vm_wlan_sniffer_off(onWiFiSnifferOff, pContext);
        }
    }
    else
    {
        vm_log_info("vm_wlan_sniffer_on fails, result=%d", res->result);
        pContext->result.result = VM_WLAN_RESULT_FAILED;
        LTask.post_signal();
    }
}
static void onWiFiEnabled(void *userData, vm_wlan_req_res_enum result)
{
  LWiFiConnectContext *pContext = (LWiFiConnectContext*)userData;

  vm_log_info("onWiFiEnabled result=%d", result);

  do
  {
    if (VM_WLAN_REQ_RES_DONE != result)
    {
      vm_log_info("wifi status change error=%d", result);
      break;
    }

    if(true == pContext->isWaitApInfo)
    {
        VMINT snifferOnRet = vm_wlan_sniffer_on(NULL, &onWiFiSnifferOn, pContext);
        if(VM_WLAN_RESULT_PROCESSING != snifferOnRet)
        {
            vm_log_info("wlan sniffer on fails ret=%d", snifferOnRet);
            break;
        }
        vm_log_info("start waiting AP info");
        return;
    }

    vm_log_info("vm_wlan_reg_noti");

    // register IP callback
    vm_wlan_reg_noti(VM_WLAN_NOTI_IP_AVAILABLE, &onWiFiIPReady, pContext);

    vm_log_info("vm_wlan_connect");
    // connect to AP
    VMINT connectRet = vm_wlan_connect(&pContext->apInfo, &onWifiConnected, pContext);

    vm_log_info("vm_wlan_connect ret =%d", connectRet);
    if (connectRet != VM_WLAN_RESULT_PROCESSING)
    {
      vm_log_info("vm_wlan_connect fails ret=%d", connectRet);
      break;
    }

    vm_log_info("start waiting connect & IP address");
    return;
  }
  while (0);

  // fail and allow arduino thread to keep going
  vm_log_info("vm_wlan_mode_set cb result=%d", result);
  pContext->result.result = VM_WLAN_RESULT_FAILED;
  LTask.post_signal();
}

static boolean wifiBegin(void* userData)
{
  vm_log_info("wifiBegin (in MMI)");


  LWiFiConnectContext *pContext = (LWiFiConnectContext*)userData;

  const VMINT wlanStatus = vm_wlan_status();
  // check if we already connected
  if (wlanStatus & VM_WLAN_STA_STATUS_CONNECTED)
  {
    pContext->result.result = VM_WLAN_RESULT_STATE_ERROR;
    return true;
  }

  // first we enable WiFi and wait for callback
  if (VM_WLAN_SET_MODE_STA != vm_wlan_mode_get())
  {
    vm_wlan_mode_set(VM_WLAN_SET_MODE_STA, &onWiFiEnabled, pContext);
  }
  else
  {
    onWiFiEnabled(pContext, VM_WLAN_REQ_RES_DONE);
  }

  // block Arduino thread
  return false;
}

int LWiFiClass::wifiConnectImpl(LWiFiConnectContext &context)
{
  vm_log_info("wifiConnectImpl");
  LTask.remoteCall(&wifiBegin, &context);

  // return 1 when success. 0 when fail
  if (VM_WLAN_RESULT_SUCCESS == context.result.result)
  {
    // copy resulting information
    m_apInfo = context.connectedInfo;
    m_ipInfo = context.ipInfo;
    m_apParam.auth_mode = context.apInfo.auth_mode;
    strncpy((char*)m_apParam.psk, (char*)context.apInfo.password, VM_WLAN_PROF_PSWD_MAX_LEN);
    strncpy((char*)m_apParam.ssid, (char*)context.apInfo.ssid, VM_WLAN_PROF_MAX_SSID_LEN);
    return 1;
  }
  else
  {
    vm_log_info("wifiConnectImpl fails=%d", context.result.result);
    return 0;
  }

}

int LWiFiClass::connect(const char* ssid)
{
  // connect to open network
  LWiFiConnectContext context;
  strncpy((char*)context.apInfo.ssid, ssid, VM_WLAN_PROF_MAX_SSID_LEN);
  memset(context.apInfo.password, 0, sizeof(context.apInfo.password));
  context.apInfo.auth_mode = VM_WLAN_AUTH_MODE_OPEN;

  return wifiConnectImpl(context);
}

int LWiFiClass::connect(const char* ssid, const LWiFiLoginInfo &loginInfo)
{
  LWiFiConnectContext context;
  switch (loginInfo.m_enc)
  {
  case LWIFI_OPEN:
    context.apInfo.auth_mode = VM_WLAN_AUTH_MODE_OPEN;
    break;
  case LWIFI_WEP:
    context.apInfo.auth_mode = VM_WLAN_AUTH_MODE_WEP;
    break;
  case LWIFI_WPA:
    context.apInfo.auth_mode = VM_WLAN_AUTH_MODE_WPA_ONLY_PSK;
    break;
  }
  strncpy((char*)context.apInfo.ssid, ssid, VM_WLAN_PROF_MAX_SSID_LEN);
  strncpy((char*)context.apInfo.password, loginInfo.m_password.c_str(), VM_WLAN_PROF_PSWD_MAX_LEN);

  return wifiConnectImpl(context);
}

int LWiFiClass::connectSmart(void)
{
    LWiFiConnectContext context;
    context.isWaitApInfo = true;
    return wifiConnectImpl(context);
}

int LWiFiClass::connectWEP(const char* ssid, const char* key)
{
  // connect with WEP
  LWiFiConnectContext context;
  strncpy((char*)context.apInfo.ssid, ssid, VM_WLAN_PROF_MAX_SSID_LEN);
  strncpy((char*)context.apInfo.password, key, VM_WLAN_PROF_PSWD_MAX_LEN);
  context.apInfo.auth_mode = VM_WLAN_AUTH_MODE_WEP;

  return wifiConnectImpl(context);
}

int LWiFiClass::connectWPA(const char* ssid, const char *passphrase)
{
  // connect with WPA
  LWiFiConnectContext context;
  strncpy((char*)context.apInfo.ssid, ssid, VM_WLAN_PROF_MAX_SSID_LEN);
  strncpy((char*)context.apInfo.password, passphrase, VM_WLAN_PROF_PSWD_MAX_LEN);
  // There are only 4 modes supported in LINKIT:
  // VM_WLAN_AUTH_MODE_OPEN
  // VM_WLAN_AUTH_MODE_WEP
  // VM_WLAN_AUTH_MODE_WPA2_ONLY
  // VM_WLAN_AUTH_MODE_WPA_ONLY_PSK;
  // and the "VM_WLAN_AUTH_MODE_WPA_ONLY_PSK" mode
  // will automatically switch between WPA2 and WPA / WPA_PSK.
  // so we use this mode.
  context.apInfo.auth_mode = VM_WLAN_AUTH_MODE_WPA_ONLY_PSK;

  return wifiConnectImpl(context);
}

//------------------------------------
//	scanNetworks methods
//------------------------------------
struct LWiFiScanContext
{
  vm_wlan_scan_result_struct result;

  LWiFiScanContext()
  {
    memset(&result, 0, sizeof(result));
  }

  ~LWiFiScanContext()
  {

  }

  static void scanCallback(VMUINT32 job_id, void *user_data, vm_wlan_scan_result_struct *scan_res)
  {
    LWiFiScanContext *pContext = (LWiFiScanContext*)user_data;
    pContext->result = *scan_res;
    // result collected.
    vm_log_info("scanCallback scan_res=%d", scan_res->result);
    LTask.post_signal();
  }

  static boolean mmiCall(void *userData)
  {
    LWiFiScanContext *pContext = (LWiFiScanContext*)userData;
    const VMINT job = vm_wlan_scan(&scanCallback, pContext);
    vm_log_info("vm_wlan_scan ret=%d", job);
    if (job > 0)
    {
      // started scan,
      // let Arduino thread wait for signal.
      return false;
    }
    else
    {
      // failed to scan, post signal to continue;
      // return true;
      return false;
    }

  }
};

int8_t LWiFiClass::scanNetworks()
{
  vm_log_info("scanNetworks");
  LWiFiScanContext context;
  LTask.remoteCall(&LWiFiScanContext::mmiCall, &context);
  m_scanInfo = context.result;
  vm_log_info("scanNetworks ret=%d", m_scanInfo.ap_list_num);
  return m_scanInfo.ap_list_num;
}

char*	LWiFiClass::SSID(uint8_t networkItem)
{
  if (networkItem >= m_scanInfo.ap_list_num)
  {
    return NULL;
  }

  // length check
  vm_wlan_scan_ap_info_struct &apInfo = m_scanInfo.ap_list[networkItem];

  if (apInfo.ssid_len < VM_WLAN_WNDRV_SSID_MAX_LEN && apInfo.ssid_len >= 0)
  {
    apInfo.ssid[apInfo.ssid_len] = '\0';
  }

  return (char*)m_scanInfo.ap_list[networkItem].ssid;
}

int32_t LWiFiClass::RSSI(uint8_t networkItem)
{
  if (networkItem >= m_scanInfo.ap_list_num)
  {
    return 0;
  }

  return m_scanInfo.ap_list[networkItem].rssi;
}

//------------------------------------
//	status/domain resolve methods
//------------------------------------

static boolean wifiStatus(void *userData)
{
  vm_wlan_sta_status_enum *pStatus = (vm_wlan_sta_status_enum*)userData;
  *pStatus = (vm_wlan_sta_status_enum)vm_wlan_status();
}

LWifiStatus LWiFiClass::status()
{
  vm_wlan_sta_status_enum wlanStatus = VM_WLAN_STA_STATUS_INACTIVE;
  LTask.remoteCall(&wifiStatus, &wlanStatus);

  if (wlanStatus & VM_WLAN_STA_STATUS_BUSY)
  {
    // this should not happen to Arduino,
    // since we block until state change done.
    // so it should not return BUSY
    return LWIFI_STATUS_DISCONNECTED;
  }

  if (wlanStatus & VM_WLAN_STA_STATUS_INACTIVE)
  {
    return LWIFI_STATUS_DISABLED;
  }

  if (wlanStatus & VM_WLAN_STA_STATUS_CONNECTED)
  {
    return LWIFI_STATUS_CONNECTED;
  }

  if (wlanStatus & VM_WLAN_STA_STATUS_ACTIVE)
  {
    return LWIFI_STATUS_DISCONNECTED;
  }

  if (wlanStatus & VM_WLAN_STA_STATUS_INVALID_MAC)
  {
    return LWIFI_STATUS_DISABLED;
  }

  if (wlanStatus & VM_WLAN_STA_STATUS_SNIFFER)
  {
    return LWIFI_STATUS_DISCONNECTED;
  }
}

struct LWiFiResolveContext
{
  const char *domainName;
  vm_soc_dns_result dns;
  VMINT resolveState;

  LWiFiResolveContext():
      domainName(NULL),
      resolveState(VM_E_SOC_INVAL)
  {
    memset(&dns, 0, sizeof(dns));
  }

  ~LWiFiResolveContext()
  {
  }
};

static VMINT wifiResolveCallback(VMINT jobId, vm_soc_dns_result *pDNS, void *userData)
{
  vm_log_info("wifiResolveCallback");
  LWiFiResolveContext *pContext = (LWiFiResolveContext*)userData;
  unsigned char* ipArray = (unsigned char*)&pDNS->address[0];
  vm_log_info("DNS resolve callback, cause=%d, num=%d, address=%d.%d.%d.%d",
              pDNS->error_cause,
              pDNS->num,
              ipArray[0],
              ipArray[1],
              ipArray[2],
              ipArray[3]);

  // TODO: since we don't know the definition of error_cause yet,
  // treat all as OK.
  if (pDNS && pDNS != &pContext->dns)
  {
    vm_log_info("pDNS != pContext->dns");
    pContext->dns = *pDNS;
  }
  pContext->resolveState = VM_E_SOC_SUCCESS;
  LTask.post_signal();
}

static boolean wifiResolveDomainName(void *userData)
{
  LWiFiResolveContext *pContext = (LWiFiResolveContext*)userData;

  vm_log_info("vm_soc_get_host_by_name_ex: %s", pContext->domainName);
  pContext->resolveState = vm_soc_get_host_by_name_ex(VM_TCP_APN_WIFI,
                           pContext->domainName,
                           &pContext->dns,
                           &wifiResolveCallback,
                           pContext);
  vm_log_info("vm_soc_get_host_by_name_ex ret = %d", pContext->resolveState);

  if (pContext->resolveState > 0)
  {
    // not done yet
    return false;
  }

  switch (pContext->resolveState)
  {
  case VM_E_SOC_SUCCESS:  // Get IP address successfully, result is filled.
    return true;
  case VM_E_SOC_WOULDBLOCK:  // wait response from network, result could be gotten from callback.
    // need to wait, return directly
    // so MMI message loop may continue.
    return false;
  case VM_E_SOC_INVAL:  // invalid arguments: null domain_name, etc.
  case VM_E_SOC_ERROR:  // unspecified error
  case VM_E_SOC_LIMIT_RESOURCE:  // socket resources not available
  case VM_E_SOC_INVALID_ACCOUNT:  // invalid data account id
    return true;
  }
}

int LWiFiClass::hostByName(const char* aHostname, IPAddress& aResult)
{
  vm_log_info("hostByName");
  LWiFiResolveContext context;
  // no memory copy since we're blocking call
  context.domainName = aHostname;
  LTask.remoteCall(&wifiResolveDomainName, (void*)&context);

  vm_log_info("context.resolveState = %d", context.resolveState);
  unsigned char* ipArray = (unsigned char*)&context.dns.address[0];
  vm_log_info("Arduino DNS resolve callback, cause=%d, num=%d, address=%d.%d.%d.%d",
              context.dns.error_cause,
              context.dns.num,
              ipArray[0],
              ipArray[1],
              ipArray[2],
              ipArray[3]);
  // parse result
  if (VM_E_SOC_SUCCESS == context.resolveState)
  {
    // TODO: why are there multiple ip addresses?

    aResult = context.dns.address[0];

    vm_log_info("get IP=%d.%d.%d.%d",
                aResult[0],
                aResult[1],
                aResult[2],
                aResult[3]);
    return 1;
  }
  else
  {
    return 0;
  }
}

//------------------------------------
//	property methods
//------------------------------------
struct LWiFiDisconnectContext
{
  VM_SIGNAL_ID sigDisconnect;
  vm_wlan_req_res_enum result;

  LWiFiDisconnectContext():
      result((vm_wlan_req_res_enum)VM_WLAN_REQ_RES_FAILED)
  {
    sigDisconnect = vm_signal_init();
  }

  ~LWiFiDisconnectContext()
  {
    vm_signal_deinit(sigDisconnect);
  }
};

static void LWiFiOnDisconnect(void *userData, vm_wlan_req_res_enum res)
{
  LWiFiDisconnectContext *pContext = (LWiFiDisconnectContext*)userData;
  pContext->result = res;
  vm_signal_post(pContext->sigDisconnect);
}

static boolean wifiDisconnect(void* userData)
{
  LWiFiDisconnectContext *pContext = (LWiFiDisconnectContext*)userData;
  vm_wlan_disconnect(&LWiFiOnDisconnect, pContext);
}

int LWiFiClass::disconnect(void)
{
  LWiFiDisconnectContext context;

  LTask.remoteCall(&wifiDisconnect, &context);

  vm_signal_wait(context.sigDisconnect);

  return 0;
}


static boolean wifiMacAddress(void* userData)
{
  vm_log_info("wifiMacAddress called");
  LWiFiClass *pThis = (LWiFiClass*)userData;
  vm_wlan_prof_str_info_qry_struct qry;
  qry.dest = pThis->m_macAddress;
  qry.dest_len = VM_WLAN_WNDRV_MAC_ADDRESS_LEN;
  qry.req_len = VM_WLAN_WNDRV_MAC_ADDRESS_LEN;
  pThis->m_lastError = vm_wlan_get_mac_address(&qry);
  vm_log_info("wifiMacAddress called, result = %d", pThis->m_lastError);
  vm_log_info("req_len=%d", qry.req_len);
  return true;
}

uint8_t* LWiFiClass::macAddress(uint8_t* mac)
{
  // clear mac address
  //vm_log_info("macAddress called");
  memset(m_macAddress, 0, VM_WLAN_LOC_MAC_ADDR_LEN);
  LTask.remoteCall(&wifiMacAddress, this);
  if (mac)
  {
    memcpy(mac, m_macAddress, VM_WLAN_LOC_MAC_ADDR_LEN);
  }
  return (uint8_t*)&m_macAddress[0];
}

IPAddress LWiFiClass::localIP()
{
  return IPAddress(m_ipInfo.ip_addr);
}

IPAddress LWiFiClass::subnetMask()
{
  return IPAddress(m_ipInfo.netmask);
}

IPAddress LWiFiClass::gatewayIP()
{
  return IPAddress(m_ipInfo.gateway);
}

char* LWiFiClass::SSID()
{
  return m_apParam.ssid;
}

uint8_t* LWiFiClass::BSSID(uint8_t* bssid)
{
  memcpy(bssid, m_apInfo.bssid, VM_WLAN_WNDRV_MAC_ADDRESS_LEN);
  return bssid;
}

static boolean wifiConnectedAPRSSI(void *userdata)
{
  VMINT *rssi_out = (VMINT*)userdata;
  vm_wlan_get_connected_ap_info(rssi_out, VM_WLAN_AP_INFO_RSSI);
  return true;
}

int32_t LWiFiClass::RSSI()
{
  VMINT rssi_out = 0;
  LTask.remoteCall(&wifiConnectedAPRSSI, &rssi_out);
  return (int32_t)rssi_out;
}

//------------------------------------
//	singleton
//------------------------------------
LWiFiClass LWiFi;
