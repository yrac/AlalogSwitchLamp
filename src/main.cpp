#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <DNsserver.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Time.h>
#include <TimeLib.h>
#include <Timezone.h>
#include <Servo.h>

#include <Temp.h>

// Define NTP properties
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDREss  "pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)

// Define Servo Properties
#define ServoPin  D4
#define ServoOff  180
#define ServoInit 90
#define ServoOn 0


// Define other Output
#define Ledblue D7
#define LedGreen D8
#define Fan D2

//Define other Input
#define ButtonTrigger D1
#define ntc A0

// Set up the NTP UDP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDREss, NTP_OFFSET, NTP_INTERVAL);

// Set up the servo
Servo shutterServo;

//Global variable
int HH = 0;
int MM = 0;
int ss = 0;
int LightBright = 150;
int LightStats = 0;
uint8_t OnLights = Ledblue;
uint8_t OffLights = LedGreen;
bool HasConn = false;
bool FiredOn = false;
bool FiredOff = false;
bool IsOn = false;
bool IsFanRun = false;
int RunTimeFan = 60; //in second
int FanRun = 0;

int OnHour = 17;
int OnMinutes = 45;
int OffHour = 5;
int OffMinutes = 30;
int LastUpdateHours = 0;
int IntervalUpdate = 4;

//Define Test Servo
int TestSer = 0;
int TestSeq = 10;


void initServo() {
  Serial.println("Begin Test Servo");
  delay(2000);

  Serial.println("Steady");
  shutterServo.attach(ServoPin); 
  delay(2000); 

  Serial.println("On");
  shutterServo.write(ServoOn);  
  delay(2000);

  Serial.println("Neutral");
  shutterServo.write(ServoInit);  
  delay(2000);

  Serial.println("Off");
  shutterServo.write(ServoOff); 
  delay(2000);

  Serial.println("Neutral");
  shutterServo.write(ServoInit); 
  delay(2000);

  Serial.println("End Test Servo");
  //shutterServo.detach();
}

void initFan(){
Serial.println("Begin Test Fan");
digitalWrite(Fan, 255);
delay(5000);
digitalWrite(Fan, 0);
Serial.println("End Test Fan");
}

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

void FiringServo(bool IsOn){  
  if(IsOn && !FiredOn){
    delay(1000);
    //shutterServo.attach(ServoPin); 
    shutterServo.write(ServoOn);
    FiredOn = true;
    FiredOff = false;
    Serial.println("On");
    delay(1000);
    shutterServo.write(ServoInit);
    ss+=2;
  }else if(!IsOn && !FiredOff){
    delay(1000);
    //shutterServo.attach(ServoPin); 
    shutterServo.write(ServoOff);
    FiredOff = true;
    FiredOn = false;
    Serial.println("Off");    
    delay(1000);
    ss+=2;
    shutterServo.write(ServoInit);
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

void BlinkLights(){
    //digitalWrite(OffLights, LOW);
  if(ss % 2 == 1){
    LightStats = 100 + MM;
  }else{
    LightStats = 0;
  }  
  analogWrite(OnLights, LightStats);
}

boolean Connect(){
  Init();
  WiFiManager wifiManager;

  analogWrite(LedGreen, 255);
  analogWrite(Ledblue, 255);
  delay(5000);
  
  HasConn = wifiManager.autoConnect("NodeMCU");
  Serial.println("Connected!");
  delay(1500);
  return HasConn;
}

void PrintTime(){
  Serial.println("----------------------------");
  Serial.println("Time is : "+ String(HH) +":"+ MM +":"+ ss);
  Serial.println("----------------------------");
}

void UpdateTime(){

  timeClient.begin(); 
  timeClient.setTimeOffset(25200);  
  delay(5000);
  timeClient.update();

  HH = timeClient.getHours();
  MM = timeClient.getMinutes();
  ss = timeClient.getSeconds();  
}

void setup()
{  
    Connect();   
    UpdateTime();
    PrintTime();
    WiFi.mode(WIFI_OFF);
}

//Function to convert time to milisecond
//in order to get excact larger time as day time
int ToMilis(int hh, int mm){
  int res = (hh * 60 * 60) + (mm * 60);
  return res;
}

void SetLightDay(int hh, int mm){   
  int off = ToMilis(OffHour, OffMinutes);
  int on = ToMilis(OnHour, OnMinutes);
  int currtime = ToMilis(hh, mm);

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

  // Serial.println("On : " + String(on));
  // Serial.println("Off : " + String(off));
  // Serial.println("Curr : " + String(currtime));
}

void RunTime(){
  ss = ss + 1;
  delay(1000);
  if (ss >= 60)
  {
    ss = 0;
    MM = MM + 1;
  }

  if (MM >= 60)
  {
    MM = 0;
    HH = HH + 1;    
  }

  if (HH >= 24)
  {
    HH = 0;
  }    

  SetLightDay(HH, MM);
}

void ButtonState(){
  //int button = digitalRead(ButtonTrigger);

  Serial.println(String(digitalRead(ButtonTrigger)));

  // if (button == HIGH) {
  //   // turn LED on:
  //   analogWrite(OffLights, 200);
  // } else {
  //   // turn LED off:
  //   analogWrite(OffLights, 0);
  // }
}

void TestServo(){
  shutterServo.attach(ServoPin);
  Serial.println(String(TestSer));
  shutterServo.write(TestSer);
  delay(2000);
  TestSer = TestSer + TestSeq;
  if(TestSer > 180) 
  {
    TestSer = 0;
    shutterServo.write(TestSer);
    delay(2000);
    shutterServo.detach();
    delay(10000);
  }
}

void GetUpdateTime(){
  if(HH - LastUpdateHours >= IntervalUpdate){
    UpdateTime();
    LastUpdateHours = HH;
  }
}

void RunFan(){
  FanRun = FanRun >= RunTimeFan ? 0 : FanRun;
  if(FanRun == 0){    
    double temp = Temp(analogRead(ntc));
    int speed = 0;
    FanRun++;
      if(temp >= 40 && temp <= 50){
        speed = 200;
      }else if(temp >= 50){
        speed = 255;
      }else{
        FanRun = 0;
      }      
      digitalWrite(Fan, speed);
      analogWrite(OffLights, speed);        
  }else
  {
   FanRun++;
  }
}

void loop()
{   
  RunTime();
  BlinkLights();
  PrintTime();  
  //Temp(analogRead(ntc));
  RunFan();
  // TestServo();
}