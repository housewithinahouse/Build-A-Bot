void checkTheSensors() {
  int edgeSensorValue = analogRead(edgeSensorPin);

  int distanceValue = sonar.ping_in(); // measure distance in inches. 
  Serial.println(distanceValue);

  //check the edge  sensor and find out if we are on the edge
  if (edgeSensorValue > edgeSensorThreshold){
    youAreOnTheEdge = true;
  }
  else{
    youAreOnTheEdge = false;
  }  

  if (distanceValue < distanceThreshold) {
    youCurrentlySeeTheOtherRobot = true;
  }
  else {
    youCurrentlySeeTheOtherRobot = false;
  }
}

void moveAwayFromEdge(){
   sumoBot.backward(500);
  sumoBot.left(1400);

  youAreOnTheEdge = false;    
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
