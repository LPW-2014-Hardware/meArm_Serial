#include "meArm.h"
#include <Servo.h>

#define BASE_PIN 11
#define BASE_MIN_SWEEP 145
#define BASE_MAX_SWEEP 49
#define BASE_MIN_ANGLE -pi/4
#define BASE_MAX_ANGLE pi/4

#define SHOULDER_PIN 6
#define SHOULDER_MIN_SWEEP 118
#define SHOULDER_MAX_SWEEP 22
#define SHOULDER_MIN_ANGLE pi/4
#define SHOULDER_MAX_ANGLE 3*pi/4

#define ELBOW_PIN 9
#define ELBOW_MIN_SWEEP 144
#define ELBOW_MAX_SWEEP 36
#define ELBOW_MIN_ANGLE pi/4
#define ELBOW_MAX_ANGLE -pi/4

#define GRIPPER_PIN 10
#define GRIPPER_MIN_SWEEP 75
#define GRIPPER_MAX_SWEEP 115
#define GRIPPER_MIN_ANGLE pi/2
#define GRIPPER_MAX_ANGLE 0

meArm arm(
  BASE_MIN_SWEEP, BASE_MAX_SWEEP, BASE_MIN_ANGLE, BASE_MAX_ANGLE,
  SHOULDER_MIN_SWEEP, SHOULDER_MAX_SWEEP, SHOULDER_MIN_ANGLE, SHOULDER_MAX_ANGLE,
  ELBOW_MIN_SWEEP, ELBOW_MAX_SWEEP, ELBOW_MIN_ANGLE, ELBOW_MAX_ANGLE,
  GRIPPER_MIN_SWEEP, GRIPPER_MAX_SWEEP, GRIPPER_MIN_ANGLE, GRIPPER_MAX_ANGLE
);

void setup() {
  Serial.begin(9600);
  arm.begin(
    BASE_PIN,
    SHOULDER_PIN,
    ELBOW_PIN,
    GRIPPER_PIN
  );
}

int pX = 0;
int pY = 100;
int pZ = 50;
boolean pG = false;

void loop() {
  while (Serial.available() > 0) {
    int command = Serial.read();
    
    switch (command) {
      case 'x' :
        pX = Serial.parseInt();
        Serial.print("X");
        Serial.print(pX);
        Serial.print("\n");
        break;
      case 'y' :
        pY = Serial.parseInt();
        Serial.print("Y");
        Serial.print(pY);
        Serial.print("\n");
        break;
      case 'z' :
        pZ = Serial.parseInt();
        Serial.print("Z");
        Serial.print(pZ);
        Serial.print("\n");
        break;
      case 'g' :
        if (Serial.parseInt() > 0) {
          pG = true;
          Serial.print("GCLOSE\n");
        } else {
          pG = false;
          Serial.print("GOPEN\n");
        }
        break;
      default :
        Serial.print("E404\n");
    }
  }
  
  // Open or close the gripper
  if (pG) {
    //Serial.print("gripper closed\n");
    arm.closeGripper();
  } else {
    //Serial.print("gripper open\n");
    arm.openGripper();
  }
  //Serial.print("\nX Position: ");
  //Serial.print(pX);
  //Serial.print("\nY Position: ");
  //Serial.print(pY);
  //Serial.print("\nZ Position: ");
  //Serial.print(pZ);

  // Set the position of the arm
  arm.gotoPoint(pX,pY,pZ);
}
