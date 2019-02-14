/* */

int sensorPin = A0; 
int lightPin = 3;
int lightTriggerLevel = 800;
int lightMaximumLevel = 600;

float rawRange = 1024; // 3.3v
float logRange = 5; // 3.3v = 10^5 lux (the max our sensor can measure)

void setup() {
 analogReference(EXTERNAL); //
 Serial.begin(9600);
 Serial.println("Responsive Plant Light Setup");
 pinMode(sensorPin, INPUT);
 pinMode(lightPin, OUTPUT);
}

void loop() {
  int rawValue = analogRead(sensorPin);
  if(rawValue<lightTriggerLevel){
    if(rawValue<lightMaximumLevel){
      analogWrite(lightPin, 255);
    }
    else{
      int lightLevel = map(lightTriggerLevel-rawValue, 0, lightTriggerLevel-lightMaximumLevel, 0, 255);
    }
    
  }

  Serial.print("Light Level in Area:");
  Serial.println(rawValue);
}

float RawToLux(int raw)
{
 float logLux = raw * logRange / rawRange;
 return pow(10, logLux);
}
