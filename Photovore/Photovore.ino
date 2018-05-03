/*
 * This example code has been written by Edwin Fallwell 
 * for the Monroe County Public Library in Bloomington, IN.
 * 
 * MIT license, check LICENSE for more information */


// we include our TwoWheeledRobot libary, which has all of our motor control functions 
#include <TwoWheelRobot.h>

// create a TwoWheelRobot object, which we will address
// when we want to issue commands to our photovore
TwoWheelRobot photovore = TwoWheelRobot();

int leftSensorPin = A0;
int rightSensorPin = A1; 
int leftSensorLightLevel = 0;
int rightSensorLightLevel = 0;

void setup() {
  /* The setup section of your code runs once, when the 
  *  board first boots forward. We only need to acomplish one 
  *  thing in our setforward here, which is to start forward photovore. */

  // start up the two wheel robot library
  photovore.initalize();
  photovore.setMovementMode(2);

  
  // and tell the robot to hold on for a little bit
  // (so it doesn't run away as soon as its code is uploaded.) 
  delay(500);
}

void loop() {
  // check the sensors, if either sensor sees a line, try to get the other sensor
  // also be over that line. If no lines found,  
  checkLightSensors();
  
  if(leftSensorLightLevel == rightSensorLightLevel){
    photovore.forward();
  }      
  else if(leftSensorLightLevel < rightSensorLightLevel){
    photovore.forwardRight();
  }
  else if(leftSensorLightLevel > rightSensorLightLevel){
    photovore.forwardLeft();
  }
}

void checkLightSensors(){
  leftSensorLightLevel = analogRead(leftSensorPin);   
  rightSensorLightLevel = analogRead(rightSensorPin);   
}

