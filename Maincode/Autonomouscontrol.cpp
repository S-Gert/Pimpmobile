#include "Autonomouscontrol.h"
#include "Arduino.h"

AutoControl::AutoControl(){
  RX_motors = 0;
  RX_servo = 0;
  RX_brakes = 0;
}

void AutoControl::readWriteSerial(int write_value){
  if (Serial.available() >= 3 * sizeof(int)) {
    for (int i = 0; i < 3; i++) {
      read_values[i] = Serial.read() | (Serial.read() << 8);
    }

    RX_motors = read_values[0];
    RX_servo = read_values[1];
    RX_brakes = read_values[2];

    Serial.write((byte)(write_value & 0xFF));
    Serial.write((byte)((write_value >> 8) & 0xFF));
  }
}

int AutoControl::getMotorsRX(){
  return RX_motors;
}

int AutoControl::getServoRX(){
  return RX_servo;
}

bool AutoControl::getBrakesRX(){
  if (RX_brakes >= 1){
    return true;
  } else {
    return false;
  }
}