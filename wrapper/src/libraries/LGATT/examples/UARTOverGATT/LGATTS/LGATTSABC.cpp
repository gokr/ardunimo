#include "vmbtgatt.h"
#include "LGATTSABC.h"


static LGATTServiceInfo g_abc_decl[] =
{
    {TYPE_SERVICE, "6e400001-b5a3-f393-e0a9-e50e24dcca9e", TRUE, 0, 0, 0},
    {TYPE_CHARACTERISTIC, "6e400002-b5a3-f393-e0a9-e50e24dcca9e", FALSE, VM_GATT_CHAR_PROP_WRITE, VM_GATT_PERM_WRITE, 0},
    {TYPE_CHARACTERISTIC, "6e400003-b5a3-f393-e0a9-e50e24dcca9e", FALSE, VM_GATT_CHAR_PROP_NOTIFY | VM_GATT_CHAR_PROP_INDICATE, VM_GATT_PERM_READ, 0},
    {TYPE_DESCRIPTOR, "00002902-0000-1000-8000-00805f9b34fb", FALSE, VM_GATT_CHAR_PROP_NOTIFY, VM_GATT_PERM_READ | VM_GATT_PERM_WRITE, 0},
    {TYPE_END, 0, 0, 0, 0, 0}
};


LGATTServiceInfo *LGATTUT::onLoadService(int32_t index)
{
    return g_abc_decl;
}

