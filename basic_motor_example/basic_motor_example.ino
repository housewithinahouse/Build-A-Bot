// We've also attached a daughter board to our Feather. This additional board.
// also known as a Wing, or a Shield if we were using an Arduino, needs a
// library to drive it. This statement includes this library so that we have access to
// it in the rest of our program. 
#include <Adafruit_MotorShield.h>

// We need to create an object representing the Adafruit Motor Shield. We do this by
// creating an object of the type "Adafruit_MotorShield" named AFMS. 
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// We're also creating two objects of the type "Adafruit_DCMotor", one for each of the 
// motors on our drawing robot. 
Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(3);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(4);

void setup() {
  // put your setup code here, to run once:
   AFMS.begin();  // create with the default frequency 1.6KHz

    // turn on motors
  L_MOTOR->setSpeed(0);
  L_MOTOR->run(RELEASE);

  R_MOTOR->setSpeed(0);
  R_MOTOR->run(RELEASE);
}

void loop() {
  L_MOTOR->setSpeed(100);
  R_MOTOR->setSpeed(100);
  L_MOTOR->run(BACKWARD);
  R_MOTOR->run(FORWARD);
}
