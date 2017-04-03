#include "MomentaryPushButton.h"
#include "Pin.h"
#include "RgbLed.h"

// Pin mappings
PowerPin  buttonPower(1);
GroundPin buttonGround(2);
InputPin  buttonInput(3);
OutputPin buttonOutput(4);

PowerPin  ledPower(6);
OutputPin red(7);
OutputPin green(8);
OutputPin blue(9);

// Components
RgbLed led(ledPower, red, green, blue);
MomentaryPushButton button(buttonPower, buttonInput, buttonGround);

byte message = 0;

void setup()
{
    Serial.begin(2400);
    Pin::ValidateSingleUsage();
    led.setup();
    button.setup();
    led.green();
}

void loop()
{
    if (button.high())
    {
        message = 1;
        Serial.print(message);
        led.red();
    }
    else
    {
        led.green();
    }
}
