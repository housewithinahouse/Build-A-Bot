/*********************************************************************
  This is a project based around an example for the Adafruit nRF51822 based Bluefruit LE modules, orginally modified to drive a 3-wheeled BLE Robot Rover! by http://james.devi.to

  This code has been further modified by Edwin Fallwell + Matt Neer for the Monroe County Public Library in Bloomington, IN.

  MIT license, check LICENSE for more information
  All text above, and the splash screen below must be included in
  any redistribution
*********************************************************************/

#include <Arduino.h>

// This is all setup for our bluetooth module built into the Feather
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include "BluefruitConfig.h"

// We've also attached a daughter board to our Feather. This additional board.
// also known as a Wing, or a Shield if we were using an Arduino need a
// library to drive it.
#include <Adafruit_MotorShield.h>

// Our pen lift servo also needs its own library full of helper functions.
#include <Servo.h>

// Finally, we wrapped up all of our drawing robot's functionality into a library. 
#include "Drawy.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// And connect 2 DC motors to port M3 & M4 !
Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(3);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(4);

//This is where we give Drawy it's name!
//I'm thinking about nameing it Drude instead.
String BROADCAST_NAME = "Drawy";

String BROADCAST_CMD = String("AT+GAPDEVNAME=" + BROADCAST_NAME);

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// function prototypes over in packetparser.cpp
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

// the packet buffer
extern uint8_t packetbuffer[];

char buf[60];


// Set your forward, reverse, drift corrections, and turning speeds as well as the 
// segment time. 
#define ForwardSpeed                60
#define ReverseSpeed                60
#define TurningSpeed                60
#define DriftCorrection             1
#define SegmentLength               150



//create a Servo object, which we will address when we need to talk to the servo
Servo servo;

// Set Servo Pin
int servopin = A0;

// Variable for holding state of pen
bool penDown = false;

/**************************************************************************/
/*!
    @brief  Sets up the HW and the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(9600);

  AFMS.begin();  // create with the default frequency 1.6KHz

  // turn on motors
  L_MOTOR->setSpeed(0);
  L_MOTOR->run(RELEASE);

  R_MOTOR->setSpeed(0);
  R_MOTOR->run(RELEASE);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit Robot Controller Example"));
  Serial.println(F("-----------------------------------------"));

  /* Initialize the module */
  BLEsetup();

  //Set up servo pin
  servo.attach(A0);
}

void loop(void)
{
  // read new packet data
  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);

  readController();

}

bool isMoving = false;
unsigned long lastPress = 0;

bool readController() {
  uint8_t maxspeed;

  // Buttons
  if (packetbuffer[1] == 'B') {

    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';

    if (pressed) {
      if (buttnum == 1) {
        //cycle the pen
        if (penDown){
          lift();
          penDown = false;
        }
        else {
          draw();
          penDown = true;
        }        
      }

      if (buttnum == 2) {
        //do cool stuff
        draw();
        for(int i = 0; i<100; i++){
          int option = random(1,20);
          switch(option){
            case 1:
              up();
              left();
              down();
            break;
            case 2:
              down();
              left();
              up();
            break;
            default:
              left();
          }
        }
        lift();
      }

      if (buttnum == 3) {
        writeDrawy();
      }

      if (buttnum == 4) {
        mattDraw();
      }

      if (buttnum == 5) {
        isMoving = true;
        L_MOTOR->run(BACKWARD);
        R_MOTOR->run(BACKWARD);
        maxspeed = ReverseSpeed;
      }

      if (buttnum == 6) {
        isMoving = true;
        L_MOTOR->run(FORWARD);
        R_MOTOR->run(FORWARD);
        maxspeed = ForwardSpeed;
      }



      if (buttnum == 7) {
        isMoving = true;
        L_MOTOR->run(BACKWARD);
        R_MOTOR->run(FORWARD);
        maxspeed = TurningSpeed;
      }

      if (buttnum == 8) {
        isMoving = true;
        L_MOTOR->run(FORWARD);
        R_MOTOR->run(BACKWARD);
        maxspeed = TurningSpeed;
      }

      lastPress = millis();

      // speed up the motors
      for (int speed = 0; speed < maxspeed; speed += 5) {
        L_MOTOR->setSpeed(speed + DriftCorrection);
        R_MOTOR->setSpeed(speed - DriftCorrection);
        delay(5); // 250ms total to speed up
      }
    } else {
      isMoving = false;
      // slow down the motors
      for (int speed = maxspeed; speed >= 0; speed -= 5) {
        L_MOTOR->setSpeed(speed + DriftCorrection);
        R_MOTOR->setSpeed(speed - DriftCorrection);
        delay(5); // 50ms total to slow down
      }
      L_MOTOR->run(RELEASE);
      R_MOTOR->run(RELEASE);
    }
  }
}


void BLEsetup() {
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  /* Perform a factory reset to make sure everything is in a known state */
  Serial.println(F("Performing a factory reset: "));
  if (! ble.factoryReset() ) {
    error(F("Couldn't factory reset"));
  }

  //Convert the name change command to a char array
  BROADCAST_CMD.toCharArray(buf, 60);

  //Change the broadcast device name here!
  if (ble.sendCommandCheckOK(buf)) {
    Serial.println("name changed");
  }
  delay(250);

  //reset to take effect
  if (ble.sendCommandCheckOK("ATZ")) {
    Serial.println("resetting");
  }
  delay(250);

  //Confirm name change
  ble.sendCommandCheckOK("AT+GAPDEVNAME");

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in Controller mode"));
  Serial.println(F("Then activate/use the sensors, color picker, game controller, etc!"));
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while (! ble.isConnected()) {
    delay(500);
  }

  Serial.println(F("*****************"));

  // Set Bluefruit to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("*****************"));
}



