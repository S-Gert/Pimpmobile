#include <Servocontrol.h>
#include <Motorcontrol.h>
#include <Receiver.h>

// ServoControl servo(D6, D3);
// MotorControl motors(D9, D0);
ReceiverData receiver(D8, D7);

double ch1, ch2;

void setup(){
}

void loop(){
  // servo.runConstant(200, 0);
  // motors.runConstant(128, 0);
  ch1, ch2 = receiver.readChannels();
  receiver.printValues(ch1, ch2);
}