#include "tcTcpcryptSocketProvider.h"

#include "mozilla/ModuleUtils.h"
#include "nsEmbedString.h"
#include "nsMemory.h"
#include "nsIClassInfoImpl.h"
#include <prio.h>
#include "nspr/private/pprio.h"
#include <stdio.h>

tcTcpcryptSocketProvider::tcTcpcryptSocketProvider()
{

}

tcTcpcryptSocketProvider::~tcTcpcryptSocketProvider()
{

}

NS_IMPL_CLASSINFO(tcTcpcryptSocketProvider, 
                  NULL, 
                  0, 
                  TC_TCPCRYPTSOCKETPROVIDER_CID)

NS_IMPL_ISUPPORTS1_CI(tcTcpcryptSocketProvider, nsISocketProvider)


NS_IMETHODIMP 
tcTcpcryptSocketProvider::NewSocket(PRInt32 aFamily,
                                    const char *aHost, 
                                    PRInt32 aPort, 
                                    const char *aProxyHost, 
                                    PRInt32 aProxyPort,
                                    PRUint32 aFlags,
                                    PRFileDesc **fd, 
                                    nsISupports **aSecurityInfo)
{
    nsresult rv;
    int osfd;
    *fd = PR_OpenTCPSocket(aFamily);
    rv = *fd ? NS_OK : NS_ERROR_OUT_OF_MEMORY;

    if (!NS_FAILED(rv)) {
        printf("---------------------------\n");
        printf("NewSocket: %p\n", *fd);
        osfd = PR_FileDesc2NativeHandle(*fd);
        printf("osfd = %d\n", osfd);
        printf("---------------------------\n");
    }

    return rv;
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
    printf("333333333333333333333333333333333\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}



