#include <FS.h> 
#include <TempControl.h>
 

#define Fan D2

extern int FanRun;
int speed = 0;
double temp = 0;
int FanRunElapsed;
bool IsFanRun = false;
int RunTimeFan = 60; //in secc
int mintemp, maxtemp, crisistemp, idletemp, countIdle;


void initFan(){
    Serial.println("Begin Test Fan");
    digitalWrite(Fan, 255);
    delay(5000);
    digitalWrite(Fan, 0);
    Serial.println("End Test Fan");
    mintemp = 37;
    maxtemp = mintemp + 2;
    crisistemp = 50;
}

void RunFan(){
  temp = Temp(analogRead(ntc));    
  if(FanRun <= 0){        
    FanRun--;
      if(temp >= maxtemp){
        speed = 250;  
        FanRun = RunTimeFan;
        countIdle = 0;
        FanRunElapsed = 0;
      }else{
        FanRun = 0;
        speed = 0;
        idletemp = temp;
        countIdle++;
      }              
  }else{
    if(temp > mintemp){
       FanRun++;
       if(FanRunElapsed >= (RunTimeFan * 30) && temp < crisistemp)
        {         
          mintemp++;
          maxtemp = mintemp+2;
          FanRun = RunTimeFan;
        }         
    }else{   
      if(FanRun > RunTimeFan) FanRun = RunTimeFan;
      FanRun--;
    }
  }  
  
  if(countIdle == (RunTimeFan * 10)  && temp < crisistemp){
      mintemp = idletemp;
      maxtemp = mintemp + 2;
  }
  if(speed > 0) FanRunElapsed++;
  digitalWrite(Fan, speed);    
  analogWrite(OffLights, speed);
}
