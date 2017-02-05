#include "LoadCell.h"

LoadCell::LoadCell(const PowerPin& p, const OutputPin& dat,
  const OutputPin& clk, const GroundPin& g,
  double calibrationConstant, bool print, int powerOnDelay)
  : p(p), dat(dat), clk(clk), g(g)
{
  initial.calibrationConstant = calibrationConstant;
  initial.powerOnDelay = powerOnDelay;
  initial.print = print;
  loadCell = Q2HX711(dat.pin, clk.pin);
}

void LoadCell::setup()
{
  p.setup();
  g.setup();
  if(tare != nullptr)
  {
    tare->setup();
  }
  if(check != nullptr)
  {
    check->setup();
  }
  startupDelay();
  getTareValue();
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
  if(tare != nullptr)
  {
    if(digitalRead(tare->pin))
    {
      getTareValue();
      measurement = state.offset;
    }
  }
  return measurement;
}
int LoadCell::checkContinue()
{
  int ret = (check == nullptr) ? true : digitalRead(check->pin);
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
  if(initial.print) { Serial.print("Startup noise delay... "); }
  delay(initial.powerOnDelay);
  if(initial.print) { Serial.println("Done."); }  
}
void LoadCell::getTareValue()
{
  if(initial.print) { Serial.print("Acquiring tare value... "); }
  const InputPin* originalCheck = check;
  check = nullptr;
  state.offset = average(averaging.tare);
  check = originalCheck;
  if(initial.print) { Serial.println("Done."); }
}
