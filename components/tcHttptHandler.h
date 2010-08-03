#ifndef _TCHTTPTHANDLER_H
#define _TCHTTPTHANDLER_H

#include "nsIHttpProtocolHandler.h"
#include "nsCOMPtr.h"

// 45174059-8f44-45c6-9826-3f7e367cef2f
#define TC_HTTPTHANDLER_CID \
  { 0x45174059, 0x8f44, 0x45c6,                         \
      { 0x98, 0x26, 0x3f, 0x7e, 0x36, 0x7c, 0xef, 0x2f}}


class tcHttptHandler : public nsIHttpProtocolHandler
{
public:
    // we basically just want to override GetScheme...
    // all other methods should be forwarded to the nsHttpHandler instance.
    
    NS_DECL_ISUPPORTS
    NS_DECL_NSIPROTOCOLHANDLER
    // NS_FORWARD_NSIPROTOCOLHANDLER        (httpHandler->)
    NS_FORWARD_NSIPROXIEDPROTOCOLHANDLER (httpHandler->)
    NS_FORWARD_NSIHTTPPROTOCOLHANDLER    (httpHandler->)


    tcHttptHandler();
    virtual ~tcHttptHandler() { }

    nsresult Init();

protected:
    nsCOMPtr<nsIHttpProtocolHandler> httpHandler;
};


#endif // _TCHTTPTHANDLER_H

