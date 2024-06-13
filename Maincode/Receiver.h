#ifndef Receiver_h
#define Receiver_h
#include "Arduino.h"

class ReceiverData {
  public:
    ReceiverData();
    long readChannelMapped(byte channel_input, int minmax_limit, int min_map, int max_map, int buffer_size); 
    long readChannelRaw(byte channel_input);
  private:
    
};

#endif