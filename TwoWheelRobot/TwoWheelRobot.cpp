/** if you've not already looked at TwoWheelRobot.h before this, I'd recomend starting there... **/




#include "Arduino.h"
#include "TwoWheelRobot.h"

int TwoWheelRobot::_default_segment_length = 150;

TwoWheelRobot::TwoWheelRobot()
{
  // Set speed
  _l_speed = 60;
  _r_speed = 60;

  // Delay Lengths
  _default_pause_length = 50;
}

void TwoWheelRobot::initalize(){
  // start motorshield 
  _AFMS.begin();

  // turn on motors
  _L_MOTOR->setSpeed(0);
  _L_MOTOR->run(RELEASE);

  _R_MOTOR->setSpeed(0);
  _R_MOTOR->run(RELEASE);
}

// Movement building blocks
void TwoWheelRobot::_stop()
{
  _L_MOTOR->run(RELEASE);
  _R_MOTOR->run(RELEASE);
  delay(_default_pause_length);
}

void TwoWheelRobot::_go(uint8_t l_cmd, uint8_t r_cmd)
{
  _L_MOTOR->setSpeed(_l_speed);
  _R_MOTOR->setSpeed(_r_speed);
  _L_MOTOR->run(l_cmd);
  _R_MOTOR->run(r_cmd);
}

// Basic movements
void TwoWheelRobot::forward(int segment_length = _default_segment_length) 
{
  _go(FORWARD, FORWARD);
  delay(segment_length);
  _stop();
}

void TwoWheelRobot::backward(int segment_length = _default_segment_length) 
{
  _go(BACKWARD, BACKWARD);
  delay(segment_length);
  _stop();
}

void TwoWheelRobot::right(int segment_length = _default_segment_length) 
{
  _go(FORWARD, BACKWARD);
  delay(segment_length);
  _stop();
}

void TwoWheelRobot::left(int segment_length = _default_segment_length) 
{
  _go(BACKWARD, FORWARD);
  delay(segment_length);
  _stop();
}

void TwoWheelRobot::backwardRight(int segment_length = _default_segment_length) 
{
  _go(RELEASE, BACKWARD);
  delay(segment_length);
  _stop();
}

void TwoWheelRobot::forwardRight(int segment_length = _default_segment_length) 
{
  _go(RELEASE, FORWARD);
  delay(segment_length);
  _stop();
}

void TwoWheelRobot::backwardLeft(int segment_length = _default_segment_length) 
{
  _go(BACKWARD, RELEASE);
  delay(segment_length);
  _stop();
}

void TwoWheelRobot::forwardLeft(int segment_length = _default_segment_length) 
{
  _go(FORWARD, RELEASE);
  delay(segment_length);
  _stop();
}

