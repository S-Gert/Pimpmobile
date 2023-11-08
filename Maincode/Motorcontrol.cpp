#include "Motorcontrol.h"
#include "Arduino.h"

// pins analog D9, digital D0
MotorControl::MotorControl(int analog_pin, int digital_pin){
  pinMode(analog_pin, OUTPUT);
  pinMode(digital_pin, OUTPUT);
  _analog_pin = analog_pin;
  _digital_pin = digital_pin;
}

void MotorControl::run(int pwm_val){
  if (pwm_val < 0){
    digitalWrite(_digital_pin, HIGH);
  } else {
    digitalWrite(_digital_pin, LOW);
  }
  analogWrite(_analog_pin, abs(pwm_val));
}

