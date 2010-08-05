FFTcpcrypt.prototype.onFirefoxLoad = function(event) {
  document.getElementById("contentAreaContextMenu")
          .addEventListener("popupshowing", function (e){ fftcpcrypt.showFirefoxContextMenu(e); }, false);
};

FFTcpcrypt.prototype.showFirefoxContextMenu = function(event) {
  // show or hide the menuitem based on what the context menu is on
  document.getElementById("context-fftcpcrypt").hidden = gContextMenu.onImage;
};

window.addEventListener("load", function() {
    fftcpcrypt.onFirefoxLoad();
  }, false);
