void waterLED(bool cycleIsOn){
  if(cycleIsOn){
    byte waterHueStart = 166;
    byte waterHueRange = 30;

    
   if(currentMillis - previousMoistureMillis >= moistureAnimationInterval/10){ //replace with something like this: https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
      moistureLevel+=2;
    }
    if(currentMillis - previousWaterMillis >= waterAnimationInterval){  //replace with something like this: https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
      for(int i = 0; i < NUM_WATER_LEDS; i++){
        if((currentMillis%2==0 && i%2==1)||(currentMillis%2==1 && i%2!=1)){
          waterLEDs[i]=CRGB::White;
        }
        else{
          waterLEDs[i]= CHSV(random(waterHueStart, waterHueStart+waterHueRange),255,255); 
        }
      }
    }
  }
  else{
    fadeToBlackBy(waterLEDs, NUM_WATER_LEDS, 10);
  }
}
