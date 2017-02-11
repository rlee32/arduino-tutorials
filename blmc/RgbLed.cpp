#include "RgbLed.h"

void RgbLed::setup()
{
  r.setup();
  g.setup();
  b.setup();
  p.setup();
}

void RgbLed::set(SignalType rs, SignalType gs, SignalType bs)
{
  digitalWrite(r.pin, rs);
  digitalWrite(g.pin, gs);
  digitalWrite(b.pin, bs);
}
