Components.utils.import("resource://fftcpcrypt/TcpcryptAuthInfoObserver.js");

const START_EVENT = "sessionstore-windows-restored";

function FFTcpcrypt() { }

FFTcpcrypt.prototype = {
  onLoad: function() {
    // this.strings = document.getElementById("fftcpcrypt-strings");
    this.observerService.addObserver(this, START_EVENT, false);
  },

  get observerService() {
    return Components.classes["@mozilla.org/observer-service;1"]
                     .getService(Components.interfaces.nsIObserverService);
  },

  observe: function(subject, topic, data) {
    if (topic == START_EVENT) {
      this._authInfoObserver = new TcpcryptAuthInfoObserver();
      this._authInfoObserver.register();
      this.observerService.removeObserver(this, START_EVENT);
    }
  },

  onUnload: function() {
    this._authInfoObserver.unregister();
  },

  onToolbarButtonCommand: function(e) {
    // just reuse the function above.  you can change this, obviously!
    fftcpcrypt.onMenuItemCommand(e);
  }
};

var fftcpcrypt;

window.addEventListener("load", function() {
    fftcpcrypt = new FFTcpcrypt();
    fftcpcrypt.onLoad();
  }, false);
window.addEventListener("unload", function() {
    fftcpcrypt.onUnload();
  }, false);
