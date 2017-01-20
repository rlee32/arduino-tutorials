#pragma once

#include "Arduino.h"

class RgbLed
{
public:
  RgbLed(int vccPin, int redPin, int greenPin, int bluePin);

  void setup();
  void set(uint8_t r, uint8_t g, uint8_t b);
  void red()    { set(OnSignal, OffSignal, OffSignal); }
  void green()  { set(OffSignal, OnSignal, OffSignal); }
  void blue()   { set(OffSignal, OffSignal, OnSignal); }
  void yellow() { set(OnSignal, OnSignal, OffSignal); }
private:
  // pin assignments
  int redPin = -1;
  int greenPin = -1;
  int bluePin = -1;
  int vccPin = -1;
  // this is determined by common anode / cathode.
  const uint8_t OnSignal = LOW;
  const uint8_t OffSignal = HIGH;
};