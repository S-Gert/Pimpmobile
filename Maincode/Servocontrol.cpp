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

void ServoControl::run(int input, int encoder_pos, bool direction){
  int encoder_middle_value = 500;
  int desired_turn_angle = input + encoder_middle_value;

  if(desired_turn_angle <= encoder_pos + 5 && desired_turn_angle >= encoder_pos - 5){
    return;
  } 

  if (direction == 1){
    digitalWrite(_digital_pin, HIGH);
    if(encoder_pos > desired_turn_angle){
      digitalWrite(_digital_pin, LOW);
    }
  } else if (direction == 0) {
    digitalWrite(_digital_pin, LOW);
    if(encoder_pos < desired_turn_angle){
      digitalWrite(_digital_pin, HIGH);
    }
  }
    digitalWrite(_analog_pin, HIGH);
    //delayMicroseconds(10);
    digitalWrite(_analog_pin, LOW);
    //delayMicroseconds(10);
}

void ServoControl::returnToCenter(int encoder_pos){
  if(encoder_pos > 505){
    run(0, encoder_pos, 0);
  } else if(encoder_pos < 495){
    run(0, encoder_pos, 1);
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
    run(rc_channel_value, encoder_pos, 1);
  } else if(rc_channel_value < 0){ // turning left
    run(rc_channel_value, encoder_pos, 0);
  } else if(rc_channel_value == 0){
    returnToCenter(encoder_pos);
  }
}