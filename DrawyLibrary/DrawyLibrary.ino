/*********************************************************************
  
  This example code has been written by Edwin Fallwell + Matt Neer for the Monroe County Public Library in Bloomington, IN.

  MIT license, check LICENSE for more information
*********************************************************************/

#include <Arduino.h>
#include "Drawy.h"

Drawy drawy = Drawy();

void setup()
{
  drawy.initalize();
}

void loop()
{
  for(int i = 0; i<100; i++)
  {
    int option = random(1,3);
    switch(option)
    {
      case 1:
        drawy.up();
        drawy.left();
        drawy.down();
      break;
      
      case 2:
        drawy.down();
        drawy.left();
        drawy.up();
      break;
      
      default:
        drawy.left();
    }
  }
}  





