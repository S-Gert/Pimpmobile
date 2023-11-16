#include <Servocontrol.h>
#include <Motorcontrol.h>
#include <Receiver.h>

// Create objects
ServoControl servo(D6, D3);
MotorControl motors(D9, D0);
ReceiverData receiver(D8, D7);

int forward_motor_pin = D4;
int backward_motor_pin = D10;

double ch1, ch2;

void setup(){
  Serial.begin(9600);
  pinMode(forward_motor_pin, INPUT);
  pinMode(backward_motor_pin, INPUT);
}

void loop(){
  // ch1 = receiver.readChannel1();
  // ch2 = receiver.readChannel2();
  // servo.run(ch2, 45);
  // motors.run(ch1);
  // receiver.printValues(ch1, ch2);
  if (digitalRead(forward_motor_pin) == 1){
  motors.teleopRun(1, 200, 100, 1);
  } else if (digitalRead(backward_motor_pin) == 1){
  motors.teleopRun(1, 200, 100, 0);
  } else if (digitalRead(forward_motor_pin) == 0){
  motors.teleopRun(0, 200, 100, 1);
  } else if (digitalRead(backward_motor_pin) == 0){
  motors.teleopRun(0, 200, 100, 0);
  }
  // if (digitalRead(input_pin) == 1){
  //   Serial.println("HIGH");
  // }
  // // delay(3000);
  // motors.teleopRun(0, 400, 50, 1);
  // delay(3000);
}