#include "LGATTUUID.h"

#define UUID_STR_LEN_128    (32)
#define UUID_STR_LEN_16     (8)
#define UUID_STR_LEN_2      (4)
static uint32_t uuid_squeeze(uint8_t* str, uint8_t ch)
{
    uint32_t i,j;
    for (i = 0, j = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ch)
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';

    return j;
}

static uint8_t chr2u8(char chr)
{
	uint8_t ret = 0;
	if(chr >= '0' && chr <= '9')
	{
		ret = chr - '0';
	}
	else if(chr >= 'a' && chr <= 'f')
	{
		ret = chr - 'a' + 10;
	}
	else if(chr >= 'A' && chr <= 'F')
	{
		ret = chr - 'A' + 10;
	}
	return ret;
}

static void str2uuid_int(const char* str, uint8_t* uuid)
{
    uint32_t len = 0;
    uint8_t* uuid_str = NULL;
    uint32_t uuid_len = 0;
    int i,j;
	uint8_t H4 = 0;
	uint8_t L4 = 0;

    len = strlen((const char *)str); //mmi_chset_utf8_strlen(str);
    uuid_str = (uint8_t*)malloc(len + 1);
    if (uuid_str != NULL)
    {
        memset(uuid_str, 0x0, len+1);
        memcpy(uuid_str, str, len);
        uuid_str[len] = '\0';                
        
        uuid_len = uuid_squeeze((uint8_t*)uuid_str, '-');
        
        switch (uuid_len)
        {
        case UUID_STR_LEN_128:
        case UUID_STR_LEN_16:
        case UUID_STR_LEN_2:
            {
                for (i = 0, j = uuid_len - 2; j >= 0; j -= 2)
                {
                	H4 = chr2u8(uuid_str[j]);
					L4 = chr2u8(uuid_str[j+1]);
                	uuid[i] = H4*16 + L4;
                    i++;
                }
                //uuid->len = i;
            }
            break;
        default:
            break;
        }

        free(uuid_str);
        uuid_str = NULL;
    }
    else
    {
        //APP_LOG("int_gatt_str_to_uuid no memory");
    }

}



LGATTUUID::LGATTUUID()
{
    memset(&_uuid, 0, sizeof(_uuid));
}

LGATTUUID::LGATTUUID(uint16_t uuid)
{
    _uuid.len = sizeof(uint16_t);
    _uuid.uuid[1] = (uint8_t)(uuid >> 8);
    _uuid.uuid[0] = (uint8_t)uuid;
    _uuid.uuid[2] = 0;
}

LGATTUUID::LGATTUUID(const char *uuid)
{
    str2uuid(_uuid.uuid, uuid);
    _uuid.len = sizeof(_uuid.uuid);
    //Serial.print(*this);
    //Serial.println();
}

LGATTUUID::LGATTUUID(const VM_BT_UUID &uuid)
{
    _uuid = uuid;
}


bool LGATTUUID::operator==(const LGATTUUID& uuid) const 
{
    if (_uuid.len != uuid._uuid.len)
        return false;
    return !memcmp(_uuid.uuid, uuid._uuid.uuid, _uuid.len);
}

bool LGATTUUID::operator==(const char* uuid) const
{
    LGATTUUID tmp_uuid(uuid);
    if (tmp_uuid == *this)
    {
        return true;
    }

    return false;
}

// Overloaded index operator to allow getting and setting individual octets of the address
uint8_t LGATTUUID::operator[](int index) const 
{
    return _uuid.uuid[index];
}

uint8_t& LGATTUUID::operator[](int index)
{
    return _uuid.uuid[index];
}

// Overloaded copy operators to allow initialisation of LGATTUUID objects from other types
LGATTUUID& LGATTUUID::operator=(const char *uuid)
{
    _uuid.len = sizeof(_uuid.uuid);
    str2uuid(_uuid.uuid, uuid);

    return *this;
}

LGATTUUID& LGATTUUID::operator=(uint16_t uuid)
{
    _uuid.len = sizeof(uint16_t);
    _uuid.uuid[1] = (uint8_t)(uuid >> 8);
    _uuid.uuid[0] = (uint8_t)uuid;
    _uuid.uuid[2] = 0;
    return *this;
}

LGATTUUID& LGATTUUID::operator=(const VM_BT_UUID &uuid)
{
    _uuid = uuid;
    return *this;
}

size_t LGATTUUID::printTo(Print& p) const
{
    size_t n = 0;
    for (int i =_uuid.len-1; i >= 0; i--)
    {
        if (_uuid.uuid[i] <= 0xf)
            p.print('0');
        n += p.print(_uuid.uuid[i], HEX);
        if (12 == i || 
            10 == i || 
            8 == i ||
            6 == i)
            n += p.print('-');
    }

    return n;
    

    return 0;
}

void LGATTUUID::str2uuid(uint8_t *uuid_dst, const char *uuid) const
{
    str2uuid_int(uuid, uuid_dst);
}

