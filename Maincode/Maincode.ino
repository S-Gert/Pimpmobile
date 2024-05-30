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
EncoderData servo_encoder(4, 5, 6);
ReceiverData receiver;

// struct serial start

struct sendata { //data to send
volatile int val;
};
struct receive { //data to receive
  volatile int x;
  volatile int y;
  volatile int z;
};
struct sendata values;
struct receive bytes;
const int total_bytes=3*sizeof(int);
int i;
byte buf[total_bytes];

// struct serial end

bool motor_brake_state = 0;
int encoder_pos = 500; // ~500 is center, 780 max right, 220 max left
int ch1_right_horizontal, ch3_left_vertical, ch9_switch_lock, ch6_switch_to_toggle, ch7_diff_toggle, ch8_tri_switch;
int to_motors = 0, to_servo = 0, to_brakes = 0, drive_state = 0;

int current_time = 0;
int last_time = 0;

int diff(int motors_pwm, int encoder){
  double exp_x = (abs(encoder - 500) - 220) / 45; // encoder max 280, exp curve threshold 200, curve steepness 45
  double exp_function = 1 / (1 + exp(-exp_x));
  int new_pwm = motors_pwm * (1 - exp_function);
  return new_pwm;
}

void run_diff(int motors_pwm, int encoder){
  if (encoder > 500){
    l_motor.run(motors_pwm);
    r_motor.run(diff(motors_pwm, encoder));
    } else {
    r_motor.run(motors_pwm);
    l_motor.run(diff(motors_pwm, encoder));
    }
}

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(1);
  pinMode(motor_brakes, OUTPUT);
  pinMode(servo_driver_toggle, OUTPUT);
  drive_state = 0;
  delay(3000); // time for the receiver and remote to properly start without giving crazy numbers
}

void readChannels(){
  ch9_switch_lock = receiver.readChannelRaw(9);
  ch8_tri_switch = receiver.readChannelRaw(8); // the values are: 1000, 1500, 2000
  ch3_left_vertical = receiver.readChannelMapped(2, 255, 1000, 2000, 30, 0);
  ch1_right_horizontal = receiver.readChannelMapped(0, 280, 980, 1978, 0, 0);
  ch7_diff_toggle = receiver.readChannelRaw(7);
  ch6_switch_to_toggle = receiver.readChannelRaw(6);
  encoder_pos = servo_encoder.read();
}

void loop(){
  readChannels();
  // timer
  current_time = millis();

  // Turning buffer near 0
  if (-5 < ch1_right_horizontal && ch1_right_horizontal < 5){
    ch1_right_horizontal = 0;
  }

  // ####### MOTOR LOCK ######
  if (ch9_switch_lock == 1000){
    digitalWrite(servo_driver_toggle, HIGH);
    if (motor_brake_state == 0){
      digitalWrite(motor_brakes, HIGH);
      motor_brake_state = 1;
    }
    r_motor.run(0);
    l_motor.run(0);
  // ####### REMOTE CONTROL ######
  } else if (ch9_switch_lock != 1000 && ch6_switch_to_toggle == 1000){
      digitalWrite(servo_driver_toggle, LOW);
    if (motor_brake_state == 1){
      digitalWrite(motor_brakes, LOW);
      motor_brake_state = 0;
    }

    //turning
    if (ch1_right_horizontal > 0){ // turning right
      servo.run(encoder_pos, ch1_right_horizontal, 1, 0);
    } else if(ch1_right_horizontal < 0){ // turning left
      servo.run(encoder_pos, ch1_right_horizontal, 0, 0);
    } else if(ch1_right_horizontal == 0){
      servo.returnToCenter(encoder_pos);
    }
    
    //differential and motors
    if (ch7_diff_toggle == 1000){
      run_diff(ch3_left_vertical, encoder_pos);
    } else {
      l_motor.run(ch3_left_vertical);
      r_motor.run(ch3_left_vertical);
    }
  } // end of remote control else if

  //// #### GPS command to Jetson ####
  if (ch9_switch_lock == 2000 && ch8_tri_switch == 1000){
    // normal state
      values.val = ch8_tri_switch;
      //drive_state = 0;
  }
  if (ch9_switch_lock == 2000 && ch8_tri_switch == 2000){
    // save new gps data
      values.val = ch8_tri_switch;
      //drive_state = 20;
  }

  //// ####### TELEOP ######
  if (ch6_switch_to_toggle == 2000 && ch9_switch_lock == 2000){
    if (motor_brake_state == 1){
      digitalWrite(motor_brakes, LOW);
      motor_brake_state = 0;
    }
    
    // drive via gps data
    if (ch9_switch_lock == 2000 && ch8_tri_switch == 1500){
        values.val = ch8_tri_switch;
        //drive_state = 10;
    }

    // struct serial start
    if (Serial.available() >= total_bytes) {
      i=0;
      while(i<total_bytes){
        buf[i] = Serial.read();
        i++;
      }
      //delay(5); // !!
      memmove(&bytes,buf,sizeof(bytes));
      to_motors = bytes.x;
      to_servo = bytes.y;
      to_brakes = bytes.z;
      values.val = to_brakes;

    } // struct serial end

    if (to_brakes == 1) {
      digitalWrite(motor_brakes, HIGH);
    } else {
      digitalWrite(motor_brakes, LOW);
      
      //differential and motors
      if (ch7_diff_toggle == 1000){
        run_diff(to_motors, encoder_pos);
      } else {
        l_motor.run(to_motors);
        r_motor.run(to_motors);
      } // end of diff

    } // end of brake check

    if (to_servo > 0){
      servo.run(encoder_pos, to_servo, 1, 1); // turning right
    } else if(to_servo < 0) { // turning left
      servo.run(encoder_pos, to_servo, 0, 1);
    } 
 
  } // end of teleop if
  
  if (current_time >= last_time + 50){
    last_time = millis();
    Serial.write((const uint8_t*)&values,sizeof(values));
    //values.val = to_motors; // FOR TESTING!!!
    //Serial.write((const uint8_t*)&values,sizeof(values));
  }

} // end of loop