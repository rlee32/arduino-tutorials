#pragma once

#include "Arduino.h"
#include "Pin.h"

class RgbLed
{
public:
  RgbLed(const PowerPin& p, const OutputPin& r, const OutputPin& g, const OutputPin& b)
    : p(p), r(r), g(g), b(b) {}
  void setup();
  using SignalType = decltype(LOW);
  void set(SignalType rs, SignalType gs, SignalType bs);
  void red()    { set(OnSignal, OffSignal, OffSignal); }
  void green()  { set(OffSignal, OnSignal, OffSignal); }
  void blue()   { set(OffSignal, OffSignal, OnSignal); }
  void yellow() { set(OnSignal, OnSignal, OffSignal); }
private:
  // pin assignments
  const PowerPin& p;
  const OutputPin& r;
  const OutputPin& g;
  const OutputPin& b;
  // this is determined by common anode / cathode.
  const SignalType OnSignal = LOW;
  const SignalType OffSignal = HIGH;
};