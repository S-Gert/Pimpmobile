#ifndef Servocontrol_h
#define Servocontrol_h
#include "Arduino.h"

class ServoControl {
  public:
    ServoControl(int analog_pin, int digital_pin, int servo_driver_toggle_pin);
    void run(int encoder_angle, int input, bool direction, bool teleop);
    void returnToCenter(int enc_pos);
    void activateServo(bool state);
    void remoteControlTurning(int rc_channel_value, int encoder_pos);
  private:
    int _analog_pin;
    int _digital_pin;
    int _servo_driver_toggle_pin;
};

#endif