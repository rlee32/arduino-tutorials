#pragma once

#include "Arduino.h"

class MomentaryPushButton
{
public:
  // For externally-supplied voltage.
  MomentaryPushButton(int inputPin);
  // For Arduino-supplied voltage.
  MomentaryPushButton(int vccPin, int inputPin, int groundPin);
  void setup();
  int read();
private:
  int inputPin = -1;
  int vccPin = -1;
  int groundPin = -1;
};