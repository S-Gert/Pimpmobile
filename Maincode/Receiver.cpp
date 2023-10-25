#include "Receiver.h"
#include "Arduino.h"

// ch1 D8, ch2 D7
ReceiverData::ReceiverData(int channel_1, int channel_2)  {
  Serial.begin(9600);
  pinMode(channel_1, INPUT);
  pinMode(channel_2, INPUT);
  double channel_val = 0;
  _channel_1 = channel_1;
  _channel_2 = channel_2;
}

int ReceiverData::constrainValues(int value, int minout, int maxout){
  value -= 1826;
  int newValue = map(value, -610, 610, minout, maxout);
  if (newValue < 6 && newValue > -6){
    return 0;
  }
  return newValue;
}

double ReceiverData::readChannelBase(int channel, int minout, int maxout){
  channel_val = 0;
  for (int j = 0;j < 6; j++){
    channel_val = channel_val + pulseIn(channel, HIGH);
    if (j == 5){
      channel_val = channel_val / 5;
      double output_val = constrainValues(channel_val, minout, maxout);
      return output_val;
    }
  }
}

double ReceiverData::readChannel1 () {
  return readChannelBase(_channel_1, -256, 256);
}
double ReceiverData::readChannel2() {
  return readChannelBase(_channel_2, -300, 300);
}

void ReceiverData::printValues(double ch1, double ch2){
  Serial.println("  ");
  Serial.print("Channel 1= ");
  Serial.print(int(ch1));
  Serial.print(" Channel 2= ");
  Serial.println(int(ch2));
}