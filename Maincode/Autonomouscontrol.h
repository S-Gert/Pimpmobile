#ifndef Autonomouscontrol_h
#define Autonomouscontrol_h
#include "Arduino.h"
#include "Motorcontrol.h"
#include "Servocontrol.h"

class AutoControl {
  public:
    AutoControl();

    struct Sendata {
      volatile int TX_val;
    };

    struct Receive {
      volatile int x;
      volatile int y;
      volatile int z;
    };

    struct Sendata values;
    struct Receive bytes;

    const int total_bytes = 3*sizeof(int);
    int i;

    int RX_motors;
    int RX_servo;
    int RX_brakes;
    byte buf[];

    void readSerial();
    void writeSerial(int write_value);
    void autoServo(ServoControl servo, int encoder_pos);
    void autoMotors(MotorControl l_motor, MotorControl r_motor, int diff_toggle, int encoder);
};

#endif