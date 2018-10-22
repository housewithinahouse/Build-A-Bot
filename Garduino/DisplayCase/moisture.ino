void moistureLEDshow(){
  if(cycle%51==0){
    for(int i = 0; i < NUM_MOISTURE_LEDS; i++){
      int colorRange = 17;
      int colorStart = map(moistureLevel, 0, 255, 50, 120);
      moistureLEDs[i] = CHSV( (gHue%colorRange)+colorStart, 255, 255);
      gHue += 1;
    }
  }
}
