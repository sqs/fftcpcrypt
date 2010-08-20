const EXPORTED_SYMBOLS = ['TcpcryptAuthInfoObserver'];


function setTimeout(func, delay)
{
var timer =
Components.classes["@mozilla.org/timer;1"].createInstance(Components.interfaces.nsITimer);
var callback = { that: this, notify: function () {
func.call(this.that); } };
timer.initWithCallback(callback, delay,
Components.interfaces.nsITimer.TYPE_ONE_SHOT);
return timer;
}


// reference to the interface defined in nsIHttpActivityObserver.idl
const nsIHttpActivityObserver = Components.interfaces.nsIHttpActivityObserver;
const nsISocketTransport = Components.interfaces.nsISocketTransport;

// reference to the required base interface that all components must support
const nsISupports = Components.interfaces.nsISupports;

function TcpcryptAuthInfoObserver(fftcpcrypt) {
  let c = "@mozilla.org/network/http-activity-distributor;1";
  let activityDistributor = Components.classes[c]
                            .getService(Components.interfaces.nsIHttpActivityDistributor);
  activityDistributor.addObserver(this);
  this._fftcpcrypt = fftcpcrypt;

  this._log("TcpcryptAuthInfoObserver() \n\n");
}

TcpcryptAuthInfoObserver.prototype = {
  _log: function(s) {
    dump("-- TcpcryptAuthInfoObserver: " + s + "\n");
  },

  observeActivity: function(channel, aActivityType, aActivitySubtype,
                            aTimestamp, aExtraSizeData, aExtraStringData)
  {
      if (true || aActivitySubtype == nsIHttpActivityObserver.ACTIVITY_SUBTYPE_RESPONSE_COMPLETE) {
        //setTimeout(function(){
        channel.QueryInterface(Components.interfaces.nsIChannel);
        dump(">>>> " + acType(aActivityType) + " : " + 
             acSubType(aActivitySubtype) + "\n:::: " +
             channel.URI.spec + "\n");
        if (channel.securityInfo) {
            let tcI = Components.interfaces.tcITransportSessionInfo;
            let tc  = channel.securityInfo.QueryInterface(tcI);
            dump("--------------------------------------------------\n"+
                 channel.URI.hostPort + ": " + 
                 "TCP_CRYPT_SESSID = " + tc.sessionID + "\n" +
                 "--------------------------------------------------\n");
            this._fftcpcrypt.onTcpcryptSessionEstablished(channel.URI, tc.sessionID);
            //},1);
        } else {
            dump("securityInfo is undefined\n");
        }
    }
  } 
};

function acType(a)
{
  switch (a) {
    case nsIHttpActivityObserver.ACTIVITY_TYPE_SOCKET_TRANSPORT:
      return "ACTIVITY_TYPE_SOCKET_TRANSPORT";
    case nsIHttpActivityObserver.ACTIVITY_TYPE_HTTP_TRANSACTION:
      return "ACTIVITY_TYPE_HTTP_TRANSACTION";
      
    default:
      return a;
  }
}

function acSubType(a)
{
  switch (a) {
    case nsIHttpActivityObserver.ACTIVITY_SUBTYPE_REQUEST_HEADER:
      return "ACTIVITY_SUBTYPE_REQUEST_HEADER";
    case nsIHttpActivityObserver.ACTIVITY_SUBTYPE_REQUEST_BODY_SENT:
      return "ACTIVITY_SUBTYPE_REQUEST_BODY_SENT";
    case nsIHttpActivityObserver.ACTIVITY_SUBTYPE_RESPONSE_START:
      return "ACTIVITY_SUBTYPE_RESPONSE_START";
    case nsIHttpActivityObserver.ACTIVITY_SUBTYPE_RESPONSE_HEADER:
      return "ACTIVITY_SUBTYPE_RESPONSE_HEADER";
    case nsIHttpActivityObserver.ACTIVITY_SUBTYPE_RESPONSE_COMPLETE:
      return "ACTIVITY_SUBTYPE_RESPONSE_COMPLETE";
    case nsIHttpActivityObserver.ACTIVITY_SUBTYPE_TRANSACTION_CLOSE:
      return "ACTIVITY_SUBTYPE_TRANSACTION_CLOSE";
      
    case nsISocketTransport.STATUS_RESOLVING:
      return "STATUS_RESOLVING";
    case nsISocketTransport.STATUS_CONNECTING_TO:
      return "STATUS_CONNECTING_TO";
    case nsISocketTransport.STATUS_CONNECTED_TO:
      return "STATUS_CONNECTED_TO";
    case nsISocketTransport.STATUS_SENDING_TO:
      return "STATUS_SENDING_TO";
    case nsISocketTransport.STATUS_WAITING_FOR:
      return "STATUS_WAITING_FOR";
    case nsISocketTransport.STATUS_RECEIVING_FROM:
      return "STATUS_RECEIVING_FROM";    
      
    default:
      return a;
  }
}