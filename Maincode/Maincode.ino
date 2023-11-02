#include <Servocontrol.h>
#include <Motorcontrol.h>
#include <Receiver.h>

// Objektide loomine
ServoControl servo(D6, D3);
MotorControl motors(D9, D0);
ReceiverData receiver(D8, D7);

double ch1, ch2;
int time;

void setup(){
  Serial.begin(9600);
}

void loop(){
  // time = 0;
  ch2 = receiver.readChannel2();
  // ch1 = receiver.readChannel1();
  // receiver.printValues(ch1, ch2);
  servo.run(ch2, 180);
  // time = millis();
  // servo.run(50);
  // delay(5000);
  //Serial.print(time);
}