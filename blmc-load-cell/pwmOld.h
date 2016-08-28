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