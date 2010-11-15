EXPORTED_SYMBOLS = ['tcpcrypt_getsessid'];

Components.utils.import("resource://gre/modules/ctypes.jsm");

var tcpcrypt = {};
tcpcrypt = function() {
    let lib = ctypes.open(ctypes.libraryName("tcpcrypt"));

    /* declare function prototypes */
    this._tcpcrypt_getsessid =
        lib.declare("tcpcrypt_getsessid",
                    ctypes.default_abi,
                    ctypes.char.ptr, /* return val (sessid) */
                    ctypes.char.ptr, /* remote_ip */
                    ctypes.uint16_t, /* remote_port */
                    ctypes.char.ptr, /* local_ip */
                    ctypes.uint16_t  /* local_port */
                    );
}

tcpcrypt.prototype = {
    getsessid: function (remoteHost, remotePort) {
        let remoteIP = this._resolve_host(remoteHost);
        let sessidCharPtr = this._tcpcrypt_getsessid(remoteIP, remotePort, "", 0);
        if (sessidCharPtr.isNull())
            return null;
        else
            return sessidCharPtr.readString();
    },

    _resolve_host: function (host) {
        let dnsService = Components.classes["@mozilla.org/network/dns-service;1"]
                 .createInstance(Components.interfaces.nsIDNSService);
        let dnsRecord = dnsService.resolve(host, 0);
        let ipString = dnsRecord.getNextAddrAsString();
        return ipString;
    }
}

var tcpcrypt_singleton;
if (!tcpcrypt_singleton)
    tcpcrypt_singleton = new tcpcrypt();

function tcpcrypt_getsessid(remoteHost, remotePort) {
    return tcpcrypt_singleton.getsessid(remoteHost, remotePort);
}
