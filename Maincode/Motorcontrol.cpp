#include "Motorcontrol.h"
#include "Arduino.h"

// pins analog D4, digital D0
MotorControl::MotorControl(int analogPin, int digitalPin){
  Serial.begin(9600);
  pinMode(analogPin, OUTPUT);
  pinMode(digitalPin, OUTPUT);
  _analogPin = analogPin;
  _digitalPin = digitalPin;
}

void MotorControl::forwards(int delayMicroSec){
  digitalWrite(_analogPin, HIGH);
  delayMicroseconds(delayMicroSec);
  digitalWrite(_analogPin, LOW);
  delayMicroseconds(delayMicroSec);
}
void MotorControl::backwards(int delayMicroSec){
  digitalWrite(_digitalPin, HIGH);
  digitalWrite(_analogPin, HIGH);
  delayMicroseconds(delayMicroSec);
  digitalWrite(_analogPin, LOW);
  delayMicroseconds(delayMicroSec);
}