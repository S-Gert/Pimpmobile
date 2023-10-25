#include "Arduino.h"
#include "Servocontrol.h"

//constructor :: <-- scope resolution operator
// pins analog D6, digital D3
ServoControl::ServoControl(int analogPin, int digitalPin){
  Serial.begin(9600);
  pinMode(analogPin, OUTPUT);
  pinMode(digitalPin, OUTPUT);
  _analogPin = analogPin;
  _digitalPin = digitalPin;
}

void ServoControl::run(int delayMicroSec){
  if (delayMicroSec < 0){
    digitalWrite(_digitalPin, HIGH);
  } else {
    digitalWrite(_digitalPin, LOW);
  }
  if (delayMicroSec != 0){
  digitalWrite(_analogPin, HIGH);
  delayMicroseconds(abs(delayMicroSec));
  digitalWrite(_analogPin, LOW);
  delayMicroseconds(abs(delayMicroSec));
  }
}