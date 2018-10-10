int analogSensorA = A1;

void setup()
{
  Serial.begin(9600);
  pinMode(analogSensorA, INPUT);
 // pinMode(analogSensorB, INPUT);
}

void loop() {

  Serial.print("Sensor A: ");
  Serial.println(analogRead(analogSensorA));
 // Serial.print("Sensor B: ");
//  Serial.println(analogRead(analogSensorB));
  delay(1000);
}
