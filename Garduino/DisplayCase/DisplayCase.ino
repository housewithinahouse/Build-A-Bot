#include "FastLED.h"
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include "RTClib.h"

const int waterPumpPin = 2;
const int waterSolenoidPin = 3; 
const int waterLEDPin = 4;      
const int solarLEDPin = 5;      
const int moistureLEDPin = 6;   
const int rs = 7; //kill// 3 digital pins free now! 
const int en = 8; //kill// What do you want to do with 
const int d4 = 9; //kill// them?
const int chipSelect = 10;      // 10-13 needed for SD card
const int d6 = 11; // < need these 3 pins free for SPI
const int d7 = 12; // < elimanate
const int d5 = 13; // < ...got a new shield that uses I2C!
const int waterLightSensorPin = A0;
const int solarLightSensorPin = A1;
const int moistureSensorPin = A2;
const int moistureDecreaseSpeedPin = A3;

#define NUM_WATER_LEDS    16
CRGB waterLEDs[NUM_WATER_LEDS];

#define NUM_SOLAR_LEDS    16
CRGB solarLEDs[NUM_SOLAR_LEDS];

#define NUM_MOISTURE_LEDS    16
CRGB moistureLEDs[NUM_MOISTURE_LEDS];

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// "needed for LCD backlight" kinda. Would be cool if we could get RGB lcd...
#define WHITE 0x7

RTC_PCF8523 rtc;

int gHue = 0;
int neoPixelMaxBrightness = 10; 

int moistureLevel = 0;
int realMoistureLevel = 0;

int moistureDecreaseSpeed = 251; // change all of these to millis
int solarCycleLength = 900;      // <
int textDisplayCycle = 300;      // <

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

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  Wire.begin();
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
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

  // central logic of system
  if(waterLightSensorTriggered||waterUntilFull){
    waterCycleRunning = true;
    waterLEDset();
  }
  else{
    waterCycleRunning = false;
    waterLEDdecay();
  }
  if(solarLightSensorTriggered|timeToShine){
    solarCycleRunning = true;
    solarLEDset();
  }
  else{
    solarCycleRunning = false;
    solarLEDdecay();
  }

  moistureLEDset();

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
  
  //run the lcd display code
  lcdDisplay();

  //light up all the lights
  FastLED.show();
  
  //increase the cycle count
  cycle++;  // shouldn't need this after we retime animations to use millis. 
}


