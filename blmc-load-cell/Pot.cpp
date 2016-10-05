#include "Pot.h"

Pot::Pot
(int inputPin, int rawMin, int rawMax, int scaledMin, int scaledMax)
: inputPin(inputPin), rawMin(rawMin), rawMax(rawMax), 
  scaledMin(scaledMin), scaledMax(scaledMax) {}
Pot::Pot
(int inputPin, int vccPin, int gndPin, 
  int rawMin, int rawMax, int scaledMin, int scaledMax)
  : inputPin(inputPin), vccPin(vccPin), gndPin(gndPin), 
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