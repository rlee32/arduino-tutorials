#pragma once

#include "Arduino.h"
#include <Servo.h> // ESC uses same signals as Servo

template<int Levels>
class Esc
{
public:
  Esc(int vccPin, int signalPin, int gndPin, 
    int minWidth, int maxWidth);
  void setup();
  int throttle(int level);
  void off();
  int width(int level) { return widths[level]; }
private:
  int vccPin = -1;
  int signalPin = -1;
  int gndPin = -1;
  Servo pwmDevice;
  int widths[Levels] = {};
  int minWidth = 0; // microseconds
  int maxWidth = 0; // microseconds
};

template<int Levels>
Esc<Levels>::Esc(int vccPin, int signalPin, int gndPin, 
  int minWidth, int maxWidth)
: vccPin(vccPin), signalPin(signalPin), gndPin(gndPin), 
  minWidth(minWidth), maxWidth(maxWidth)
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
void Esc<Levels>::setup()
{
  if(signalPin > -1) pwmDevice.attach(signalPin);
  // simulate vcc
  if(vccPin > -1)
  {
    pinMode(vccPin, OUTPUT);
    digitalWrite(vccPin, HIGH);
  }
  // simulate ground
  if(gndPin > -1)
  {
    pinMode(gndPin, OUTPUT);
    digitalWrite(gndPin, LOW);
  }
}

template<int Levels>
int Esc<Levels>::throttle(int level)
{
  level = constrain(level, 0, Levels-1);
  pwmDevice.writeMicroseconds(widths[level]);
  return level;
}

template<int Levels>
void Esc<Levels>::off()
{
  pwmDevice.writeMicroseconds(minWidth);
}
