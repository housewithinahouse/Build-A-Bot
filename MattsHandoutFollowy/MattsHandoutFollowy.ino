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



int rightSide, leftSide; 

int leftSensor = A0;
int rightSensor = A1;


void setup() {
 AFMS.begin();  // create with the default frequency 1.6KHz
  
  // turn on motors
  L_MOTOR->setSpeed(60);
  L_MOTOR->run(RELEASE);

  R_MOTOR->setSpeed(60);
  R_MOTOR->run(RELEASE);

  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);

}

void loop() {
  leftSide = leftSensor;
  rightSide = rightSensor;

    if(leftSide > rightSide){
      L_MOTOR->run(RELEASE);
      R_MOTOR->run(FORWARD);
      delay(30);
    }

    if(rightSide > leftSide){
      L_MOTOR->run(FORWARD);
      R_MOTOR->run(RELEASE);
      delay(30);
    }
  
    
}
