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

void ServoControl::runConstant(int delayMicroSec){
  digitalWrite(_analogPin, HIGH);
  delayMicroseconds(delayMicroSec);
  digitalWrite(_analogPin, LOW);
  delayMicroseconds(delayMicroSec);
}