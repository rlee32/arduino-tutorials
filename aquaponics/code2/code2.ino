#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);//First two are PWM; last four are digital.

unsigned long ITP = 900;//seconds, inlet time period.
unsigned long OTP = 25;//seconds, outlet time period. 

const int relay =  13;//Digital pin number.

//Voltage reader constants.
const int AP = 0;//Analog read pin for the voltage read.
const int R1 = 10000;//Resistor 1 Ohms.
const int R2 = 3330;//Resistor 2 Ohms.
unsigned long VRT=200;//Voltage refresh time, milliseconds. Real-time reading can be too fast.

//Holder variables.
int CRS;//current relay signal.
unsigned long CTP;//current time period.
unsigned long PM;//previous millis() reading.
unsigned long PVM;//previous Voltage millis() reading.
unsigned long EE;//elapsed, difference between PM and millis().
double CV;



void setup() {
  //Initialize relay pin.
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  //Initialize time keeping.
  PM=millis();
  PVM=millis();
  //Initalize LCD.
  lcd.begin(20,4);
  lcd.clear();
  //lcd.print("Hello World!");
  lcdPrint(0,0,"Pumping ");
  lcdPrint(0,1,"");
  //lcdPrint(0,2,"Out Time: ");
  //lcdPrint(10,2,String(OTP));
  //lcdPrint(0,3,"In Time: ");
  //lcdPrint(9,3,String(ITP));
  lcdPrint(8,3,String(ITP));
  lcdPrint(8+digits(ITP),3,"s/");
  lcdPrint(8+digits(ITP)+2,3,String(OTP));
  lcdPrint(8+digits(ITP)+2+digits(OTP),3,"s");
  //Convert to milliseconds.
  ITP = ITP*1000;
  OTP = OTP*1000;
  //Initialize the holders so that pumping in starts first.
  CTP=ITP;
  CRS=LOW;
  //Voltage reader constant.
  CV=(R1+R2)/R2*5.0/1023.0;
}

void loop()
{ 
  //When millis() overflows, set to pump inward cycle.
  checkOverflow();
  
  //Normal routine.
  checkToggle();
  updateCountdown();
  //updateVoltage();
  updateVoltageSlow();
}

void updateCountdown(){
  if(CRS==LOW){
    lcdPrint(8,0,"Inward:   ");
  } else {
    lcdPrint(8,0,"Outward:   ");
  }
  unsigned long TT=(CTP-getTime())/1000;
  lcdPrint(0,1,String(TT));
  lcdPrint(digits(TT),1,"s    ");
}
void toggle(){
  if(CRS==LOW){
    CTP=OTP;
    CRS=HIGH;
  } else {
    CTP=ITP;
    CRS=LOW;
  }
}
void lcdPrint(int col,int row,String text){
  lcd.setCursor(col,row);
  lcd.print(text);
}
void resetTimer(){
  PM=millis();
}
void checkOverflow(){
  if(PM>millis()){
    CRS=LOW;
    CTP=ITP;
    resetTimer();
  }
}
unsigned long getTime(){
  return (millis()-PM);
}

void checkToggle(){
  EE = getTime();
  if(EE>CTP){
    toggle();
    digitalWrite(relay,CRS);
    resetTimer();
  }
}
int digits(unsigned long II){
  return ((String(II)).length());
}

String doubleToString(double input,int decimalPlaces){
  //Rounds down (via intermediary integer conversion truncation)
  if(decimalPlaces!=0){
    String string = String((int)(input*pow(10,decimalPlaces)));
    if(abs(input)<1){
      if(input>0)
        string = "0"+string;
      else if(input<0)
      string = string.substring(0,1)+"0"+string.substring(1);
    }
    return string.substring(0,string.length()-decimalPlaces)+"."+string.substring(string.length()-decimalPlaces);
  }
  else {
    return String((int)input);
  }
}

double getVoltage(int AR){
  //AR: analogRead value.
  //CV: constant determined from voltage divider resistor values.
  return AR*CV;
}

void updateVoltage(){
  int AR = analogRead(AP);
  double VV = getVoltage(AR);
  lcdPrint(14,1,doubleToString(VV,2));
  lcdPrint(18,1,"V ");
}
unsigned long getVTime(){
  return (millis()-PVM);
}
void updateVoltageSlow(){
  unsigned long time = getVTime();
  if(time>=VRT){
    int AR = analogRead(AP);
    double VV = getVoltage(AR);
    lcdPrint(14,1,doubleToString(VV,2));
    lcdPrint(18,1,"V ");
    PVM=millis();
  }
}

