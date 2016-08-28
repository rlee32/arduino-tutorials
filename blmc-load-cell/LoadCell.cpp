#include "LoadCell.h"

LoadCell::LoadCell(int vccPin, int tarePin, double calibrationConstant)
{
  // Just to be clear
  pins.vcc  = vccPin;
  pins.dat  = vccPin-1;
  pins.clk  = vccPin-2;
  pins.gnd  = vccPin-3;
  pins.tare = tarePin;
  initial.calibrationConstant = calibrationConstant;
  initial.powerOnDelay = 1000;
  initial.print = true;
  loadCell = Q2HX711(pins.dat, pins.clk);
}

LoadCell::LoadCell(int vccPin, int tarePin, double calibrationConstant,
  int powerOnDelay, bool print)
{
  // Just to be clear
  pins.vcc  = vccPin;
  pins.dat  = vccPin-1;
  pins.clk  = vccPin-2;
  pins.gnd  = vccPin-3;
  pins.tare = tarePin;
  initial.calibrationConstant = calibrationConstant;
  initial.powerOnDelay = powerOnDelay;
  initial.print = print;
  loadCell = Q2HX711(pins.dat, pins.clk);
}

LoadCell::LoadCell(int vccPin, int datPin, int clkPin, int gndPin,
    int tarePin, double calibrationConstant)
{
  // Just to be clear
  pins.vcc  = vccPin;
  pins.dat  = datPin;
  pins.clk  = clkPin;
  pins.gnd  = gndPin;
  pins.tare = tarePin;
  initial.calibrationConstant = calibrationConstant;
  initial.powerOnDelay = 1000;
  initial.print = true;
  loadCell = Q2HX711(pins.dat, pins.clk);
}

void LoadCell::setup()
{
  pinMode(pins.vcc, OUTPUT);
  pinMode(pins.gnd, OUTPUT);
  pinMode(pins.tare, INPUT);
  digitalWrite(pins.vcc, HIGH);
  digitalWrite(pins.gnd, LOW);
  startupDelay();
  tare();
}
double LoadCell::getLoad()
{
  if(initial.print) Serial.print("Reading: ");
  double measurement = load(averaging.load);
  if(initial.print) Serial.print(measurement);
  if(initial.print) Serial.println(" lbs");
  return measurement;
}
int LoadCell::checkTare()
{
  int measurement = 0;
  if( digitalRead(pins.tare) ) measurement = tare();
  return measurement;
}

double LoadCell::average(int readings)
{
  double sum = 0;
  int i = 0;
  while(i < readings)
  {
    sum += readyRead();
    ++i;
  }
  return sum / readings;
}
double LoadCell::load(int readings)
{
  return (average(readings) - state.offset)*initial.calibrationConstant;
}
double LoadCell::readyRead()
{
  while(not loadCell.readyToSend());
  return loadCell.read();
}
void LoadCell::startupDelay()
{
  // Put a delay after setting VCC and GND pins 
  //  (powering on the load cell amplifier),
  //  so that readings are accurate.
  if(initial.print) Serial.print("Startup noise delay... ");
  delay(initial.powerOnDelay);
  if(initial.print) Serial.println("Done.");  
}
int LoadCell::tare()
{
  if(initial.print) Serial.print("Acquiring tare value... ");
  state.offset = average(averaging.tare);
  if(initial.print) Serial.println("Done.");
  return state.offset;
}