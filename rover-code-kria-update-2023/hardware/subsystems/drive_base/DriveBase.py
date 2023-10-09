#!/usr/bin/env python3
""" 
File: DriveBase.py 
 
Description: This file contains the implementation of a DriveBase class that 
extends the DifferentialDrive class. It provides methods for controlling the 
movement of a rover using drive wheels. 
 
Author: Ryan Barry
Date Created: August 12, 2023
"""
import sys

import numpy as np
import rclpy
from geometry_msgs.msg import Twist
from rclpy.node import Node
from std_msgs.msg import Float32

sys.path.append("../..")
from DifferentialDrive import DifferentialDrive
from DriveWheel import DriveWheel
from MobileRobotKinematics import MobileRobotKinematics
from RoverConstants import AUTONOMOUS_MODE, WHEEL_NAMES
from RoverPinout import *
from VelocityPublisher import VelocityPublisher


class DriveBase(MobileRobotKinematics, Node):
    def __init__(self, operating_mode):
        MobileRobotKinematics.__init__(self)
        Node.__init__("drive_base_node")
        self.left_sub = self._create_subscription(
            Float32, "drive_base/left_target_velocity", self.left_callback, 10
        )
        self.right_sub = self._create_subscription(
            Float32, "drive_base/right_target_velocity", self.right_callback, 10
        )
        self.rover_sub = self._create_subscription(
            Twist, "drive_base/target_rover_velocity", self.rover_callback, 10
        )
        self.left_velo_pub = self.create_publisher(Float32, "drive_base/left_target_velocity", 10)
        self.right_velo_pub = self.create_publisher(Float32, "drive_base/right_target_velocity", 10)

        self.operating_mode = operating_mode
        self.target_velocity_old = None
        self.target_left_velocity_old = None
        self.target_right_velocity_old = None

        # A dictionary of publishers for the targeted velocities of each wheel
        self.wheels = {}

        for i in range(len(WHEEL_NAMES)):
            name = WHEEL_NAMES[i]
            pwm_pin = WHEEL_PINS[f"{name}_pwm"]

            # Add a tuple of VelocityPublisher and DriveWheel objects to the
            # self.wheels dictionary for each wheel name
            velo_pub = VelocityPublisher(name)
            wheel = DriveWheel(name=name, pwm_pin=pwm_pin)
            self.wheels[name] = (velo_pub, wheel)

        rclpy.spin(self)

    def left_callback(self, msg):
        # Process left target velocity message
        if self.operating_mode == AUTONOMOUS_MODE:
            self.target_left_velocity = msg.data

    def right_callback(self, msg):
        # Process right target velocity message
        if self.operating_mode == AUTONOMOUS_MODE:
            self.target_right_velocity = msg.data

    def rover_callback(self, msg):
        # Process rover target velocity message
        if self.operating_mode == AUTONOMOUS_MODE:
            x = msg.linear.x
            y = msg.linear.y
            z = msg.linear.z
            w = msg.angular.z
            self.target_velocity = np.array([[x], [y], [z], [w]])

    def set_right_velo(self, velocity):
        msg = Float32()
        msg.data = velocity
        self.right_velo_pub.publish(msg)

    def set_left_velo(self, velocity):
        msg = Float32()
        msg.data = velocity
        self.left_velo_pub.publish(msg)

    def run(self):
        if self.target_velocity != self.target_velocity_old:
            self.inverse_kinematics()
            self.target_velocity_old = self.target_velocity

        if (
            self.target_left_velocity != self.target_left_velocity_old
            or self.target_right_velocity != self.target_right_velocity_old
        ):
            self.forward_kinematics()
            self.target_left_velocity_old = self.target_left_velocity
            self.target_right_velocity_old = self.target_right_velocity

        for i, velo in enumerate(self._phi):
            # Publish the velocity to its corresponding DriveWheel
            self.wheels[WHEEL_NAMES[i]][0].publish_velocity(velo)
            # Update the pwm signal of the DriveWheel
            self.wheels[WHEEL_NAMES[i]][1].update_pwm()
