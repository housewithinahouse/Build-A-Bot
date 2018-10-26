void checkTheSensors(){
  int waterLightSensorValue = analogRead(waterLightSensorPin);
  int solarLightSensorValue = analogRead(solarLightSensorPin);
  
  if(waterLightSensorValue < waterLightSensorThreshold){
    waterLightSensorTriggered = true;
    logInteraction(F("water"));   
  }
  else{
    waterLightSensorTriggered = false;
  }

  if(solarLightSensorValue < solarLightSensorThreshold){
    solarLightSensorTriggered = true;
    logInteraction(F("solar"));
  }
  else{
    solarLightSensorTriggered = false;
  }

  realMoistureLevel = map(analogRead(moistureSensorPin),lowerMoistureSensorThreshold, upperMoistureSensorThreshold, 0, 255);
  
}
