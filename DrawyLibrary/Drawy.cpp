#include "Arduino.h"
#include "Drawy.h"

Drawy::Drawy()
{
  // Set servo Pin
  _servopin = A0;
}

void Drawy::initalize(){
  

  _AFMS.begin();  // create with the default frequency 1.6KHz

  // turn on motors
  _L_MOTOR->setSpeed(0);
  _L_MOTOR->run(RELEASE);

  _R_MOTOR->setSpeed(0);
  _R_MOTOR->run(RELEASE);

  //Set up servo pin
  _servo.attach(_servopin);

  // Set variable for holding state of pen
  _penDown = false;
}

void Drawy::penUp(){
  _servo.write(180);
}

void Drawy::penDown(){
  _servo.write(130);
}

