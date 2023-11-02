#include "Arduino.h"
#include "Servocontrol.h"

// pins analog D6, digital D3
ServoControl::ServoControl(int analogPin, int digitalPin){
  Serial.begin(9600);
  pinMode(analogPin, OUTPUT);
  pinMode(digitalPin, OUTPUT);
  _analogPin = analogPin;
  _digitalPin = digitalPin;
  _prevRecData = 0;
  _position = 0;
  _pulse = 400;
}

int ServoControl::getStepsForDesiredDeg(double desiredAngle) {
  double stepsMax = _pulse * 50; // gearbox ratio
  return stepsMax / 360 * desiredAngle;
}

double ServoControl::calculateDeg(double recData, double desiredAngle) {
  int stepsForDesiredDeg = getStepsForDesiredDeg(desiredAngle);
  double stepsPerDeg = stepsForDesiredDeg / desiredAngle; //55.5555
  double stepsPerRecData = 1000 / desiredAngle;  //22.222222
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

void ServoControl::rightTurn(double recData, double desiredAngle) {
  digitalWrite(_digitalPin, LOW);
  if (recData > _prevRecData) {
    moveDegree(calculateDeg((recData-_prevRecData), desiredAngle));
  } else {
    digitalWrite(_digitalPin, HIGH); // vajadusel muudab!
    moveDegree(calculateDeg((_prevRecData-recData), desiredAngle));
  }
}

void ServoControl::leftTurn(double recData, double desiredAngle) {
  digitalWrite(_digitalPin, HIGH);
  if (recData < _prevRecData) {
    moveDegree(calculateDeg((abs(recData)-abs(_prevRecData)), desiredAngle));
  } else {
    digitalWrite(_digitalPin, LOW); // vajadusel muudab!
    moveDegree(calculateDeg((abs(_prevRecData)-abs(recData)), desiredAngle));
  }
}

bool ServoControl::bufferZone(double recData, double _prevRecData) {
  return (recData > (_prevRecData+50) || recData < (_prevRecData-50));
}

void ServoControl::run(double recData, double desiredAngle){
  if (recData != 0){
    if (bufferZone(recData, _prevRecData)){
      if (recData > 0){ 
        rightTurn(recData, desiredAngle);
      } else { 
        leftTurn(recData, desiredAngle);
      }
    }
  }
  _prevRecData = recData;
}