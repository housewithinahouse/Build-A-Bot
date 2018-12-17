void checkTheSensors(){
  int waterLightSensorValue = analogRead(waterLightSensorPin);
  int solarLightSensorValue = analogRead(solarLightSensorPin);

  int waterLightSensorThreshold = 300;    //out of 1024
  int solarLightSensorThreshold = 300;    //out of 1024
  
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
  int lowerMoistureSensorThreshold = 100; //out of 1024
  int upperMoistureSensorThreshold = 150; //out of 1024

  realMoistureLevel = map(analogRead(moistureSensorPin),lowerMoistureSensorThreshold, upperMoistureSensorThreshold, 0, 255);
  
}
