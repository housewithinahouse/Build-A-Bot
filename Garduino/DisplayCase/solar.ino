//void cycleColors(int colorStart, int colorRange){
//  for(int i = 0; i < NUM_LEDS; i++){
//       leds[i] = CHSV( (gHue%colorRange)+colorStart, 255, 255);
//       gHue += 1;
//       delay(10);
//       FastLED.show();
//    }
//}

void solarLEDset(){
  for(int i = 0; i < NUM_SOLAR_LEDS; i++){
    solarLEDs[i]=CRGB::White;
  }
}

void solarLEDdecay(){
  fadeToBlackBy(solarLEDs, NUM_SOLAR_LEDS, 10);
}
