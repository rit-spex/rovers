#!/usr/bin/env python3
"""
File: DriveWheel.py

Description: This script contains the DriveWheel class, which inherits from Motor.
A drive wheel object can be instantiated within the drive base of the rover.
The class includes a function to calculate and publish its velocity to a topic.

Author: Ryan Barry
Date Created: August 12, 2023
"""
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32

import sys
sys.path.append("../peripherals/")
sys.path.append("../..")
from peripherals.Motor import Motor
from RoverConstants import WHEEL_RADIUS

class VelocityPublisher(Node):
    def __init__(self, name):
        self.name = name
        super().__init__(f'{self.name}_velocity_publisher')
        self.publisher_ = self.create_publisher(Float32, f'velocity_topics/{self.name}_velocity', 10)

    def publish_velocity(self, velocity):
        msg = Float32()
        msg.data = velocity
        self.publisher_.publish(msg)
        self.get_logger().info(f'Published {self.name} velocity: %f' % velocity)


class DriveWheel(Motor):
    def __init__(self, name):
        self.__name = name
        self.__velocity = 0.0
        self.__velo_pub = VelocityPublisher(self.__name)
        self.__wheel_radius = WHEEL_RADIUS
        
    def set_radius(self, radius):
        self.__wheel_radius = radius
        
    def calculate_velocity(self):
        # Insert code here to calculate the velocity of the wheel
        self.__velo_pub.publish_velocity(self.__velocity)