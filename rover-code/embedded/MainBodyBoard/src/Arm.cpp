#include "../include/Arm.h"

Arm::Arm()
{
    // Set used pins to output
    pinMode(wristDir, OUTPUT);
    pinMode(wristSpeed, OUTPUT);
    pinMode(shoulderDir, OUTPUT);
    pinMode(shoulderSpeed, OUTPUT);  

    // Initialize and start timer to outut correct PWM signals
    Timer3.initialize(time);
    Timer3.start();


}

void Arm::moveShoulder(Direction direction)
{
  // If direction is not OFF, move motor
  if(direction != OFF)
  {
    // Write direction, HIGH is one way LOW is the other
    digitalWrite(shoulderDir, (int)direction);
    Timer3.pwm(shoulderSpeed, 511);
  }
  // If direction is OFF, stop motor
  else if(direction == OFF)
  {
    Timer3.pwm(shoulderSpeed, 0);
  }
}

void Arm::moveWrist(Direction direction)
{
  // If direction is not OFF, move motor
  if(direction != OFF)
  {
    // Write direction, HIGH is one way LOW is the other
    digitalWrite(wristDir, (int)direction);
    Timer3.pwm(wristSpeed, 511);
  }
  // If direction is OFF, stop motor
  else if(direction == OFF)
  {
    Timer3.pwm(wristSpeed, 0);
  }
}

void Arm::moveElbow(Direction direction)
{
  uint8_t cmd;
  int speed;
  if(direction == FORWARD)
  {
    cmd = 0x85;  // Motor forward
    speed = ELBOW_MAX_SPEED; // needs to be positive
  }
  else if(direction == REVERSE)
  {
    cmd = 0x86;  // Motor reverse
    speed = ELBOW_MAX_SPEED; // needs to be positive
  }
  else if(direction == OFF)
  {
    cmd = 0x85;  // Can be either direction to stop motor
    speed = 0; // stop motor
  }
  Wire.beginTransmission(ELBOW_I2C);
  Wire.write(cmd);
  Wire.write(speed & 0x1F);
  Wire.write(speed >> 5 & 0x7F);
  Wire.endTransmission();
}

void Arm::moveClaw(Direction direction)
{
  if(direction == FORWARD)
  {
    tic.setTargetVelocity(clawMaxSpeed);
  }
  else if(direction == REVERSE)
  {
    tic.setTargetVelocity(-clawMaxSpeed);
  }
  else if(direction == OFF)
  {
    tic.haltAndHold();
  }
}

void Arm::moveArm(Direction shoulderDirection, Direction wristDirection, Direction elbowDirection, Direction clawDirection)
{
  moveShoulder(shoulderDirection);
  moveWrist(wristDirection);
  moveElbow(elbowDirection);
  moveClaw(clawDirection);
}