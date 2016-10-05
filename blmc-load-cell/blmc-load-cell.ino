#include "Pot.h"
#include "RgbLed.h"
#include "Esc.h"
#include "MomentaryPushButton.h"
#include "LoadCell.h"

const int Levels = 20;
const int checkPin = A5;

Esc<Levels> esc(-1, 9, 7, 1000, 2000); // pins 7, 9
Pot pot(A0, A1, A2, 23, 1000, 0, Levels - 1); // pins A0, A1, A2
MomentaryPushButton safety(checkPin, A4, A3); // pins A3, A4, A5
RgbLed led(11, 10); // pins 10, 11, 12, 13
LoadCell loadCell(5, -1, 0.00000998086, checkPin); // pins 2, 3, 4, 5

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

