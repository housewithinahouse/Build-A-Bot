// we should make something more intersting for the solar LEDs

void solarLEDset(){
  for(int i = 0; i < NUM_SOLAR_LEDS; i++){
    solarLEDs[i]=CRGB::White;
  }
}

void solarLEDdecay(){
  fadeToBlackBy(solarLEDs, NUM_SOLAR_LEDS, 10);
}
