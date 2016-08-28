#include "Pot.h"

Pot::Pot
(int inputPin, int rawMin, int rawMax, int scaledMin, int scaledMax)
: inputPin(inputPin), rawMin(rawMin), rawMax(rawMax), 
  scaledMin(scaledMin), scaledMax(scaledMax) {}

void Pot::setup()
{
  pinMode(inputPin, INPUT);
}

int Pot::readRaw()
{
  return analogRead( inputPin );
}

int Pot::readScaled()
{
  int scaled = map( readRaw(),
    rawMin, rawMax,
    scaledMin, scaledMax );
  return constrain( scaled, scaledMin, scaledMax );
}