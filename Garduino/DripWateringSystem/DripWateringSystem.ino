const int moistureSensorPin = A2;
const int waterSolenoidPin = 3;

byte moistureLevel = 0;

bool waterUntilFull = false;

unsigned long currentMillis = 0;

unsigned long previousWateringMillis = 0;
unsigned long wateringStartTime = 0;



void setup() {
  // put your setup code here, to run once:
  pinMode(waterSolenoidPin, OUTPUT);
  pinMode(moistureSensorPin, INPUT);
}

void loop() {
// measure moisture
  int lowerMoistureSensorThreshold = 100; //out of 1024
  int upperMoistureSensorThreshold = 150; //out of 1024
  byte moistureLevel = map(analogRead(moistureSensorPin),lowerMoistureSensorThreshold, upperMoistureSensorThreshold, 0, 255);

  const long wateringInterval = 10000;
  byte wateringThreshold = 20;
  if ((moistureLevel < wateringThreshold) && (currentMillis - previousWateringMillis >= wateringInterval)){
    waterUntilFull = true;
    previousWateringMillis = currentMillis;
  }
  else{
    waterUntilFull = false;
  }

  const long wateringLength = 100;
  if(waterUntilFull && (currentMillis - wateringStartTime >= wateringLength){
    digitalWrite(3, HIGH);
    wateringStartTime = currentMillis;
  }
  else{
    digitalWrite(3,LOW);
  }
}
