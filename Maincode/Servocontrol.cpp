#include "Arduino.h"
#include "Servocontrol.h"

//pins analog D6, digital D3
ServoControl::ServoControl(int analog_pin, int digital_pin){
  Serial.begin(9600);
  pinMode(analog_pin, OUTPUT);
  pinMode(digital_pin, OUTPUT);
  _analog_pin = analog_pin;
  _digital_pin = digital_pin;
  _prev_step_count = 0;
  _prev_receiver_data = 0;
  _position = 0;
  _pulse = 400;

  // teleop variables

  _current_steps = 0;
}

int ServoControl::getStepsForDesiredDeg(double desired_angle) {
  double steps_max = _pulse * 50; // steps_max = pulse * gearbox ratio
  return steps_max / 360 * desired_angle;
}

double ServoControl::calculateSteps(int receiver_data, int max_received_value, double desired_angle) {
  int steps_for_desired_deg = getStepsForDesiredDeg(desired_angle);
  double steps_per_degree = steps_for_desired_deg / desired_angle; //13.888888
  double steps_per_receiver_data = max_received_value / desired_angle;  //22.222222
  double steps = (abs(receiver_data) / steps_per_receiver_data) * steps_per_degree; // steps needed for x degree turn
  return steps;
}

void ServoControl::moveDegree(double steps){
  for (int i; i < int(steps); i++){
    digitalWrite(_analog_pin, HIGH);
    delayMicroseconds(100);
    digitalWrite(_analog_pin, LOW);
    delayMicroseconds(100);
  }
}

void ServoControl::turn(double step_count, bool direction) {
  if (step_count > _prev_step_count) {
    digitalWrite(_digital_pin, direction);
    moveDegree(step_count - _prev_step_count);
  } else {
    digitalWrite(_digital_pin, !direction);
    moveDegree(_prev_step_count - step_count);
  }
}

void ServoControl::runSimple(int delay, bool direction){
  if (direction == 1){
    digitalWrite(_digital_pin, HIGH);
  } else if (direction == 0) {
    digitalWrite(_digital_pin, LOW);
  }
  digitalWrite(_analog_pin, HIGH);
  delayMicroseconds(delay);
  digitalWrite(_analog_pin, LOW);
  delayMicroseconds(delay);
}

void ServoControl::returnToCenter(int delay){
  if(_current_steps > 0){
    for (int i; i < int(abs(_current_steps)); i++){
      runSimple(delay, 0);
    }// end of for loop
  } else if (_current_steps < 0){
    for (int i; i < int(abs(_current_steps)); i++){
      runSimple(delay, 1);
    }//end of for loop
  }// end of if
  _current_steps = 0;
}
void ServoControl::runTeleOp(int delay, bool direction, int max_angle_steps){
  if (abs(_current_steps) < max_angle_steps){
    if (direction == 1){
      _current_steps += 100;
    } else if (direction == 0){
      _current_steps -= 100;
    }
    for (int i; i < 100; i++){
      runSimple(delay, direction);
    }
    // Serial.print(_current_steps);
    // Serial.print('\n');
  } else {
    return;
  }
}

void ServoControl::run(int receiver_data, double desired_angle){
  double step_count = calculateSteps(receiver_data, 4, desired_angle);
  if (receiver_data >= 0 && _prev_receiver_data >= 0){ 
    turn(step_count, 1);
  } else { 
    turn(step_count, 0);
  }
  _prev_step_count = step_count;
  _prev_receiver_data = receiver_data;
}