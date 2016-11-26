#include "LoadCell.h"

//LoadCell loadCell(A3, -1, 0.00001010916, -1); // 10 kg primary sensor
//LoadCell loadCell(A3, -1, 0.00000998086, -1); // 10 kg secondary sensor
LoadCell loadCell(5, -1, 1.6e-5, -1); // 30 kg

void setup()
{
  Serial.begin(9600);
  loadCell.setup();
}

void loop()
{
  loadCell.getLoad();
}
