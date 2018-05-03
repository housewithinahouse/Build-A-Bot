/* 
 *  This is a very simple line following robot. 
 *  If it sees a line, it moves the oposite wheel. 
 *  
 *  It is based on a handout by Matt Neer, 
 *  written by Edwin Fallwell for MCPL
 */

// got to include the library to make the motorshield work
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// And connect 2 DC motors to port M3 & M4 !
Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(3);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(4);

// Create names for each sensor 
int leftSensor = A2;
int rightSensor = A1;



// Create variables to store sensor readings
int rightSide, leftSide; 

void setup() {
  AFMS.begin();  // create with the default frequency 1.6KHz
  // turn on motors
  L_MOTOR->setSpeed(50);
  L_MOTOR->run(RELEASE);

  R_MOTOR->setSpeed(60);
  R_MOTOR->run(RELEASE);
 
 //set sensors to receive information
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
 
}

void loop() {
 //write value of left and right side to readings of each sensor 
  leftSide = analogRead(leftSensor);
  rightSide = analogRead(rightSensor);
 //test to see which sensor is over the line
 //then turn the opposite wheel to keep the line centered
    if(leftSide > rightSide){
      L_MOTOR->run(RELEASE);
      R_MOTOR->run(FORWARD);
//      delay(100);
    }

    if(rightSide > leftSide){
      L_MOTOR->run(FORWARD);
      R_MOTOR->run(RELEASE);
//      delay(100);
    }
}
