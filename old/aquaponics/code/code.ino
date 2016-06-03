#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);//First two are PWM; last four are digital.

long refreshinterval = 5;//seconds
long outpumpinterval = 1;//seconds 

const int outpump =  13;//Digital pin number.
const int inpump = 14;//Digital pin number.

//Holder variables.
int refreshing;
unsigned long previousMillis,currentMillis,elapsed;

void setup() {
  refreshing = LOW;
  previousMillis = 0;
  // set the digital pin as output:
  pinMode(outpump, OUTPUT);
  pinMode(inpump, OUTPUT);
  //convert to milliseconds
  refreshinterval = refreshinterval*1000;
  outpumpinterval = outpumpinterval*1000;
  
  
  
  lcd.begin(16,4);
  lcd.setCursor(0,0);
  lcd.print("Countdown: ");
  lcd.setCursor(0,1);
  lcd.print("Inlet Period: ");
  lcd.setCursor(0,2);
  lcd.print("Outlet Period: ");
  lcd.setCursor(0,3);
  lcd.print("");
}

void loop()
{
  currentMillis = millis();
  elapsed = currentMillis-previousMillis;
  if(refreshing == HIGH){
   if(elapsed > outpumpinterval){
    digitalWrite(outpump, LOW);//stop pumping out water.
    digitalWrite(inpump, LOW);//start pumping in water.
    refreshing = LOW;
   }
  } else {
    if(elapsed > refreshinterval) {
      previousMillis = currentMillis;   
      refreshing = HIGH;
      digitalWrite(outpump, HIGH);//start pumping out water.
      digitalWrite(inpump, HIGH);//stop pumping in water.
    }
  }
}

void updateCountdown(){
  lcd.setCursor(14,0);
  lcd.print(millis()/1000);
}

