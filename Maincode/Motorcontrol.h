#ifndef Motorcontrol_h
#define Motorcontrol_h
#include "Arduino.h"

class MotorControl {
  public:
    MotorControl(int analog_pin, int digital_pin, int motor_brakes_pin);
    void run(int pwm_val);
    void activateBrakes(bool state);
    int diff(int motor_pwm, int encoder);
  private:
    bool _brake_state;
    int _motor_brakes_pin;
    int _analog_pin;
    int _digital_pin;
};

#endif