#include <Arduino.h>
//#include <services/WifiServices.h>
#include <LightsControl.h>
#include <TimeControl.h>
#include <FanControl.h>
#include <services/RepositoryServices.h>

//Ubidots
//const char* UBIDOTS_TOKEN = "BBFF-kMyEA6VX6t7s8WoRgB127VcxCTFk6v";

//Define other Input
#define ButtonTrigger D1

// Set up Ubidots
//Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

//Global variable

void Event(bool state){
  if(state){
    analogWrite(OffLights, 255);
  }else{
    analogWrite(OffLights, 0);
  }
}

void Init(){
  Serial.begin(9600);  
  pinMode(Ledblue, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(ButtonTrigger, INPUT);
  pinMode(ntc, INPUT);
  pinMode(Fan, OUTPUT);
  initServo();
  initFan();
  initLight();
}

void setup()
{  
    Init();
    Connect();   
    UpdateTime();
    PrintTime();
    WiFi.mode(WIFI_OFF);
}

void ButtonState(){
  //int button = digitalRead(ButtonTrigger);

  //Serial.println(String(digitalRead(ButtonTrigger)));

  // if (button == HIGH) {
  //   // turn LED on:
  //   analogWrite(OffLights, 200);
  // } else {
  //   // turn LED off:
  //   analogWrite(OffLights, 0);
  // }
}

void loop()
{   
  RunTime();
  BlinkLights(ss);
  PrintTime();  
  RunFan();
  //SendUbi();
}