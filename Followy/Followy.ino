/* 
 *  This is a very simple line following robot. 
 *  The only feature is that it rams up its speed 
 *  if it doesn't see a line. 
 *  
 *  Edwin Fallwell, MCPL 3/25/18
 */

// got to include the library to make the motorshield work
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// And connect 2 DC motors to port M3 & M4 !
Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(3);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(4);

// These vars hold the info about our speed
int currentSpeed = 0; 
int maxSpeed = 100;
int defaultSpeed = 60;

// These vars are used in line detection + logic.
int lineThreshold = 0; //set to something a little more logical. Testing will decide. 
bool lineDetectedFlag = false;

void setup() {
 // turn on motors
  L_MOTOR->setSpeed(0);
  L_MOTOR->run(RELEASE);

  R_MOTOR->setSpeed(0);
  R_MOTOR->run(RELEASE);

  // set the current speed to default. 
  currentSpeed = defaultSpeed;

}

void loop() {
  L_MOTOR->setSpeed(currentSpeed);
  R_MOTOR->setSpeed(currentSpeed);
  
  if((analogRead(A1) > lineThreshold) && (analogRead(A2) > lineThreshold)){
    //don't see no line at all
    L_MOTOR->run(FORWARD);
    R_MOTOR->run(FORWARD);
    lineDetectedFlag = false; 
  }
  else if((analogRead(A1) < lineThreshold) && (analogRead(A2) > lineThreshold)){
    //leftSensor detects line
    L_MOTOR->run(RELEASE);
    R_MOTOR->run(FORWARD);
    lineDetectedFlag = true; 
  }
  else if((analogRead(A1) > lineThreshold) && (analogRead(A2) < lineThreshold)){
    //rightSensor detects line
    L_MOTOR->run(FORWARD);
    R_MOTOR->run(RELEASE);
    lineDetectedFlag = true; 
  }
  else{
    //both see line/nothing
    L_MOTOR->run(RELEASE);
    R_MOTOR->run(RELEASE);
  }

  /* This part ramps up the speed until a line is detected. 
   * If a line is detected, drop the speed back down to default speed to avoid 
   * over shooting the line.
   */
  
  if(lineDetectedFlag){ //if we've detected a line
    currentSpeed = defaultSpeed; //slow back down
  }
  else{
    if(currentSpeed < maxSpeed){ //if we're going slower than max speed
      currentSpeed += 1; //accelerate by 1 
    }
  }
    
}
