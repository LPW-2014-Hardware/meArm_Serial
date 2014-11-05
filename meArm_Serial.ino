#include "meArm.h"
#include <Servo.h>

#define BASE_PIN 11
#define BASE_MIN 544
#define BASE_MAX 2400
#define SHOULDER_PIN 6
#define SHOULDER_MIN 544
#define SHOULDER_MAX 2400
#define ELBOW_PIN 9
#define ELBOW_MIN 544
#define ELBOW_MAX 3400
#define GRIPPER_PIN 10
#define GRIPPER_MIN 544
#define GRIPPER_MAX 2400
meArm arm;

void setup() {
  Serial.begin(9600);
  arm.begin(
    BASE_PIN, BASE_MIN, BASE_MAX,
    SHOULDER_PIN, SHOULDER_MIN, SHOULDER_MAX,
    ELBOW_PIN, ELBOW_MIN, ELBOW_MAX,
    GRIPPER_PIN, GRIPPER_MIN, GRIPPER_MAX
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
