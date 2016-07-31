// Author: Robert Lee
// Email: rlee32@gatech.edu

// You must install the HX711 library first. 
//  It can be easily installed from the Arduino IDE via 
//  'Sketch' > 'Include Library' > 'Manage Libraries...' 
//  and searching for the HX711 library. 
// After installation, the appropriate header can be added via 
// the 'Include Library...' popout menu. 
#include <Q2HX711.h>
// This is a wrapper class for the basic library.
// Set constants in the base class.
// #include "Sensor.h"

// Parameters.
// Proportionality constant of 
//  amplified signal value to physical value.
const static double CALIBRATION_CONSTANT = 0.00002;
// Highest pin in a 4-pin connector.
// Pins adjacent in this order: VCC,DAT,CLK,GND 
const static int VCC_PIN = 11;
const static int TARE_READINGS = 100;
const static int WEIGHT_READINGS = 100;
const static int POWER_ON_DELAY = 1000; // ms

// Derived variables.
const static int DAT_PIN = VCC_PIN-1;
const static int CLK_PIN = VCC_PIN-2;
const static int GND_PIN = VCC_PIN-3;
Q2HX711 sensor(DAT_PIN, CLK_PIN);
static double offset = 0;

void setup()
{
  pinMode(VCC_PIN,OUTPUT); // VCC
  //pinMode(DAT_PIN,INPUT); // DAT
  //pinMode(CLK_PIN,INPUT); // CLK
  pinMode(GND_PIN,OUTPUT); // GND
  digitalWrite(VCC_PIN, HIGH);
  digitalWrite(GND_PIN, LOW);
  // Put a delay after setting VCC and GND pins 
  //  (powering on the load cell amplifier),
  //  so that readings are accurate.
  Serial.begin(9600);
  Serial.println("HX711 scale demo");
  Serial.print("Startup noise delay... ");
  delay(POWER_ON_DELAY);
  Serial.println("Done.");
  tare();
}

void loop()
{
  Serial.print("Reading: ");
  Serial.print( weight(WEIGHT_READINGS) ); //scale.get_units() returns a float
  Serial.print(" lbs");
  Serial.println();
 
}

double average(double readings)
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
double weight()
{
  return (readyRead() - offset)*CALIBRATION_CONSTANT;
}
double weight(int readings)
{
  return (average(readings) - offset)*CALIBRATION_CONSTANT;
}
void tare()
{
  offset = average(TARE_READINGS);
}
double readyRead()
{
  while(not sensor.readyToSend());
  return sensor.read();
}
