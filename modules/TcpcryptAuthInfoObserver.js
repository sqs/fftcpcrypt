const EXPORTED_SYMBOLS = ['TcpcryptAuthInfoObserver'];

function TcpcryptAuthInfoObserver() {
  this._log("TcpcryptAuthInfoObserver() \n\n");
}

TcpcryptAuthInfoObserver.prototype = {
  _log: function(s) {
    dump("TcpcryptAuthInfoObserver: " + s + "\n");
  },

  observe: function(subject, topic, data) {
    if (topic == "http-on-examine-response") {
      var httpChannel = subject.QueryInterface(Components.interfaces.nsIHttpChannel);
      dump("-----------------------------------\n\n\n");
      this._log("securityInfo = " + httpChannel.securityInfo.toSource());
    }
  },

  get observerService() {
    return Components.classes["@mozilla.org/observer-service;1"]
                     .getService(Components.interfaces.nsIObserverService);
  },

  register: function() {
    this.observerService.addObserver(this, "http-on-examine-response", false);
  },

  unregister: function() {
    this.observerService.removeObserver(this, "http-on-examine-response");
  }

};