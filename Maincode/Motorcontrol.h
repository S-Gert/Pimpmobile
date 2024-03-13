#ifndef Motorcontrol_h
#define Motorcontrol_h
#include "Arduino.h"

class MotorControl {
  public:
    MotorControl(int analog_pin, int digital_pin);
    void run(int pwm_val);
  private:
    int _analog_pin;
    int _digital_pin;
};

#endif