#ifndef __GATT_SERVER_H__
#define __GATT_SERVER_H__
//#ifdef __cplusplus
//extern "C" 
//{
//#endif


#include "LGATT.h"
#include "LGATTServer.h"
#include "vmbtgatt.h"
#define MAX_ATTRS 8


boolean gattServiceRemoteCallHandler(void *userdata);

class GATTService
{
public:
    boolean init(LGATTService &s);
    void deinit(LGATTService &s);

    
    static boolean rBegin(void *userdata);
    static boolean rSend(void *userdata);
    static boolean rEnd(void *userdata);
    
private:

    static void initCB(LGATTService *service);
    static void *alloc(); /* gatts_srv_ctx_t */
    static void dealloc(void *ptr); /* gatts_srv_ctx_t */
    static VMINT toRegist(LGATTService *service);
    static VMINT addDeclaration(LGATTService *service, VM_ATT_HANDLE srvc_handle, ard_decl_type_enum type);


    static void register_server_callback(void *reg_ctx, VM_OS_STATUS status, vm_bt_uuid_struct *app_uuid);
    static void service_added_callback(VM_OS_STATUS status, void *reg_ctx,
                VM_GATT_SVC_UUID *srvc_id, VM_ATT_HANDLE srvc_handle);
    static void characteristic_added_callback(VM_OS_STATUS status, void *reg_ctx,
                    VM_ATT_UUID *uuid, VM_ATT_HANDLE srvc_handle, VM_ATT_HANDLE char_handle);
    static void descriptor_added_callback(VM_OS_STATUS status, void *reg_ctx,
                    VM_ATT_UUID *uuid, VM_ATT_HANDLE srvc_handle, VM_ATT_HANDLE descr_handle);
    static void service_started_callback(VM_OS_STATUS status, void *reg_ctx,
                                             VM_ATT_HANDLE srvc_handle);
    static void listen_callback(void *reg_ctx, VM_OS_STATUS status);
    static void connection_callback(vm_gatt_conn_struct *conn, VMBOOL connected, VM_BD_ADDR *bd_addr);
    static void request_read_callback(vm_gatt_conn_struct *conn, VMUINT16 trans_id, VM_BD_ADDR *bd_addr,
                                          VM_ATT_HANDLE attr_handle, VMUINT16 offset, VMBOOL is_long);
    static void request_write_callback(vm_gatt_conn_struct *conn, VMUINT16 trans_id, VM_BD_ADDR *bd_addr,
                                           VM_ATT_HANDLE attr_handle, VM_ATT_VALUE *value, VMUINT16 offset,
                                           VMBOOL need_rsp, VMBOOL is_prep);


    static vm_gatts_callback_struct _gatts_service_cb;

};

boolean gattServerRemoteCallHandler(void *userdata);
class GATTServer
{
public:


    static boolean rBegin(LGATTServerClass *server);
    static boolean rEnd(LGATTServerClass *server);

    static boolean rEnQ(const gatts_q_node &node);

    static LGATTService *getCtxByUUID(vm_bt_uuid_struct *app_uuid);
    static LGATTService *getCtxByCTX(void *reg_ctx);
    static LGATTService *getCtxByHandle(void *reg_ctx, VM_ATT_HANDLE srvc_handle);
    
private:
    static void btcm_cb(VMUINT evt, void* param, void* user_data);
    static boolean init(LGATTServerClass *server);
    static boolean deinit(LGATTServerClass *server);

    static LGATTServerClass *_server;
    static VMINT _hdl_btcm;
};


//#ifdef __cplusplus
//}
//#endif

#endif
