// this is the library that makes servos easy to work with
// we need to "include" it to have access to it in our program
#include <Servo.h>

// this will create a Servo object, which we will address
// when we want to issue commands to the servo
Servo my_servo;

void setup() {
  /* The setup section of your code runs once, when the 
  *  board first boots up. We only need to acomplish one 
  *  thing in our setup here, which is to attach the Servo
  *  object to a pin so it knows where to ourput to. */
  
  //tell the "Servo" object what pin to output to
  my_servo.attach(A0);
}

void loop() {
  /* The loop section of your code will be run through 
   * continuously, from top to bottom. In this example,    
   * we will rotate our servo from 0 to 180 degrees, back
   * and forth, forever. There is a one second pause between
   * rotations. */
  
  //set the servo to 0 degrees
  my_servo.write(0);
  
  //wait 1 second
  delay(1000);
  
  //set the servo to 180 degrees
  my_servo.write(180);
  
  //wait 1 second
  delay(1000);  
}
