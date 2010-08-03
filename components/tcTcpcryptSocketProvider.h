#ifndef _TCTCPCRYPTSOCKETPROVIDER_H
#define _TCTCPCRYPTSOCKETPROVIDER_H

#include "nsISocketProvider.h"

// ecc32972-1cb3-484e-bdeb-907526dbf4eb
#define TC_TCPCRYPTSOCKETPROVIDER_CID \
  { 0xecc32972, 0x1cb3, 0x484e,                         \
      { 0xbd, 0xeb, 0x90, 0x75, 0x26, 0xdb, 0xf4, 0xeb}}

class tcTcpcryptSocketProvider : public nsISocketProvider
{
public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSISOCKETPROVIDER
    
    ~tcTcpcryptSocketProvider();
};

#endif // _TCTCPCRYPTSOCKETPROVIDER_H
