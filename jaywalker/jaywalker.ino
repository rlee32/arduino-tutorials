#include "Pin.h"
#include "Pot.h"
#include "RgbLed.h"
#include "Esc.h"
#include "MomentaryPushButton.h"

constexpr int Levels = 40; // basically, potentiometer resolution.
constexpr double FrontScale = 1;
constexpr double BackScale = 1;
constexpr bool Debug = true;

// front motors
const auto fescg = GroundPin(13);
const auto fescp = PowerPin(12);
const auto fesco = OutputPin(11);

// back motors
const auto bescg = GroundPin(8);
const auto bescp = PowerPin(9);
const auto besco = OutputPin(10);

// led
const auto ledp = PowerPin(7);
const auto ledr = OutputPin(6);
const auto ledg = OutputPin(4);
const auto ledb = OutputPin(5);

// potentiometer
const auto poti = InputPin(A0);
const auto potp = PowerPin(A1);
const auto potg = GroundPin(A2);

// trigger
const auto momg = GroundPin(A3);
const auto momp = PowerPin(A4);
const auto momi = InputPin(A5);

Esc<Levels> fesc(fescp, fesco, fescg, 1000, 2000);
Esc<Levels> besc(bescp, besco, bescg, 1000, 2000);
Pot pot(potp, poti, potg, 23, 1000, 0, Levels - 1);
MomentaryPushButton safety(momp, momi, momg);
RgbLed led(ledp, ledr, ledg, ledb);

void setup()
{
  fesc.setup();
  besc.setup();
  pot.setup();
  safety.setup();
  led.setup();
  if (Debug)
  {
    Serial.begin(9600);
  }
}

void fireLight(const int level)
{
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

void fire(const int scaledPotSignal)
{
  const int flevel = fesc.throttle(FrontScale * scaledPotSignal);
  const int blevel = besc.throttle(BackScale * scaledPotSignal);
  fireLight(flevel);
  if (Debug)
  {
    Serial.print("Front, back levels: ");
    Serial.print(flevel);
    Serial.print(", ");
    Serial.println(blevel);
  }
}

void off()
{
  fesc.off();
  besc.off();
  led.red();
}

void loop()
{
  if(safety.read())
  {
    fire(pot.readScaled());
  }
  else
  {
    off();
  }
}



