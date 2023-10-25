#include <Servocontrol.h>
#include <Motorcontrol.h>
#include <Receiver.h>

// Objektide loomine
ServoControl servo(D6, D3);
//MotorControl motors(D9, D0);
ReceiverData receiver(D8, D7);

double ch1, ch2;

void setup(){
  Serial.begin(9600);
}

void loop(){
  // ch1 = receiver.readChannel1();
  // ch2 = receiver.readChannel2();
  // receiver.printValues(ch1, ch2);
  servo.run(400);
  //motors.run(ch1);
}