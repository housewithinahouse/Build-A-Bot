/*
 * This example code has been written by Edwin Fallwell + Matt Neer 
 * for the Monroe County Public Library in Bloomington, IN.
 * 
 * MIT license, check LICENSE for more information */


// we include our TwoWheeledRobot libary, which has all of our motor control functions 
#include <TwoWheelRobot.h>

// create a TwoWheelRobot object, which we will address
// when we want to issue commands to our example robot
TwoWheelRobot blocky = TwoWheelRobot();

bool leftSensorSeesLine = false;
bool rightSensorSeesLine = false;
bool foundALine = false;
int leftSensorPin = A0;
int rightSensorPin = A1; 
int leftBumperPin = 20;
int rightBumperPin = 21;
int lineThreshold = 600; // number derived from testing

void setup() {
  /* The setup section of your code runs once, when the 
  *  board first boots forward. We only need to acomplish one 
  *  thing in our setforward here, which is to start forward blocky. */

  // start up the two wheel robot library
  blocky.initalize();
  blocky.setMovementMode(2);

  
  // and tell the robot to hold on for a little bit
  // (so it doesn't run away as soon as its code is uploaded.) 
  delay(500);
}

void loop() {
  // check the sensors, if either sensor sees a line, try to get the other sensor
  // also be over that line. If no lines found, wander around aimlessly. If it does 
  // find a line, sit there, waiting for something to bump into you. If you are bumped
  // freak out, and then go back to wandering, looking for a new line. 

  checkEachSensor();
  
  if(leftSensorSeesLine && rightSensorSeesLine){
    blocky.stop();
    foundALine = true;
  }      
  else if(rightSensorSeesLine){
    blocky.right();
  }
  else if(leftSensorSeesLine){
    blocky.left();
  }
  else if(foundALine){
    blocky.stop();
  }
  else{
    wanderRandomly();
  }

  if(somethingBumpsYou()){
    freakOut();
    foundALine = false;
  }  
}


void checkEachSensor(){
  // updates the vars: leftSensorSeesLine + rightSensorSeesLine
    
  if((analogRead(leftSensorPin)) > lineThreshold){
    leftSensorSeesLine = true;
  }
  else{
    leftSensorSeesLine = false;
  }
  
  if((analogRead(rightSensorPin)) > lineThreshold){
    rightSensorSeesLine = true;
  }
  else{
    rightSensorSeesLine = false;
  }
}

void wanderRandomly(){
  // issues a series of random commands to our robot
    
  blocky.forward(100); //TODO: replace with actually random movement
}

bool somethingBumpsYou(){
  // returns true if either bumper is hit

  // turn the pins into inputs
  pinMode(leftBumperPin, INPUT);
  pinMode(rightBumperPin, INPUT);

  // check to see if either one goes high  
  if((digitalRead(leftBumperPin) == HIGH)||(digitalRead(rightBumperPin)) == HIGH){
    return true;
  }
  else{
    return false;
  }
}

void freakOut(){
  // preforms a crazy chaotic series of moves    
  blocky.backward(400);
  blocky.left(1100); //TODO: replace with more interesting actions
}





