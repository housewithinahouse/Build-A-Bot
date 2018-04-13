int rightSensor = A1;

void setup()
{
  Serial.begin(9600);
  Serial.println("Adafruit Bluefruit Robot Controller Example");
  pinMode(rightSensor, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(rightSensor));
  
}
