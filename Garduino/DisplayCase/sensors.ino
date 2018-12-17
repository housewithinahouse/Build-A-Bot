void checkTheSensors(){
  int waterLightSensorValue = analogRead(waterLightSensorPin);
  int solarLightSensorValue = analogRead(solarLightSensorPin);

  float sensorWeight = 0.1;

  if(waterLightSensorValue > waterAvg){
    waterAvg += sensorWeight;
  }
  else{
    waterAvg -= sensorWeight;
  }
  if(solarLightSensorValue > solarAvg){
    solarAvg += sensorWeight;
  }
  else{
    solarAvg -= sensorWeight;
  }
  int waterLightSensorThreshold = waterAvg - 20;    //out of 1024
  int solarLightSensorThreshold = solarAvg - 20;    //out of 1024
    
  if(waterLightSensorValue < waterLightSensorThreshold){
    waterLightSensorEvent += 1;
  }
  else{
    waterLightSensorEvent = 0;
  }

  if(waterLightSensorEvent > 2){
    waterLightSensorTriggered = true;
    logInteraction(F("water"));
  }
  else{
    waterLightSensorTriggered = false;
  }

  if(solarLightSensorValue < solarLightSensorThreshold){
    solarLightSensorEvent += 1;
  }
  else{
    solarLightSensorEvent = 0;
  }

  if(solarLightSensorEvent > 2){
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
