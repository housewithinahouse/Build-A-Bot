import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port
int linefeed = 10; // new line ASCII = 10
int avgVal = 600;


void setup() 
{
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil(linefeed);
}

void draw()
{
  if(val>avgVal){
    avgVal+=5;
  }
  else if(val<avgVal){
    avgVal-=5;
  }
  background(map(avgVal,0,1024, 0, 255));
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
