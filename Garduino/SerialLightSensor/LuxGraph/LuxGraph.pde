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
  for (int i = y.length-1; i > 0; i--) {
    y[i] = 700;
  }
}

void draw()
{
  background(20);//map(val, 0, 1025, 10, 240));             // Set background to gray
  
  // add rules
  stroke(255);
  strokeWeight(1);
  int lineOffset = 40;
  line(lineOffset, height-500, width, height-500);
  line(lineOffset, height-450, width, height-450);
  line(lineOffset, height-400, width, height-400);
  line(lineOffset, height-350, width, height-350);
  line(lineOffset, height-300, width, height-300);
  line(lineOffset, height-250, width, height-250);
  line(lineOffset, height-200, width, height-200);
  line(lineOffset, height-150, width, height-150);
  line(lineOffset, height-100, width, height-100);
  line(lineOffset, height-50, width, height-50);
  
  // label axis
  fill(255);
  textSize(11);
  text("lux",8, height -20);
  
  // add legend
  textSize(10);
  text("50000", 5, height-497);
  text("24000", 5, height-447); 
  text(" 8500", 5, height-397);  
  text(" 2800", 5, height-347);  
  text("  850", 5, height-297);  
  text("  275", 5, height-247);  
  text("  100", 5, height-197);  
  text("    30", 5, height-147);  
  text("    10", 5, height-97);  
  text("     3", 5, height-47);  
  
  // main graph
  int mapY = int(map(val, 0, 1024, 0, 512));
  for (int i = y.length-1; i > 0; i--) {
    y[i] = y[i-1];
  }
  y[0] = height-mapY;
  for (int i = 3; i < y.length; i++) {
    if(y[i] < height-420){
      stroke(0,255,50, 150);
    }
    else{
      stroke(255,50,0, 150);
      
    }
    strokeWeight(2);
    line(i, y[i], i-1, y[i-1]);
    
  }
  
  //target green area
  fill(0,255, 50, 40);
  noStroke();
  rect(0, height-450, width, 40);
  
  //so it doesn't race away
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
