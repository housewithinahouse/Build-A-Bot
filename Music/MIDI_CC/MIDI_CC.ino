const uint8_t NOTE_OFF = 0x80;
const uint8_t NOTE_ON = 0x90;
const uint8_t KEY_PRESSURE = 0xA0;
const uint8_t CC = 0xB0;
const uint8_t PROGRAM_CHANGE = 0xC0;
const uint8_t CHANNEL_PRESSURE = 0xD0;
const uint8_t PITCH_BEND = 0xE0;

const uint8_t analogPin = A0;

const uint8_t channel = 1;        // MIDI channel 1
const uint8_t controller = 0x10;  // General Purpose Controller 1

void setup() {
  Serial.begin(31250);
}

void loop() {
  static uint8_t previousValue = 0b10000000;       // Declare a static variable to save the previous CC value
                                                   // and initialize it to 0b10000000 (the most significant bit is set, 
                                                   // so it is different from any possible 7-bit CC value).

  uint16_t analogValue = analogRead(analogPin);    // Read the value of the analog input
  uint8_t CC_value = analogValue >> 3;             // Convert from a 10-bit number to a 7-bit number by shifting
                                                   // it 3 bits to the right.
  
  if (CC_value != previousValue) {                 // If the current value is different from the previous value
    sendMIDI(CC, channel, controller, CC_value);     // Send the new value over MIDI
    previousValue = CC_value;                        // Remember the new value
  }
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
