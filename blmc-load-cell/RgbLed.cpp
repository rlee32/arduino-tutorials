#include "RgbLed.h"

RgbLed::RgbLed(int redPin)
: redPin(redPin), greenPin(redPin+1), bluePin(redPin+2) {}
RgbLed::RgbLed(int redPin, int greenPin, int bluePin)
: redPin(redPin), greenPin(greenPin), bluePin(bluePin) {}

void RgbLed::setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void RgbLed::set(Color color)
{
  digitalWrite(redPin, color.r);
  digitalWrite(greenPin, color.g);
  digitalWrite(bluePin, color.b);
}
