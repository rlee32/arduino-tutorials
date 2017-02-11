#include "Pin.h"
#include "Pot.h"
#include "RgbLed.h"
#include "Esc.h"
#include "MomentaryPushButton.h"

constexpr int Levels = 20; // basically, potentiometer resolution.

const auto escg = GroundPin(11);
const auto escp = PowerPin(10);
const auto esco = OutputPin(9);

const auto ledp = PowerPin(10);
const auto ledr = OutputPin(11);
const auto ledg = OutputPin(13);
const auto ledb = OutputPin(12);

const auto poti = InputPin(A0);
const auto potp = PowerPin(A1);
const auto potg = GroundPin(A2);

const auto momg = GroundPin(A3);
const auto momp = PowerPin(A4);
const auto momi = InputPin(A5);

Esc<Levels> esc(escp, esco, escg, 1000, 2000);
Pot pot(potp, poti, potg, 23, 1000, 0, Levels - 1);
MomentaryPushButton safety(momp, momi, momg);
RgbLed led(ledp, ledr, ledg, ledb);

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



