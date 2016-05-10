//Ways to calculate frequency:
//-Establish a sampling period and count the occurences in the sampling period.
//-Calculate the time between a given number of hits.

int AP = 0;//Analog pin number.
int OP = 13;//Digital output pin number.
int TH = 500;//Threshold for sensor trigger.

int DD;

void setup(){
  Serial.begin(9600);//Setup serial.
  pinMode(OP,OUTPUT);
}

void loop(){
  DD = analogRead(AP);//Read the input pin.


  if(DD<TH){
    digitalWrite(OP,HIGH);
  } else {
    digitalWrite(OP,LOW); 
  }


  //delay(1000);
  //Serial.println(DD);//Display 
}
