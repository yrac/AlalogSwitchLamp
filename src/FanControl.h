#include <TempControl.h>

#define Fan D2

int FanRun = 0;
int speed = 0;
double temp = 0;
bool IsFanRun = false;
int RunTimeFan = 60000; //in milisec


void initFan(){
    Serial.println("Begin Test Fan");
    digitalWrite(Fan, 255);
    delay(5000);
    digitalWrite(Fan, 0);
    Serial.println("End Test Fan");
}

void RunFan(){
  FanRun = FanRun >= RunTimeFan ? 0 : FanRun;
  if(FanRun == 0){    
    temp = Temp(analogRead(ntc));    
    FanRun++;
      if(temp >= 40 && temp <= 50){
        speed = 200;  
      }else if(temp >= 50){
        speed = 255;
      }else{
        FanRun = 0;
        speed = 0;
        State = "Idle Fan at " + String(speed) +" speed";
      }      
      digitalWrite(Fan, speed);    
  }else
  {
   FanRun++;
   State = "Run Fan at " + String(speed) +" speed";
  }  
}
