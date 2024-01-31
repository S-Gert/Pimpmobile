#include "Arduino.h"
#include "Servocontrol.h"

//pins analog D6, digital D3: analog 9 digital 3
ServoControl::ServoControl(int analog_pin, int digital_pin){
  Serial.begin(9600);
  pinMode(analog_pin, OUTPUT);
  pinMode(digital_pin, OUTPUT);
  _analog_pin = analog_pin;
  _digital_pin = digital_pin;
  _last_turn_angle;
}

void ServoControl::run(int encoder_angle, int max_angle, int min_angle, int input, bool direction){
  int turn_angle = input + 500;
  if(turn_angle == encoder_angle){
    return;
  }
  if (direction == 1){
    digitalWrite(_digital_pin, HIGH);
    if(encoder_angle > turn_angle){
      digitalWrite(_digital_pin, LOW);
    }
  } else if (direction == 0) {
    digitalWrite(_digital_pin, LOW);
    if(encoder_angle < turn_angle){
      digitalWrite(_digital_pin, HIGH);
    }
  }
    digitalWrite(_analog_pin, HIGH);
    delayMicroseconds(100);
    digitalWrite(_analog_pin, LOW);
    delayMicroseconds(100);
}