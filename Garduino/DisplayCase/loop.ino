void loop(){
  // two light level sensors, a pot, and our moisture sensor
  checkTheSensors();

  // central logic of system, needs to have animations broken out into their own function probs. 
  if(waterLightSensorTriggered||waterUntilFull){
    waterCycleRunning = true;
  }
  else{
    waterCycleRunning = false;
  }
  if(solarLightSensorTriggered|timeToShine){
    solarCycleRunning = true;
  }
  else{
    solarCycleRunning = false;
  }
  
  currentMillis = millis();
  waterLED(waterCycleRunning);
  solarLED(solarCycleRunning);
  moistureLED();

  //plant grows drier
  decreaseMoisture();

  //if the moisture ever gets down to the lower moisture limit, water until moisture threshold is hit
  int moistureLevelToStartWateringAt = 0;  //out of 255
  int moistureLevelToStopWateringAt = 200; //out of 255
  
  if(moistureLevel<=moistureLevelToStartWateringAt){
    waterUntilFull=true;
  }
  else if(moistureLevel>moistureLevelToStopWateringAt){
    waterUntilFull=false;
  }

  //oscillate between having solar light on and off at 50% duty cycle
   if(currentMillis - previousSolarMillis >= solarCycleInterval){ 
     timeToShine=!timeToShine;
     previousSolarMillis = currentMillis;
  }

  LEDMatrixShow();
  
  //run the lcd display code
  lcdDisplay();

  //light up all the lights
  FastLED.show();

  checkButtons();
}
