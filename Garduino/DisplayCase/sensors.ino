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
  Serial.print("water Avg:");
  Serial.println(waterAvg);
  Serial.print("water sen:");
  Serial.println(waterLightSensorValue);

  int waterLightSensorThreshold = waterAvg - 20;    //out of 1024
  int solarLightSensorThreshold = solarAvg - 50;    //out of 1024
  
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
