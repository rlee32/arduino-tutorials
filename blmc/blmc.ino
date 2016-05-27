// Author: Robert Lee
// Email: rlee32@gatech.edu
#include <Servo.h>

// Pins.
const int PIN_MOTOR = 6; // pwm-capable output pin.
// Careful not to set PIN_SAFETY to 0 or 1 if using Serial.print().
const int PIN_SAFETY = 7; // motor-on digital input pin (may use analog pins).
const int PIN_POT = A0; // potentiometer analog input pin.
const int PIN_RGB[3] = { 9, 10, 11 }; // for indicator light.
// Potentiometer constants.
// To ensure maximum and minimum are reached, 
//  ADC_MAX should be a little lower than actual max, and
//  ADC_MIN should be a little higher than actual min.
// We divide signal values into finite levels to prevent jumpiness.
const int ADC_MAX = 975; // ADC units (0 to 1023, inclusive).
const int ADC_MIN = 25; // ADC units (0 to 1023, inclusive).
const int ADC_LEVELS = 20; // We divide signal values into finite levels.
// Pulse width constants.
const int WIDTH_MAX = 2400; // microseconds.
const int WIDTH_MIN = 600; // microseconds.
int WIDTHS[ADC_LEVELS] = {  };
// LED indicator status lights, for binary output mode.
// PWM output mode does not use these, and provides more colors.
// For PWM output, the assumed scale is blue-to-red rainbow.
// Turns out, using Servo library disables PWM pins on 9, 10, and 11.
// Be usre to take into account common anode or common cathode setup.
const int COLOR_READY[3] = {0,1,1};
const int COLOR_THRUST[3] = {1,1,0};
const int COLOR_MAX[3] = {1,0,1};
const int COLOR_MIN[3] = {0,1,0};

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
  // Initialize indicator light.
  for(int i = 0; i < 3; ++i) pinMode( PIN_RGB[i], OUTPUT );
  set_indicator_light_pwm( 0 );
//  Serial.begin( 9600 );
}

void loop()
{
  if( digitalRead( PIN_SAFETY ) ) //== HIGH )
  {
    throttle();
  }
  else
  {
    off();
  }
//  delay(50);
//  debug();
}

// Sets the ESC pulse width according to pot input.
int throttle()
{
  int level = map( analogRead( PIN_POT ),
    ADC_MIN, ADC_MAX,
    0, ADC_LEVELS-1 );
  level = constrain( level, 0, ADC_LEVELS-1 );
  motor.writeMicroseconds( WIDTHS[level] );
//  Serial.print(level);Serial.print(": ");Serial.println(WIDTHS[level]); delay(1000);
  const int* color = (level < ADC_LEVELS-1) ? COLOR_THRUST : COLOR_MAX;
  color = ( level ) ? color : COLOR_MIN;
  set_indicator_light( color );
  return WIDTHS[level];
}

void off()
{
  motor.writeMicroseconds( WIDTH_MIN );
  set_indicator_light( COLOR_READY );
}

// Status indicator light functions.

// For binary output
void set_indicator_light(const int rgb[3])
{
  for(int i = 0; i < 3; ++i) digitalWrite( PIN_RGB[i], rgb[i] );
}

// For PWM output
void set_indicator_light_pwm(const int rgb[3])
{
//  Serial.println("RGB:");
  for(int i = 0; i < 3; ++i)
  {
    analogWrite( PIN_RGB[i], rgb[i] );
//    Serial.print(PIN_RGB[i]);
//    Serial.print(": ");
//    Serial.println(rgb[i]);
  }
}

// For PWM output
void set_indicator_light_pwm(int level)
{  
  int scale_value = map( level,
    0, ADC_LEVELS-1,
    0, 255 );
    int rgb[3] = { 0, 0, 0 };
  scalar2rgb(scale_value, rgb);
  set_indicator_light_pwm( rgb );
}

// Blue-to-red rainbow color scale, often used in CFD.
// val: value in [0, 255], i.e. [blue, red]
// rgb: the appropriate rgb values are stored here.
void scalar2rgb( double val, int rgb[3] )
{
  const int minval = 0;
  const int maxval = 255;
  // Derived from: https://www.particleincell.com/2014/colormap/
  // Normalize
  double f = (val - minval) / (maxval - minval);
  // Invert the value to get blue to red as 0 to 1.
  double a = 4 * ( 1 - f ); //invert and group
  int X = (int) a;  //this is the integer part
  int Y = (int) ( 255 * ( a - X ) ); //fractional part from 0 to 255
  rgb[0] = 0;
  rgb[1] = 0;
  rgb[2] = 0;
  if (maxval == minval) X = 4;
  switch(X)
  {
      case 0: 
        rgb[0]=255; 
        rgb[1]=Y; 
        break;
      case 1: 
        rgb[0]=255-Y; 
        rgb[1]=255; 
        break;
      case 2: 
        rgb[1]=255; 
        rgb[2]=Y; 
        break;
      case 3: 
        rgb[1]=255-Y; 
        rgb[2]=255; 
        break;
      case 4: 
        rgb[2]=255; 
        break;
  }
}

// Debugging functions.

void debug()
{
//  Serial.println( throttle() );
  Serial.println( digitalRead( PIN_SAFETY ) );
  delay( 1000 );
}


