#pragma once

#include <assert.h>

#include "Arduino.h"

struct Pin
{
    Pin(int pin) : pin(pin)
    {
        assert(pin >= 0 and pin <= MaxPin);
        ++Usage[pin];
    }
    const int pin = -1;
    static void ValidateSingleUsage()
    {
        for(int i = 0; i <= MaxPin; ++i)
        {
            assert(Usage[i] == 1 or Usage[i] == 0);
        }
    }
private:
    static constexpr int MaxPin = 40; // This may depend on your Arduino model.
    static int Usage[MaxPin + 1]; // zero-initialize.
};

struct PowerPin : public Pin
{
    PowerPin(int pin) : Pin(pin) {}
    void setup() const
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);
    }
};

struct GroundPin : public Pin
{
    GroundPin(int pin) : Pin(pin) {}
    void setup() const
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
};

struct InputPin : public Pin
{
    InputPin(int pin) : Pin(pin) {}
    void setup() const
    {
        pinMode(pin, INPUT);
    }
};

struct OutputPin : public Pin
{
    OutputPin(int pin) : Pin(pin) {}
    void setup() const
    {
        pinMode(pin, OUTPUT);
    }
};

