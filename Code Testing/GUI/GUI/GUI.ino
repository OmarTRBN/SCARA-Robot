#include "step_control.h"

AccelStepper motorX(1, X_MOTOR_STEP, X_MOTOR_DIR);
AccelStepper motorY(1, Y_MOTOR_STEP, Y_MOTOR_DIR);
AccelStepper motorZ(1, Z_MOTOR_STEP, Z_MOTOR_DIR);
AccelStepper motorA(1, A_MOTOR_STEP, A_MOTOR_DIR);

int ledPin = 13; // LED connected to digital pin 13

void setup() {
  initLimitSwitches();
  Serial.begin(9600);
  Serial.println("Setup complete");
  motorY.setMaxSpeed(1600);
  motorY.setAcceleration(400);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove any leading or trailing whitespace

    Serial.print("Received command: '");
    Serial.print(command);
    Serial.println("'");

    if (command.startsWith("ACCELERATION:"))
    {
      int number = command.substring(7).toInt();
      motorY.runToNewPosition(number);
      // You can add more actions based on the received number here
    }
    else if (command.startsWith("SPEED:"))
    {
      int number = command.substring(7).toInt();
      motorX.setSpeed(number);
      motorY.setSpeed(number);
      motorZ.setSpeed(number);
      motorA.setSpeed(number);
    }
    else if(command == "HOME")  // Changed from startsWith to exact match
    {
      Serial.println("HOME command recognized");
      homeMotor(&motorX, limitSwitchX);
      motorX.runToNewPosition(long(-180.0 * X_ANGLE_TO_STEP));
    }
    else
    {
      Serial.println("Unrecognized command");
    }
  }

}


