#include "Pot.h"
#include "RgbLed.h"
#include "Esc.h"
#include "MomentaryPushButton.h"

const int Levels = 20;
Esc<Levels> esc(10, 9, 11, 1000, 2000);
Pot pot(A1, A0, A2, 23, 1000, 0, Levels - 1);
MomentaryPushButton safety(A4, A5, A3);
RgbLed led(4, 5, 7, 6);

void setup()
{
  esc.setup();
  pot.setup();
  safety.setup();
  led.setup();
  Serial.begin(9600);
}

void loop()
{
  if(safety.read())
  {
    const int level = esc.throttle(pot.readScaled());
//    Serial.println(level);
    switch(level)
    {
      case 0:
        led.yellow();
        break;
      case Levels - 1:
        led.blue();
        break;
      default:
        led.green();
        break;
    }
  }
  else
  {
    esc.off();
    led.red();
  }
}



