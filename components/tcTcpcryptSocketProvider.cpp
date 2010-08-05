#include "tcTcpcryptSocketProvider.h"

#include "mozilla/ModuleUtils.h"
#include "nsEmbedString.h"
#include "nsMemory.h"
#include "nsIClassInfoImpl.h"
#include <prio.h>
#include "nspr/private/pprio.h"

extern "C" {
#include "lib/tcpcrypt.h"
#include "tcpcrypt/tcpcrypt.h"
#include "tcpcrypt/tcpcrypt_ctl.h"
}

#include <stdio.h>
#include <cstring>
#include <errno.h>

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

        unsigned char buf[1024];
        int tc_enable;
        unsigned int len;

        len = sizeof(buf);
        if (tcpcrypt_getsockopt(osfd, IPPROTO_TCP, TCP_CRYPT_ENABLE,
                                buf, &len) == -1) {
            printf("errno = %d\n", errno);
            if (errno == ENOENT) {
                tc_enable = 0;
            } else {
                printf("getsockopt error for TCP_CRYPT_ENABLE: %s (%d)\n",
                       strerror(errno), errno);
                exit(1);
            }
        } else {
            tc_enable = !!buf[0];
        }

        printf("TCP_CRYPT_ENABLE = %s\n", tc_enable ? "YES" : "NO");
        //        printf("TCP_CRYPT_SESSID = %s\n");
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



