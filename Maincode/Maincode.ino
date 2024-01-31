#include "Servocontrol.h"
#include "Motorcontrol.h"
#include "Receiver.h"
#include "Encoder.h"

#define servo_driver_toggle 13

// Create objects with pins
ServoControl servo(51, 33);
MotorControl motors(9, 22);
EncoderData encoder(4, 5, 6);
ReceiverData receiver;
int encoder_pos = 500; // ~500 is center
int RXed_int;
int ch1_right_horizontal, ch3_left_vertical, ch8_switch_lock, ch6_switch_to_toggle;

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(10);
  delay(3000); // time for the receiver and remote to properly start without giving crazy numbers
}

void returnToCenter(int enc_pos){
  if(enc_pos > 505){
    servo.run(enc_pos, 1001, -1, 0, 0);
  } else if(enc_pos < 495){
    servo.run(enc_pos, 1001, -1, 0, 1);
  }
}

void loop(){
  ch8_switch_lock = receiver.readChannelRaw(9);
  ch3_left_vertical = receiver.readChannelMapped(2, 255, 1000, 2000, 30, 0);
  ch1_right_horizontal = receiver.readChannelMapped(0, 280, 980, 1978, 0, 0);
  if (-5 < ch1_right_horizontal && ch1_right_horizontal < 5){ // Buffer near 0
    ch1_right_horizontal = 0;
  }
  ch6_switch_to_toggle = receiver.readChannelRaw(6);
  encoder_pos = encoder.read();

  // ####### MOTOR LOCK ######
  if (ch8_switch_lock == 1000){ //Lock motors and servo
    digitalWrite(servo_driver_toggle, HIGH);
    motors.run(0);
    Serial.println(ch1_right_horizontal);
    //Serial.println("--MOTORS LOCKED--");

    // ####### REMOTE CONTROL ######
  } else if (ch8_switch_lock != 1000 && ch6_switch_to_toggle == 1000){
    if (ch1_right_horizontal > 0){
      servo.run(encoder_pos, 780, 220, ch1_right_horizontal, 1);
    } else if(ch1_right_horizontal < 0){
      servo.run(encoder_pos, 780, 220, ch1_right_horizontal, 0);
    } else if(ch1_right_horizontal == 0){
      returnToCenter(encoder_pos);
    }
    digitalWrite(servo_driver_toggle, LOW);
    motors.run(ch3_left_vertical);
    //Serial.println("--UNLOCKED--");
  }
  //// ####### TELEOP ######
  if (ch6_switch_to_toggle == 2000 && ch8_switch_lock == 2000){
    RXed_int = Serial.parseInt();
    Serial.println(encoder_pos);
    }
}