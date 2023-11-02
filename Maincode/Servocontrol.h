#ifndef Servocontrol_h
#define Servocontrol_h
#include "Arduino.h"

class ServoControl {
  public:
    ServoControl(int analogPin, int digitalPin);
    void run(double recData, double desiredAngle);
    void moveDegree(double recData);
    double calculateDeg(double recData, double desiredAngle);
    int getStepsForDesiredDeg(double desiredAngle);
    bool bufferZone(double recData, double _prevRecData);
    void rightTurn(double recData, double desiredAngle);
    void leftTurn(double recData, double desiredAngle);
  private:
    double _pulse;
    int _analogPin;
    int _digitalPin;
    double _prevRecData;
    int _position;
};

#endif