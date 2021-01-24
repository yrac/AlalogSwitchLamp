#include <FS.h>
#include <Arduino.h>
#include <services/FireBaseServices.h>
#include <LightsControl.h>
#include <TimeControl.h>
#include <services/RepositoryServices.h>
#include <loopTimer.h>
#include <millisDelay.h>
//Ubidots
//const char* UBIDOTS_TOKEN = "BBFF-kMyEA6VX6t7s8WoRgB127VcxCTFk6v";

//Define other Input
#define ButtonTrigger D1

String StateTime = "", StateDate = "", LastUpdate = "";
int FanRun = 0;
millisDelay delaycheck;
millisDelay delayloop;
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
  EEPROM.begin(512);
  //Serial.begin(115200);
  pinMode(Ledblue, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(ButtonTrigger, INPUT);
  pinMode(ntc, INPUT);
  pinMode(Fan, OUTPUT);
  initServo();
  initFan();
  initLight();
  InitWebServer();
  //InitFireBase();
}

void setup()
{
    Init();
    Connect();
    UpdateTime();
    delaycheck.start(2000);
    delayloop.start(1000);
}

void AnotherCheck(){
  if(CheckConnection()) //CheckFireBase();
  CheckServo();
  GetUpdateTime();
}

void loop()
{
  if(delayloop.justFinished()){
    delayloop.repeat();
    RunFan();
    RunTime();
    BlinkLights(ss);
  }

    if (delaycheck.justFinished()) {
        delaycheck.repeat();
        AnotherCheck();
    }
}
