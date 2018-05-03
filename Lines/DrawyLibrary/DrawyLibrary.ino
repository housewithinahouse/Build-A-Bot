o/*
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

  // put the pen on the page
  drawy.penDown();

  // generate a random number between 1 - 3 and store it 
  // in the variable "option"
  int option = random(1,3);
  
  // this is our switch statement. A switch statement takes an input, in this case
  // the random number we generated eariler and stored as "option". Then executes
  // which ever case matches 
  switch(option)
  {
    
    
    case 1: //if option == 1
      //our drawing bot has 8 basic wheel movements they are:
      drawy.up();
      drawy.down();
      drawy.left();
      drawy.right();
      drawy.upLeft();
      drawy.downLeft();
      drawy.upRight();
      drawy.downRight();
    break; 
   
    case 2: //if option == 2
      //you can use these in any order you want, and use as many or as few as you choose
      drawy.down();
      drawy.left();
      drawy.up();
    break;
        
    default: //what to do if option doesn't match anything. 
      drawy.left();  //some times, however, you gotta take a page from NASCAR's book. 
  }

}  





