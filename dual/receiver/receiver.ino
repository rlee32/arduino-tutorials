//RECIEVER CODE
//Feel free to use this code however you like, 
//but please credit lordvon and this site!
#include <Servo.h>

Servo elevation;
Servo azimuth;

#define highpulse 2400
#define lowpulse 600
//constants for additional controls.
const int C1 = 3;//pin number for control output 1.
const int C2 = 4;//pin number for control output 2.

char received;
char pulsechar[4];
int counter=0;
int pulse;
boolean delimiter;

void setup(){
  Serial.begin(9600);
  while (!Serial.available()){}
  received = Serial.read();
  elevation.attach(12);
  azimuth.attach(13);
  //code for additional controls.
  pinMode(C1,OUTPUT);
  pinMode(C2,OUTPUT);
}

void loop(){
  // if (Serial.available())
  // {
  // Serial.println(char(Serial.read()));
  // }
  delimiter = checkDelimiter(received);
  if (!delimiter){
    counter = 0;
    while (!delimiter){
      while (!Serial.available()){}
      pulsechar[counter] = received;
      counter += 1;
      received = Serial.read();
      delimiter = checkDelimiter(received);
    }
    pulsechar[counter] = '\0';
    pulse = atoi(pulsechar);
    switch (received){
      case ',':
        azimuth.writeMicroseconds(pulse);
        break;
      case ';':
        elevation.writeMicroseconds(pulse);
        break;
      case '.':
        digitalWrite(C1, pulse);
        break;
      case ':':
        digitalWrite(C2, pulse);
        break;
    }
    debug();
  } else {
    while (!Serial.available()){}
    received = Serial.read();
  }
}

boolean checkDelimiter(char received){
  return (received == ',') || (received == ':') || (received == ';') || (received == '.');
}
void debug(){
  switch (received){
    case ',':
      //Serial.print("Azimuth: ");
      //Serial.println(pulse);
      break;
    case ';':
      //Serial.print("Elevation: ");
      //Serial.println(pulse);
      break;
    case '.':
      //Serial.print("C1: ");
      //Serial.println(pulse);
      break;
    case ':':
      Serial.print("C2: ");
      Serial.println(pulse);
      break;
  }
  delay(1000);
}
