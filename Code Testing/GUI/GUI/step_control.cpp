#include "step_control.h"

float X_ANGLE_TO_STEP = 8.0 * 4.0 / 1.8;

bool homeMotor(AccelStepper* stepMotor, int limitSwitch)
{  
  Serial.print("Reached home function.\n");
  stepMotor->setMaxSpeed(1200); // Set a safe homing speed
  stepMotor->setAcceleration(400);
  stepMotor->moveTo(1000000); // Move the stepper a large negative distance

  while (digitalRead(limitSwitch) == LOW)  // Assume active LOW switch
  {
    stepMotor->run();
    if (stepMotor->distanceToGo() == 0) // Prevent endless loop in case of switch failure
    {
      return false;  // Homing failed
    }
  }
  
  stepMotor->stop(); // Stop the motor
  stepMotor->setCurrentPosition(0);  // Set this position as home
  return true;  // Homing successful
}

void initLimitSwitches()
{
  pinMode(limitSwitchX, INPUT_PULLUP);
  pinMode(limitSwitchY, INPUT_PULLUP);
  pinMode(limitSwitchZ, INPUT_PULLUP);
  pinMode(limitSwitchA, INPUT_PULLUP);
}
