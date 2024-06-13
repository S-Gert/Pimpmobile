#include "Autonomouscontrol.h"
#include "Arduino.h"

AutoControl::AutoControl(){
  i = 0;

  RX_motors = 0;
  RX_servo = 0;
  RX_brakes = 0;
  old_time = millis();
  new_time = millis();
}

void AutoControl::readSerial(){
  byte buf[total_bytes];
  if (Serial.available() >= total_bytes) {
    i=0;
    while(i < total_bytes){
      buf[i] = Serial.read();
      i++;
    }
    memmove(&bytes,buf,sizeof(bytes));
    RX_motors = int(bytes.x);
    RX_servo = int(bytes.y);
    RX_brakes = int(bytes.z);
  } // struct serial end
}

void AutoControl::writeSerial(int write_value){
  new_time = millis();
  if (new_time >= old_time + 100){
    values.TX_val = float(write_value);
    //values.TX_val = RX_brakes;
    Serial.write((const uint8_t*)&values,sizeof(values));
    old_time = new_time;
  }
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