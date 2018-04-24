/*
 * This example code has been written by Edwin Fallwell + Matt Neer 
 * for the Monroe County Public Library in Bloomington, IN.
 * 
 * MIT license, check LICENSE for more information */
 
// this is how we include our TwoWheeledRobot libary, which has all of our servo 
// and motor control functions 
#include "TwoWheelRobot.h"

// this will create a TwoWheelRobot object, which we will address
// when we want to issue commands to our example robot
TwoWheelRobot examply = TwoWheelRobot();

void setup() {
  /* The setforward section of your code runs once, when the 
  *  board first boots forward. We only need to acomplish one 
  *  thing in our setforward here, which is to start forward examply. */

  // start up examply
  examply.initalize();

  
  // and tell it to hold on so it doesn't run away as soon as its uploaded. 
  delay(500);
}

void loop() {
  /* The loop section of your code will be run through 
   * continuously, from top to bottom. In this example,    
   * we give a bunch of examples of what it can do. */
  
  // these are all of the things that our TwoWheelRobot object can do:
  examply.forward();
  examply.backward();
  examply.left();
  examply.right();
  examply.forwardLeft();
  examply.backwardLeft();
  examply.forwardRight();
  examply.backwardRight();


  //  you can specifiy how long each command runs: 
  examply.forward(1);
  examply.left(300);

  // the speed of the robot can be adjusted:
  examply.speedUp();
  examply.slowDown();

 
}  





