// this is the Drawy library, used to make it easier to work with our little drawing friend. 
// Let's go over the parts of this library and explain how they all work. 

// In order to prevent libraries from messing up if they get included more than once, 
// you gotta wrap the whole thing in this #ifndef then #define (if not defined then define) statement. 
#ifndef Drawy_h
#define Drawy_h

// While normal .ino sketches don't have to explictly include "Arduino.h", libraries do. 
#include "Arduino.h"

// I've also included the two libraries that we used for servo and motor control in those example sketches
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
    static int _default_segment_length;
    int _default_pause_length;
    void _stop();
    void _go(uint8_t l_cmd, uint8_t r_cmd);
  public: 
    Drawy();
    void initalize();
    void penUp();
    void penDown();
    void penCycle();
    void up(int segment_length = _default_segment_length);
    void down();
    void left();
    void right();
    void upLeft();
    void downLeft();
    void upRight();
    void downRight();
};

#endif
