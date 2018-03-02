#include "Arduino.h"
#include "Drawy.h"

Drawy::Drawy()
{
  // Set servo Pin
  _servopin = A0;

  // Set speed
  _l_speed = 60;
  _r_speed = 60;

  // Delay Lengths
  _default_segment_length = 150;
  _default_pause_length = 50;
}

void Drawy::initalize(){
  // start motorshield 
  _AFMS.begin();

  // turn on motors
  _L_MOTOR->setSpeed(0);
  _L_MOTOR->run(RELEASE);

  _R_MOTOR->setSpeed(0);
  _R_MOTOR->run(RELEASE);

  // Set up servo pin
  _servo.attach(_servopin);

  // Set variable for holding state of pen
  _penDown = false;
}

// Pen Movements
void Drawy::penUp()
{
  _servo.write(130);
  _penDown = true;
}

void Drawy::penDown()
{
  _servo.write(180);
  _penDown = false;
}

void Drawy::penCycle() 
{
  _penDown ? penUp() : penDown(); 
}


// Movement building blocks
void Drawy::_stop()
{
  _L_MOTOR->run(RELEASE);
  _R_MOTOR->run(RELEASE);
  delay(_default_pause_length);
}

void Drawy::_go(uint8_t l_cmd, uint8_t r_cmd)
{
  _L_MOTOR->setSpeed(_l_speed);
  _R_MOTOR->setSpeed(_r_speed);
  _L_MOTOR->run(l_cmd);
  _R_MOTOR->run(r_cmd);
}

// Basic movements
void Drawy::up() 
{
  _go(FORWARD, FORWARD);
  delay(_default_segment_length);
  _stop();
}

void Drawy::down() 
{
  _go(BACKWARD, BACKWARD);
  delay(_default_segment_length);
  _stop();
}

void Drawy::right() 
{
  _go(FORWARD, BACKWARD);
  delay(_default_segment_length);
  _stop();
}

void Drawy::left() 
{
  _go(BACKWARD, FORWARD);
  delay(_default_segment_length);
  _stop();
}

void Drawy::downDiagonalRight() {
  _go(RELEASE, BACKWARD);
  delay(_default_segment_length);
  _stop();
}
void Drawy::upDiagonalRight() {
  _go(RELEASE, FORWARD);
  delay(_default_segment_length);
  _stop();
}

void Drawy::downDiagonalLeft() {
  _go(BACKWARD, RELEASE);
  delay(_default_segment_length);
  _stop();
}

void Drawy::upDiagonalLeft() {
  _go(FORWARD, RELEASE);
  delay(_default_segment_length);
  _stop();
}

