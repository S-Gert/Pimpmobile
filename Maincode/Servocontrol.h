#ifndef Servocontrol_h
#define Servocontrol_h
#include "Arduino.h"

class ServoControl {
  public:
    ServoControl(int analogPin, int digitalPin);
    void runConstant(int delayMicroSec);
  private:
    int _analogPin;
    int _digitalPin;
};

#endif