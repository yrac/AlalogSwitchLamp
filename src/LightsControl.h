#include <Arduino.h>
#include <ServoControl.h>

#define Ledblue D7
#define LedGreen D8

int LightBright = 150;
int LightStats = 0;
bool IsOn = false;
bool FiringOn = false;
bool isInit = true;
uint8_t OnLights = Ledblue;
uint8_t OffLights = LedGreen;
int savesecond = 0;


void initLight(){
    Serial.println("Begin Test Light");
    analogWrite(LedGreen, 255);
    delay(1000);
    analogWrite(LedGreen, 0);
    delay(500);
    analogWrite(Ledblue, 255);
    delay(1000);
    analogWrite(Ledblue, 0);
    Serial.println("End Test Light");
}

void BlinkLights(int second){
  if(second % 2 == 1){
    LightStats = 130 + (second * 2);
  }else{
    LightStats = 0;
  }  
  analogWrite(OnLights, LightStats);
}

void ResetLinght(){
  analogWrite(OnLights, 0);
  analogWrite(OffLights, 0);
}

void SetLightDay(int milcur, int miloff, int milon){
  int sunrise = miloff;
  int sunset = milon;
  int currtime = milcur;

  //Define Off Time
  if(currtime >= sunrise && currtime <= sunset){ 
    OnLights =  Ledblue;
    OffLights = LedGreen;
    IsOn = false;

  ///Define On Time
  }else {//if(currtime >= sunset) {//if(!IsOn){
    OnLights =  LedGreen;
    OffLights = Ledblue;
    IsOn = true;
  }

if(isInit){
  FiringServo(IsOn);
  FiringOn = IsOn; 
  isInit = false;
}else if(IsOn != FiringOn){
  FiringServo(IsOn);
  FiringOn = IsOn; 
  } 
}
