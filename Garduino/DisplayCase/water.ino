void waterLEDset(){
  int waterHueStart = 166;
  int waterHueRange = 30;
  
  if(cycle%moistureDecreaseSpeed/3==0){ //replace with something like this: https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
    moistureLevel+=2;
  }
  if(cycle%51==0){  //replace with something like this: https://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
    for(int i = 0; i < NUM_WATER_LEDS; i++){
      if((cycle%2==0 && i%2==1)||(cycle%2==1 && i%2!=1)){
        waterLEDs[i]=CRGB::White;
      }
      else{
        waterLEDs[i]= CHSV(random(waterHueStart, waterHueStart+waterHueRange),255,255); 
      }
    }
  }
  
}

void waterLEDdecay(){
  fadeToBlackBy(waterLEDs, NUM_WATER_LEDS, 10);
}
