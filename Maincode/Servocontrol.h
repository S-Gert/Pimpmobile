#ifndef Servocontrol_h
#define Servocontrol_h
#include "Arduino.h"

class ServoControl {
  public:
    ServoControl(int analogPin, int digitalPin);
    void run(double recData, double desiredAngle);
    void moveDegree(double steps);
    double calculateSteps(double recData, double desiredAngle);
    int getStepsForDesiredDeg(double desiredAngle);
    void turn(double stepCount, bool direction);
  private:
    double _pulse;
    int _analogPin;
    int _digitalPin;
    double _prevStepCount;
    int _position;
};

#endif