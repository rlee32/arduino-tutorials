#include "LoadCell.h"

LoadCell::LoadCell(int vccPin, int tarePin, double calibrationConstant, 
  int checkPin)
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
  initial.checkPin = checkPin;
  loadCell = Q2HX711(pins.dat, pins.clk);
}

LoadCell::LoadCell(int vccPin, int tarePin, double calibrationConstant,
  int powerOnDelay, bool print, int checkPin)
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
  initial.checkPin = checkPin;
  loadCell = Q2HX711(pins.dat, pins.clk);
}

LoadCell::LoadCell(int vccPin, int datPin, int clkPin, int gndPin,
  int tarePin, double calibrationConstant, int checkPin)
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
  initial.checkPin = checkPin;
  loadCell = Q2HX711(pins.dat, pins.clk);
}

void LoadCell::setup()
{
  pinMode(pins.vcc, OUTPUT);
  pinMode(pins.gnd, OUTPUT);
  if(pins.tare > -1) pinMode(pins.tare, INPUT);
  digitalWrite(pins.vcc, HIGH);
  digitalWrite(pins.gnd, LOW);
  startupDelay();
  tare();
}

double LoadCell::getLoad()
{
  if(not checkContinue()) return 0;
  int actualReadings = averaging.load;
  double measurement = load(averaging.load);
  bool print = initial.print and abs(measurement) > initial.printTol;
  if(print)
  {
    Serial.print("Reading (average of ");
    Serial.print(state.actualReadings);
    Serial.print("): ");
    Serial.print(measurement);
    Serial.println(" lbs");
  }
  return measurement;
}
int LoadCell::checkTare()
{
  int measurement = 0;
  if(pins.tare > -1)
  {
    if( digitalRead(pins.tare) ) measurement = tare();
  }
  return measurement;
}
int LoadCell::checkContinue()
{
  int ret = (initial.checkPin < 0)
    ? true : digitalRead(initial.checkPin);
  return ret;
}
double LoadCell::average(int readings)
{
  double sum = 0;
  int i = 0;
  while(i < readings and checkContinue())
  {
    sum += readyRead();
    ++i;
  }
  state.actualReadings = i;
  return (i == 0) ? 0 : sum / i;
}
double LoadCell::load(int readings)
{
  double averageReading = average(readings);
  return (averageReading - state.offset)*initial.calibrationConstant;
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
  int originalCheckPin = initial.checkPin;
  initial.checkPin = -1;
  state.offset = average(averaging.tare);
  initial.checkPin = originalCheckPin;
  if(initial.print) Serial.println("Done.");
  return state.offset;
}
