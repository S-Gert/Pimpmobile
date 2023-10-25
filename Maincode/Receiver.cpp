#include "Receiver.h"
#include "Arduino.h"

// ch1 D8, ch2 D7
ReceiverData::ReceiverData(int channel_1, int channel_2)  {
  Serial.begin(9600);
  pinMode(channel_1, INPUT);
  pinMode(channel_2, INPUT);
  double  channel_1Val = 0;    // channel value 
  double  channel_2Val = 0;    // channel value
  _channel_1 = channel_1;
  _channel_2 = channel_2;
}

double ReceiverData::readChannels () {
  // reads 5 time to have a "good" value
  for (int j = 0;j < 6; j++){
    channel_1Val = channel_1Val + pulseIn(_channel_1, HIGH);  // reading value from receiver
    channel_2Val = channel_2Val + pulseIn(_channel_2, HIGH);  // reading value from receiver
    if (j == 5){
      channel_1Val = channel_1Val / 5;
      channel_2Val = channel_2Val / 5;
      break; // I make an average of the values because they are slightly fluctuating
    }
  }
  return channel_1Val, channel_2Val;
}
void ReceiverData::printValues(double channel_1Val, double channel_2Val){
  Serial.println("  ");
  Serial.print("Channel 1= ");
  Serial.print(int(channel_1Val));
  Serial.print(" Channel 2= ");
  Serial.println(int(channel_2Val));
}