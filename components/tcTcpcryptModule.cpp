#include "nsIGenericFactory.h"
#include "tcHttptHandler.h"
#include "tcTcpcryptSocketProvider.h"

#include <stdio.h>
#include <stdlib.h>

NS_GENERIC_FACTORY_CONSTRUCTOR_INIT(tcHttptHandler, Init);
NS_GENERIC_FACTORY_CONSTRUCTOR(tcTcpcryptSocketProvider);

static NS_METHOD tcHttptHandlerRegistration(nsIComponentManager *aCompMgr,
                                            nsIFile *aPath, 
                                            const char *registryLocation,
                                            const char *componentType,
                                            const nsModuleComponentInfo *info)
{
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    exit(1);
    // Registration specific activity goes here
    return NS_OK;
}


static const nsModuleComponentInfo components[] = 
{
    {
      "tcTcpcryptSocketProvider",
      TC_TCPCRYPTSOCKETPROVIDER_CID,
      "@mozilla.org/network/socket;2?name=tcpcrypt",
      tcTcpcryptSocketProviderConstructor
    },
    {
      "Tcpcrypt httpt handler",
      TC_HTTPTHANDLER_CID,
      NS_NETWORK_PROTOCOL_CONTRACTID_PREFIX "httpt",
      tcHttptHandlerConstructor,
      tcHttptHandlerRegistration
    }
};

NS_IMPL_NSGETMODULE(httpt, components);


