#ifndef Servocontrol_h
#define Servocontrol_h
#include "Arduino.h"

class ServoControl {
  public:
    ServoControl(int servoAnalogPin, int servoDigitalPin);
    void runConstant(int delayMicroSec);
  private:
    int _servoAnalogPin;
    int _servoDigitalPin;
};

#endif