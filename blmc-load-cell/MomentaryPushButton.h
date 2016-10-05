#pragma once

#include "Arduino.h"

class MomentaryPushButton
{
public:
  MomentaryPushButton(int inputPin);
  // For the case where there is a pull down/up resistor between the ground/vcc and input.
  MomentaryPushButton(int inputPin, int vccPin, int groundPin);
  void setup();
  int read();
private:
  int inputPin = -1;
  int vccPin = -1;
  int groundPin = -1;
};