#include <FS.h> 
#include <Arduino.h>
#include <Servo.h> 

// Define Servo Properties
#define ServoPin  D4
int ServoOff  = 180;
int ServoInit = 90;
int ServoOn = 10;
int ServoState = 0;
bool ServoChecked = false;
String State;

// Set up the servo
Servo shutterServo;

///Firing servo by state
void FiringServo(bool IsOn){ 
  Serial.println(!shutterServo.attached()); 
  if(!shutterServo.attached()) {
      shutterServo.attach(ServoPin);      
      delay(500);
    }
  if(IsOn){    
    shutterServo.write(ServoOn); 
    ServoState = ServoOn;
    Serial.println("On");
    State = "Servo Firing to On ";
  }else{    
    shutterServo.write(ServoOff); 
    ServoState = ServoOff;
    Serial.println("Off");       
    State = "Servo Firing to Off ";
  }      
  delay(1000);
  ServoChecked = false;   
}

///Init servo
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

///Check servo possition
void CheckServo(){
  if(!ServoChecked){
    if(!shutterServo.attached()){ 
      shutterServo.attach(ServoPin);
    }

    if(shutterServo.read() != ServoInit){
      shutterServo.write(ServoInit);
      shutterServo.detach();
      ServoChecked = true;
    }
  }
}

///Firing servo by angle
void FiringServo(int angle){ 
  if(!shutterServo.attached()){
     shutterServo.attach(ServoPin);
     shutterServo.write(angle);
  }
}