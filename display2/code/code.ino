//Info on the Voltage Reader:
//Allows for voltages higher than 5 V to be read.
//Utilizes a two-resistor voltage divider.
//Higher voltages leads to lower resolution or read.
//0-5V Resolution: 0.0048828125 V
//0-10V Resulotion: 0.009765625 V

//Parameters and Settings.
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);//The first two inputs are PWM pins, and the other four are digital pins.

//unsigned int OP = 13;//Digital output pin number.
unsigned int CP = 20;//Count period. Should be at least 2. Higher: more accurate. Lower: faster updates.
unsigned int TO = 10;//Timeout, in seconds. The max length of time allowed for a single RPM read, before an RPM of 0 is assumed.
//unsigned int TH = 500;//Threshold for sensor trigger.

unsigned int VAP = 0;//Analog pin number for the voltage sensor.
int R1 = 3900;//First resistor, on the side of the high voltage to be measured.
int R2 = 3900;//Second resistor, on the ground side.

//Holder / Intermediate Variables.
volatile unsigned int RR;//Revolutions.
unsigned int RPM;//The calculated rotational speed in Revolutions Per Minute.
volatile long OT;//Old time; the start time at which the time period, used in the RPM calculation, begins.
volatile long CT;//Current time.
volatile long DT;//Time difference.

double CV;//The constant to infer the measured voltage.
double VV;//The inferred Voltage (what will be read).

unsigned int DD;//The digitized analog read value.

void setup(){
  lcd.begin(16,4);
  lcd.setCursor(0,0);
  lcd.print("Status: OK");
  lcd.setCursor(0,1);
  lcd.print("RPM: 0");
  lcd.setCursor(0,2);
  lcd.print("Voltage: 0");
  lcd.setCursor(0,3);
  lcd.print("Hits: 0");
  

  attachInterrupt(0, hit, FALLING);//0 is on Pin 2, 1 is on Pin 3
  RR = 0;
  RPM = 0;
  OT = 0;
  CT = 0;
  DT = 0;
  
  CV=(R1+R2)/R2;
  
  //pinMode(OP,OUTPUT);
}

void loop(){
  updateRPM();
  updateVoltage();
  
  updateHits();
  updateTimer();
}

void hit(){
  RR++;
  if(RR==1){//First revolution for this read.
    OT=micros();
  } else if(RR>=CP){//Last revolution for this read.
    CT=micros();
    if(CT>OT){
      DT=CT-OT;
      //RPM=((RR-1)*60*1000000L) / DT;
    }
    RR=0;
  }
}

void updateRPM(){
  if((micros()-CT) > (TO*1000000L)){
    DT=0;
    RR=0;
    CT=micros();
    //lcd.setCursor(5,1);
    //lcd.print("Timed Out.");
  } else {
    if(DT>0){
      RPM=((CP-1)*60*1000000L) / DT;
    } else {
      RPM=0;
    }
    lcd.setCursor(5,1);
    lcd.print(RPM);
    lcd.print("          "); 
  }
}

void updateHits(){
  lcd.setCursor(6,3);
  lcd.print(RR);
  lcd.print("          ");
}

void updateTimer(){
  lcd.setCursor(14,0);
  lcd.print(millis()/1000);
}

void updateVoltage(){  
  DD = analogRead(VAP);//Read the input pin
  //VV = (DD*5*CV*1000)/1023;//Calculate the Voltage, in mV.
  VV = (DD*5)/1023;//Calculate the Voltage, in V.
  lcd.setCursor(9,2);
  lcd.print(VV);
  lcd.print(" V   ");
}
