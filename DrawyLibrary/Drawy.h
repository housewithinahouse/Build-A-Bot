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
  public: 
    Drawy();
    void initalize();
    void penUp();
    void penDown();
};

#endif
