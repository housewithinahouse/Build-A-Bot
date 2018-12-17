void setup() {
  Serial.begin(57600); //needed speed for rtc 
  
  if (!SD.begin(chipSelect)) {
    Serial.println(F("initialization failed!"));
    return;
  }
  Serial.println(F("initialization done."));

  Wire.begin();
  
  //if (! rtc.begin()) {
   // Serial.println(F("Couldn't find RTC"));
  //  while (1);
 // }

  matrix.begin(0x70);  // pass in the address
  
  byte neoPixelMaxBrightness = 60; 
  FastLED.addLeds<NEOPIXEL, waterLEDPin>(waterLEDs, NUM_WATER_LEDS); 
  FastLED.addLeds<NEOPIXEL, solarLEDPin>(solarLEDs, NUM_SOLAR_LEDS); 
  FastLED.addLeds<NEOPIXEL, moistureLEDPin>(moistureLEDs, NUM_MOISTURE_LEDS); 
  FastLED.setBrightness(neoPixelMaxBrightness); 

  lcd.begin(16, 2);
  lcd.createChar(0, waterdropEmpty);
  lcd.createChar(1, waterdropFilled);
  lcd.createChar(2, sunEmpty);
  lcd.createChar(3, sunFilled);
  lcd.setBacklight(0x7);



  pinMode(waterPumpPin, OUTPUT);
  pinMode(waterSolenoidPin, OUTPUT);
  pinMode(waterLightSensorPin, INPUT);
  pinMode(solarLightSensorPin, INPUT);
  pinMode(moistureSensorPin, INPUT);
}
