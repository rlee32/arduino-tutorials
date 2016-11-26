#pragma once

/**
 * \author Robert Lee
 * \email rlee32@gatech.edu
 *
 * You must install the HX711 library first. 
 * It can be easily installed from the Arduino IDE via 
 *  'Sketch' > 'Include Library' > 'Manage Libraries...' 
 *  and searching for the HX711 library. 
 * After installation, the appropriate header can be added via 
 *  the 'Include Library...' popout menu. 
 * 
 * Usage:
 *  In 'global' / 'translation unit' space:
 *    // Example arguments. Can also use different constructors.
 *    // Set calibration constant to 1 for raw readings when calibrating.
 *    LoadCell loadCell(11, 7, 0.002);
 *  In setup:
 *    loadCell.configure(); // assumes Serial.begin() has been called.
 *  In loop:
 *    // Don't need to store return values, but can if you want.
 *    double loadValue = loadCell.getLoad(); // also prints
 *    double tareValue = loadCell.checkTare(); // also prints
**/
#include <Arduino.h>
#include <Q2HX711.h>

class LoadCell
{
public:
  // This ctor assumes load cell pins are adjacent in this order: 
  //   VCC, DAT, CLK, Ground (GND)
  //   This order matches the SparkFun breakout board for load cells:
  //    https://www.sparkfun.com/products/13879
  LoadCell(int vccPin, int tarePin, double calibrationConstant, 
    int checkPin);
  // This ctor gives options for power-on delay and printing.
  LoadCell(int vccPin, int tarePin, double calibrationConstant, 
    int powerOnDelay, bool print, int checkPin);
  // This ctor is available if you want to manually specify pins.
  LoadCell(int vccPin, int datPin, int clkPin, int gndPin,
    int tarePin, double calibrationConstant, int checkPin); 

  // This should be called in setup(). 
  // Assumes that Serial.begin has already been called.
  // Open to modify to your needs/taste.
  void setup();

  // This averages and prints out the measured load.
  // Also returns the measured load value.
  double getLoad();

  // This checks if tare button is pressed and resets 
  //   the current reading to zero if pressed.
  // Also returns the tare value.
  int checkTare();

  void setTareAveraging(int count) { averaging.tare = count; }
  void setLoadAveraging(int count) { averaging.load = count; }
private:
  struct Pins
  {
    int vcc = 11;
    int dat = 10;
    int clk = 9;
    int gnd = 8;
    int tare = 7;
  } pins;
  Q2HX711 loadCell = Q2HX711(pins.dat, pins.clk);
  struct State
  {
    // This is the value that tare subtracts to zero-out the reading.
    double offset = 0;
    int actualReadings = 0;
  } state;
  // Defines the number of readings to average for the output. 
  struct Averaging
  {
    int tare = 50;
    int load = 10;
  } averaging;
  struct Initial
  {
    // This is particular to every load cell 
    //  and must be found empirically.
    double calibrationConstant = 0.00000998086;
    // Milliseconds to wait before doing first tare.
    int powerOnDelay = 2000;
    bool print = true;
    double printTol = 1e-2;
    int checkPin = -1; // if > -1, only continue averaging if HIGH.
  } initial;

  double average(int readings);
  double load(int readings);
  double readyRead();
  void startupDelay();
  int tare();
  int checkContinue();
};
