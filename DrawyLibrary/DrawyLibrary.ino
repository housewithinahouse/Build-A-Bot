/*********************************************************************
  
  This example code has been written by Edwin Fallwell + Matt Neer for the Monroe County Public Library in Bloomington, IN.
  It uses the Adafruit Motor Library for most of its functions. 

  MIT license, check LICENSE for more information
*********************************************************************/

#include <Arduino.h>
#include "Drawy.h"

Drawy drawy = Drawy();

void setup(void)
{
  drawy.initalize();
}

void loop(void)
{
  drawy.penUp();
  delay(200);
  drawy.penDown();
  delay(200);
}  





