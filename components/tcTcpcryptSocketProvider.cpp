#include "tcTcpcryptSocketProvider.h"

#include "nsIGenericFactory.h"
#include <stdio.h>
//#include "nspr.h"

NS_IMPL_ISUPPORTS1(tcTcpcryptSocketProvider, nsISocketProvider);

tcTcpcryptSocketProvider::~tcTcpcryptSocketProvider()
{

}

NS_IMETHODIMP 
tcTcpcryptSocketProvider::NewSocket(PRInt32 aFamily,
                                    const char *aHost, 
                                    PRInt32 aPort, 
                                    const char *aProxyHost, 
                                    PRInt32 aProxyPort,
                                    PRUint32 aFlags,
                                    PRFileDesc **aFileDesc, 
                                    nsISupports **aSecurityInfo)
{
    NS_ENSURE_ARG_POINTER(aFileDesc);
  
    printf("@@@@@@@@@@@@@@@@@@@@@@@\n");
    
    return NS_OK;

    /*return nsISocketProvider::NewSocket(aFamily,
                                        aHost,
                                        aPort,
                                        aProxyHost,
                                        aProxyPort,
                                        aFlags,
                                        aFileDesc,
                                        aSecurityInfo);*/
}

NS_IMETHODIMP 
tcTcpcryptSocketProvider::AddToSocket(PRInt32 aFamily,
                                      const char *aHost,
                                      PRInt32 aPort,
                                      const char *aProxyHost,
                                      PRInt32 aProxyPort,
                                      PRUint32 aFlags,
                                      struct PRFileDesc *aFileDesc,
                                      nsISupports **aSecurityInfo)
{
    // does not make sense to strap a UDP socket onto an existing socket
    NS_NOTREACHED("Cannot layer UDP socket on an existing socket");
    return NS_ERROR_UNEXPECTED;
}



