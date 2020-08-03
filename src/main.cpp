#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <NTPClient.h>
//#include <DNsserver.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Time.h>
#include <TimeLib.h>
#include <Timezone.h>
#include <Servo.h>

// Define NTP properties
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDREss  "id.pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)

// Define Servo Properties
#define ServoPin  D4
#define ServoOff  120
#define ServoInit 90
#define ServoOn 60

// Define other Output
#define Ledblue D7
#define LedGreen D8

//Define other Input
#define ButtonTrigger D1

// Set up the NTP UDP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDREss);//, NTP_OFFSET, NTP_INTERVAL);

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

int OnHour = 15;
int OnMinutes = 30;
int OffHour = 5;
int OffMinutes = 30;


void initServo() {
  Serial.println("Warm Up");
  delay(2000);

  Serial.println("Steady");
  shutterServo.attach(ServoPin); 
  delay(2000); 

  Serial.println("Neutral");
  shutterServo.write(ServoInit);  
  delay(2000);

  Serial.println("On");
  shutterServo.write(ServoOn);  
  delay(2000);

  Serial.println("Off");
  shutterServo.write(ServoOff); 
  delay(2000);

  Serial.println("Neutral");
  shutterServo.write(ServoInit); 
  delay(2000);

  Serial.println("Done");
  shutterServo.detach();
}

void FiringServo(bool IsOn){
  if(IsOn && !FiredOn){
    shutterServo.attach(ServoPin); 
    shutterServo.write(ServoOn);
    FiredOn = true;
    FiredOff = false;
    Serial.println("On");
  }else if(!IsOn && !FiredOff){
    shutterServo.attach(ServoPin); 
    shutterServo.write(ServoOff);
    FiredOff = true;
    FiredOn = false;
    Serial.println("Off");
  }else{
    shutterServo.write(ServoInit);
    shutterServo.detach();
    // digitalWrite(ServoPin, LOW);
    Serial.println("Neutral");
  }  
}

void Init(){
  Serial.begin(9600);  
  pinMode(Ledblue, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(ButtonTrigger, INPUT);
  initServo();
}

void BlinkLights(){
    digitalWrite(OffLights, LOW);
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

  digitalWrite(LedGreen, HIGH);
  digitalWrite(Ledblue, HIGH);
  delay(5000);
  
  wifiManager.autoConnect("NodeMCU");
  Serial.println("Connected!");
  delay(1500);
  HasConn = true;
  return HasConn;
}

void PrintTime(){
  Serial.println("----------------------------");
  Serial.println("Time is : "+ String(HH) +":"+ MM +":"+ ss);
  Serial.println("----------------------------");
}

void setup()
{  
  if(!HasConn){
    Connect();   
    timeClient.begin(); 
    timeClient.setTimeOffset(25200);  
    timeClient.update();

    HH = timeClient.getHours();
    MM = timeClient.getMinutes();
    ss = timeClient.getSeconds();  
    PrintTime();
    digitalWrite(LedGreen, LOW);
    digitalWrite(Ledblue, LOW);
  }
}

int ToMilis(int hh, int mm){
  int res = (hh * 60 * 60) + (mm * 60);
  return res;
}

void SetLightDay(int hh, int mm){   
  int off = ToMilis(OffHour, OffMinutes);
  int on = ToMilis(OnHour, OnMinutes);
  int currtime = ToMilis(hh, mm);
  bool IsOn = false;

  if(currtime >= on && currtime < off){ //Define Off Time
    OnLights =  Ledblue;
    OffLights = LedGreen;
    IsOn = false;
  }else if(currtime >= off && currtime >= on){ //Define On Time
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
  if (ss == 60)
  {
    ss = 0;
    MM = MM + 1;
  }

  if (MM == 60)
  {
    MM = 0;
    HH = HH + 1;    
  }

  if (HH == 24)
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
  Serial.println("80");
  shutterServo.write(45);
  delay(500);
  shutterServo.write(90);
  delay(5000);
  
  Serial.println("100");
  shutterServo.write(140);
  delay(500);
  shutterServo.write(90);
  delay(5000);
}


void loop()
{   
  RunTime();
  BlinkLights();
  //PrintTime();  
  //TestServo();
}