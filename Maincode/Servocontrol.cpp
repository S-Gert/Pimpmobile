#include "Arduino.h"
#include "Servocontrol.h"

//pins analog D6, digital D3: analog 9 digital 3
ServoControl::ServoControl(int analog_pin, int digital_pin){
  Serial.begin(9600);
  pinMode(analog_pin, OUTPUT);
  pinMode(digital_pin, OUTPUT);
  _analog_pin = analog_pin;
  _digital_pin = digital_pin;
}

void ServoControl::run(int max_angle, bool direction){
  if (direction == 1){
    digitalWrite(_digital_pin, HIGH);
  } else if (direction == 0) {
    digitalWrite(_digital_pin, LOW);
  }
    digitalWrite(_analog_pin, HIGH);
    delayMicroseconds(100);
    digitalWrite(_analog_pin, LOW);
    delayMicroseconds(100);
}