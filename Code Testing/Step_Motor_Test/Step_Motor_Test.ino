#include <AccelStepper.h>

// Define the stepper motor connections
#define STEP_PIN 2
#define DIR_PIN 5
#define ENABLE 8
// Create an instance of AccelStepper
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);
  // Set the maximum speed and acceleration
  stepper.setMaxSpeed(1600); // steps per second
  stepper.setAcceleration(400); // steps per second^2

  // Set the initial target position
  stepper.moveTo(3200);
}

void loop() {
  // Move the stepper to the target position
  if (stepper.distanceToGo() == 0) {
    // Once we reach the target position, set a new target position
    stepper.moveTo(-stepper.currentPosition());
  }
  
  // This function will be called at a constant interval and will take care of acceleration and deceleration
  stepper.run();
}
