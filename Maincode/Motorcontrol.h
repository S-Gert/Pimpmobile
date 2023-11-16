#ifndef Motorcontrol_h
#define Motorcontrol_h
#include "Arduino.h"

class MotorControl {
  public:
    MotorControl(int analog_pin, int digital_pin);
    void run(int pwm_val);
    void teleopRun(bool input, int max_pwm_speed, int rampup_delay, bool forward);
  private:
    int _analog_pin;
    int _digital_pin;
    int  _rampup_increment;
    int _current_pwm_speed;
};

#endif