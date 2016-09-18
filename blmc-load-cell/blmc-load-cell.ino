#include "Pot.h"
#include "RgbLed.h"
#include "Esc.h"
#include "MomentaryPushButton.h"
#include "LoadCell.h"

const int Levels = 20;
Esc<Levels> esc(-1, 4, 2, 1000, 2500);
Pot pot(A0, 23, 1000, 0, Levels - 1);
MomentaryPushButton safety(7);
RgbLed led(9, 10, 11);
LoadCell loadCell(A5, -1, 0.00000998086, 7);

// RGB LED colors.
const RgbLed::Color readyColor(0,1,1);
const RgbLed::Color minColor(0,1,0);
const RgbLed::Color midColor(1,1,0);
const RgbLed::Color maxColor(1,0,1);

void setup()
{
  Serial.begin(9600);
  loadCell.setup();
  esc.setup();
  pot.setup();
  safety.setup();
  led.setup();
}

void loop()
{
  if(safety.read())
  {
    int level = esc.throttle(pot.readScaled());
    switch(level)
    {
      case 0:
        led.set(minColor);
        break;
      case Levels - 1:
        led.set(maxColor);
        break;
      default:
        led.set(midColor);
        break;
    }
    loadCell.getLoad();
  }
  else
  {
    esc.off();
    led.set(readyColor);
  }
}

