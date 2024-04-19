#include <Arduino.h>
#include "../include/MainBodyBoard.h"
#include "../include/Motor.h"
#include "../include/Xbee.h"
#include <Servo.h>
#include <Wire.h>

//int armMotor = 15;

MainBodyBoard mbb;
//DriveBase motor = DriveBase();
//Wheel motor = Wheel(PWM_PINS::PWM_PIN_0);
// Servo motor1;
// Servo motor2;
// Servo motor3;
// Servo motor4;
// Servo motor5;
// Servo motor6;
//Xbee xbee;

// void static exitSafeStart(int motor)
// {
//   Wire.beginTransmission(motor);
//   Wire.write(0x83);
//   Wire.endTransmission();
// }

// void static setMotorSpeed(int16_t speed, int motor)
// {
//   uint8_t cmd = 0x85;
//   if(speed <0)
//   {
//     cmd = 0x86;
//     speed = -speed;
//   }
//   Wire.beginTransmission(motor);
//   Wire.write(cmd);
//   Wire.write(speed & 0x1F);
//   Wire.write(speed >> 5 & 0x7F);
//   Wire.endTransmission();
// }

void setup() 
{
  //Wire.begin();
  //exitSafeStart(armMotor);
  //pinMode(PWM_PIN_0, OUTPUT);
  pinMode(STATUS_LIGHT_PIN, OUTPUT);
  digitalWrite(STATUS_LIGHT_PIN, LOW);
  //mbb = MainBodyBoard();
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1);  
  //xbee = Xbee();
  Serial.println("Main Body Board");


  //analogWriteFrequency(PWM_PIN_0, 100);
  // motor1.attach(PWM_PIN_0, 1000, 2000);
  // motor2.attach(PWM_PIN_1, 1000, 2000);
  // motor3.attach(PWM_PIN_2, 1000, 2000);
  // motor4.attach(PWM_PIN_3, 1000, 2000);
  // motor5.attach(PWM_PIN_4, 1000, 2000);
  // motor6.attach(PWM_PIN_5, 1000, 2000);

  //motor.write(100);
  // motor1.writeMicroseconds(1000);
  // motor2.writeMicroseconds(1000);
  // motor3.writeMicroseconds(1000);
  // motor4.writeMicroseconds(1000);
  // motor5.writeMicroseconds(1000);
  // motor6.writeMicroseconds(1000);
  // motor.setSpeed(100);
}

//bool statusLightOn = false;
//String input = "";

float rightAxis = 0.0;
float leftAxis = 0.0;

int counter = 0;
int lastcounter = 0;
void loop() 
{
  //motor.setSpeed(1);
  //motor.updateSingleWheel(1, 1);
  // motor1.writeMicroseconds(1000);
  // motor2.writeMicroseconds(1000);
  // motor3.writeMicroseconds(1000);
  // motor4.writeMicroseconds(1000);
  // motor5.writeMicroseconds(1000);
  // motor6.writeMicroseconds(1000);
  //xbee.UpdateValues();
  //String result = "";
  //for(int Controller = 0; Controller < 10; Controller++)
  //{
  //  result += (String(Controller) + ": " + String(xbee.getCurrentValue((Xbee::CONTROLLER)Controller)) + " ");
  //}
  //Serial.println(result);
  //motor.writeMicroseconds(1700);
  if(lastcounter != Serial2.available())
  {
    counter = 0;
    lastcounter = Serial2.available();
    while(Serial2.available() > 3)
  {
    //Serial.println("Serial2 is available");
    int input = Serial2.read();
    if(input == 0xDE)
    {
      float joy1 = Serial2.read();
      float joy2 = Serial2.read();
      if(joy1 > 200)
      {
        Serial.println("Ignore");
      }
      else
      {
        Serial.print("joy1 ");
        //Serial.print(joy1, DEC);
        leftAxis = (joy1 - 100.0) / 100.0;
        Serial.println(leftAxis);
        // motor1.writeMicroseconds(1500 + (joy1 - 100));
        // motor2.writeMicroseconds(1500 + (joy1 - 100));
        // motor3.writeMicroseconds(1500 + (joy1 - 100));
      }
      if(joy2 > 200)
      {
        Serial.println("Ignore");
      }
      else
      {
        Serial.print("joy2 ");
        //Serial.print(joy2, DEC);
        rightAxis = (joy2 - 100.0) / 100.0;
        Serial.println(rightAxis);
        // motor4.writeMicroseconds(1500 - (joy2 + 100));
        // motor5.writeMicroseconds(1500 - (joy2 + 100));
        // motor6.writeMicroseconds(1500 - (joy2 + 100));
      }
    }
    mbb.drive(leftAxis, rightAxis);
  }
    //mbb.updateSubsystems();
    //input += (char)Serial2.read();
    //Serial.println( (char)Serial2.read());
    //if(input == 106 || input == 250)
    //{
    //  int increase = Serial2.read();
    //  motor.writeMicroseconds(1500 + (increase - 128));
    //  Serial.println("Motor speed set to: " + String(motor.readMicroseconds()));
    //}
    //
    //digitalWrite(STATUS_LIGHT_PIN, LOW);    
    //if(statusLightOn)
    //{
    //  digitalWrite(STATUS_LIGHT_PIN, LOW);
    //  statusLightOn = false;
    //}
    //else
    //{
    //  digitalWrite(STATUS_LIGHT_PIN, HIGH);
    //  statusLightOn = true;
    //}
    
  }
  else
  {
    counter++;
  }
  
  if(counter > 30)
  {
    //motor1.writeMicroseconds(1500);
    //motor2.writeMicroseconds(1500);
    //motor3.writeMicroseconds(1500);
    //motor4.writeMicroseconds(1500);
    //motor5.writeMicroseconds(1500);
    //motor6.writeMicroseconds(1500);
    mbb.drive(0.0, 0.0);
    digitalWrite(STATUS_LIGHT_PIN, HIGH);    

    while (true)
    {
      /* code */
    } 
  }
  
  //setMotorSpeed(400,15);
  delay(100);

}