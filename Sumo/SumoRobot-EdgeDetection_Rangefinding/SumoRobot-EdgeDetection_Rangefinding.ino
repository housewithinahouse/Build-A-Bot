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

// and this is a library for our ultrasonic sensor
#include <NewPing.h>

// we'll need to use four different pins for this project, 2 analog and 2 digital
int ultrasonicTriggerPin = 21;
int ultrasonicRecieverPin = 22;
int leftEdgeSensorPin = A0;
int rightEdgeSensorPin = A1;

// we also need to set the max distance that we want to scan at
// this number should be less than 400
int maxUltrasonicRange = 200;

// a couple of vars to hold some information about our state
bool youAreOnTheEdge = false;
bool leftEdgeSensorIsOnTheEdge, rightEdgeSensorIsOnTheEdge = false;
bool youCurrentlySeeTheOtherRobot = false;

// we've also got some numbers that we use as thresholds to measure 
// against the data from our sensors
int distanceThreshold = 36;
int leftEdgeSensorThreshold, rightEdgeSensorThreshold = 400;

// we need to create an sumobot object that we'll issue commands to
TwoWheelRobot sumoBot = TwoWheelRobot(); 

// and a NewPing object that we use to control our ultrasonic sensor
NewPing sonar(ultrasonicTriggerPin, ultrasonicRecieverPin, maxUltrasonicRange);


// below is a flowchart of the robot's behavior.
// start at setup, which runs only once, and then proceed to 
// loop around, asking the questions and following the arrows. 
/*

setup
|
├------------------------┐
|                        |
└>CHECK the sensors-┐    └--------------------┬-┬-┐
┌-------------------┘                         | | |
|                                             | | |
└>ask "am I on the edge?"                     | | |
    yes--->MOVE away from edge----------------┘ | |
    no--┐                                       | | 
        |                                       | |
        └->ask "can I see the other robot?"     | |
            yes->CHARGE the other robot---------┘ |
            no-->LOOK for the other robot---------┘

*/
// and that it, that's the core of our whole program. 
// With this, we can locate our foes and destory 
// them utterly.  Let's go over it in more detail:


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
  else if (youCurrentlySeeTheOtherRobot) {
    chargeTheOtherRobot();
  }
  else {
    lookForTheOtherRobot();
  }
  
  
}

void checkTheSensors() {
  int leftEdgeSensorValue = analogRead(leftEdgeSensorPin);
  int rightEdgeSensorValue = analogRead(rightEdgeSensorPin);
  int distanceValue = sonar.ping_in(); // measure distance in inches. 

  //check the edge left sensor and find out if our left side is on the edge
  if (leftEdgeSensorValue < leftEdgeSensorThreshold){
    leftEdgeSensorIsOnTheEdge = true;
  }
  else{
    leftEdgeSensorIsOnTheEdge = false;
  }

  //check the right edge sensor and find out our right side is on the edge
  if (rightEdgeSensorValue < rightEdgeSensorThreshold){
    rightEdgeSensorIsOnTheEdge = true;
  }
  else{
    rightEdgeSensorIsOnTheEdge = false;
  }

  // sets a var to true if either sensor is on the edge
  if(leftEdgeSensorIsOnTheEdge || rightEdgeSensorIsOnTheEdge){
    youAreOnTheEdge = true;
  }

  if (distanceValue < distanceThreshold) {
    youCurrentlySeeTheOtherRobot = true;
  }
  else {
    youCurrentlySeeTheOtherRobot = false;
  }
}

void moveAwayFromEdge(){
  if(leftEdgeSensorIsOnTheEdge){
    sumoBot.backward();
  }
  if(rightEdgeSensorIsOnTheEdge){
    sumoBot.backward();
  }

  youAreOnTheEdge = false;

  // note, this assumes that you're mounting the sensors in the
  // front. If you're mounting them in the rear, you'd need to use 
  // different logic.   
}

void chargeTheOtherRobot(){
  sumoBot.forward();
}

void lookForTheOtherRobot(){
  // this is where we set up the search pattern that 
  // the sumoBot will use to try and locate the other robot. 
  
  // our inital pattern is very simple: spin left. 
  sumoBot.left();

  // feel free to make your pattern more complicated,
  // and hopefully more effective. 
}

/*
 * something to note about the ultrasonic rangefinders we're using, 
 * we'll need to hook them up to the 5v rail, and use a voltage divider 
 * on the output. Google "3.3 v ultrasonic sensor voltage divider" for 
 * instructions. 
 */

