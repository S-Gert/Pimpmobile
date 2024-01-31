#ifndef Servocontrol_h
#define Servocontrol_h
#include "Arduino.h"

class ServoControl {
  public:
    ServoControl(int analog_pin, int digital_pin);
    void run(int encoder_angle, int max_angle, int min_angle, int input, bool direction);
  private:
    int _analog_pin;
    int _digital_pin;
    int _last_turn_angle;
};

#endif