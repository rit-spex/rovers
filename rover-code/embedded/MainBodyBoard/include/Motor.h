#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Servo.h>
#include "Motor.h"
#include "Pinout.h"

#define SPARK_MAX_MIN 1350
#define SPARK_MAX_MAX 1650

class Motor {
    public:
        Motor();
        Motor(PWM_PINS pwm_pin);
        void setSpeed(float duty_cycle_us);
    private:
        int pwm_pin;
        Servo motor;
};
#endif
