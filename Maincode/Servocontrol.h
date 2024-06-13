#ifndef Servocontrol_h
#define Servocontrol_h
#include "Arduino.h"

class ServoControl {
  public:
    ServoControl(int analog_pin, int digital_pin, int servo_driver_toggle_pin);
    const int encoder_center = 500;
    void run(int input, int encoder_pos, bool direction);
    void returnToCenter(int encoder_pos);
    void activateServo(bool state);
    int bufferZone(int input, int buffer_size);
    void runWithBufferAndDirection(int input, int encoder_pos);
  private:
    int _analog_pin;
    int _digital_pin;
    int _servo_driver_toggle_pin;
};

#endif