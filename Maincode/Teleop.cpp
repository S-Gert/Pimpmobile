#include "Teleop.h"
#include "Arduino.h"

Teleop::TeleOperation(int baud_rate, int timeout){
  Serial.begin(baud_rate);
  Serial.setTimeout(timeout);
}