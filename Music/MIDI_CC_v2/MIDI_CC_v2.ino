const uint8_t analogPin = A0;

void setup(){
  Serial.begin(38400);
}
void loop(){
  uint16_t analogValue = analogRead(analogPin);    // Read the value of the analog input
  uint8_t CC_value = analogValue >> 3; 
      
  midi(0x0, 0xB0, 0x10, CC_value);
  delay(1000);
}
void midi(byte channel, byte command, byte arg1, byte arg2) {
  if (command < 128) {
    // shift over command
    command <<= 4;
    // add channel to the command
    command |= channel;
  }
  Serial.write(command);
  Serial.write(arg1);
  Serial.write(arg2);
}
