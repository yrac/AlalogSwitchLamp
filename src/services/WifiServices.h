#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif

//#include <DNsserver.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <template/Xmltemplate.h>
#include <FanControl.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

AsyncWebServer server(80);
DNSServer dns;
bool HasConn = false;
bool shouldSaveConfig = false;
char serveraddr[50] = "http://contoh.com";

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String htmlopening = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;} #main {display: table; margin: auto;  padding: 0 10px 0 10px; } h2,{text-align:center; } .button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}</style><title>AutoAnalogLamp</title></head><body><div id='main'>";
String htmltemp, htmlfan, htmltime;
String htmlservo = "";
String htmlclosing = "</div></body></html>";
String htmlcurtime = "";
 
//String request = "";
String ResponseBody ="";
extern String StateTime, StateDate, LastUpdate ;
extern int ServoState;

String processor(const String& var){
  //Serial.println(var);
  if(var == "GETSTATE"){
    return String(temp);
  }
}

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void InitWebServer(){

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/getstate", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    DynamicJsonBuffer jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["Clock"] = StateTime;
    root["Date"] = StateDate;
    root["Temperature"] = round(temp);
    root["Fan"] = speed;
    root["Servo"] = ServoState;
    root["LastUpdate"] = LastUpdate;
    root["RunningHour"] =  (( millis()/1000 ) / 60 ) / 60;
    root["RunningMinutes"] = (millis()/1000 ) / 60;
    root["Info"] = State;
    root.printTo(*response);
    request->send(response);  
    });

  server.begin();
}

boolean Connect(){
  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) == HIGH ? LOW : LOW);
  // WiFiManagerParameter custom_output("server", "server addr", serveraddr, 50);
  AsyncWiFiManager  wifiManager(&server,&dns);
  // wifiManager.setSaveConfigCallback(saveConfigCallback);
  // wifiManager.addParameter(&custom_output);

  analogWrite(LedGreen, 255);
  analogWrite(Ledblue, 255);
  delay(5000);

 // wifiManager.setAPStaticIPConfig(IPAddress(192,168,11,1));
  HasConn = wifiManager.autoConnect("NodeMCU");
  Serial.println("Connected!");
  delay(1000);
  ResetLinght();

  // start a server
  server.begin();
  Serial.println("Server started");
  digitalWrite(LED_BUILTIN, HIGH);
  //WiFi.mode(WIFI_OFF);
  return HasConn;
}

void CheckConnection(){
  uint8_t pulledstate = LOW;
  if(WiFi.status() == WL_CONNECTED){  
    pulledstate = LOW;
  }else
  {
    pulledstate = HIGH;
  }
  digitalWrite(LED_BUILTIN, pulledstate);
}
