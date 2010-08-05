var fftcpcrypt = {
  onLoad: function() {
    // initialization code
    this.initialized = true;
    this.strings = document.getElementById("fftcpcrypt-strings");
  },

  onToolbarButtonCommand: function(e) {
    // just reuse the function above.  you can change this, obviously!
    fftcpcrypt.onMenuItemCommand(e);
  }
};

window.addEventListener("load", fftcpcrypt.onLoad, false);
