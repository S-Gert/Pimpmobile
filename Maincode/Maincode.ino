#include <Servocontrol.h>
#include <Motorcontrol.h>
#include <Receiver.h>

// Create objects
ServoControl servo(D6, D3);
MotorControl motors(D9, D0);
ReceiverData receiver(D8, D7);

const int forward_motor_pin = D4;
const int backward_motor_pin = D10;
const int servo_left_pin = D12;
const int servo_right_pin = D14;
int servo_left_pin_read;
int servo_right_pin_read;
int forward_motor_pin_read;
int backward_motor_pin_read;
int max_angle_steps = servo.getStepsForDesiredDeg(45); 
double ch1, ch2;

void setup(){
  Serial.begin(9600);
  pinMode(forward_motor_pin, INPUT);
  pinMode(backward_motor_pin, INPUT);
  pinMode(servo_left_pin, INPUT);
  pinMode(servo_right_pin, INPUT);
}

void loop(){
  servo_left_pin_read = digitalRead(servo_left_pin);
  servo_right_pin_read = digitalRead(servo_right_pin);
  forward_motor_pin_read = digitalRead(forward_motor_pin);
  backward_motor_pin_read = digitalRead(backward_motor_pin);

  if (servo_left_pin_read == 1){
    servo.runTeleOp(100, 1, max_angle_steps);
  } else if (servo_right_pin_read == 1){
    servo.runTeleOp(100, 0, max_angle_steps);
  } else if (servo_left_pin_read == 0 && servo_right_pin_read == 0){
    servo.returnToCenter(100);
  }

  if (forward_motor_pin_read == 1){
  motors.teleopRun(1, 200, 100, 1);
  } else if (backward_motor_pin_read == 1){
  motors.teleopRun(1, 200, 100, 0);
  } else if (forward_motor_pin_read == 0){
  motors.teleopRun(0, 200, 100, 1);
  } else if (backward_motor_pin_read == 0){
  motors.teleopRun(0, 200, 100, 0);
  }
  
  // Serial.print(servo_left_pin_read);
  // Serial.print('\n');
  // Serial.print(servo_right_pin_read);
  // Serial.print('\n');

  // Serial.print(forward_motor_pin_read);
  // Serial.print('\n');
  // Serial.print(backward_motor_pin_read);
  // Serial.print('\n');

  // ch1 = receiver.readChannel1();
  // ch2 = receiver.readChannel2();
  // servo.run(ch2, 45);
  // motors.run(ch1);
  // receiver.printValues(ch1, ch2);


}