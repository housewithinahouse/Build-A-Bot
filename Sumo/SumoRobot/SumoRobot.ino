void setup() {
  delay(5000);
}

void loop() {

  checkTheSensors();

  if (youAreOnTheEdge) {
    moveAwayFromEdge();
  }
  else if (youCurrentlySeeTheOtherRobot) {
    chargeTheOtherRobot();
  }
  else {
    lookForTheOtherRobot();
  }

}

void checkTheSensors() {
  int ultrasonicValue = analogRead(ultrasonicSensorPin);
  int leftEdgeSensorValue = analogRead(leftEdgeSensorPin);
  int rightEdgeSensorValue = analogRead(rightEdgeSensorPin);

  if (ultrasonicValue > ultrasonicThreshold) {
    youCurrentlySeeTheOtherRobot = true;
  }
  else {
    youCurrentlySeeTheOtherRobot = false;
  }


//check the left sensor
  if (leftEdgeSensorValue < leftEdgeSensorThreshold){
    leftEdgeSensorIsOnTheEdge = true;
  }
  else{
    leftEdgeSensorisOnTheEdge = false;
  }

//check the right sensor
  if (rightEdgeSensorValue < rightEdgeSensorThreshold){
    rightEdgeSensorIsOnTheEdge = true;
  }
  else{
    rightEdgeSensorisOnTheEdge = false;
  }

  if(leftEdgeSensorIsOnTheEdge || rightEdgeSensorIsOnTheEdge){
    youAreOnTheEdge = true;
  }
  
}


