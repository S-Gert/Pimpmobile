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
int RXed_int;
int ch1_right_horizontal, ch3_left_vertical, ch8_switch_lock, ch6_switch_to_toggle;

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(10);
  delay(3000); // time for the receiver and remote to properly start without giving crazy numbers
}

void loop(){
  ch8_switch_lock = receiver.readChannelRaw(9);
  ch3_left_vertical = receiver.readChannelMapped(2, 255, 1000, 2000, 30, 0);
  ch1_right_horizontal = receiver.readChannelMapped(0, 4, 960, 1978, 0, 0);
  ch6_switch_to_toggle = receiver.readChannelRaw(6);

  if (ch8_switch_lock == 1000){ //Lock motors and servo
    digitalWrite(servo_driver_toggle, HIGH);
    motors.run(0);
    Serial.println("--MOTORS LOCKED--");
  } else if (ch8_switch_lock != 1000 && ch6_switch_to_toggle == 1000){ // Remote control
    if (ch1_right_horizontal > 0){
      servo.run(420, 1);
    } else if(ch1_right_horizontal < 0){
      servo.run(420, 0);
    }
    digitalWrite(servo_driver_toggle, LOW);
    motors.run(ch3_left_vertical);
    Serial.println("--UNLOCKED--");
  }
  //Serial communication code:
  if (ch6_switch_to_toggle == 2000 && ch8_switch_lock == 2000){
    RXed_int = Serial.parseInt();
    Serial.println(encoder.read());
    }
}