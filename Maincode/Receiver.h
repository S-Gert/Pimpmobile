#ifndef Receiver_h
#define Receiver_h
#include "Arduino.h"

class ReceiverData {
  public:
    ReceiverData(int channel_1, int channel_2);
    int readChannel1 ();
    int readChannel2 ();
    void printValues(int ch1, int ch2);
  
  private:
    int constrainValues(int value, int minout, int maxout);
    int readChannelBase(int channel, int minout, int maxout);
    int _channel_1;
    int _channel_2;
};

#endif