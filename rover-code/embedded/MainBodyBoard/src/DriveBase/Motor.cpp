#include "../../include/Motor.h"

#define SPARK_MAX_MIN 1000
#define SPARK_MAX_MAX 2000

Motor::Motor(PWM_PINS pwm_pin){
    this->pwm_pin = pwm_pin;
    //pinMode((int)this->pwm_pin, OUTPUT);
    motor.attach(this->pwm_pin, SPARK_MAX_MIN, SPARK_MAX_MAX);  // Assuming 'motor' is a member variable of the Motor class
}

void Motor::setSpeed(float duty_cycle_us) {
    motor.write(duty_cycle_us);
}
