const Cc = Components.classes;
const Ci = Components.interfaces;

Components.utils.import("resource://gre/modules/XPCOMUtils.jsm");

function tcHttptHandler() {
  dump("@@@@@@@@@@@@@@@@@@@@@\n");
}

tcHttptHandler.prototype = {
  classDescription: 'httpt protocol handler',
  classID: Components.ID('{45174059-8f44-45c6-9826-3f7e367cef2f}'),
  contractID: "@mozilla.org/network/protocol;1?name=httpt",
  QueryInterface: XPCOMUtils.generateQI([Ci.nsIProtocolHandler]),

  scheme: "httpt",
  defaultPort: 80,
  protocolFlags: Ci.nsIProtocolHandler.URI_NOAUTH,

  /* nsIHttpProtocolHandler */ 
  savedHttpHandler: 
    Components.classesByID["{4f47e42e-4d23-4dd3-bfda-eb29255e9ea3}"]. 
    getService(Components.interfaces.nsIHttpProtocolHandler), 

  allowPort: function(port, scheme) {
    return true;
  },

  newURI: function(aSpec, aOriginCharset, aBaseURI) {
    let url = Components.classes["@mozilla.org/network/standard-url;1"].
              createInstance(Components.interfaces.nsIStandardURL);
    url.init(Components.interfaces.nsIStandardURL.URLTYPE_AUTHORITY,
             this.defaultPort, aSpec, aOriginCharset, aBaseURI);
    return url.QueryInterface(Components.interfaces.nsIURI);
  },

  newChannel: function(aURI) {
    return this.savedHttpHandler.newProxiedChannel(aURI, null);
  }
};

const NSGetFactory = XPCOMUtils.generateNSGetFactory([tcHttptHandler]);