#include <Arduino.h>
#include <Servo.h>

// Define Servo Properties
#define ServoPin  D4
int ServoOff  = 180;
int ServoInit = 90;
int ServoOn = 0;
extern int ServoState = 0;

String State;

// Set up the servo
Servo shutterServo;

void FiringServo(bool IsOn){  
  if(IsOn){
    if(!shutterServo.attached()) shutterServo.attach(ServoPin);
    ServoState = ServoOn;
    Serial.println("On");
    //delay(500);
    //shutterServo.detach();
    State = "Servo Firing to On ";
    //shutterServo.detach();
  }else{
    if(!shutterServo.attached()) shutterServo.attach(ServoPin);
    ServoState = ServoOff;
    Serial.println("Off");    
    //delay(500);
    //shutterServo.write(ServoInit);    
    State = "Servo Firing to Off ";
  }    
  shutterServo.write(ServoState);
  delay(1000);
  shutterServo.detach();
  
}

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
