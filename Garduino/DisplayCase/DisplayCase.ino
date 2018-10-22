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
const int moistureDecreaseSpeedPin = A3;

int gHue = 0;

int moistureLevel = 0;
int realMoistureLevel = 0;
int moistureDecreaseSpeed = 251;

int cycle = 0;

int waterLightSensorThreshold = 300; 
int solarLightSensorThreshold = 300;
int lowerMoistureThreshold = 100;
int upperMoistureThreshold = 150;

bool evenCycle = false;
bool waterUntilFull = false;
bool waterLightSensorTriggered = false;
bool solarLightSensorTriggered = false;

byte waterdropEmpty[8] = {
  0b00100,
  0b00100,
  0b01010,
  0b01010,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};

byte waterdropFilled[8] = {
  0b00100,
  0b00100,
  0b01110,
  0b01110,
  0b11111,
  0b11111,
  0b01110,
  0b00000
};

byte sunEmpty[8] = {
  0b00000,
  0b10101,
  0b01110,
  0b10001,
  0b10001,
  0b01110,
  0b10101,
  0b00000
};

byte sunFilled[8] = {
  0b00000,
  0b10101,
  0b01110,
  0b11111,
  0b11111,
  0b01110,
  0b10101,
  0b00000
};


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, waterLEDPin>(waterLEDs, NUM_WATER_LEDS); 
  FastLED.addLeds<NEOPIXEL, solarLEDPin>(lightLEDs, NUM_LIGHT_LEDS); 
  FastLED.setBrightness(50); 

  lcd.begin(16, 2);
  lcd.createChar(0, waterdropEmpty);
  lcd.createChar(1, waterdropFilled);
  lcd.createChar(2, sunEmpty);
  lcd.createChar(3, sunFilled);

  pinMode(waterPumpPin, OUTPUT);
  pinMode(waterSolenoidPin, OUTPUT);
  pinMode(waterLightSensorPin, INPUT);
  pinMode(solarLightSensorPin, INPUT);
  pinMode(moistureSensorPin, INPUT);
  pinMode(moistureDecreaseSpeedPin, INPUT);
}

void loop(){
  checkTheSensors();
  if(waterLightSensorTriggered||waterUntilFull){
    waterLEDshow();
    lcd.setCursor(0, 1);
    lcd.write(byte(1));
    lcd.print(" ");
    lcd.print(map(moistureLevel, 0, 255, 0, 100));
    lcd.print("%   ");
  }
  else{
    waterLEDDecay();
    lcd.setCursor(0, 1);
    lcd.write(byte(0));
    lcd.print(" ");
    lcd.print(map(moistureLevel, 0, 255, 0, 100));
    lcd.print("%   ");
  }
 if(solarLightSensorTriggered){
    lcd.setCursor(6, 1);
    lcd.write(byte(2));
    
 //   solarLEDshow();
 }
 else{
    lcd.setCursor(6, 1);
    lcd.write(byte(3));
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

void checkTheSensors(){
  int waterLightSensorValue = analogRead(waterLightSensorPin);
  int solarLightSensorValue = analogRead(solarLightSensorPin);
  
  if(waterLightSensorValue < waterLightSensorThreshold){
    waterLightSensorTriggered = true;
    Serial.println(analogRead(waterLightSensorPin));
    lcd.setCursor(0, 0);
    lcd.print("*");
  }
  else{
    waterLightSensorTriggered = false;
    lcd.setCursor(0, 0);
    lcd.print(" ");
  }

  if(solarLightSensorValue > solarLightSensorThreshold){
    solarLightSensorTriggered = true;
  }
  else{
    solarLightSensorTriggered = false;
  }

  moistureDecreaseSpeed = map(analogRead(moistureDecreaseSpeedPin), 0, 1024, 1, 255);

  realMoistureLevel = map(analogRead(moistureSensorPin),lowerMoistureThreshold, upperMoistureThreshold, 0, 255);
  
}

void decreaseMoisture(){
  if(cycle%moistureDecreaseSpeed==0){
    moistureLevel-=1;
  }
  moistureLevel = constrain(moistureLevel, 0, 255);   
}


void waterLEDshow(){
  int waterHueStart = 166;
  int waterHueRange = 30;
  
  if(cycle%moistureDecreaseSpeed/3==0){
    moistureLevel+=2;
  }
  if(cycle%51==0){
    for(int i = 0; i < NUM_WATER_LEDS; i++){
      if((!evenCycle && i%2==1)||(evenCycle && i%2!=1)){
        waterLEDs[i]=CRGB::White;
      }
      else{
        waterLEDs[i]= CHSV(random(waterHueStart, waterHueStart+waterHueRange),255,255); 
      }
    }
  }
  
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
