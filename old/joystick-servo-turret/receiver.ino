//RECIEVER CODE
//Feel free to use this code however you like, but please credit lordvon and this site!
#include <Servo.h>

Servo elevation;
Servo azimuth;

#define highpulse 2400
#define lowpulse 600

char received;
char pulsechar[4];
int counter=0;
int pulse;
boolean delimiter;

void setup()
{
Serial.begin(9600);
while (!Serial.available()){}
received = Serial.read();
elevation.attach(12);
azimuth.attach(13);
}

void loop()
{
// if (Serial.available())
// {
// Serial.println(char(Serial.read()));
// }
delimiter = (received == ',') || (received == ':');
if (!delimiter)
{
counter = 0;
while (!delimiter)
{
while (!Serial.available()){}
pulsechar[counter] = received;
counter += 1;
received = Serial.read();
delimiter = (received == ',') || (received == ':');
}
pulsechar[counter] = '\0';
pulse = atoi(pulsechar);
switch (received)
{
case ',':
azimuth.writeMicroseconds(pulse);
break;
case ':':
elevation.writeMicroseconds(pulse);
break;
}
}
else
{
while (!Serial.available()){}
received = Serial.read();
}
}
