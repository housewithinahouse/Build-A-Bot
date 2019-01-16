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
int[] y = new int[400];
int avgVal = 600;

int linefeed = 10; // new line ASCII = 10


void setup() 
{
  size(400, 600);
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
  background(255);             // Set background to white
  print("Val:");
  println(val);
  if(val>avgVal){
    avgVal+=2;
  }
  else if(val<avgVal){
    avgVal-=2;
  }
  
  int mapY = int(map(val, 0, 1024, 0, 400));
  for (int i = y.length-1; i > 0; i--) {
    y[i] = y[i-1];
  }
  y[0] = height-mapY;
  println(y[0]);
  for (int i = 3; i < y.length; i++) {
   // stroke(int(map(i, 0, 500, 0, 255)), int(map(i, 0, 500, 255, 0)), 255); 
    line(i, y[i], i-1, y[i-1]);
  }
  //textSize(32);
  //text(avgVal, 300, 570); 
  delay(10);
}

void serialEvent (Serial myPort){
  String myString = myPort.readString();
  if (myString != null) 
  {
    // trim crap
    myString = trim(myString);
    val = int(myString); //make string to integer
    println(val);
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
