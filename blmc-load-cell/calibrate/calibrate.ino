#include "LoadCell.h"

LoadCell loadCell(A5, -1, 0.00001010916, -1);
// LoadCell loadCell(A5, -1, 0.00000998086, -1);

void setup()
{
  Serial.begin(9600);
  loadCell.setup();
}

void loop()
{
  loadCell.getLoad();
}
