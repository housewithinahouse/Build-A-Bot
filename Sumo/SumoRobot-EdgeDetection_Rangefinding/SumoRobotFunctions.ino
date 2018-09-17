void checkTheSensors() {
  int leftEdgeSensorValue = analogRead(leftEdgeSensorPin);
  int rightEdgeSensorValue = analogRead(rightEdgeSensorPin);
  int distanceValue = sonar.ping_in(); // measure distance in inches. 

  //check the edge left sensor and find out if our left side is on the edge
  if (leftEdgeSensorValue < leftEdgeSensorThreshold){
    leftEdgeSensorIsOnTheEdge = true;
  }
  else{
    leftEdgeSensorIsOnTheEdge = false;
  }

  //check the right edge sensor and find out our right side is on the edge
  if (rightEdgeSensorValue < rightEdgeSensorThreshold){
    rightEdgeSensorIsOnTheEdge = true;
  }
  else{
    rightEdgeSensorIsOnTheEdge = false;
  }

  // sets a var to true if either sensor is on the edge
  if(leftEdgeSensorIsOnTheEdge || rightEdgeSensorIsOnTheEdge){
    youAreOnTheEdge = true;
  }

  if (distanceValue < distanceThreshold) {
    youCurrentlySeeTheOtherRobot = true;
  }
  else {
    youCurrentlySeeTheOtherRobot = false;
  }
}

void moveAwayFromEdge(){
  if(leftEdgeSensorIsOnTheEdge){
    sumoBot.backward();
  }
  if(rightEdgeSensorIsOnTheEdge){
    sumoBot.backward();
  }

  youAreOnTheEdge = false;

  // note, this assumes that you're mounting the sensors in the
  // front. If you're mounting them in the rear, you'd need to use 
  // different logic.   
}

void chargeTheOtherRobot(){
  sumoBot.forward();
}

void lookForTheOtherRobot(){
  // this is where we set up the search pattern that 
  // the sumoBot will use to try and locate the other robot. 
  
  // our inital pattern is very simple: spin left. 
  sumoBot.left();

  // feel free to make your pattern more complicated,
  // and hopefully more effective. 
}
