#ifndef step_control_h
#define step_control_h

#include "Arduino.h"
#include <AccelStepper.h>

#define X_MOTOR_STEP 2
#define X_MOTOR_DIR 5
#define Y_MOTOR_STEP 3
#define Y_MOTOR_DIR 6
#define Z_MOTOR_STEP 4
#define Z_MOTOR_DIR 7
#define A_MOTOR_STEP 12
#define A_MOTOR_DIR 13

#define STEPPER_ENABLE 8

#define limitSwitchX 9
#define limitSwitchY 10
#define limitSwitchZ 11
#define limitSwitchA A0

extern float X_ANGLE_TO_STEP;
extern float Y_ANGLE_TO_STEP;
extern float Z_ANGLE_TO_STEP;
extern float A_ANGLE_TO_STEP;

bool homeMotor(AccelStepper* stepMotor, int limitSwitch);
void initLimitSwitches();

#endif
