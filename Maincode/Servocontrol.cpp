#include "Arduino.h"
#include "Servocontrol.h"// pins analog D6, digital D3
ServoControl::ServoControl(int analogPin, int digitalPin){
  Serial.begin(9600);
  pinMode(analogPin, OUTPUT);
  pinMode(digitalPin, OUTPUT);
  _analogPin = analogPin;
  _digitalPin = digitalPin;
  _prevStepCount = 0;
  _position = 0;
  _pulse = 400;

}
int ServoControl::getStepsForDesiredDeg(double desiredAngle) {
  double stepsMax = _pulse * 50; // gearbox ratio
  return stepsMax / 360 * desiredAngle;
}
double ServoControl::calculateSteps(double recData, double desiredAngle) {
  int stepsForDesiredDeg = getStepsForDesiredDeg(desiredAngle);
  double stepsPerDeg = stepsForDesiredDeg / desiredAngle; //13.888888
  double stepsPerRecData = 4 / desiredAngle;  //22.222222
  double steps = (abs(recData) / stepsPerRecData) * stepsPerDeg; // steps needed for x degree turn
  return steps;
}
void ServoControl::moveDegree(double steps){
  for (int i; i < int(steps); i++){
    digitalWrite(_analogPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(_analogPin, LOW);
    delayMicroseconds(100);
  }
  
}
void ServoControl::turn(double stepCount, bool direction) {
  if (stepCount > _prevStepCount) {
    digitalWrite(_digitalPin, direction);
    moveDegree(stepCount - _prevStepCount);
  } else {
    digitalWrite(_digitalPin, direction);
    moveDegree(_prevStepCount - stepCount);
  }
}
void ServoControl::run(double recData, double desiredAngle){
  double stepCount = calculateSteps(recData, desiredAngle);
  if (recData >= 0){ 
    turn(stepCount, 0);
  } else { 
    turn(stepCount, 1);
  }
  _prevStepCount = stepCount;
}