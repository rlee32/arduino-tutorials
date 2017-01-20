#include "Pot.h"

Pot::Pot(int vccPin, int inputPin, int gndPin, 
  int rawMin, int rawMax, int scaledMin, int scaledMax)
  : vccPin(vccPin), inputPin(inputPin), gndPin(gndPin), 
    rawMin(rawMin), rawMax(rawMax), 
    scaledMin(scaledMin), scaledMax(scaledMax) {}

void Pot::setup()
{
  pinMode(inputPin, INPUT);
  if(vccPin > -1)
  {
    pinMode(vccPin, OUTPUT);
    digitalWrite(vccPin, HIGH);
  }
  if(gndPin > -1)
  {
    pinMode(gndPin, OUTPUT);
    digitalWrite(gndPin, LOW);
  }
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