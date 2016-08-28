#pragma once

#include "Arduino.h"
#include <Servo.h> // Motor uses same signals as Servo

template<int Levels>
class Motor
{
public:
  Motor(int outputPin, int minWidth, int maxWidth);
  void setup();
  int throttle(int level);
  void off();
private:
  Servo pwmDevice;
  int outputPin = -1;
  int widths[Levels] = {};
  int minWidth = 0; // microseconds
  int maxWidth = 0; // microseconds
};

template<int Levels>
Motor<Levels>::Motor(int outputPin, int minWidth, int maxWidth)
: outputPin(outputPin), minWidth(minWidth), maxWidth(maxWidth)
{
  // Initialize pulse width discretization.
  int increment = (maxWidth - minWidth) / (Levels - 1);
  for(int i = 0; i < Levels; ++i)
  {
    widths[i] = minWidth + i * increment;
  }
  widths[0] = minWidth;
  widths[Levels-1] = maxWidth;
}

template<int Levels>
void Motor<Levels>::setup()
{
  pwmDevice.attach(outputPin);
}

template<int Levels>
int Motor<Levels>::throttle(int level)
{
  level = constrain(level, 0, Levels-1);
  pwmDevice.writeMicroseconds(widths[level]);
  return level;
}

template<int Levels>
void Motor<Levels>::off()
{
  pwmDevice.writeMicroseconds(minWidth);
}
