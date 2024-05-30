#ifndef Servocontrol_h
#define Servocontrol_h
#include "Arduino.h"

class ServoControl {
  public:
    ServoControl(int analog_pin, int digital_pin);
    void run(int encoder_angle, int input, bool direction, bool teleop);
    void returnToCenter(int enc_pos);
  private:
    int _analog_pin;
    int _digital_pin;
};

#endif