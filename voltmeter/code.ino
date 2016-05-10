//Allows for voltages higher than 5 V to be read.
//Utilizes a two-resistor voltage divider.
//Higher voltages leads to lower resolution or read.
//0-5V Resolution: 0.0048828125 V
//0-10V Resulotion: 0.009765625 V

int AP = 3;// The analog input pin number.
int R1 = 10000;//First resistor, on the side of the voltage to be measured.
int R2 = 3300;//Second resistor, on the ground side.

double CV;//The constant to infer the measured voltage.
int AR;// variable to store the analog value read.
double VV;//The inferred Voltage (what will be read).

void setup()
{
  CV=(R1+R2)/R2*5.0/1023.0;
  Serial.begin(9600);//Setup serial.
}

void loop()
{
  AR = analogRead(AP);//Read the input pin
  VV = getVoltage(AR);//Calculate the Voltage.
  Serial.println(VV);
}

double getVoltage(int AR){
  //AR: analogRead value.
  //CV: constant determined from voltage divider resistor values.
  return AR*CV;
}
