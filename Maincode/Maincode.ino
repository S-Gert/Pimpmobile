#include "Servocontrol.h"
#include "Motorcontrol.h"
#include "Receiver.h"

#define servo_driver_toggle 13
// Create objects with output pins
ServoControl servo(51, 33);
MotorControl motors(9, 22);
ReceiverData receiver;

int max_angle_steps = servo.getStepsForDesiredDeg(45); 
int ch1_right_horizontal, ch3_left_vertical, ch8_switch;
bool last_direction;

String RXed_byte;

void setup(){
  Serial.begin(9600);
}

void remote_control(){
  ch1_right_horizontal = receiver.readChannelMapped(0, 4, 960, 1978, 0, 0);
  ch3_left_vertical = receiver.readChannelMapped(2, 255, 1000, 2000, 10, 0);
  servo.run(ch1_right_horizontal, 45);
  motors.run(ch3_left_vertical);
  Serial.println(ch1_right_horizontal);
}

void loop(){
  //Remote control lock code:
  // while (receiver.readChannelRaw(9) == 1000){ // If switch is down, then this code executes
  //   Serial.println("--MOTORS LOCKED--");
  //   //motors.run(0);
  //}
  ch8_switch = receiver.readChannelRaw(9);
  ch3_left_vertical = receiver.readChannelMapped(2, 255, 1000, 2000, 10, 0);
  ch1_right_horizontal = receiver.readChannelMapped(0, 4, 960, 1978, 0, 0);

  if (ch8_switch == 1000){
    digitalWrite(servo_driver_toggle, HIGH);
    motors.run(0);
    Serial.println("--MOTORS LOCKED--");
  } else {
    if (ch1_right_horizontal > 0){
      servo.runSimple(45, 1);
    } else if(ch1_right_horizontal < 0){
      servo.runSimple(45, 0);
    }// else if(ch1_right_horizontal == 0){
    //  servo.returnToCenter();
    //}
    //servo.printSteps();
    digitalWrite(servo_driver_toggle, LOW);
    //servo.run(ch1_right_horizontal, 45);
    motors.run(ch3_left_vertical);
  }
  //remote_control();
  //servo.run(ch1_right_horizontal, 45);
  //Serial.println(ch8_switch);
  //Serial communication code:
  // if (Serial.available()){
  //   RXed_byte = Serial.readString();
  //   Serial.print(RXed_byte);
  // }
}