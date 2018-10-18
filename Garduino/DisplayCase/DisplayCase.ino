#include "FastLED.h"

#define NUM_WATER_LEDS    6
CRGB waterLEDs[NUM_WATER_LEDS];

const int waterLightShowPin = 5; 
const int solarLightShowPin = 6; 
const int moistureLightShowPin = 7; 
int buttonState;
int gHue = 0;

int moistureLevel = 255;

bool evenCycle = false;
bool waterUntilFull = false;
bool waterLightShowSensorTriggered = false;
bool solarLightShowSensorTriggered = false;

void setup() {
  addWaterLEDs(6);
  setWaterLEDBrightness(50); 
}

void loop(){
 // checkTheSensors();
  if(waterLightShowSensorTriggered||waterUntilFull){
    waterLightShow();
  }
  else{
    waterLightShowDecay();
  }
 //if(solarLightShowSensorTriggered){
 //   solarLightShow();
 // }
 // else{
 //   solarLightShowDecay();
 // }

 // moistureLightShow();

  FastLED.show();
  
 // decreaseMoisture();
  if(moistureLevel<0){
    waterUntilFull=true;
  }
  else if(moistureLevel>200){
    waterUntilFull=false;
  }
  //flip flop the cycle ticker
  evenCycle = !evenCycle;
}

void setWaterLEDBrightness(int brightness){
  brightness = constrain(brightness, 0, 100);
  FastLED.setBrightness(brightness);
}

void addWaterLEDs(int LEDcount){
  FastLED.addLeds<NEOPIXEL, 2>(waterLEDs, LEDcount); 
}


void waterLightShow(){
  int waterHueStart = 166;
  int waterHueRange = 60;
  for(int i = 0; i < NUM_WATER_LEDS; i++){
    if((!evenCycle && i%2==1)||(evenCycle && i%2!=1)){
      waterLEDs[i]=CRGB::White;
    }
    else{
      waterLEDs[i]= CHSV(random(waterHueStart, waterHueStart+waterHueRange),255,255); 
    }
  }
  moistureLevel+=2;
}

void waterLightShowDecay(){
  fadeToBlackBy(waterLEDs, NUM_WATER_LEDS, 1);
}


//void cycleColors(int colorStart, int colorRange){
//  for(int i = 0; i < NUM_LEDS; i++){
//       leds[i] = CHSV( (gHue%colorRange)+colorStart, 255, 255);
//       gHue += 1;
//       delay(10);
//       FastLED.show();
//    }
//}

//void fadeToBlack(){
//  fadeToBlackBy(leds, NUM_LEDS, 1);
//  delay(5);
//  FastLED.show();
//}
