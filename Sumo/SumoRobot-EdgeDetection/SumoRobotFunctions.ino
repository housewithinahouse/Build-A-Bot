void checkTheSensors() {
  int edgeSensorValue = analogRead(edgeSensorPin);

  //check the edge  sensor and find out if we are on the edge
  if (edgeSensorValue > edgeSensorThreshold){
    youAreOnTheEdge = true;
  }
  else{
    youAreOnTheEdge = false;
  }  
}

void moveAwayFromEdge(){
  sumoBot.backward(500);
  sumoBot.left(1400);

  youAreOnTheEdge = false; 
}

void moveAroundTheArena(){
  sumoBot.forward();
}
