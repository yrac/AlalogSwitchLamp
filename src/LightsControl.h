#include <Arduino.h>
#include <ServoControl.h>

#define Ledblue D7
#define LedGreen D8

int LightBright = 150;
int LightStats = 0;
bool IsOn = false;
uint8_t OnLights = Ledblue;
uint8_t OffLights = LedGreen;


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
    LightStats = 100 + second;
  }else{
    LightStats = 0;
  }  
  analogWrite(OnLights, LightStats);
}

void SetLightDay(int milcur, int miloff, int milon){   
  int off = miloff;
  int on = milon;
  int currtime = milcur;

  //Define Off Time
  if(currtime >= off && currtime <= on){ 
    OnLights =  Ledblue;
    OffLights = LedGreen;
    IsOn = false;

  ///Define On Time
  }else {//if(!IsOn){
    OnLights =  LedGreen;
    OffLights = Ledblue;
    IsOn = true;
  }

  FiringServo(IsOn);
}
