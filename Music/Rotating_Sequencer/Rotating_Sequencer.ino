#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "FifteenStep.h"
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BLEMIDI.h"
#include "BluefruitConfig.h"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

#define FACTORYRESET_ENABLE         1
#define MINIMUM_FIRMWARE_VERSION    "0.7.0"

FifteenStep seq = FifteenStep(1024);
Adafruit_BLEMIDI blemidi(ble);

bool isConnected = false;
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}
void connected(void)
{
  isConnected = true;
  Serial.println(F(" CONNECTED!"));
}

void disconnected(void)
{
  Serial.println("disconnected");
  isConnected = false;
}

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(3);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

int analogSensorPinA = A0;
int analogSensorPinB = A1;
int analogSensorPinC = A2;
int analogSensorPinD = A3;
int analogSensorThreshold = 500;

bool triggerA = false;
bool triggerB = false;
bool triggerC = false;
bool triggerD = false;

void setup()
{

  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ) {
      error(F("Couldn't factory reset"));
    }
  }

  //ble.sendCommandCheckOK(F("AT+uartflow=off"));
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();
  
  /* Set BLE callbacks */
  ble.setConnectCallback(connected);
  ble.setDisconnectCallback(disconnected);
  
  Serial.println(F("Enable MIDI: "));
  if ( ! blemidi.begin(true) )
  {
    error(F("Could not enable MIDI"));
  }
    
  ble.verbose(false);
  Serial.print(F("Waiting for a connection..."));
  
  pinMode(analogSensorPinA, INPUT);
  pinMode(analogSensorPinB, INPUT);
  pinMode(analogSensorPinC, INPUT);
  pinMode(analogSensorPinD, INPUT);
  AFMS.begin();  // create with the default frequency 1.6KHz
  myMotor->setSpeed(19);

  
}

void loop() {
  Serial.print("  ");
  myMotor->run(FORWARD);
  if (analogRead(analogSensorPinA) > analogSensorThreshold) {
    triggerA = true;
  } else {
    triggerA = false;
  }
  if (analogRead(analogSensorPinB) > analogSensorThreshold) {
    triggerB = true;
  } else {
    triggerB = false;
  }
  if (analogRead(analogSensorPinC) > analogSensorThreshold) {
    triggerC = true;
  } else {
    triggerC = false;
  }
  if (analogRead(analogSensorPinD) > analogSensorThreshold) {
    triggerD = true;
  } else {
    triggerD = false;
  }

  if (triggerA) {
    Serial.print("+++   ");
  } else {
    Serial.print("---   ");
  }
  if (triggerB) {
    Serial.print("+++   ");
  } else {
    Serial.print("---   ");
  }
  if (triggerC) {
    Serial.print("+++   ");
  } else {
    Serial.print("---   ");
  }
  if (triggerD) {
    Serial.print("+++   ");
  } else {
    Serial.print("---   ");
  }
  Serial.println();
  delay(50);
}
