#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Drawy
{
  private:
   Adafruit_MotorShield _AFMS;  
   Servo _servo;
  public: 
    Drawy(Adafruit_MotorShield AFMS, Servo servo);
    void penUp();
    void penDown();
};

#endif
