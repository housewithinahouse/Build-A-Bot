/* */

int sensorPin = A0; 
int lightPin = 3;

void setup() {
 analogReference(EXTERNAL); //
 Serial.begin(9600);
 Serial.println("Responsive Plant Light");
 pinMode(sensorPin, INPUT);
 pinMode(lightPin, OUTPUT);
}

void loop() {
  int rawValue = analogRead(sensorPin);
  analogWrite(map(rawValue, 0, 1024, 0, 255);

  Serial.print("Light Level in Area:");
  Serial.println(rawValue);
}

