// Parameters
constexpr int SignalPin = A1;
constexpr int Threshold = 5; // [0, 1023]

// Standard parameters
constexpr int Frequency = 50; // Hertz
constexpr int MaxMicroseconds = 2000;
constexpr int MinMicroseconds = 1000;

// Derived parameters
constexpr double PeriodMicroseconds = 1e6 / Frequency;
constexpr double MaxSignal = 1023.0 * MaxMicroseconds / PeriodMicroseconds;
constexpr double MinSignal = 1023.0 * MinMicroseconds / PeriodMicroseconds;

void setup()
{
  pinMode(SignalPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  const int rv = analogRead(SignalPin);
  if (rv > Threshold)
  {
    Serial.print("Duty cycle: ");
    Serial.print(map(rv, MinSignal, MaxSignal, 0.0, 100.0));
    Serial.println("%");
  }
}



