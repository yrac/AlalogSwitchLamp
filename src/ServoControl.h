#include <FS.h>
#include <Arduino.h>
#include <Servo.h>
#include <loopTimer.h>
#include <millisDelay.h>

// Define Servo Properties
#define ServoPin  D4
int ServoOff  = 0;
int ServoInit = 50;
int ServoOn = 110;
int ServoState = 0;
bool ServoChecked = false;
uint16_t servomin = 480;
uint16_t servomax = 2500;
String State;
millisDelay delayBegin, delayEnd;

// Set up the servo
Servo shutterServo;

///Firing servo by state
void FiringServo(bool IsOn, bool force = false){
  if(!shutterServo.attached())
  {
    shutterServo.attach(ServoPin, servomin, servomax);
  }

    ServoState = shutterServo.read();
    Serial.println(ServoState);
      if((IsOn && (ServoState != ServoOn)) || force){
        shutterServo.write(ServoOn);
        Serial.println("On");
        State = "Servo Firing to On ";
      }else if((!IsOn && (ServoState != ServoOff)) || force){
        shutterServo.write(ServoOff);
        Serial.println("Off");
        State = "Servo Firing to Off ";
      }
      ServoChecked = false;
      //shutterServo.write(ServoInit);
      ServoState = shutterServo.read();
}

///Init servo
void initServo() {
  delayBegin.start(3000);
  delayEnd.start(3000);
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
  shutterServo.detach();
}

///Check servo possition
void CheckServo(){
  if(delayEnd.justFinished()){
      delayEnd.repeat();
    //if(!ServoChecked){
      // if(!shutterServo.attached()){
      //   shutterServo.attach(ServoPin, servomin, servomax);
      //   Serial.println("Servo : " + shutterServo.attached());
      // }

      if(shutterServo.read() != ServoInit){
        shutterServo.write(ServoInit);
        Serial.println("Servo Pos " + shutterServo.read());
        //shutterServo.detach();
        ServoChecked = true;
        Serial.println("Servo has checked and detach");
      }
    }
  //}
}

///Firing servo by angle
void FiringServo(int angle){
  if(!shutterServo.attached()){
     shutterServo.attach(ServoPin);
     shutterServo.write(angle);
  }
}
