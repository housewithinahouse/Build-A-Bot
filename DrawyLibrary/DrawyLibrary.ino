/*
 * This example code has been written by Edwin Fallwell + Matt Neer 
 * for the Monroe County Public Library in Bloomington, IN.
 * 
 * MIT license, check LICENSE for more information */
 
// this is how we include our Drawy libary, which has all of our servo 
// and motor control functions 
#include "Drawy.h"

// this will create a Drawy object, which we will address
// when we want to issue commands to drawy
Drawy drawy = Drawy();

void setup() {
  /* The setup section of your code runs once, when the 
  *  board first boots up. We only need to acomplish one 
  *  thing in our setup here, which is to start up drawy. */

  // start up drawy
  drawy.initalize();
}

void loop() {
  /* The loop section of your code will be run through 
   * continuously, from top to bottom. In this example,    
   * we will generate a random number and use it to pick 
   * drawy's movement, over and over again. */

  // generate a random number between 1 - 3 and store it 
  // in the variable "option"
  int option = random(1,3);

  // put the pen on the page
  drawy.penDown();
  
  // this is our switch statement. 
  switch(option)
  {
    
    //if option == 1
    case 1:
      drawy.up();
      drawy.left();
      drawy.down();
    break;

    //if option == 2
    case 2:
      drawy.down();
      drawy.left();
      drawy.up();
    break;

    //what to do if option doesn't match anything. 
    default:
      drawy.left();
  }

}  





