#pragma once

#include "Arduino.h"
#include "Pin.h"

class MomentaryPushButton
{
public:
  MomentaryPushButton(const PowerPin&, const InputPin&, const GroundPin&);
  void setup();
  int read();
  bool high();
private:
  const PowerPin& p;
  const InputPin& i;
  const GroundPin& g;
};
