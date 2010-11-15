Components.utils.import("resource://fftcpcrypt/TcpcryptAuthInfoObserver.js");

function FFTcpcrypt() { }

FFTcpcrypt.prototype = {
  onLoad: function() {
    // this.strings = document.getElementById("fftcpcrypt-strings");
    this._authInfoObserver = new TcpcryptAuthInfoObserver(this);
  },

  get _curTabTcpcryptSessions() {
      delete this._curTabTcpcryptSessions;
      return this._curTabTcpcryptSessions = 
          document.getElementById("tcpcrypt-secinfo-sessid");
  },

  get _button() {
    delete this._button;
    return this._button = document.getElementById("tcpcrypt-toolbar-button");
  },

  get _popup() {
    delete this._popup;
    return this._popup = document.getElementById("tcpcrypt-secinfo-popup");
  },


  //***********************************************************************//
  // UI Callbacks

  onToolbarButtonCommand: function(event) {
      var sessions = gBrowser.mCurrentBrowser.tcpcryptSessions;
      var val = [];
      for (sessid in sessions) {
          var urls = sessions[sessid];
          val.push(sessid + ": " + urls.join("   "));
      }
      this._curTabTcpcryptSessions.textContent = val.join("\n");
      this._popup.openPopup(this._button, "after_end", 25, -10);
  },

  onPopupShowing: function(event) {
    // The popupshowing event fires for the menulist too, but we only want
    // to handle the events for the panel as a whole.
    if (event.target != this._popup)
      return;
  },


  //***********************************************************************//
  // Transport Callbacks

  onTcpcryptSessionEstablished: function (url, sessid) {
      dump("onTcpcryptSessionEstablished: " +
           url.spec + ", " + sessid + "\n");

      var browser = gBrowser.mCurrentBrowser;
      if (!browser.hasOwnProperty('tcpcryptSessions'))
          browser.tcpcryptSessions = {};
      if (!browser.tcpcryptSessions.hasOwnProperty(sessid))
          browser.tcpcryptSessions[sessid] = [];

      var items = browser.tcpcryptSessions[sessid];
      if (items.indexOf(url.spec) == -1) {
          browser.tcpcryptSessions[sessid].push(url.spec);
      }
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
