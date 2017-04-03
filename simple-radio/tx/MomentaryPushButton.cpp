#include "MomentaryPushButton.h"

MomentaryPushButton::MomentaryPushButton(
    const PowerPin& p, const InputPin& i, const GroundPin& g)
    : p(p), i(i), g(g) {}

void MomentaryPushButton::setup()
{
    i.setup();
    g.setup();
    p.setup();
}

int MomentaryPushButton::read()
{
    return digitalRead(i.pin); 
}

bool MomentaryPushButton::high()
{
    return digitalRead(i.pin) == HIGH; 
}
