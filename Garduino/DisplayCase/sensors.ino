void checkTheSensors(){
  int waterLightSensorValue = analogRead(waterLightSensorPin);
  int solarLightSensorValue = analogRead(solarLightSensorPin);
  
  if(waterLightSensorValue < waterLightSensorThreshold){
    waterLightSensorTriggered = true;   
  }
  else{
    waterLightSensorTriggered = false;
  }

  if(solarLightSensorValue < solarLightSensorThreshold){
    solarLightSensorTriggered = true;
  }
  else{
    solarLightSensorTriggered = false;
  }

  moistureDecreaseSpeed = map(analogRead(moistureDecreaseSpeedPin), 0, 1024, 1, 255);
  solarCycleLength = moistureDecreaseSpeed*60;

  realMoistureLevel = map(analogRead(moistureSensorPin),lowerMoistureSensorThreshold, upperMoistureSensorThreshold, 0, 255);
  
}
