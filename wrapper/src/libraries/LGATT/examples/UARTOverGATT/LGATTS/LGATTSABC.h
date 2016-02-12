#ifndef __LGATT_ABC_H__
#define __LGATT_ABC_H__

#include "LGATTServer.h"


class LGATTUT : public LGATTService
{
    // prepare the data for profile
    virtual LGATTServiceInfo *onLoadService(int32_t index);
};


#endif
