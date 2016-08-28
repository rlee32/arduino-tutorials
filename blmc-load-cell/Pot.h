#pragma once

#include "Arduino.h"

class Pot
{
public:
  Pot(int inputPin, int rawMin, int rawMax, int scaledMin, int scaledMax);
  void setup();
  int readRaw();
  int readScaled();
private:
  int inputPin = -1;
  int rawMin = 23;
  int rawMax = 1000;
  int scaledMin = 0;
  int scaledMax = 1023;
};
