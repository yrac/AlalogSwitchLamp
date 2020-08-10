#include <Arduino.h>
#include <Servo.h>

// Define Servo Properties
#define ServoPin  D4
#define ServoOff  180
#define ServoInit 90
#define ServoOn 0

bool FiredOn = false;
bool FiredOff = false;


// Set up the servo
Servo shutterServo;

void FiringServo(bool IsOn){  
  if(IsOn && !FiredOn){
    //Event(true);
    shutterServo.write(ServoOn);
    FiredOn = true;
    FiredOff = false;
    Serial.println("On");
    delay(1000);
    shutterServo.write(ServoInit);
    //ss+=2;
    //Event(false);
  }else if(!IsOn && !FiredOff){
    //Event(true);    
    shutterServo.write(ServoOff);
    FiredOff = true;
    FiredOn = false;
    Serial.println("Off");    
    delay(1000);
    //ss+=2;
    shutterServo.write(ServoInit);
    //Event(false);
  }    
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
