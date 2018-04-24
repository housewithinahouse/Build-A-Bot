/*
 * This example code has been written by Edwin Fallwell + Matt Neer 
 * for the Monroe County Public Library in Bloomington, IN.
 * 
 * MIT license, check LICENSE for more information */
 
// this is how we include our Drawy libary, which has all of our servo 
// and motor control functions 
#include "TwoWheelRobot.h"

// this will create a Drawy object, which we will address
// when we want to issue commands to examply
TwoWheelRobot examply = TwoWheelRobot();

void setup() {
  /* The setup section of your code runs once, when the 
  *  board first boots up. We only need to acomplish one 
  *  thing in our setup here, which is to start up examply. */

  // start up examply
  examply.initalize();
}

void loop() {
  /* The loop section of your code will be run through 
   * continuously, from top to bottom. In this example,    
   * we will generate a random number and use it to pick 
   * examply's movement, over and over again. */
  examply.up();
  examply.down();
  examply.left();
  examply.right();
  examply.upLeft();
  examply.downLeft();
  examply.upRight();
  examply.downRight();

   
  }

}  





