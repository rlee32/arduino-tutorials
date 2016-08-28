#pragma once

#include "Arduino.h"

class MomentaryPushButton
{
public:
  MomentaryPushButton(int inputPin);
  void setup();
  int read();
private:
  int inputPin = -1;
};