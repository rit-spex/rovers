#include <Arduino.h>
#include "../include/MainBodyBoard.h"
#include "../include/Motor.h"
#include <XBee.h>

MainBodyBoard mbb;
XBee xbee = XBee();
Motor motor = Motor(PWM_PINS::PWM_PIN_0);

void setup() 
{
  pinMode(STATUS_LIGHT_PIN, OUTPUT);
  digitalWrite(STATUS_LIGHT_PIN, HIGH);
  mbb = MainBodyBoard();
  Serial.begin(9600);
  Serial.println("Main Body Board");
  // Serial2.begin(9600);

  // xbee.begin(Serial2);
}

void loop() 
{
  motor.setSpeed(1700);
  // xbee.readPacket();
  // if (xbee.getResponse().isAvailable()) 
  // {
  //   Serial.println("Response is available");
  // }
  // int incomingByte = Serial2.read();
  // Serial.println(incomingByte, DEC);
  // // Serial2.flush();
  // // if (command == 1) 
  // // {
  // //   digitalWrite(STATUS_LIGHT_PIN, LOW);
  // // }
  //   //mbb.updateSubsystems();
  //   delay(1);
}

