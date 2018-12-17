// we should make something more intersting for the solar LEDs

void solarLED(bool cycleIsOn){
  if(cycleIsOn){
    for(int i = 0; i < NUM_SOLAR_LEDS; i++){
      solarLEDs[i]=CHSV( gHue + random8(64,110), 200, 255);

      //This is where we get to make pretty animations for the solar part of the cycle. 
    }
  }
  else{
    fadeToBlackBy(solarLEDs, NUM_SOLAR_LEDS, 10);
  }
}
