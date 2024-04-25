#ifndef ARM_H
#define ARM_H
#include <Arduino.h>
#include <TimerThree.h>
#include <Wire.h>
#include <Tic.h>

// define these pins, wristDir and shoulderDir can be any digital output
// wristSpeed and shoulderSpeed need to be pins 9 and 6
#define wristDir 1 
#define wristSpeed 9 // MUST BE PIN 9
#define shoulderDir 2
#define shoulderSpeed 6 // MUST BE PIN 6

// I2C device number
#define ELBOW_I2C 15 // brushed motor
#define ELBOW_MAX_SPEED 3200
#define clawID 16 // stepper motor
#define clawMaxSpeed 100 * 10000 // 100 steps per second

class Arm
{
    public:
        enum Direction
        {
            FORWARD = 1,
            REVERSE = 0,
            OFF = 2
        };
        Arm();
        void startUp();
        // functions to move the harmonic drives. These are the exact same but with different pin outputs
        // Functions work by setting timer output at either 50% duty cycle
        void moveShoulder(Direction direction);
        void moveWrist(Direction direction);
        void moveElbow(Direction direction);
        void moveClaw(Direction direction);
        void moveArm(Direction shoulderDirection, Direction wristDirection, Direction elbowDirection, Direction clawDirection);
        TicI2C tic{16};
    private:

        
        // Changing this time will change the motor speeds 30 us seems to be a good starting speed
        int time = 30; // time in microseconds
};

#endif