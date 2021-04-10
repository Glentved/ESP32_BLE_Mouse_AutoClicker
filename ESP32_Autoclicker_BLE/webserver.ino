#include <DNSServer.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

DNSServer dnsServer;
AsyncWebServer server(80);

#define AP_SSID "AutoClicker_Setup_12345678"
#define AP_password "12345678"

class CaptiveRequestHandler : public AsyncWebHandler {
  public:
    CaptiveRequestHandler() {}
    virtual ~CaptiveRequestHandler() {}

    bool canHandle(AsyncWebServerRequest *request) {
      return true;
    }

    void handleRequest(AsyncWebServerRequest *request) {

      // Stream response (build)
      AsyncResponseStream *response = request->beginResponseStream("text/html");

      // handle POST


      int paramsNr = request->params();
      for (int i = 0; i < paramsNr; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->name() == "clickspeed") {
          interval_time = p->value().toInt();
          EEPROM.writeInt(2, interval_time);
          EEPROM.commit();      
        }
      }

      starttime = millis(); // keep wifi connected
      endtime = starttime;

      // START HTML Page

      response->print(F("<!DOCTYPE html><html><head>"));
      response->print(F("<meta charset=\"utf-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\"><meta http-equiv=\"Cache-Control\" content=\"no-cache, no-store, must-revalidate\" /><meta http-equiv=\"Pragma\" content=\"no-cache\" /><meta http-equiv=\"Expires\" content=\"-1\" />"));
      response->print(F("<style>#grad1 {  height: 800px;  background-color: blue;  background-image: linear-gradient(lightgreen, green);}</style>"));
      response->print(F("<div id=\"grad1\"><center><title>AutoClicker setup page</title></head><body>"));
      response->print(F("<h1>AutoClicker setup page</h1>"));


      response->print(F("<form action='/action_page.php'>"));
      response->print(F("<br><p>Click speed"));
      response->print(F("<br>min 10 sec"));
      response->print(F("<br>max 300 milli sec</p>"));
      response->print(F("<input type='range' id='clickspeed' name='clickspeed' min='200' max='10000' value='"));

      response->print(interval_time);
      response->print(F("'><br>"));

      response->print(F("<input type='submit' value='SET'>"));
      response->print(F("</form>"));

      response->print(F("</div>"));
      response->print(F("</center></body></html>"));
      request->send(response);
    }
};

void setup_Webserver() {
  WiFi.softAP(AP_SSID, AP_password);
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); //only when requested from AP
  server.begin();
}

void webserver_stop() {
  server.end();
  WiFi.mode(WIFI_OFF);
}
void Webserver_loop() {
  dnsServer.processNextRequest(); //webserver loop
}
