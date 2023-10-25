#ifndef Receiver_h
#define Receiver_h
#include "Arduino.h"

class ReceiverData {
  public:
    ReceiverData(int channel_1, int channel_2);
    double readChannels ();
    void printValues(double channel_1Val, double channel_2Val);
    double  channel_1Val = 0;
    double  channel_2Val = 0; 
  
  private:
    int _channel_1;
    int _channel_2;
};

#endif