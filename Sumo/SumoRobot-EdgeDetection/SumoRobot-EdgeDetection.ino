/*
 * SumoBot! 
 * You're creating a rock'em sock'em fighting machine dedicated to just one goal: 
 * pushing the other robot over the edge while avoiding the same fate for yourself! 
 *
 * We'll be using Adafruit's Adabox002: Making Things Move, and some aditional parts:
 * an ultrasonic rangefinder, two ultraviolet edge dectectors, and a whole heap of foamcore,   
 * glue, and tape to create our robot warriors. 
 *
 * Below you'll find the code that makes it all tick, feel free to modifiy it for your own robot, 
 * battles can be won in code as much as in construction. Have fun!
 
 * sumoBot code by Edwin Fallwell + Matt Neer for the Monroe County Public Library in Bloomington, Indiana (2018). 
 * released under an MIT Liscense. 
 */

// this is a library for controling two wheeled robots
#include <TwoWheelRobot.h>

// we'll need to use 1 analog pin for this project
int edgeSensorPin = A0;


// a couple of vars to hold some information about our state
bool youAreOnTheEdge = false;
bool edgeSensorIsOnTheEdge = false;

// we've also got some numbers that we use as thresholds to measure 
// against the data from our sensors
int edgeSensorThreshold = 600;


// we need to create an sumobot object that we'll issue commands to
TwoWheelRobot sumoBot = TwoWheelRobot(); 

// below is a flowchart of the robot's behavior.
// start at setup, which runs only once, and then proceed to 
// loop around, asking the questions and following the arrows. 
/*

setup
|
├------------------------┐
|                        |
└>CHECK the sensors-┐    └--------------------┬-┐
┌-------------------┘                         | | 
|                                             | | 
└>ask "am I on the edge?"                     | | 
    yes--->MOVE away from edge----------------┘ | 
    no--------->MOVE around the arena-----------┘

*/
// and that it, that's the core of our whole program. 
// With this, we can avoid the edge and destory our foes
// utterly if they happen to be in our way.  
// Let's go over it in more detail:


void setup() {
  // in our setup phase we initalize our robot,
  // which sets up some properties like speed
  // and then delay for 5 seconds so that the robot 
  // doesn't just run away as soon as we turn it on. 
  sumoBot.initalize();
  delay(5000);
}

void loop() {
  // our loop follows the flow chart we outlined above. 
  // first we: 
  checkTheSensors();

  //and then:
  if (youAreOnTheEdge) {
    moveAwayFromEdge();
  }
  else {
    moveAroundTheArena();
  }
  
  
}

void checkTheSensors() {
  int edgeSensorValue = analogRead(edgeSensorPin);

  //check the edge left sensor and find out if our left side is on the edge
  if (edgeSensorValue > edgeSensorThreshold){
    youAreOnTheEdge = true;
  }
  else{
    youAreOnTheEdge = false;
  }
  
}

void moveAwayFromEdge(){
  sumoBot.backward(500);
  sumoBot.left(14
  00);

  youAreOnTheEdge = false; 
}

void moveAroundTheArena(){
  sumoBot.forward();
}
