#ifndef Drawy_h
#define Drawy_h

#include "Arduino.h"
#include <Adafruit_MotorShield.h>
#include <Servo.h>

class Drawy
{
  private:
    Adafruit_MotorShield _AFMS = Adafruit_MotorShield();;  
    Servo _servo;
    Adafruit_DCMotor *_L_MOTOR = _AFMS.getMotor(3);
    Adafruit_DCMotor *_R_MOTOR = _AFMS.getMotor(4);
    int _servopin;
    bool _penDown;
    int _l_speed;
    int _r_speed;
    int _default_segment_length;
    int _default_pause_length;
    void _stop();
    void _go(uint8_t l_cmd, uint8_t r_cmd);
  public: 
    Drawy();
    void initalize();
    void penUp();
    void penDown();
    void penCycle();
    void up();
    void down();
    void left();
    void right();
    void up_diagonal_left();
    void down_diagonal_left();
    void up_diagonal_right();
    void down_diagonal_right();
};

#endif
