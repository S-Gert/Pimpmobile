#include "Motorcontrol.h"
#include "Arduino.h"

// pins analog D9, digital D0, analog 8, digital 2
MotorControl::MotorControl(int analog_pin, int digital_pin, int motor_brakes_pin){
  pinMode(analog_pin, OUTPUT);
  pinMode(digital_pin, OUTPUT);
  pinMode(motor_brakes_pin, OUTPUT);
  _brake_state = false;
  _motor_brakes_pin = motor_brakes_pin;
  _analog_pin = analog_pin;
  _digital_pin = digital_pin;
}

void MotorControl::run(int pwm_val){
  if (pwm_val < 0){
    digitalWrite(_digital_pin, LOW);
  } else {
    digitalWrite(_digital_pin, HIGH);
  }
  analogWrite(_analog_pin, abs(pwm_val));
}

void MotorControl::activateBrakes(bool state){
  if (state && !_brake_state){
    digitalWrite(_motor_brakes_pin, HIGH);
    run(0);
    _brake_state = true;
  } else if (!state && _brake_state){
    digitalWrite(_motor_brakes_pin, LOW);
    _brake_state = false;
  }
}

int MotorControl::diff(int motor_pwm, int encoder){
  double exp_x = (abs(encoder - 500) - 220) / 45; // encoder max 280, exp curve threshold 200, curve steepness 45
  double exp_function = 1 / (1 + exp(-exp_x));
  int new_pwm = motor_pwm * (1 - exp_function);
  return new_pwm;
}