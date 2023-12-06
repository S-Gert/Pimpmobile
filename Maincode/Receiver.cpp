#include "Receiver.h"
#include "Arduino.h"
#include <IBusBM.h>

IBusBM ibus; // Creates Ibus object

// Ibus RX1-19
ReceiverData::ReceiverData() {
  ibus.begin(Serial1);
}

long ReceiverData::readChannelMapped(byte channel_input, int minmax_limit, int min_map, int max_map,
                                     int buffer_size, int default_value) {
  uint16_t ch = ibus.readChannel(channel_input);
  long mapped_value = map(ch, min_map, max_map, (-minmax_limit), minmax_limit);
  if (mapped_value <= buffer_size && mapped_value >= (-buffer_size)){
    return 0;
  }
  return mapped_value;
}
long ReceiverData::readChannelRaw(byte channel_input){
  return ibus.readChannel(channel_input);
}