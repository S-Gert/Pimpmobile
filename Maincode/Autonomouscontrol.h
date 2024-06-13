#ifndef Autonomouscontrol_h
#define Autonomouscontrol_h
#include "Arduino.h"

class AutoControl {
  public:
    AutoControl();

    int read_values[3];
    int RX_motors;
    int RX_servo;
    int RX_brakes;

    void readWriteSerial(int write_value);
    int getMotorsRX();
    int getServoRX();
    bool getBrakesRX();
};

#endif