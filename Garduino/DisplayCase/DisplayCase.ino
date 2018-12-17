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
float waterAvg = 400;
float solarAvg = 0;
byte waterLightSensorEvent = 0;
// also, FYI A4 + A5 are the i2c pins so we can't use them. But we get the lcd, buttons, and matrix from these pins...


#define NUM_WATER_LEDS    16
CRGB waterLEDs[NUM_WATER_LEDS];

#define NUM_SOLAR_LEDS    60
CRGB solarLEDs[NUM_SOLAR_LEDS];

#define NUM_MOISTURE_LEDS    16
CRGB moistureLEDs[NUM_MOISTURE_LEDS];

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

//RTC_PCF8523 rtc;

byte moistureLevel = 0;
byte realMoistureLevel = 0;

// numbers needed for animation/interval:
unsigned long currentMillis = 0;

// moisture animations:
const long moistureAnimationInterval = 100;
unsigned long previousMoistureMillis = 1000; 

// moisture decay
const long moistureDecayInterval = 100;
unsigned long previousMoistureDecayMillis = 0; 

// matrix stuff
int matrixCursorPos = 20; 
const long matrixAnimationInterval = 500;
unsigned long previousMatrixMillis = 0;

// solar cycle: 
const long solarCycleInterval = 50000;
unsigned long previousSolarMillis = 0;

// water animation cycle:
unsigned long previousWaterMillis = 0;
const long waterAnimationInterval = 100;

// text animation cycle:
unsigned long previousTextMillis = 0;
const long textAnimationInterval = 10000;


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
