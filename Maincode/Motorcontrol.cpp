#include "Motorcontrol.h"
#include "Arduino.h"

// pins analog D9, digital D0
MotorControl::MotorControl(int analogPin, int digitalPin){
  pinMode(analogPin, OUTPUT);
  pinMode(digitalPin, OUTPUT);
  _analogPin = analogPin;
  _digitalPin = digitalPin;
}

void MotorControl::run(int pwmVal){
  if (pwmVal < 0){
    digitalWrite(_digitalPin, HIGH);
  } else {
    digitalWrite(_digitalPin, LOW);
  }
  analogWrite(_analogPin, abs(pwmVal));
}

