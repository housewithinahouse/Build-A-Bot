// We've also attached a daughter board to our Feather. This additional board.
// also known as a Wing, or a Shield if we were using an Arduino need a
// library to drive it. 
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// And connect 2 DC motors to port M3 & M4 !
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
