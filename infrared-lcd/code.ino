//Ways to calculate frequency:
//-Establish a sampling period and count the occurences in the sampling period.
//-Calculate the time between a given number of hits.

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

unsigned int AP = 0;//Analog pin number.
unsigned int OP = 13;//Digital output pin number.
unsigned int CP = 20;//Count period. Should be at least 2. Higher: more accurate. Lower: faster updates.
unsigned int TO = 10;//Timeout, in seconds. The max length of time allowed for a single RPM read, before an RPM of 0 is assumed.
unsigned int TH = 500;//Threshold for sensor trigger.

unsigned int DD;//The digitized analog read value.
volatile int RR;//Revolutions.
unsigned int RPM;
volatile long OT;//Old time.
volatile long CT;//Current time.
volatile long DT;//Time difference.

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
  
  pinMode(OP,OUTPUT);
}

void loop(){
  /*
  DD = analogRead(AP);//Read the input pin.
  
  if(DD<TH){
    digitalWrite(OP,HIGH);
  } else {
    digitalWrite(OP,LOW); 
  }
  */


  //delay(1000);
  //Serial.println(DD);//Display
  //lcd.setCursor(0, 2);
  updateRPM();
  
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
  lcd.print("      ");
}

void updateTimer(){
  lcd.setCursor(14,0);
  lcd.print(millis()/1000);
}
