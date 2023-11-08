#include "Receiver.h"
#include "Arduino.h"

// ch1 D8, ch2 D7
ReceiverData::ReceiverData(int channel_1, int channel_2)  {
  pinMode(channel_1, INPUT);
  pinMode(channel_2, INPUT);
  _channel_1 = channel_1;
  _channel_2 = channel_2;
}

int ReceiverData::constrainValues(int value, int minout, int maxout){
  value -= 1519;
  int new_value = map(value, -507, 507, minout, maxout);
  if (new_value <= 1 && new_value >= -1){
    return 0;
  }
  return new_value;
}

int ReceiverData::readChannelBase(int channel, int minout, int maxout){
  int channel_val = 0;
  for (int j = 0;j < 5; j++){
    channel_val += pulseIn(channel, HIGH);
  }
      channel_val /= 5;
      return constrainValues(channel_val, minout, maxout);
}

int ReceiverData::readChannel1() {
  return readChannelBase(_channel_1, -256, 256);
}

int ReceiverData::readChannel2() {
  int rec_out = readChannelBase(_channel_2, -5, 5);
  if (rec_out == 0) { // Create buffer between -1 and +1 where value remains 0 by removing 1 from either end of value
    return rec_out;
  } else if (rec_out > 0) {
    return (rec_out-1);
  } else {
    return (rec_out+1);
  }
}

void ReceiverData::printValues(int ch1, int ch2){
  Serial.println("  ");
  Serial.print("Channel 1= ");
  Serial.print(int(ch1));
  Serial.print(" Channel 2= ");
  Serial.println(int(ch2));
}