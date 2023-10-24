#include <Servocontrol.h>
#include <Motorcontrol.h>

//ServoControl servo(D6, D3);
MotorControl motors(D9, D0);

void setup(){
}

void loop(){
  //servo.runConstant(200, 0);
  motors.runConstant(128, 0);
}