#include "RgbLed.h"

RgbLed::RgbLed(int vccPin, int redPin, int greenPin, int bluePin)
  : vccPin(vccPin), redPin(redPin), greenPin(greenPin), bluePin(bluePin) {}

void RgbLed::setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  if(vccPin > -1)
  {
    pinMode(vccPin, OUTPUT);
    digitalWrite(vccPin, HIGH);
  }
}

void RgbLed::set(uint8_t r, uint8_t g, uint8_t b)
{
  digitalWrite(redPin, r);
  digitalWrite(greenPin, g);
  digitalWrite(bluePin, b);
}
