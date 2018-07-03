
//Light Painting Wand

//This is the code for our light painting wand.

void setup() {
  // during the setup, we need to tell our code how many LEDs there
  // are and set those LEDs brightness
  addLEDs(6);
  setLEDBrightness(50); // out of 100
}

void loop(){
  // the loop part of our code will run over and over again.
  // our goal is to cycle through some subset of colors of the rainbow

  //first we set what portion of the rainbow we cycle through
  int colorRange = 1; // out of 255

  // and our starting point on the rainbow
  int colorStart = 1; //out of 255

  // cycleColors will set our LEDs to the next phase on the rainbow
  cycleColors(colorRange,colorStart);
  
  //addGlitter(1); // optional code to make glitter happen. 

  // after we've set our colors, we call showColors to show them
  showColors();  
}















//---Everything down here you don't have to worry about!
//---This is all the stuff that actually makes it go. 


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
