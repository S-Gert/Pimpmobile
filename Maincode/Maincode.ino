#include <Servocontrol.h>
#include <Motorcontrol.h>
#include <Receiver.h>

// Create objects
ServoControl servo(D6, D3);
MotorControl motors(D9, D0);
ReceiverData receiver(D8, D7);

double ch1, ch2;

void setup(){
  Serial.begin(9600);
}

void loop(){
  ch1 = receiver.readChannel1();
  ch2 = receiver.readChannel2();
  servo.run(ch2, 45);
  motors.run(ch1);
  receiver.printValues(ch1, ch2);
}