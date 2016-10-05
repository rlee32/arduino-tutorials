#pragma once

#include "Arduino.h"

class RgbLed
{
public:
  // assumes the green pin is redPin + 1 and the blue pin is redPin + 2.
  RgbLed(int redPin);
  RgbLed(int redPin, int vccPin);
  RgbLed(int redPin, int greenPin, int bluePin);
  RgbLed(int redPin, int greenPin, int bluePin, int vccPin);

  struct Color
  {
    Color(int r_, int g_, int b_) : r(r_), g(g_), b(b_) {}
    int r = 0;
    int g = 0;
    int b = 0;
  };

  void setup();
  void set(Color color);
private:
  // pin assignments
  int redPin = -1;
  int greenPin = -1;
  int bluePin = -1;
  int vccPin = -1;
};