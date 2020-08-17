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
 
String request = "";
String ResponseBody ="";
extern String StateTime, StateDate ;
extern int ServoState;

String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(temp);
  }
  else if(var == "FAN"){
    return String(speed);
  }
  else if(var == "SERVO"){
    return String(ServoState);
  }
  return String();
}

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void InitWebServer(){

  ResponseBody = "{\n    \"Clock\": \""+StateTime+"\",\n    \"Temperature\": \""+StateTime+"\",\n    \"Fan\": \""+StateTime+"\",\n    \"Servo\": \""+StateTime+"\"\n}";


  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/getstate", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncJsonResponse * response = new AsyncJsonResponse();
    //response->addHeader("Server","ESP Async Web Server");
    JsonObject& root = response->getRoot();
    root["Clock"] = StateTime;
    root["Date"] = StateDate;
    root["Fan"] = speed;
    root["Temp"] = temperature;
    root["Servo"] = ServoState;
    
    response->setLength();
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

#pragma region OLD
// std::tuple<bool, bool, bool> SendGetInfo(double temp, String time){ //tuple<IsClientConn, IsFanRun, IsServoOnPossition>
//    // Check if a client has connected
//     WiFiClient client = server.available();
//     bool IsFanRun, IsServoOnPossition;
//     bool IsClientAction = false;
//     if (client)
//     {
//           // Read the first line of the request
//           request = client.readStringUntil('\r');
//           IsClientAction = request.length() > 14;

//           Serial.println("request:");
//           Serial.println(request);
//           Serial.println("request length:");
//           Serial.println(request.length());
 
//           if       ( request.indexOf("FANON") > 0 )  { IsFanRun = true;      }
//           else if  ( request.indexOf("FANOFF") > 0 ) { IsFanRun = false;      }
         

//           if       ( request.indexOf("SERVOON") > 0 && IsOn)  { IsServoOnPossition = true;      }
//           else if  ( request.indexOf("SERVOOF") > 0 && !IsOn) { IsServoOnPossition = false;      }
          

//           if (IsFanRun) 
//           {
//             htmlfan = "<form id='F1' action='FANOFF'><input class='button' type='submit' value='Turn Off Fan' ></form><br>";
//           }
//           else                              
//           {
//             htmlfan = "<form id='F1' action='FANON'><input class='button' type='submit' value='Turn On Fan' ></form><br>";
//           }

//           if (!IsServoOnPossition) 
//           {
//             htmlservo = "<form id='F1' action='SERVOON'><input class='button' type='submit' value='Turn On Lights' ></form><br>";
//           }
//           else                              
//           {
//             htmlservo = "<form id='F1' action='SERVOOF'><input class='button' type='submit' value='Turn Off Lights' ></form><br>";
//           }
 
//           htmltemp = "<h2>"+String(temp)+"</h2>";
//           htmlcurtime = "<h1>"+time+"</h1>";
 
//           client.flush();
 
//           client.print( header );
//           client.print( htmlopening );    
//           client.print( htmlcurtime );
//           client.print( htmltemp );
//           client.print( htmlfan );
//           client.print( htmlservo );
//           client.print( htmlclosing );
 
//           delay(5);
//           client.println("<meta http-equiv='refresh' content='10'>");
 
//          // The client will actually be disconnected when the function returns and 'client' object is detroyed
 
//     }
//     return std::make_tuple(IsClientAction, IsFanRun, IsServoOnPossition);
// }
#pragma endregion


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
