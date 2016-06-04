// Author: Robert Lee
// Email: rlee32@gatech.edu

// You must install the HX711 library first. It is easy.
// It can be installed from the Arduino IDE via 
// 'Sketch' > 'Manage Libraries...' and searching for the HX711 library. 
// After installation, the appropriate header can be added via 
// the 'Include Library...' popout menu. 
#include <Q2HX711.h>

// Amplified signal value to physical value
const static double CALIBRATION_CONSTANT = -7050.0;
const static int DAT_PIN = 3;
const static int CLK_PIN = 2;

Q2HX711 scale(DAT_PIN, CLK_PIN);

void setup()
{
  Serial.begin(9600);
  Serial.println("HX711 scale demo");
  Serial.println("Readings:");
}

void loop()
{
  if( scale.readyToSend() )
  {
    Serial.print("Reading: ");
    Serial.print( scale.read() ); //scale.get_units() returns a float
    Serial.print(" lbs");
    Serial.println();
  }
}


