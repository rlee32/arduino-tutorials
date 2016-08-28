#include "MomentaryPushButton.h"

MomentaryPushButton::MomentaryPushButton(int inputPin) 
: inputPin(inputPin) {}

void MomentaryPushButton::setup()
{
  pinMode(inputPin, INPUT);
}

int MomentaryPushButton::read()
{
  return digitalRead(inputPin);
}