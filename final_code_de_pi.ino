#include <SoftwareSerial.h>
// SoftwareSerial for serial communication with HM10 bluetooth module.
#include <ArduinoBlue.h>
// ArduinoBlue bluetooth library
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>
// Library for servo motor

int BLUETOOTH_TX =2;
int BLUETOOTH_RX =3;

int ID;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *Rmotor = AFMS.getMotor(2);
Adafruit_DCMotor *Lmotor = AFMS.getMotor(1);
Adafruit_DCMotor *Mmotor = AFMS.getMotor(3);

Servo pinces;
SoftwareSerial softSerial(BLUETOOTH_TX, BLUETOOTH_RX);
ArduinoBlue phone(softSerial);




void actuateurUp()  {
 Mmotor -> run(FORWARD);
}
void actuateurDown()  {
 Mmotor -> run(BACKWARD);
}

void actuateurStop() {
 Mmotor -> run(RELEASE);
}

void forward() {
  Rmotor -> run(FORWARD);
  Lmotor -> run(FORWARD);
}

void backward() {
  Rmotor -> run(BACKWARD);
  Lmotor -> run(BACKWARD);
}

void Stop() {
  Rmotor -> run(RELEASE);
  Lmotor -> run(RELEASE);
}

void turnRight() {
  Rmotor -> run(BACKWARD);
  Lmotor -> run(FORWARD);
}
void turnLeft() {
  Lmotor -> run(BACKWARD);
  Rmotor -> run(FORWARD);
}
int button;
void robotControl() {

  int throttle = phone.getThrottle() -49;
  int steering = phone.getSteering() -49;
  int sliderID = phone.getSliderId();
  int bouton = phone.getButton();
  int sliderVal = phone.getSliderVal() - 50;



   if (sliderID == 5) {
      Serial.println(sliderVal);
   if (sliderVal >= 10){
     actuateurUp();
   }
   else if (sliderVal <= -10){
     actuateurDown();
   }
   else{
     actuateurStop();
   }
 } 


  if(bouton != -1) {
    button = bouton;
  }
  if (button == 2) {
    pinces.attach(9);
    pinces.write(90);
    delay(200);
    pinces.detach();
    
  }
  if (button == 3) {
    pinces.attach(9);
    pinces.write(0);
    delay(200);
    pinces.detach();
  }
  if (button == 4) {
    pinces.detach();
  }

  if (steering == 0 && throttle == 0) {
    Stop();
  }
  else if (steering > 0) {
    turnLeft();
  }
  else if (steering < 0) {
    turnRight();
  }
  else if (throttle < 0) {
    forward();
  }
  else if (throttle > 0 ) {
    backward();
  }



}

void setup() {
  AFMS.begin();
  delay(500);
  softSerial.begin(9600);
  Rmotor -> setSpeed(255);
  Lmotor -> setSpeed(255);
  Mmotor -> setSpeed(255);
  pinces.attach(9);
  pinces.write(0);
  pinces.detach();


 
}

void loop() {

  robotControl();
 
}
