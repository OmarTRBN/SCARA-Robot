#include <AccelStepper.h>

#define M0 10
#define M1 11
#define M2 12

// Define the pins for the DRV8825
const int stepPin = 3;
const int dirPin = 2;
const int enablePin = 4;

// Define the analog pin for the potentiometer
const int potPin = A0;

// Create an instance of AccelStepper
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

void setup() {
  // Set the enable pin as output and enable the driver
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
  
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  digitalWrite(M0, 0);
  digitalWrite(M1, 0);
  digitalWrite(M2, 0);

  // Set the maximum speed and acceleration
  stepper.setMaxSpeed(10000);
  stepper.setAcceleration(20);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the potentiometer (0-1023)
//  int potValue = analogRead(potPin);
//
//  // Map the potentiometer value to a speed range (e.g., 0-1000 steps per second)
//  float speedR = map(potValue, 0, 1023, 100, 1000);

  // Print the potentiometer value and speed for debugging
//  Serial.print("Potentiometer value: ");
//  Serial.print(potValue);
//  Serial.print(" - Speed: ");
//  Serial.println(speedR);

  // Set the speed of the stepper motor
  stepper.setSpeed(1200);

  // Run the motor at the set speed
  stepper.runSpeed();
  
}
