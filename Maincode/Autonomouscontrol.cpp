#include "Autonomouscontrol.h"
#include "Arduino.h"
#include "Motorcontrol.h"
#include "Servocontrol.h"

AutoControl::AutoControl(){
  i = 0;
  byte buf[total_bytes];

  RX_motors = 0;
  RX_servo = 0;
  RX_brakes = 0;
}

void AutoControl::readSerial(){
  if (Serial.available() >= total_bytes) {
    i=0;
    while(i<total_bytes){
      buf[i] = Serial.read();
      i++;
    }
    //delay(5); // !!
    memmove(&bytes,buf,sizeof(bytes));
    RX_motors = bytes.x;
    RX_servo = bytes.y;
    RX_brakes = bytes.z;
    //values.val = to_brakes;
  } // struct serial end
}

void AutoControl::writeSerial(int write_value){
  values.TX_val = write_value;
  Serial.write((const uint8_t*)&values,sizeof(values));
  //delay(1000);
}

void AutoControl::autoServo(ServoControl servo, int encoder_pos){
  if (RX_servo > 0){ // turning right
    servo.run(encoder_pos, RX_servo, 1, 1);
  } else if(RX_servo < 0) { // turning left
    servo.run(encoder_pos, RX_servo, 0, 1);
  } 
}

void AutoControl::autoMotors(MotorControl l_motor, MotorControl r_motor, int diff_toggle, int encoder){
  if (RX_brakes == 1) {
    r_motor.activateBrakes(true);
    l_motor.activateBrakes(true);
  } else {
    r_motor.activateBrakes(false);
    l_motor.activateBrakes(false);
    
    //differential and motors
    if (diff_toggle == 1000){
      //run_diff(RX_motors, encoder_pos);
      if (encoder > 500){
        l_motor.run(RX_motors);
        r_motor.run(r_motor.diff(RX_motors, encoder));
      } else {
        r_motor.run(RX_motors);
        l_motor.run(l_motor.diff(RX_motors, encoder));
      }
    } else {
      l_motor.run(RX_motors);
      r_motor.run(RX_motors);
    } // end of diff
  } // end of brake
}