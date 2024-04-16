#include <Arduino.h>
#include "../include/MainBodyBoard.h"
#include "../include/Motor.h"
#include "../include/Xbee.h"
#include <Servo.h>

//MainBodyBoard mbb;
//Motor motor = Motor(PWM_PINS::PWM_PIN_0);
Servo motor;
//Xbee xbee;

void setup() 
{  
  //pinMode(PWM_PIN_0, OUTPUT);
  pinMode(STATUS_LIGHT_PIN, OUTPUT);
  digitalWrite(STATUS_LIGHT_PIN, HIGH);
  //mbb = MainBodyBoard();
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1);  
  //xbee = Xbee();
  Serial.println("Main Body Board");


  //analogWriteFrequency(PWM_PIN_0, 100);
  //motor.attach(PWM_PIN_0, 1000, 2000);
  //motor.write(100);
  //motor.writeMicroseconds(1500);
  // motor.setSpeed(100);
}

bool statusLightOn = false;
String input = "";

void loop() 
{
  //xbee.UpdateValues();
  String result = "";
  //for(int Controller = 0; Controller < 10; Controller++)
  //{
  //  result += (String(Controller) + ": " + String(xbee.getCurrentValue((Xbee::CONTROLLER)Controller)) + " ");
  //}
  Serial.println(result);
  //motor.writeMicroseconds(1700);
  //while(Serial2.available() > 0)
  //{
    //Serial.println("Serial2 is available");
    // if(Serial2.peek() != 217 && Serial2.peek() != 218)
    // {
    //   Serial.println(Serial2.peek(), HEX);
    //   delay(100);
    // }
    //input += (char)Serial2.read();
    //Serial.println( (char)Serial2.read());
    // if(input == 106 || input == 250)
    // {
    //   int increase = Serial2.read();
    //   motor.writeMicroseconds(1500 + (increase - 128));
    //   Serial.println("Motor speed set to: " + String(motor.readMicroseconds()));
    // }
    
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
  //}
  //Serial.println(input);
  delay(100);

}

