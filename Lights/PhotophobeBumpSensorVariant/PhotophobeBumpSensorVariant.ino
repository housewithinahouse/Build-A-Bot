/*
 * This example code has been written by Edwin Fallwell 
 * & Matt Neer for the Monroe County Public Library in Bloomington, IN.
 * 
 * MIT license, check LICENSE for more information */


// we include our TwoWheeledRobot libary, which has all of our motor control functions 
#include <TwoWheelRobot.h>

// create a TwoWheelRobot object, which we will address
// when we want to issue commands to our photophobe
TwoWheelRobot photophobe = TwoWheelRobot();

int leftSensorPin = A0;
int rightSensorPin = A1; 

int leftBumpSensorPin = 20;
int rightBumpSensorPin = 21;

int leftSensorLightLevel = 0;
int rightSensorLightLevel = 0;
int high, low, ave = 0;

bool bumpedLeft = false;
bool bumpedRight = false;

void setup() {
  // start up the two wheel robot library
  photophobe.initalize();
  photophobe.setSpeed(100);
  Serial.begin(9600);
}

void loop() {

  checkLightSensors();
  
  averages();

  if(leftSensorLightLevel < high && leftSensorLightLevel > low){
    photophobe.backward();
  }
  else if(leftSensorLightLevel < rightSensorLightLevel){
    photophobe.backwardRight();
  }
  else if(leftSensorLightLevel > rightSensorLightLevel){
    photophobe.backwardLeft();
  }

  checkBumpSensors();
  
  if(bumpedLeft){
    photophobe.left(150);
    bumpedLeft = false;    
  }
  if(bumpedRight){
    photophobe.right(150);
    bumpedRight = false;
  }
}

void checkLightSensors(){
  leftSensorLightLevel = analogRead(leftSensorPin);   
  rightSensorLightLevel = analogRead(rightSensorPin);
  /* Serial.print("left: "); 
  Serial.println(leftSensorLightLevel);
  Serial.println("right: ");
  Serial.println(rightSensorLightLevel);
  delay(100); */
}

void averages(){
  ave = (leftSensorLightLevel + rightSensorLightLevel) / 2;
  low = ave - 5;
  high = ave + 5;
}

void checkBumpSensors(){
  bumpedLeft = digitalRead(leftBumpSensorPin);
  bumpedRight = digitalRead(rightBumpSensorPin);
  
}

