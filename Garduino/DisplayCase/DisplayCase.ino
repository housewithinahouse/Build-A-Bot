#include "FastLED.h"
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
//#include "RTClib.h"
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

const int waterPumpPin = 2;
const int waterSolenoidPin = 3; 
const int waterLEDPin = 4;      
const int solarLEDPin = 5;      
const int moistureLEDPin = 6;   
const int chipSelect = 10;      // 10-13 needed for SD card
const int waterLightSensorPin = A0;
const int solarLightSensorPin = A1;
const int moistureSensorPin = A2;
const int moistureDecreaseSpeedPin = A3; // < honestly, we could make a menu system and free up this pin for another sensor if we wanna. 
// also, FYI A4 + A5 are the i2c pins so we can't use them. But we get the lcd, buttons, and 

#define NUM_WATER_LEDS    16
CRGB waterLEDs[NUM_WATER_LEDS];

#define NUM_SOLAR_LEDS    16
CRGB solarLEDs[NUM_SOLAR_LEDS];

#define NUM_MOISTURE_LEDS    16
CRGB moistureLEDs[NUM_MOISTURE_LEDS];

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// "needed for LCD backlight" kinda. Would be cool if we could get RGB lcd...
#define WHITE 0x7

//RTC_PCF8523 rtc;





byte moistureLevel = 0;
byte realMoistureLevel = 0;

int moistureDecreaseSpeed = 251; // change all of these to millis 
int solarCycleLength = 900;      // <
int textDisplayCycle = 300;      // <

// numbers needed for animation:
unsigned long currentMillis = 0;
//moisture:
const long moistureAnimationInterval = 100;
unsigned long previousMoistureMillis = 1000; 

int matrixCursorPos = 20; 
const long matrixAnimationInterval = 500;
unsigned long previousMatrixMillis = 0;

int cycle = 0;

int waterLightSensorThreshold = 300;    //out of 1024
int solarLightSensorThreshold = 300;    //out of 1024
int lowerMoistureSensorThreshold = 100; //out of 1024
int upperMoistureSensorThreshold = 150; //out of 1024

int moistureLevelToStartWateringAt = 0;  //out of 255
int moistureLevelToStopWateringAt = 200; //out of 255

bool waterUntilFull = false;
bool timeToShine = false;
bool textFlipFlop = false;
bool waterLightSensorTriggered = false;
bool solarLightSensorTriggered = false;
bool waterCycleRunning = false;
bool solarCycleRunning = false;

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
  Serial.begin(57600); //needed speed for rtc 
  
  if (!SD.begin(chipSelect)) {
    Serial.println(F("initialization failed!"));
    return;
  }
  Serial.println(F("initialization done."));

  Wire.begin();
  
  //if (! rtc.begin()) {
   // Serial.println(F("Couldn't find RTC"));
  //  while (1);
 // }

  matrix.begin(0x70);  // pass in the address
  
  byte neoPixelMaxBrightness = 10; 
  FastLED.addLeds<NEOPIXEL, waterLEDPin>(waterLEDs, NUM_WATER_LEDS); 
  FastLED.addLeds<NEOPIXEL, solarLEDPin>(solarLEDs, NUM_SOLAR_LEDS); 
  FastLED.addLeds<NEOPIXEL, moistureLEDPin>(moistureLEDs, NUM_MOISTURE_LEDS); 
  FastLED.setBrightness(neoPixelMaxBrightness); 

  lcd.begin(16, 2);
  lcd.createChar(0, waterdropEmpty);
  lcd.createChar(1, waterdropFilled);
  lcd.createChar(2, sunEmpty);
  lcd.createChar(3, sunFilled);
  lcd.setBacklight(WHITE);



  pinMode(waterPumpPin, OUTPUT);
  pinMode(waterSolenoidPin, OUTPUT);
  pinMode(waterLightSensorPin, INPUT);
  pinMode(solarLightSensorPin, INPUT);
  pinMode(moistureSensorPin, INPUT);
  pinMode(moistureDecreaseSpeedPin, INPUT);
}

void loop(){
  // two light level sensors, a pot, and our moisture sensor
  checkTheSensors();
  

  // central logic of system, needs to have animations broken out into their own function probs. 
  if(waterLightSensorTriggered||waterUntilFull){
    waterCycleRunning = true;
  }
  else{
    waterCycleRunning = false;
  }
  if(solarLightSensorTriggered|timeToShine){
    solarCycleRunning = true;
  }
  else{
    solarCycleRunning = false;
  }
  
  currentMillis = millis();
  waterLED(waterCycleRunning);
  solarLED(solarCycleRunning);
  moistureLED();

  //plant grows drier
  decreaseMoisture();

  //if the moisture ever gets down to the lower moisture limit, water until moisture threshold is hit
  if(moistureLevel<=moistureLevelToStartWateringAt){
    waterUntilFull=true;
  }
  else if(moistureLevel>moistureLevelToStopWateringAt){
    waterUntilFull=false;
  }

  //oscillate between having solar light on and off at 50% duty cycle
  if(cycle%solarCycleLength==0){  //replace with something like this: https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
     timeToShine=!timeToShine;
  }

  LEDMatrixShow();
  
  //run the lcd display code
  lcdDisplay();

  //light up all the lights
  FastLED.show();

  //increase the cycle count
  cycle++;  // shouldn't need this after we retime animations to use millis. 
  checkButtons();
}
