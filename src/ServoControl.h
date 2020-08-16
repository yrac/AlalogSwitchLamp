#include <Arduino.h>
#include <Servo.h>

// Define Servo Properties
#define ServoPin  D4
#define ServoOff  180
#define ServoInit 90
#define ServoOn 0

String State;

// Set up the servo
Servo shutterServo;

void FiringServo(bool IsOn){  
  if(IsOn){
    shutterServo.write(ServoOn);
    Serial.println("On");
    delay(500);
    //shutterServo.write(ServoInit);
    shutterServo.detach();
    State = "Servo Firing to On ";
  }else{
    if(shutterServo.attached()) shutterServo.attach(ServoPin);
    delay(200);
    shutterServo.write(ServoOff);
    Serial.println("Off");    
    delay(500);
    shutterServo.write(ServoInit);    
    State = "Servo Firing to Off ";
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
