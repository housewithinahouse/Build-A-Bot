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

// we'll need to use four different pins for this project, 2 analog and 3 digital
int ultrasonicTriggerPin = 20;
int ultrasonicRecieverPin = 21;
int edgeSensorPin = A1;
int buttonPin = 18;

// we also need to set the max distance that we want to scan at
// this number should be less than 400
int maxUltrasonicRange = 200;

// a couple of vars to hold some information about our state
bool youAreOnTheEdge = false;
bool edgeSensorIsOnTheEdge = false;
bool buttonHasBeenPushed = false;
bool youCurrentlySeeTheOtherRobot = false;

// we've also got some numbers that we use as thresholds to measure 
// against the data from our sensors
int edgeSensorThreshold = 700;
int distanceThreshold = 12;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

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
  sumoBot.initalize();
   Serial.begin(9600);
}

void loop() {
  // we need to check first if the button has been pushed. 
  // If the button has been pushed, then we wait 5 seconds and 
  // switch over to the main loop. Otherwise, we just keep
  // waiting to see if it get gets pushed. 
  int buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    buttonHasBeenPushed = true;
    delay(5000);
  }
  // after the button has been pushed, the code below will loop over
  // and over again. Until the button has been pushed it will be ignored. 
  while(buttonHasBeenPushed){
    // our loop follows the flow chart we outlined above. 
    // first we: 
    checkTheSensors();
  
    //and then:
    if (youAreOnTheEdge) {
      moveAwayFromEdge();
      Serial.println("move from edge");
    }
    else if (youCurrentlySeeTheOtherRobot) {
      chargeTheOtherRobot();
      Serial.println("charging");
    }
    else {
      lookForTheOtherRobot();
      Serial.println("looking");
    }  
  }
}

/*
 * something to note about the ultrasonic rangefinders we're using, 
 * we'll need to hook them up to the 5v rail, and use a voltage divider 
 * on the output. Google "3.3 v ultrasonic sensor voltage divider" for 
 * instructions. 
 */

