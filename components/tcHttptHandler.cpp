#include "tcHttptHandler.h"

#include "nsIHttpChannel.h"
#include "nsStringAPI.h"
#include "nsIURL.h"
#include "nsIStandardURL.h"
#include "nsISocketProviderService.h"
#include "nsISocketProvider.h"
#include "nsCOMPtr.h"
#include "nsXPCOM.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"

NS_IMPL_ISUPPORTS3(tcHttptHandler,
                   nsIHttpProtocolHandler,
                   nsIProxiedProtocolHandler,
                   nsIProtocolHandler)

tcHttptHandler::tcHttptHandler()
{
    // httpHandler = do_GetService(NS_NETWORK_PROTOCOL_CONTRACTID_PREFIX "http");
    // NS_ASSERTION(httpHandler.get() != nsnull, "no http handler? from httpt");
    // return NS_OK;
}

nsresult
tcHttptHandler::Init()
{
    nsresult rv;
    nsIServiceManager *sm;

    rv = NS_GetServiceManager(&sm);
    if (NS_FAILED(rv)) return rv;

    rv = sm->GetServiceByContractID(NS_NETWORK_PROTOCOL_CONTRACTID_PREFIX "http",
                                    NS_GET_IID(nsIHttpProtocolHandler),
                                    getter_AddRefs(httpHandler));
    NS_ASSERTION(!NS_FAILED(rv), "getServiceByContractID failed");
    if (NS_FAILED(rv)) return rv;
    NS_ASSERTION(httpHandler.get() != nsnull, "no http handler? from httpt");
    return NS_OK;
}

NS_IMETHODIMP
tcHttptHandler::GetScheme(nsACString &aScheme)
{
    aScheme.AssignLiteral("httpt");
    return NS_OK;
}

NS_IMETHODIMP
tcHttptHandler::GetDefaultPort(PRInt32 *aPort)
{
    return httpHandler->GetDefaultPort(aPort);
}

NS_IMETHODIMP
tcHttptHandler::GetProtocolFlags(PRUint32 *aProtocolFlags)
{
    return httpHandler->GetProtocolFlags(aProtocolFlags);
}

NS_IMETHODIMP
tcHttptHandler::NewURI(const nsACString &aSpec,
                       const char *aOriginCharset,
                       nsIURI *aBaseURI,
                       nsIURI **_retval)
{
    return httpHandler->NewURI(aSpec, aOriginCharset, aBaseURI, _retval);
}

NS_IMETHODIMP
tcHttptHandler::NewChannel(nsIURI *aURI, nsIChannel **_retval)
{
    return httpHandler->NewChannel(aURI, _retval);
}

NS_IMETHODIMP
tcHttptHandler::AllowPort(PRInt32 aPort, const char *aScheme, PRBool *_retval)
{
    return httpHandler->AllowPort(aPort, aScheme, _retval);
}

NS_GENERIC_FACTORY_CONSTRUCTOR(tcHttptHandler);

static const nsModuleComponentInfo components[] = 
{
  {
    "tcHttptHandlerConstructor",
    TC_HTTPTHANDLER_CID,
    "@mozilla.org/network/protocol;1?name=httpt",
    tcHttptHandlerConstructor
  }
};

NS_IMPL_NSGETMODULE("tcHttptHandlerModule", components);
