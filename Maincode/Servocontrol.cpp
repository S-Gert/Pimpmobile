#include "Arduino.h"
#include "Servocontrol.h"

//pins analog D6, digital D3: analog 9 digital 3
ServoControl::ServoControl(int analog_pin, int digital_pin, int servo_driver_toggle_pin){
  pinMode(analog_pin, OUTPUT);
  pinMode(digital_pin, OUTPUT);
  pinMode(servo_driver_toggle_pin, OUTPUT);
  _servo_driver_toggle_pin = servo_driver_toggle_pin;
  _analog_pin = analog_pin;
  _digital_pin = digital_pin;
}

void ServoControl::run(int encoder_angle, int input, bool direction, bool teleop){
  int turn_angle = input + 500;
  int to_max_turn_angle = 255;
  if(turn_angle <= encoder_angle + 5 && turn_angle >= encoder_angle - 5){
    return;
  } 

  if (teleop == 1){
    if (turn_angle >= 500 + to_max_turn_angle | turn_angle <= 500 - to_max_turn_angle){
      return;
    } 
  }

  if (direction == 1){
    digitalWrite(_digital_pin, HIGH);
    if(encoder_angle > turn_angle){
      digitalWrite(_digital_pin, LOW);
    }
  } else if (direction == 0) {
    digitalWrite(_digital_pin, LOW);
    if(encoder_angle < turn_angle){
      digitalWrite(_digital_pin, HIGH);
    }
  }
    digitalWrite(_analog_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_analog_pin, LOW);
    delayMicroseconds(10);
}

void ServoControl::returnToCenter(int enc_pos){
  if(enc_pos > 505){
    run(enc_pos, 0, 0, 0);
  } else if(enc_pos < 495){
    run(enc_pos, 0, 1, 0);
  }
}

void ServoControl::activateServo(bool state){
  digitalWrite(_servo_driver_toggle_pin, !state);
}

void ServoControl::remoteControlTurning(int rc_channel_value, int encoder_pos){
  //  Turning buffer near 0
  if (-5 < rc_channel_value && rc_channel_value < 5){
    rc_channel_value = 0;
  }
  //turning
  if (rc_channel_value > 0){ // turning right
    run(encoder_pos, rc_channel_value, 1, 0);
  } else if(rc_channel_value < 0){ // turning left
    run(encoder_pos, rc_channel_value, 0, 0);
  } else if(rc_channel_value == 0){
    returnToCenter(encoder_pos);
  }
}