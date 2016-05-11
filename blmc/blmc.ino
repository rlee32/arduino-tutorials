// Author: Robert Lee
// Email: rlee32@gatech.edu
#include <Servo.h>

// Pins.
const int PIN_MOTOR = 11; // pwm-capable output pin.
const int PIN_POT = 0; // potentiometer analog input pin.
const int PIN_SAFETY = 1; // motor-on digital input pin.
// Potentiometer constants.
// To ensure maximum and minimum are reached, 
//  ADC_MAX should be a little lower than actual max, and
//  ADC_MIN should be a little higher than actual min.
// We divide signal values into finite levels to prevent jumpiness.
const int ADC_MAX = 900; // ADC units (0 to 1023, inclusive).
const int ADC_MIN = 100; // ADC units (0 to 1023, inclusive).
const int ADC_LEVELS = 15; // We divide signal values into finite levels.
// Pulse width constants.
const int WIDTH_MAX = 2000; // microseconds.
const int WIDTH_MIN = 1000; // microseconds.
int WIDTHS[ADC_LEVELS] = {  };
// Other.
const int LOOP_DELAY = 50; // Just in case the update is too frequent.

Servo motor;

void setup()
{
  pinMode(PIN_POT, INPUT);
  pinMode(PIN_SAFETY, INPUT);
  motor.attach(PIN_MOTOR);
  // Initialize pulse width discretization.
  int width_increment = ( WIDTH_MAX - WIDTH_MIN ) / ( ADC_LEVELS - 1 );
  for( int i=0; i<ADC_LEVELS; ++i ) WIDTHS[i] = WIDTH_MIN + i*width_increment;
  WIDTHS[0] = WIDTH_MIN;
  WIDTHS[ADC_LEVELS-1] = WIDTH_MAX;
}

// Sets the ESC pulse width according to pot input.
void throttle()
{
  int level = map( analogRead( PIN_POT ),
    ADC_MIN, ADC_MAX,
    0, ADC_LEVELS-1 );
  level = constrain( level, 0, ADC_LEVELS-1 );
  motor.writeMicroseconds( WIDTHS[level] );
}

void off() { motor.writeMicroseconds( WIDTH_MIN ); }

void loop()
{
  if( digitalRead( PIN_SAFETY ) == HIGH )
  {
    throttle();
  }
  else
  {
    off();
  }
  delay( LOOP_DELAY );
  // debug();
}

void debug()
{
}


