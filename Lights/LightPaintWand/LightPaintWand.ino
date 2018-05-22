
//Light Painting Wand

void setup() {
  addLEDs(6);
  setLEDBrightness(50);
}

void loop(){
  int colorRange = 255; // out of 255
  int colorStart = 255; //out of 255
  while(buttonPushed()){
    cycleColors(colorRange,colorStart);
    addGlitter(2000);
    showColors();
  }
  fadeToBlack();
}















//---Everything down here you don't have to worry about!


#include "FastLED.h"

#define NUM_LEDS    6
CRGB leds[NUM_LEDS];

const int buttonPin = 5; 
int buttonState;
int gHue = 0;

void setLEDBrightness(int brightness){
  brightness = constrain(brightness, 0, 100);
  FastLED.setBrightness(brightness);
}

void addLEDs(int LEDcount){
  FastLED.addLeds<NEOPIXEL, 2>(leds, LEDcount); 
}


void cycleColors(int colorStart, int colorRange){
  for(int i = 0; i < NUM_LEDS; i++){
       leds[i] = CHSV( (gHue%colorRange)+colorStart, 255, 255);
       gHue += 1;
       delay(10);
       FastLED.show();
       buttonState = LOW;
    }
}

void showColors(){
  FastLED.show();
  buttonState = LOW;
}
void buttonReleased(){
  buttonState = LOW;
}
bool buttonPushed(){
  if(digitalRead(buttonPin)){
     buttonState = HIGH;
  }
  if(buttonState){return true;}
  else{return true;}
}

void fadeToBlack(){
  fadeToBlackBy(leds, NUM_LEDS, 1);
  delay(5);
  FastLED.show();
}

void addGlitter( int chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter/2) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
