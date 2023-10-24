#include "Motorcontrol.h"
#include "Arduino.h"

// pins analog D9, digital D0
MotorControl::MotorControl(int analogPin, int digitalPin){
  Serial.begin(9600);
  pinMode(analogPin, OUTPUT);
  pinMode(digitalPin, OUTPUT);
  _analogPin = analogPin;
  _digitalPin = digitalPin;
}

void MotorControl::runConstant(int pwmVal, bool direction){
  if (direction == 1){
    digitalWrite(_digitalPin, HIGH);
  } else {
    digitalWrite(_digitalPin, LOW);
  }
  analogWrite(_analogPin, value);
}
