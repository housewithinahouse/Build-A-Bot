/*
 * This example code has been written by Edwin Fallwell 
 * for the Monroe County Public Library in Bloomington, IN.
 * 
 * MIT license, check LICENSE for more information */


// we include our TwoWheeledRobot libary, which has all of our motor control functions 
#include <TwoWheelRobot.h>

// create a TwoWheelRobot object, which we will address
// when we want to issue commands to our photophobe
TwoWheelRobot photophobe = TwoWheelRobot();

int leftSensorPin = A0;
int rightSensorPin = A1; 
int leftSensorLightLevel = 0;
int rightSensorLightLevel = 0;

void setup() {
  // start up the two wheel robot library
  photophobe.initalize();
  Serial.begin(9600);
}

void loop() {

  checkLightSensors();

  if(leftSensorLightLevel > rightSensorLightLevel){
    photophobe.forwardRight();
  }
  else if(leftSensorLightLevel < rightSensorLightLevel){
    photophobe.forwardLeft();
  }
}

void checkLightSensors(){
  leftSensorLightLevel = analogRead(leftSensorPin);   
  rightSensorLightLevel = analogRead(rightSensorPin);  
  Serial.print("left: "); 
  Serial.println(leftSensorLightLevel);
  Serial.println("right: ");
  Serial.println(rightSensorLightLevel);
  delay(100);
}

