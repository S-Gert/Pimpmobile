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
  // ch2 = receiver.readChannel2();
  // ch1 = receiver.readChannel1();
  //receiver.printValues(ch1, ch2);
  // servo.moveDegree(1600);
  delay(2000);
  servo.run(3, 45);
  // Serial.print("3");
  delay(2000);
  servo.run(0, 45);
  delay(2000);
  servo.run(-3, 45);
  // Serial.print("-3");
  delay(2000);
  servo.run(0, 45);
  // delay(3000);

}