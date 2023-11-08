#ifndef Servocontrol_h
#define Servocontrol_h
#include "Arduino.h"

class ServoControl {
  public:
    ServoControl(int analog_pin, int digital_pin);
    void run(int receiver_data, double desired_angle);
    void moveDegree(double steps);
    double calculateSteps(int receiver_data, double desired_angle);
    int getStepsForDesiredDeg(double desired_angle);
    void turn(double step_count, bool direction);
  private:
    double _pulse;
    int _analog_pin;
    int _digital_pin;
    double _prev_step_count;
    int _position;
    int _prev_receiver_data;
};

#endif