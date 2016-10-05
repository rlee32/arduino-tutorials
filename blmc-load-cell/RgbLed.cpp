#include "RgbLed.h"

RgbLed::RgbLed(int redPin)
  : redPin(redPin), greenPin(redPin+1), bluePin(redPin+2) {}
RgbLed::RgbLed(int redPin, int vccPin)
  : redPin(redPin), greenPin(redPin+1), bluePin(redPin+2), vccPin(vccPin) {}
RgbLed::RgbLed(int redPin, int greenPin, int bluePin)
  : redPin(redPin), greenPin(greenPin), bluePin(bluePin) {}
RgbLed::RgbLed(int redPin, int greenPin, int bluePin, int vccPin)
  : redPin(redPin), greenPin(greenPin), bluePin(bluePin), vccPin(vccPin) {}

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

void RgbLed::set(Color color)
{
  digitalWrite(redPin, color.r);
  digitalWrite(greenPin, color.g);
  digitalWrite(bluePin, color.b);
}
