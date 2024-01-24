#ifndef Servocontrol_h
#define Servocontrol_h
#include "Arduino.h"

class ServoControl {
  public:
    ServoControl(int analog_pin, int digital_pin);
    void run(int max_angle, bool direction);
  private:
    int _analog_pin;
    int _digital_pin;
};

#endif