#include <ESP8266WiFi.h>
#include <DNsserver.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>


bool HasConn = false;

boolean Connect(){
  WiFiManager wifiManager;

  analogWrite(LedGreen, 255);
  analogWrite(Ledblue, 255);
  delay(5000);
  
  HasConn = wifiManager.autoConnect("NodeMCU");
  Serial.println("Connected!");
  delay(1500);
  return HasConn;
}
