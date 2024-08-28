#include <AccelStepper.h>
#include "stepMotors.h"

// Create the motor objects
AccelStepper motorX(1, X_MOTOR_STEP, X_MOTOR_DIR);
AccelStepper motorY(1, Y_MOTOR_STEP, Y_MOTOR_DIR);
AccelStepper motorZ(1, Z_MOTOR_STEP, Z_MOTOR_DIR);
AccelStepper motorA(1, A_MOTOR_STEP, A_MOTOR_DIR);

int motorSpeeds[4] = {1000, 1000, 1000, 1000};
int motorAccelerations[4] = {200, 200, 200, 200};

void setup()
{
  Serial.begin(9600);
  
  initLimitSwitches();

  motorX.setMaxSpeed(motorSpeeds[0]);
  motorX.setAcceleration(motorAccelerations[0]);
  motorY.setMaxSpeed(motorSpeeds[1]);
  motorY.setAcceleration(motorAccelerations[1]);
  motorZ.setMaxSpeed(motorSpeeds[2]);
  motorZ.setAcceleration(motorAccelerations[2]);
  motorA.setMaxSpeed(motorSpeeds[3]);
  motorA.setAcceleration(motorAccelerations[3]);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');
    
    if (command.startsWith("SETSPEED:")){
      // Parse the speed values
      int commaIndex1 = command.indexOf(',');
      int commaIndex2 = command.indexOf(',', commaIndex1 + 1);
      int commaIndex3 = command.indexOf(',', commaIndex2 + 1);
      motorSpeeds[0] = command.substring(9, commaIndex1).toInt();
      motorSpeeds[1] = command.substring(commaIndex1 + 1, commaIndex2).toInt();
      motorSpeeds[2] = command.substring(commaIndex2 + 1, commaIndex3).toInt();
      motorSpeeds[3] = command.substring(commaIndex3 + 1).toInt();
      
      // Set the maximum speed for each motor
      motorX.setMaxSpeed(motorSpeeds[0]);
      motorY.setMaxSpeed(motorSpeeds[1]);
      motorZ.setMaxSpeed(motorSpeeds[2]);
      motorA.setMaxSpeed(motorSpeeds[3]);
    }
    else if (command.startsWith("SETACCELERATION:")){
      // Parse the acceleration values
      int commaIndex1 = command.indexOf(',');
      int commaIndex2 = command.indexOf(',', commaIndex1 + 1);
      int commaIndex3 = command.indexOf(',', commaIndex2 + 1);
      motorAccelerations[0] = command.substring(16, commaIndex1).toInt();
      motorAccelerations[1] = command.substring(commaIndex1 + 1, commaIndex2).toInt();
      motorAccelerations[2] = command.substring(commaIndex2 + 1, commaIndex3).toInt();
      motorAccelerations[3] = command.substring(commaIndex3 + 1).toInt();
      
      motorX.setAcceleration(motorAccelerations[0]);
      motorY.setAcceleration(motorAccelerations[1]);
      motorZ.setAcceleration(motorAccelerations[2]);
      motorA.setAcceleration(motorAccelerations[3]);
    }
    else if (command.equals("HOME")){
      homeMotor(&motorZ, limitSwitchZ);
      homeMotor(&motorX, limitSwitchX);
      motorX.runToNewPosition(long(-180.0 * X_ANGLE_TO_STEP));

    }
    else if (command.startsWith("MOVETO:")){
      // Parse the target positions
      int targetX, targetY, targetZ, targetA;
      int commaIndex1 = command.indexOf(',');
      int commaIndex2 = command.indexOf(',', commaIndex1 + 1);
      int commaIndex3 = command.indexOf(',', commaIndex2 + 1);
      targetX = command.substring(7, commaIndex1).toInt();
      targetY = command.substring(commaIndex1 + 1, commaIndex2).toInt();
      targetZ = command.substring(commaIndex2 + 1, commaIndex3).toInt();
      targetA = command.substring(commaIndex3 + 1).toInt();
    }
    else if (command.startsWith("STEP:")){
      // Parse the step values
      int stepsX, stepsY, stepsZ, stepsA;
      int commaIndex1 = command.indexOf(',');
      int commaIndex2 = command.indexOf(',', commaIndex1 + 1);
      int commaIndex3 = command.indexOf(',', commaIndex2 + 1);
      stepsX = command.substring(5, commaIndex1).toInt();
      stepsY = command.substring(commaIndex1 + 1, commaIndex2).toInt();
      stepsZ = command.substring(commaIndex2 + 1, commaIndex3).toInt();
      stepsA = command.substring(commaIndex3 + 1).toInt();

      // Set the number of steps to move for each motor
      motorX.move(stepsX);
      motorY.move(stepsY);
      motorZ.move(stepsZ);
      motorA.move(stepsA);

      // Run the motors until they complete their moves
      while (motorX.distanceToGo() != 0 || motorY.distanceToGo() != 0 || 
             motorZ.distanceToGo() != 0 || motorA.distanceToGo() != 0) 
      {
        motorX.run();
        motorY.run();
        motorZ.run();
        motorA.run();
      }
    }
    else if (command.equals("PRINT_PARAMETERS")){
      // Print the current speed and acceleration values
      Serial.print("Motor X Speed: ");
      Serial.print(motorX.maxSpeed());
      Serial.print(", Acceleration: ");
      Serial.println(motorX.acceleration());
      
      Serial.print("Motor Y Speed: ");
      Serial.print(motorY.maxSpeed());
      Serial.print(", Acceleration: ");
      Serial.println(motorY.acceleration());
      
      Serial.print("Motor Z Speed: ");
      Serial.print(motorZ.maxSpeed());
      Serial.print(", Acceleration: ");
      Serial.println(motorZ.acceleration());
      
      Serial.print("Motor A Speed: ");
      Serial.print(motorA.maxSpeed());
      Serial.print(", Acceleration: ");
      Serial.println(motorA.acceleration());
    }
    else if (command.equals("PRINT_POSITIONS")){
      // Print the current position of each motor
      Serial.print("Current Positions - X: ");
      Serial.print(motorX.currentPosition());
      Serial.print(", Y: ");
      Serial.print(motorY.currentPosition());
      Serial.print(", Z: ");
      Serial.print(motorZ.currentPosition());
      Serial.print(", A: ");
      Serial.println(motorA.currentPosition());
    }

  }
}