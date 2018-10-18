
//one nail to 5v and the other to A0 w/ resistor
int moistureSensor = A0;

//storage variable
int moisture = 0;

//optimal moisture range
int high = 150;
int low = 100;

//indicator LED
int led = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(moistureSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  moisture = analogRead(moistureSensor);
  Serial.print("Moisture level: ");
  Serial.println(moisture);
  if (moisture > low && moisture < high){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }
  delay(1000);
}
