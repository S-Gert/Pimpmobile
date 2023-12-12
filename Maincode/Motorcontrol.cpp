#include "Motorcontrol.h"
#include "Arduino.h"

// pins analog D9, digital D0, analog 8, digital 2
MotorControl::MotorControl(int analog_pin, int digital_pin){
  pinMode(analog_pin, OUTPUT);
  pinMode(digital_pin, OUTPUT);
  _analog_pin = analog_pin;
  _digital_pin = digital_pin;
  _rampup_increment = 10;
  _current_pwm_speed = 0;
}

void MotorControl::run(int pwm_val){
  if (pwm_val < 0){
    digitalWrite(_digital_pin, LOW);
  } else {
    digitalWrite(_digital_pin, HIGH);
  }
  analogWrite(_analog_pin, abs(pwm_val));
}

void MotorControl::teleopRun(bool input, int max_pwm_speed, int rampup_delay, bool forward){
  if (forward == 1){
    digitalWrite(_digital_pin, HIGH);
  } else if (forward == 0) {
    digitalWrite(_digital_pin, LOW);
  }
  if (input == 1 && _current_pwm_speed < max_pwm_speed){
    _current_pwm_speed += _rampup_increment;
  } else if (input == 0 && _current_pwm_speed > 0){
    _current_pwm_speed -= _rampup_increment;
  }
  analogWrite(_analog_pin, _current_pwm_speed);
  delay(rampup_delay);
}