#include "Servocontrol.h"
#include "Motorcontrol.h"
#include "Receiver.h"
#include "Encoder.h"

#define servo_driver_toggle 13
#define motor_brakes 46

// Create objects with pins
ServoControl servo(51, 33);
MotorControl r_motor(9, 22);
MotorControl l_motor(10, 26);
EncoderData encoder(4, 5, 6);
ReceiverData receiver;

bool motor_brake_state = 0;
int encoder_pos = 500; // ~500 is center
String RXed_str;
int ch1_right_horizontal, ch3_left_vertical, ch8_switch_lock, ch6_switch_to_toggle, ch7_diff_toggle;
int to_motors, to_servo, to_brakes;

int diff(int motors_pwm, int encoder){
  double exp_x = (abs(encoder - 500) - 220) / 45; // encoder max 280, exp curve threshold 200, curve steepness 45
  double exp_function = 1 / (1 + exp(-exp_x));
  int new_pwm = motors_pwm * (1 - exp_function);
  return new_pwm;
}

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(20);
  pinMode(motor_brakes, OUTPUT);
  pinMode(servo_driver_toggle, OUTPUT);
  delay(3000); // time for the receiver and remote to properly start without giving crazy numbers
}

void loop(){
  ch8_switch_lock = receiver.readChannelRaw(9);
  ch3_left_vertical = receiver.readChannelMapped(2, 255, 1000, 2000, 30, 0);
  ch1_right_horizontal = receiver.readChannelMapped(0, 280, 980, 1978, 0, 0);
  if (-5 < ch1_right_horizontal && ch1_right_horizontal < 5){ // Buffer near 0
    ch1_right_horizontal = 0;
  }
  ch7_diff_toggle = receiver.readChannelRaw(7);
  ch6_switch_to_toggle = receiver.readChannelRaw(6);
  encoder_pos = encoder.read();

  // ####### MOTOR LOCK ######
  if (ch8_switch_lock == 1000){
    digitalWrite(servo_driver_toggle, HIGH);
    if (motor_brake_state == 0){
      digitalWrite(motor_brakes, HIGH);
      motor_brake_state = 1;
    }
    r_motor.run(0);
    l_motor.run(0);
  // ####### REMOTE CONTROL ######
  } else if (ch8_switch_lock != 1000 && ch6_switch_to_toggle == 1000){
    digitalWrite(servo_driver_toggle, LOW);
    if (motor_brake_state == 1){
      digitalWrite(motor_brakes, LOW);
      motor_brake_state = 0;
    }

    //turning
    if (ch1_right_horizontal > 0){ // turning right
      servo.run(encoder_pos, ch1_right_horizontal, 1);
    } else if(ch1_right_horizontal < 0){ // turning left
      servo.run(encoder_pos, ch1_right_horizontal, 0);
    } else if(ch1_right_horizontal == 0){
      servo.returnToCenter(encoder_pos);
    }
    
    //differential and motors
    if (ch7_diff_toggle == 1000){
      if (encoder_pos > 500){
        l_motor.run(ch3_left_vertical);
        r_motor.run(diff(ch3_left_vertical, encoder_pos));
      } else {
        r_motor.run(ch3_left_vertical);
        l_motor.run(diff(ch3_left_vertical, encoder_pos));
      }
    } else {
      l_motor.run(ch3_left_vertical);
      r_motor.run(ch3_left_vertical);
    }
    //Serial.println("--UNLOCKED--");
  }
  //// ####### TELEOP ######
  if (ch6_switch_to_toggle == 2000 && ch8_switch_lock == 2000){
    if (motor_brake_state == 1){
      digitalWrite(motor_brakes, LOW);
      motor_brake_state = 0;
    }

    if (Serial.available() > 0) {
      RXed_str = Serial.readStringUntil('\n');

      int values[3];
      int i = 0;
      char *ptr = strtok((char *)RXed_str.c_str(), ",");
      while (ptr != NULL && i < 3) {
        values[i++] = atoi(ptr);
        ptr = strtok(NULL, ",");
      }

      to_motors = values[0];
      to_servo = values[1];
      to_brakes = values[2];

      if (to_brakes == 1) {
        digitalWrite(motor_brakes, HIGH);
      } else {
        digitalWrite(motor_brakes, LOW);
      }

      l_motor.run(to_motors);
      r_motor.run(to_motors);

      //Serial.println(values[0]); // gas pedal -255 to 255
      //Serial.println(values[1]); // steering wheel -255 to 255
      //Serial.println(values[2]); // brake pedal 0 to 1
    
    } // end of Serial.available()
    if (to_servo > 0){ // turning right
      servo.run(encoder_pos, to_servo, 1);
    } else if(to_servo < 0){ // turning left
      servo.run(encoder_pos, to_servo, 0);
    } 
 
    } // end of teleop if
}