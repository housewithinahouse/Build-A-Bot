
// This is a library for our ultrasonic sensor:
#include <NewPing.h>

// A NewPing object needs three things:
int ultrasonicTriggerPin = 21;
int ultrasonicRecieverPin = 22;
int maxUltrasonicRange = 200;

// we'll name ours sonar:
NewPing sonar(ultrasonicTriggerPin, ultrasonicRecieverPin, maxUltrasonicRange);

// NewPing doesn't require any setup, but Serial does:
void setup() {
  Serial.begin(9600);
}

// and NewPing is quite easy to call. 
// We just ask it for the distance in inches
void loop() {
  int distanceValue = sonar.ping_in(); // measure distance in inches. 
  Serial.println("Distance in Inches: ");
  Serial.print(distanceValue);
  delay(1000);
}
