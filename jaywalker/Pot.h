#pragma once

#include "Arduino.h"
#include "Pin.h"

class Pot
{
public:
  Pot(const PowerPin&, const InputPin&, const GroundPin&, 
    int rawMin, int rawMax, int scaledMin, int scaledMax);
  void setup();
  int readRaw();
  int readScaled();
private:
  const PowerPin& p;
  const InputPin& i;
  const GroundPin& g;
  int rawMin = 23;
  int rawMax = 1000;
  int scaledMin = 0;
  int scaledMax = 1023;
};
