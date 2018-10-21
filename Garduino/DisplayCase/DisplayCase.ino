#include "FastLED.h"
#include <LiquidCrystal.h>

#define NUM_WATER_LEDS    16
CRGB waterLEDs[NUM_WATER_LEDS];

#define NUM_LIGHT_LEDS    6
CRGB lightLEDs[NUM_LIGHT_LEDS];

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int waterPumpPin = 2;
const int waterSolenoidPin = 3;
const int waterLEDPin = 4; 
const int solarLEDPin = 5; 
const int moistureLEDPin = 6;
const int waterLightSensorPin = A0;
const int solarLightSensorPin = A1;
const int moistureSensorPin = A2;

int gHue = 0;

int moistureLevel = 0;
int realMoistureLevel = 0;

int cycle = 0;

int waterLightSensorThreshold = 600; 
int solarLightSensorThreshold = 600;
int lowerMoistureThreshold = 100;
int upperMoistureThreshold = 150;

bool evenCycle = false;
bool waterUntilFull = false;
bool waterLightSensorTriggered = false;
bool solarLightSensorTriggered = false;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, waterLEDPin>(waterLEDs, NUM_WATER_LEDS); 
  FastLED.addLeds<NEOPIXEL, solarLEDPin>(lightLEDs, NUM_LIGHT_LEDS); 
  setLEDBrightness(50); 

  lcd.begin(16, 2);

  pinMode(waterPumpPin, OUTPUT);
  pinMode(waterSolenoidPin, OUTPUT);
  pinMode(waterLightSensorPin, INPUT);
  pinMode(solarLightSensorPin, INPUT);
  pinMode(moistureSensorPin, INPUT);
}

void loop(){
 // checkTheSensors();
  if(waterLightSensorTriggered||waterUntilFull){
    waterLEDshow();
    lcd.print("LED SHOW RUNNING");
  }
  else{
    waterLEDDecay();
    Serial.println("water LED show not running");
  }
 if(solarLightSensorTriggered){
 //   solarLED();
 }
 else{
 //   solarLEDDecay();
 }

 // moistureLED();

  FastLED.show();
  
  decreaseMoisture();
  if(moistureLevel<=0){
    waterUntilFull=true;
  }
  else if(moistureLevel>200){
    waterUntilFull=false;
  }

  //displayLCDStuff();
  
  //flip flop the cycle ticker
  evenCycle = !evenCycle;

  //increase the actual cycle count
  cycle++;
}

void setLEDBrightness(int brightness){
  brightness = constrain(brightness, 0, 100);
  FastLED.setBrightness(brightness);
}

void checkTheSensors(){
  int waterLightSensorValue = analogRead(waterLightSensorPin);
  int solarLightSensorValue = analogRead(solarLightSensorPin);
  
  if(waterLightSensorValue > waterLightSensorThreshold){
    waterLightSensorTriggered = true;
  }
  else{
    waterLightSensorTriggered = false;
  }

  if(solarLightSensorValue > solarLightSensorThreshold){
    solarLightSensorTriggered = true;
  }
  else{
    solarLightSensorTriggered = false;
  }

  realMoistureLevel = map(analogRead(moistureSensorPin),lowerMoistureThreshold, upperMoistureThreshold, 0, 255);
  
}

void decreaseMoisture(){
  moistureLevel-=1;
  moistureLevel = constrain(moistureLevel, 0, 255);
  Serial.println(moistureLevel);
   
}


void waterLEDshow(){
  int waterHueStart = 166;
  int waterHueRange = 30;
  
  if(cycle%5==1){
    for(int i = 0; i < NUM_WATER_LEDS; i++){
      if((!evenCycle && i%2==1)||(evenCycle && i%2!=1)){
        waterLEDs[i]=CRGB::White;
        Serial.println("even_cycle");
      }
      else{
        waterLEDs[i]= CHSV(random(waterHueStart, waterHueStart+waterHueRange),255,255); 
      }
    }
  }
  moistureLevel+=2;
}

void waterLEDDecay(){
  fadeToBlackBy(waterLEDs, NUM_WATER_LEDS, 10);
}


//void cycleColors(int colorStart, int colorRange){
//  for(int i = 0; i < NUM_LEDS; i++){
//       leds[i] = CHSV( (gHue%colorRange)+colorStart, 255, 255);
//       gHue += 1;
//       delay(10);
//       FastLED.show();
//    }
//}
