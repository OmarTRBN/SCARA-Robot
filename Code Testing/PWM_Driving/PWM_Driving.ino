#define M0 10
#define M1 11
#define M2 12

// Define the pins for the DRV8825
const int stepPin = 3;
const int dirPin = 2;
const int enablePin = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(enablePin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin, HIGH);
  digitalWrite(enablePin, LOW);
  
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  digitalWrite(M0, 0);
  digitalWrite(M1, 0);
  digitalWrite(M2, 0);
}

void loop() {
  analogWrite(stepPin, 127);
}
