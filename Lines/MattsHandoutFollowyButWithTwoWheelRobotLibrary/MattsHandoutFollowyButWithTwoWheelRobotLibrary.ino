#include "TwoWheelRobot.h"
TwoWheelRobot examply = TwoWheelRobot();


int leftSensor = A2;
int rightSensor = A1;

void setup() {
  examply.initalize();
    
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
}

void loop() {  
  leftSide = analogRead(leftSensor);
  rightSide = analogRead(rightSensor);
  
  if(leftSide > rightSide){
      examply.forwardRight(1);
  }

  if(rightSide > leftSide){
    examply.forwardLeft(1);
  }  

 
}  





