#include <TwoWheelRobot.h>

// we include our TwoWheeledRobot libary, which has all of our motor control functions 
#include <TwoWheelRobot.h>

// create a TwoWheelRobot object, which we will address
// when we want to issue commands to our example robot
TwoWheelRobot bumpy = TwoWheelRobot();

void setup() {
  /* The setup section of your code runs once, when the 
  *  board first boots forward. We only need to acomplish one 
  *  thing in our setforward here, which is to start forward examply. */

  // start up the two wheel robot library
  bumpy.initalize();

  bumpy.setMovementMode(2);//have it move until being told to stop
  
  // and tell the robot to hold on for a little bit
  // (so it doesn't run away as soon as its code is uploaded.) 
  delay(500);
}

void loop() {
  // create a var to hold our "have I hit something?" state
  bool hasHitSomething = false;

  // and run a loop that will drive forward, looking for something
  // this while loop will continue to run forever
  while(!hasHitSomething){
    bumpy.forward();

    // unless it hits something...
    if(hitSomething()){
      hasHitSomething = true;
    }
  }
  
  // then it will back up for a bit and start over again
  bumpy.backwardLeft();
  delay(300);
}
