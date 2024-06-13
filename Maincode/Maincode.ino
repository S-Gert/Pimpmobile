#include "Servocontrol.h"
#include "Motorcontrol.h"
#include "Receiver.h"
#include "Encoder.h"
#include "Autonomouscontrol.h"

// Create objects with pins
ServoControl servo(51, 33, 13);
MotorControl r_motor(9, 22, 46);
MotorControl l_motor(10, 26, 46);
EncoderData servo_encoder(6, 7, 8); // 4, 5, 6
AutoControl autonomous;
ReceiverData receiver;

int encoder_pos = 500; // ~500 is center, 780 max right, 220 max left
int to_motors = 0, to_servo = 0, to_brakes = 0;
int ch1_right_horizontal, ch3_left_vertical, ch4_left_knob, ch9_switch_lock, ch6_switch_to_toggle, ch7_diff_toggle, ch8_tri_switch;
float multiplied_speed;
int RXservo = 0;
int RXmotors = 0;
bool RXbrakes;

void run_diff(int motors_pwm, int encoder){
  if (encoder > 500){
    l_motor.run(motors_pwm);
    r_motor.run(r_motor.diff(motors_pwm, encoder));
    } else {
    r_motor.run(motors_pwm);
    l_motor.run(l_motor.diff(motors_pwm, encoder));
    }
}

void readRcChannels(){
  ch9_switch_lock = receiver.readChannelRaw(9);
  ch8_tri_switch = receiver.readChannelRaw(8); // the values are: 1000, 1500, 2000
  ch3_left_vertical = receiver.readChannelMapped(2, 255, 1000, 2000, 30);
  ch1_right_horizontal = receiver.readChannelMapped(0, 255, 980, 1978, 0);
  ch7_diff_toggle = receiver.readChannelRaw(7);
  ch6_switch_to_toggle = receiver.readChannelRaw(6);
  ch4_left_knob = (map(receiver.readChannelRaw(4), 1000, 2000, 0, 100));
  //speed_multiplier = ch4_left_knob / 100; // Maps value to 0.0 to 1.0 range.
  encoder_pos = servo_encoder.read();
}

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(10);
  delay(1500); // time for the receiver and remote to properly start without giving crazy numbers
}

void loop(){
  readRcChannels();
  autonomous.readWriteSerial(ch8_tri_switch);
  // autonomous.writeSerial(encoder_pos);

  /* MOTORS & SERVO LOCKED */
  if (ch9_switch_lock == 1000){
    r_motor.activateBrakes(true);
    l_motor.activateBrakes(true);
    servo.activateServo(false);

  /* MOTOR & SERVO UNLOCKED */
  } else if (ch9_switch_lock != 1000){
    servo.activateServo(true);

    /* REMOTE CONTROL */
    if (ch6_switch_to_toggle == 1000){
      r_motor.activateBrakes(false);
      l_motor.activateBrakes(false);
      servo.runWithBufferAndDirection(ch1_right_horizontal, encoder_pos);
      multiplied_speed = (ch3_left_vertical * ch4_left_knob)/100;
      
      /* DIFFERENTIAL CHECK */
      if (ch7_diff_toggle == 1000){
        run_diff(int(trunc(multiplied_speed)), encoder_pos);
      } else {
        l_motor.run(int(trunc(multiplied_speed)));
        r_motor.run(int(trunc(multiplied_speed)));
      }
    } /* end of remote control */

    /* AUTONOMOUS SERIAL CONTROL */
    if (ch6_switch_to_toggle == 2000){
      // autonomous.readSerial();
      // autonomous.writeSerial(ch8_tri_switch);
  
      RXbrakes = autonomous.getBrakesRX();
      RXmotors = autonomous.getMotorsRX();
      RXservo = autonomous.getServoRX();

      if (RXbrakes) {
        r_motor.activateBrakes(true);
        l_motor.activateBrakes(true);
      } else {
        r_motor.activateBrakes(false);
        l_motor.activateBrakes(false);

        servo.runWithBufferAndDirection(RXservo, encoder_pos);
        
        /* DIFFERENTIAL CHECK */
        if (ch7_diff_toggle == 1000){
          run_diff(RXmotors, encoder_pos);
        } else {
          l_motor.run(RXmotors);
          r_motor.run(RXmotors);
        }
      } /* end of differential and brake check*/

    } /* end of autonomous control if */
  } /* end of remote lock */

} /* end of loop */