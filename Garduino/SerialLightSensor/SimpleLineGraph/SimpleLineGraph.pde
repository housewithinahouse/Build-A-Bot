/**
 * Simple Read
 * 
 * Read data from the serial port and change the color of a rectangle
 * when a switch connected to a Wiring or Arduino board is pressed and released.
 * This example works with the Wiring / Arduino program that follows below.
 */


import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port
int[] y = new int[1000];
int avgVal = 600;

int linefeed = 10; // new line ASCII = 10


void setup() 
{
  size(1000, 600);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil(linefeed);
}

void draw()
{
  background(125);             // Set background to gray
  
  stroke(255);
  strokeWeight(1);
  fill(0,255, 50);
  //rect(0, height-450, width);
  line(50, height-450, width, height-450);
  line(50, height-400, width, height-400);
  line(50, height-350, width, height-350);
  line(50, height-300, width, height-300);
  line(50, height-250, width, height-250);
  line(50, height-200, width, height-200);
  line(50, height-150, width, height-150);
  
  textSize(10);
  stroke(255);
  text("24000", 10, height-450);
  
  text(" 8500", 10, height-400);
  
  text(" 2800", 10, height-350);
  
  text("  850", 10, height-300);
  
  text("  275", 10, height-250);
  
  text("  100", 10, height-200);
  
  text("   30", 10, height-150);
  
  
  stroke(0);
  int mapY = int(map(val, 0, 1024, 0, 512));
  for (int i = y.length-1; i > 0; i--) {
    y[i] = y[i-1];
  }
  y[0] = height-mapY;
  for (int i = 3; i < y.length; i++) {
    stroke(255,50,0, 200); 
    strokeWeight(2);
    line(i, y[i], i-1, y[i-1]);
  }
  
  
  
  delay(10);
}

void serialEvent (Serial myPort){
  String myString = myPort.readString();
  if (myString != null) 
  {
    // trim crap
    myString = trim(myString);
    val = int(myString); //make string to integer
  }
}


/*
 int mapY = int(map(val, 0, 1024, 0, 400));
  for (int i = y.length-1; i > 0; i--) {
    y[i] = y[i-1];
  }
  y[0] = mapY;
  println(y[0]);
  for (int i = 3; i < y.length; i++) {
    stroke(int(map(i*4, 0, 500, 0, 255)), int(map(y[i]*4, 0, 500, 255, 0)), 255); 
    ellipse(i*8, 250, y[i]/2, y[i]/2); //y[i-1]
  }
  textSize(32);
  text(avgVal, 300, 570); 
  delay(100);

*/
