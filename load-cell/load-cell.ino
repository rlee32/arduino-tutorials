/**
 * \author Robert Lee
 * \email rlee32@gatech.edu
 *
 * You must install the HX711 library first. 
 * It can be easily installed from the Arduino IDE via 
 *   'Sketch' > 'Include Library' > 'Manage Libraries...' 
 *   and searching for the HX711 library. 
 * After installation, the appropriate header can be added via 
 *   the 'Include Library...' popout menu.
**/
#include "LoadCell.h" // Look inside for usage details if needed.

const static int VCC_PIN = 11;
const static int TARE_PIN = 7;
const static double CALIBRATION_CONSTANT = 0.00000998086; // 0.00001012577;
LoadCell loadCell(VCC_PIN, TARE_PIN, CALIBRATION_CONSTANT);

void setup()
{
  Serial.begin(9600);
  loadCell.configure();
}

void loop()
{
  loadCell.getLoad();
  // loadCell.checkTare();
}


