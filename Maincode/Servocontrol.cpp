#include "Arduino.h"
#include "Servocontrol.h"

//constructor :: <-- scope resolution operator
ServoControl::ServoControl(int servoAnalogPin, int servoDigitalPin){
  Serial.begin(9600);
  pinMode(servoAnalogPin, OUTPUT);
  _servoAnalogPin = servoAnalogPin;
  _servoDigitalPin = servoDigitalPin;
}

void ServoControl::runConstant(int delayMicroSec){
  digitalWrite(_servoAnalogPin, HIGH);
  delayMicroseconds(delayMicroSec);
  digitalWrite(_servoAnalogPin, LOW);
  delayMicroseconds(delayMicroSec);
}