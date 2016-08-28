#include "Pot.h"
#include "RgbLed.h"
#include "Motor.h"
#include "MomentaryPushButton.h"
#include "LoadCell.h"

const int Levels = 20;
Motor<Levels> motor(6, 1000, 2000);
Pot pot(A0, 23, 1000, 0, Levels - 1);
MomentaryPushButton safety(7);
RgbLed led(9,10,11);
LoadCell loadCell(5, 12, 0.00000998086);

// RGB LED colors.
const RgbLed::Color readyColor(0,1,1);
const RgbLed::Color minColor(0,1,0);
const RgbLed::Color midColor(1,1,0);
const RgbLed::Color maxColor(1,0,1);

void setup()
{
  Serial.begin(9600);
  loadCell.setup();
  motor.setup();
  pot.setup();
  safety.setup();
  led.setup();
  // Serial.begin( 9600 );
}

void loop()
{
  if(safety.read())
  {
    switch(motor.throttle(pot.readScaled()))
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
  }
  else
  {
    motor.off();
    led.set(readyColor);
  }
  loadCell.getLoad();
}



