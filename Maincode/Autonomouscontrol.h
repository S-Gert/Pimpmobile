#ifndef Autonomouscontrol_h
#define Autonomouscontrol_h
#include "Arduino.h"
#include "Motorcontrol.h"
#include "Servocontrol.h"

class AutoControl {
  public:
    AutoControl();

    struct Sendata {
      volatile float TX_val;
    };

    struct Receive {
      volatile float x;
      volatile float y;
      volatile float z;
    };

    struct Sendata values;
    struct Receive bytes;

    const int total_bytes = 3*sizeof(float);
    int i;

    int read_values[3];
    int old_time;
    int new_time;
    int RX_motors;
    int RX_servo;
    int RX_brakes;
    // byte buf[];

    void readSerial();
    void writeSerial(int write_value);
    void readWriteSerial(int write_value);
    int getMotorsRX();
    int getServoRX();
    bool getBrakesRX();
};

#endif