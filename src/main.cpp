#include <FS.h>  
#include <Arduino.h>
//#include <services/WifiServices.h>
#include <LightsControl.h>
#include <TimeControl.h>
// #include <FanControl.h>
#include <services/RepositoryServices.h>

//Ubidots
//const char* UBIDOTS_TOKEN = "BBFF-kMyEA6VX6t7s8WoRgB127VcxCTFk6v";

//Define other Input
#define ButtonTrigger D1

String StateTime = "";
String StateDate = "";
String LastUpdate = "";
unsigned long loopmilis = 0;
int loopinterval = 1000;
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
}

void setup()
{  
    Init();    
    Connect();   
    UpdateTime();
}
 
void AnotherCheck(){
  CheckConnection();
  CheckServo();  
  GetUpdateTime();   
}

void loop()
{  
  if(millis() == 0) loopmilis = 0;
  if(millis() >= (loopmilis + loopinterval)){
    loopmilis += loopinterval;
    RunFan(); 
    RunTime();
    BlinkLights(ss);
    AnotherCheck();
  }
}

