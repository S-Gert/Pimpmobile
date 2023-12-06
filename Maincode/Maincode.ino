#include "Servocontrol.h"
#include "Motorcontrol.h"
#include "Receiver.h"

// Create objects with output pins
ServoControl servo(9, 3);
MotorControl motors(8, 2);
ReceiverData receiver;

int max_angle_steps = servo.getStepsForDesiredDeg(45); 
int ch1_right_horizontal, ch3_left_vertical;
bool last_direction;

String RXed_byte;

void setup(){
  Serial.begin(9600);
}

void loop(){
  //Remote control code:
  //ch1_right_horizontal = receiver.readChannelMapped(0, 4, 960, 1978, 0, 0);
  //ch3_left_vertical = receiver.readChannelMapped(2, 255, 1000, 2000, 10, 0);
  //servo.run(ch1_right_horizontal, 45);
  //motors.run(ch3_left_vertical);
  //Serial.println(ch1_right_horizontal);
  //Serial.println(ch3_left_vertical);

  //Serial communication code:
  if (Serial.available()){
    RXed_byte = Serial.readString();
    Serial.print(RXed_byte);
  }
}