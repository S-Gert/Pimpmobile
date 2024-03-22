#include "Encoder.h"
#include "Arduino.h"

EncoderData::EncoderData(int cs_pin, int data_pin, int clock_pin){
  Serial.begin(9600);
  pinMode(cs_pin, OUTPUT);
  pinMode(data_pin, INPUT);
  pinMode(clock_pin, OUTPUT);
  _cs_pin = cs_pin;
  _data_pin = data_pin;
  _clock_pin = clock_pin;
  unsigned int reading = 0;
}

int EncoderData::read(){
  reading = 0;
  // Pull CS low to select the encoder
  digitalWrite(_cs_pin, LOW);
  // Read 12 bits from the encoder
  for (int i = 0; i < 12; i++) {
    // Toggle the clock
    digitalWrite(_clock_pin, HIGH);
    delayMicroseconds(1); // Short delay for clock pulse
    digitalWrite(_clock_pin, LOW);
    // Read a bit of data
    reading <<= 1;
    if (digitalRead(_data_pin)) {
      reading |= 1;
    }
    delayMicroseconds(1);
  }
  // Pull CS high to deselect the encoder
  digitalWrite(_cs_pin, HIGH);
  return map(reading, 0, 4095, 0, 1000);
}