#include "Pin.h"
#include "Pot.h"
#include "RgbLed.h"
#include "Esc.h"
#include "MomentaryPushButton.h"
#include "LoadCell.h"

constexpr int Levels = 20; // basically, potentiometer resolution.
// constexpr double calibrationConstant = 9.98086e-6; // 10kg secondary sensor
constexpr double calibrationConstant = 1.6e-5; // 30kg

const auto cellg = GroundPin(2);
const auto cellc = OutputPin(3);
const auto celld = OutputPin(4);
const auto cellp = PowerPin(5);

const auto escg = GroundPin(6);
const auto escp = PowerPin(7);
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

LoadCell loadCell(cellp, celld, cellc, cellg, calibrationConstant);
Esc<Levels> esc(escp, esco, escg, 1000, 2000);
RgbLed led(ledp, ledr, ledg, ledb);
Pot pot(potp, poti, potg, 23, 1000, 0, Levels - 1);
MomentaryPushButton safety(momp, momi, momg);

void setup()
{
  Serial.begin(9600);
  loadCell.setCheckPin(momi);
  loadCell.setup();
  esc.setup();
  led.setup();
  pot.setup();
  safety.setup();
}

void loop()
{
  if(safety.read())
  {
    int level = esc.throttle(pot.readScaled());
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
    loadCell.getLoad();
  }
  else
  {
    esc.off();
    led.red();
  }
}

