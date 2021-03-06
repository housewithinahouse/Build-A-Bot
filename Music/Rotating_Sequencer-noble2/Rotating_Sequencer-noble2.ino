void setup(){
  Serial.begin(38400);
}
void loop(){
  midi(0x0, 0x9, 0x3C, 0x40);
  delay(1000);
  midi(0x0, 0x9, 0x3C, 0x40);
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
