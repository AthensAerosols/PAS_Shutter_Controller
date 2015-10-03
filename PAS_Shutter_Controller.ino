// _________________________________________________________________________________________________
// Control for arc lamp shutter and background valve
// For UGA Photoacoustic Spectrometer
// Based on Adafruit Motor Shield:
//                (https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino)
// (c) 2015 - AF (GPLv3)
// __________________________________________________________________________________________________

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_StepperMotor *shutterMotor = AFMS.getStepper(200, 2);

char inChar[16];
int i=0;
String inCharStr = "";
boolean echo = 1;
int tempindex = 0;
float tempL;

void setup() {
  Serial.begin(9600);
  AFMS.begin(1350);  // create with the default frequency 1.6KHz
  shutterMotor->setSpeed(100);   // sets motor speed in rpm 
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
}

void loop() {

  tempL = ((analogRead(A0) * (5000.0 / 1023.0)) - 0.5) * 100; // temperature (C) of L1 -- sensor on A0
  if (tempL > 250.0) shutterMotor->step(49, BACKWARD, DOUBLE);  // close shutter if too hot
  
  while (Serial.available() > 0) { 
    inChar[i] = Serial.read();
    if (inChar[i] == '\n') {
      break;
    }
    i++;
  }
  
  if (i > 0) {
    inCharStr = String(inChar);
  }
  
  if (inCharStr == "*IDN?\n") {
    Serial.println("I'm the Shutter & Mirror Controller!");
    Serial.println("v2.0, AeroSmith Lab, UGA (AF 2015)");
  }
  
  if (inCharStr == "t.l1\n") {
    Serial.println(tempL); 
  }
  
  if (inCharStr == "s.o\n") {
    shutterMotor->step(49, FORWARD, DOUBLE);
    if (echo == 1); {
      Serial.println("shutter.open OK");
    }
  }
  
  if (inCharStr == "s.c\n") {
    shutterMotor->step(49, BACKWARD, DOUBLE);
    if (echo == 1); {
      Serial.println("shutter.close OK");
    }
    shutterMotor->release();
  }
  
  if (inCharStr == "v.b\n") {
    digitalWrite(12, HIGH);
    if (echo == 1); {
      Serial.println("valve.bkg OK");
    }
  }
  
if (inCharStr == "v.s\n") {
    digitalWrite(12, LOW);
    if (echo == 1); {
      Serial.println("valve.sample OK");
    }
  }
  
  i = 0;
  inCharStr = "";
  memset(inChar, 0, sizeof(inChar));
  
  delay(100);
}
      
