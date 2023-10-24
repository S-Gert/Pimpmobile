#include <Servocontrol.h>

ServoControl servo(D4, D0);

void setup(){
}

void loop(){
  servo.runConstant(200);
}