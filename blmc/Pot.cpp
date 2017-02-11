#include "Pot.h"

Pot::Pot(const PowerPin& p, const InputPin& i, const GroundPin& g,
  int rawMin, int rawMax, int scaledMin, int scaledMax)
  : p(p), i(i), g(g),
    rawMin(rawMin), rawMax(rawMax), 
    scaledMin(scaledMin), scaledMax(scaledMax) {}

void Pot::setup()
{
  i.setup();
  g.setup();
  p.setup();
}

int Pot::readRaw()
{
  return analogRead(i.pin);
}

int Pot::readScaled()
{
  int scaled = map(readRaw(),
    rawMin, rawMax,
    scaledMin, scaledMax);
  return constrain(scaled, scaledMin, scaledMax);
}