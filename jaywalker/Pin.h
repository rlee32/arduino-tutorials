#pragma once

/*
*/

#include "Arduino.h"

struct Pin
{
    Pin(int pin) : pin(pin) {}
    const int pin;
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

