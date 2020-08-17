#include <TempControl.h>

#define Fan D2

int FanRun = 0;
int speed = 0;
double temp = 0;
bool IsFanRun = false;
int RunTimeFan = 60; //in milisec


void initFan(){
    Serial.println("Begin Test Fan");
    digitalWrite(Fan, 255);
    delay(5000);
    digitalWrite(Fan, 0);
    Serial.println("End Test Fan");
}

void RunFan(){
  temp = Temp(analogRead(ntc));    
  if(FanRun == 0){        
    FanRun--;
      if(temp >= 37 && temp <= 50){
        speed = 200;  
        FanRun += RunTimeFan;
      }else{
        FanRun = 0;
        speed = 0;
        State = "Idle Fan at " + String(speed) +" speed";
      }      
      digitalWrite(Fan, speed);    
      analogWrite(OffLights, speed);
  }else
  {
    if(FanRun <= 55) speed += FanRun;
   FanRun--;
   State = "Run Fan at " + String(speed) +" speed";
  }  
}
