//CONTROLLER CODE
//Feel free to use this code however you like, but please credit lordvon and this site!
//'ud' and 'lr' are the pot signals for the up/down and left/right pots, respectively.

//(Joysticks and their pot values are not perfect, so some things have to be empirically
//determined. The serial read function is a great tool for collecting the values.)
//range of ud: 29-1014 (middle: around 479-540; avg:~510, center:+/-35)
//range of lr: 0-960 (middle: around 419-471; avg:445, center:+/-30)
//minimum range extreme (from avg) magnitude: 445
//maximum tolerance value: 35

//Print values as 'topic:value', where 'topic' denotes either 'ud' or 'lr',
//and 'value' is the associated pot value.
//Reciever is prompted to record by ':', and ended by ','.

//"" gives characters, '' gives characters in integer form.

//Empirically determined and/or arbitrary constants.
#define ud1 0
#define lr1 1
#define highpulse 2400
#define lowpulse 600
#define lr1avg 445
#define ud1avg 510
#define tolerance1 40
#define range1 445
#define maxadd 35

int ud1val;
int lr1val;
int lr1pulse;
int ud1pulse;
int lr1previous;
int ud1previous;
boolean update;

void setup()
{
Serial.begin(9600);
//initialize servo to its center position.
lr1previous = lr1avg;
ud1previous = ud1avg;
Serial.print(':');
Serial.print((highpulse-lowpulse)/2+lowpulse);
Serial.print(',');
Serial.print((highpulse-lowpulse)/2+lowpulse);
}

void loop()
{
ud1val = analogRead(ud1);
lr1val = analogRead(lr1);
update = (abs(lr1avg-lr1val) > tolerance1) || (abs(ud1avg-ud1val) > tolerance1); 
if (update)
{
lr1val = newval(lr1val,(lr1avg-range1),(lr1avg+range1),lr1avg,lr1previous);
ud1val = newval(ud1val,(ud1avg-range1),(ud1avg+range1),ud1avg,ud1previous);
lr1previous = lr1val;
ud1previous = ud1val;
lr1pulse = map(lr1val,(lr1avg-range1),(lr1avg+range1),lowpulse,highpulse);
ud1pulse = map(ud1val,(ud1avg-range1),(ud1avg+range1),lowpulse,highpulse); 
//':' is packet delimiter, ',' is UD/LR delimiter.
//Each cycle of delimiters denote a packet.
//Packet: UD value first, then LR value. (:UD,LR:)
Serial.print(':');
Serial.print(ud1pulse);
Serial.print(',');
Serial.print(lr1pulse);
delay(25); 
update = false;
}
}

int newval(int val, int minval, int maxval, int avgval, int previousval)
{
int increment;
increment = val-avgval;
if (increment > 0)
{
increment = increment - tolerance1;
}
else if (increment < 0) { increment = increment + tolerance1; } increment = map(increment,0,range1-tolerance1,0,maxadd); val = increment + previousval; if (!(val <= maxval) || !(val >= minval))
{
if (val > maxval)
{
val = maxval;
}
else
{
val = minval;
}
}
return val;
}
