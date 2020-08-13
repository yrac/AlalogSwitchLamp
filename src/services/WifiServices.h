#include <ESP8266WiFi.h>
#include <DNsserver.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

WiFiServer server(80);
bool HasConn = false;
bool shouldSaveConfig = false;
char serveraddr[50] = "http://contoh.com";

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

boolean Connect(){
  WiFiManagerParameter custom_output("server", "server addr", serveraddr, 50);
  WiFiManager wifiManager;
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  wifiManager.addParameter(&custom_output);

  analogWrite(LedGreen, 255);
  analogWrite(Ledblue, 255);
  delay(5000);
  
  HasConn = wifiManager.autoConnect("NodeMCU");
  Serial.println("Connected!");
  delay(1500);
  return HasConn;
}
