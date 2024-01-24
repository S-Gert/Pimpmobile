#ifndef Encoder_h
#define Encoder_h
#include "Arduino.h"

class EncoderData {
  public:
    EncoderData(int cs_pin, int data_pin, int clock_pin);
    int read();
  private:
    int _cs_pin;
    int _data_pin;
    int _clock_pin;
    unsigned int reading;
};

#endif