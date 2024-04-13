#include <Arduino.h>
#include "../include/MainBodyBoard.h"
#include "../include/Motor.h"

#include <Servo.h>
//#include <XBee.h>

//MainBodyBoard mbb;
//XBee xbee = XBee();
//Motor motor = Motor(PWM_PINS::PWM_PIN_0);
Servo motor;


void setup() 
{  
  //pinMode(PWM_PIN_0, OUTPUT);
  pinMode(STATUS_LIGHT_PIN, OUTPUT);
  digitalWrite(STATUS_LIGHT_PIN, HIGH);
  //mbb = MainBodyBoard();
  Serial.begin(9600);
  Serial.println("Main Body Board");
  Serial2.begin(9600);

  //analogWriteFrequency(PWM_PIN_0, 100);
  motor.attach(PWM_PIN_0, 1000, 2000);
  //motor.write(100);
  motor.writeMicroseconds(1500);
  // motor.setSpeed(100);

  //xbee.begin(Serial2);
}

bool statusLightOn = false;
// int count123 = 0;

void loop() 
{
  //motor.writeMicroseconds(1700);
  //xbee.readPacket();
  // if (xbee.getResponse().isAvailable()) 
  // {
  //   Serial.println("Response is available");
  // }
  //Serial.println(xbee.getResponse().getApiId());
  while(Serial2.available() > 1)
  {
    // count123++;
    //Serial.println("Serial2 is available");
    int input = Serial2.read();
    Serial.println("Input: " + String(input));
    if(input == 106 || input == 250)
    {
      int increase = Serial2.read();
      motor.writeMicroseconds(1500 + (increase - 128));
      Serial.println("Motor speed set to: " + String(motor.readMicroseconds()));
    }
    
    // digitalWrite(STATUS_LIGHT_PIN, LOW);    
    // if(statusLightOn)
    // {
    //   digitalWrite(STATUS_LIGHT_PIN, LOW);
    //   statusLightOn = false;
    // }
    // else
    // {
    //   digitalWrite(STATUS_LIGHT_PIN, HIGH);
    //   statusLightOn = true;
    // }
  }

  // if(Serial2.availableForWrite()>0)
  // {
  //   Serial.println("Serial2 is available for write");
  //   Serial2.write("o");
  //   Serial2.flush();
  // }
  // Serial.println(count123);
  // char incomingByte = Serial2.read();
  // Serial2.flush();
  // Serial.println(incomingByte);
  // // if (command == 1) 
  // // {
  // //   digitalWrite(STATUS_LIGHT_PIN, LOW);
  // // }
  //mbb.updateSubsystems();
  // Serial2.write("Hello");
  // Serial2.flush();
  delay(1);
}

