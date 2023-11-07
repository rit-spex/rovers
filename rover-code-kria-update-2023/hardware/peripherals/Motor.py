"""
File: Motor.py
Description: This file defines a Motor class that can be used for controlling motors.
Author: Ryan Barry
"""

import time

from hardware.peripherals.GPIO_Peripheral import GPIO_Peripheral


class Motor:
    def __init__(self, pwm_pin=None):
        self._pwm_pin = pwm_pin  # PWM pin for controlling motor speed
        self.duty_cycle = 0.0  # Duty cycle for PWM pin

    def select_pwm_pin(self, pin_number):
        print("bruh")
        self._pwm_pin = GPIO_Peripheral(pin_number, "out")  # Set the PWM pin

    def update_pwm(self):
        current_time = time.monotonic() # Get the current time

        # Get the current state of the PWM pin
        is_high = GPIO.input(self._pwm_pin) == GPIO.HIGH

        # Compute the duty cycle and inverse frequency
        duty_scaled = self.duty_cycle / 100
        frequency_inv = 1 / self.frequency

        # Compute toggle time based on current state
        toggle_time = frequency_inv * (duty_scaled if not is_high else (1 - duty_scaled))
        self.next_toggle_time = current_time + toggle_time

        # Toggle the pin
        GPIO.output(self._pwm_pin, GPIO.LOW if is_high else GPIO.HIGH)
