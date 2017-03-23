#pragma once

#include "Arduino.h"
#include "Pin.h"
#include <Servo.h> // ESC uses same signals as Servo

template<int Levels>
class Esc
{
public:
  Esc(const PowerPin&, const OutputPin&, const GroundPin&, int minWidth, int maxWidth);
  void setup();
  int throttle(int level);
  void off();
  int width(int level) { return widths[level]; }
private:
  const PowerPin& vcc;
  const OutputPin& out;
  const GroundPin& gnd;
  Servo pwmDevice;
  int widths[Levels] = {};
  int minWidth = 0; // microseconds
  int maxWidth = 0; // microseconds
};

template<int Levels>
Esc<Levels>::Esc(const PowerPin& vcc, const OutputPin& out, const GroundPin& gnd, 
  int minWidth, int maxWidth)
  : vcc(vcc), out(out), gnd(gnd), minWidth(minWidth), maxWidth(maxWidth)
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
  pwmDevice.attach(out.pin);
  gnd.setup();
  vcc.setup();
}

template<int Levels>
int Esc<Levels>::throttle(int level)
{
  level = constrain(level, 0, Levels-1);
  pwmDevice.writeMicroseconds(widths[level]);
//  Serial.println(widths[level]);
  return level;
}

template<int Levels>
void Esc<Levels>::off()
{
  pwmDevice.writeMicroseconds(minWidth);
}
