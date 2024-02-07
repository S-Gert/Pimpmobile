#include "Servocontrol.h"
#include "Motorcontrol.h"
#include "Receiver.h"
#include "Encoder.h"

#define servo_driver_toggle 13

// Create objects with pins
ServoControl servo(51, 33);
MotorControl r_motor(9, 22);
MotorControl l_motor(10, 26);
EncoderData encoder(4, 5, 6);
ReceiverData receiver;
int encoder_pos = 500; // ~500 is center
int RXed_int;
int ch1_right_horizontal, ch3_left_vertical, ch8_switch_lock, ch6_switch_to_toggle, ch7_diff_toggle;

int diff(int motors_pwm, int encoder){
  double exp_x = (abs(encoder - 500) - 220) / 45; // encoder max 280, exp curve threshold 200, curve steepness 45
  double exp_function = 1 / (1 + exp(-exp_x));
  int new_pwm = motors_pwm * (1 - exp_function);
  return new_pwm;
}

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(10);
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
    r_motor.run(0);
    l_motor.run(0);
    Serial.println(ch1_right_horizontal);
    //Serial.println("--MOTORS LOCKED--");

    // ####### REMOTE CONTROL ######
  } else if (ch8_switch_lock != 1000 && ch6_switch_to_toggle == 1000){
    if (ch1_right_horizontal > 0){ // turning right
      servo.run(encoder_pos, ch1_right_horizontal, 1);
    } else if(ch1_right_horizontal < 0){ // turning left
      servo.run(encoder_pos, ch1_right_horizontal, 0);
    } else if(ch1_right_horizontal == 0){
      servo.returnToCenter(encoder_pos);
    }
    digitalWrite(servo_driver_toggle, LOW);
    
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
    RXed_int = Serial.parseInt();
    Serial.println(encoder_pos);
    }
}