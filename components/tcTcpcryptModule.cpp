#include "mozilla/ModuleUtils.h"
#include "nsIClassInfoImpl.h"

#include "tcTcpcryptSocketProvider.h"

#include <stdio.h>
#include <stdlib.h>

NS_GENERIC_FACTORY_CONSTRUCTOR(tcTcpcryptSocketProvider)

NS_DEFINE_NAMED_CID(TC_TCPCRYPTSOCKETPROVIDER_CID);

static const mozilla::Module::CIDEntry kTcpcryptSocketProviderCIDs[] = {
    { &kTC_TCPCRYPTSOCKETPROVIDER_CID, false, NULL, tcTcpcryptSocketProviderConstructor },
    { NULL }
};

static const mozilla::Module::ContractIDEntry kTcpcryptSocketProviderContracts[] = {
    { TC_TCPCRYPTSOCKETPROVIDER_CONTRACTID, &kTC_TCPCRYPTSOCKETPROVIDER_CID },
    { NULL }
};

static const mozilla::Module kTcpcryptSocketProviderModule = {
    mozilla::Module::kVersion,
    kTcpcryptSocketProviderCIDs,
    kTcpcryptSocketProviderContracts,
    NULL
};

NSMODULE_DEFN(tcTcpcryptModule) = &kTcpcryptSocketProviderModule;
