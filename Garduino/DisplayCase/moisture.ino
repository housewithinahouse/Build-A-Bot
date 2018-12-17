void moistureLED(){
  int gHue = 0;
  if(currentMillis - previousMoistureMillis >= moistureAnimationInterval){  // < replaced, do like this to other animations...
    previousMoistureMillis = currentMillis;
    for(int i = 0; i < NUM_MOISTURE_LEDS; i++){
      int colorRange = 17;
      int colorStart = map(moistureLevel, 0, 255, 50, 120);
      moistureLEDs[i] = CHSV( (gHue%colorRange)+colorStart, 255, 255);
      gHue += 1;
    }
  }
}

void decreaseMoisture(){
  if(currentMillis - previousMoistureDecayMillis >= moistureDecayInterval){  // < replace with something like this: https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
    moistureLevel-=1;
  }
  moistureLevel = constrain(moistureLevel, 0, 255);   
}
