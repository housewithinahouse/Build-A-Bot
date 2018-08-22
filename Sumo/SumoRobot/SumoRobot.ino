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

#include <TwoWheelRobot.h>

TwoWheelRobot sumoBot = TwoWheelRobot(); 


// we need 
int ultrasonicSensorPin = A0;
int leftEdgeSensorPin = A1;
int rightEdgeSensorPin = A2;

bool youAreOnTheEdge = false;
bool youCurrentlySeeTheOtherRobot = false;

int ultrasonicThreshold = 100;
int leftEdgeSensorThreshold, rightEdgeSensorThreshold = 400;

void setup() {
  sumoBot.initalize();
  delay(5000);
}




/*- - - - - - - - - - - - - - 
 *  This is the main body of our sketch, where we set up 
 *  the central loop that governs our robots behavior. 
 *  
 - - - - - - - - - - - - - - */

void loop() {

  checkTheSensors();

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
  int ultrasonicValue = analogRead(ultrasonicSensorPin);
  int leftEdgeSensorValue = analogRead(leftEdgeSensorPin);
  int rightEdgeSensorValue = analogRead(rightEdgeSensorPin);

  if (ultrasonicValue > ultrasonicThreshold) {
    youCurrentlySeeTheOtherRobot = true;
  }
  else {
    youCurrentlySeeTheOtherRobot = false;
  }

  //check the left sensor
  if (leftEdgeSensorValue < leftEdgeSensorThreshold){
    leftEdgeSensorIsOnTheEdge = true;
  }
  else{
    leftEdgeSensorisOnTheEdge = false;
  }

  //check the right sensor
  if (rightEdgeSensorValue < rightEdgeSensorThreshold){
    rightEdgeSensorIsOnTheEdge = true;
  }
  else{
    rightEdgeSensorisOnTheEdge = false;
  }

  if(leftEdgeSensorIsOnTheEdge || rightEdgeSensorIsOnTheEdge){
    youAreOnTheEdge = true;
  }
}

void moveAwayFromTheEdge(){
  if(leftEdgeSensorIsOnTheEdge){
    sumoBot.backwardRight();
  }
  if(rightEdgeSensorIsOnTheEdge){
    sumoBot.backwardLeft();
  }
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

