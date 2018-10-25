// we should make something more intersting for the solar LEDs

void solarLED(bool cycleIsOn){
  if(cycleIsOn){
    for(int i = 0; i < NUM_SOLAR_LEDS; i++){
      solarLEDs[i]=CRGB::White;
    }
  }
  else{
    fadeToBlackBy(solarLEDs, NUM_SOLAR_LEDS, 10);
  }
}
