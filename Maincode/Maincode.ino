#include <Servocontrol.h>
#include <Motorcontrol.h>

// ServoControl servo(D6, D3);
MotorControl motors(D4, D0);

void setup(){
}

void loop(){
  motors.forwards(100);
  // delay(3);
  // motors.backwards(100);
  // delay(3);
  // servo.runConstant(200);
}