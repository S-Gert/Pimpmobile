#ifndef Motorcontrol_h
#define Motorcontrol_h
#include "Arduino.h"

class MotorControl {
  public:
    MotorControl(int analogPin, int digitalPin);
    void run(int pwmVal);
  private:
    int _analogPin;
    int _digitalPin;
};

#endif