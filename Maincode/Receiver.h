#ifndef Receiver_h
#define Receiver_h
#include "Arduino.h"

class ReceiverData {
  public:
    ReceiverData(int channel_1, int channel_2);
    double readChannel1 ();
    double readChannel2 ();
    void printValues(double ch1, double ch2);
    double channel_val;
  
  private:
    int constrainValues(int value, int minout, int maxout);
    double readChannelBase(int channel_val, int minout, int maxout);
    int _channel_1;
    int _channel_2;
};

#endif