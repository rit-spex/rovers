#!/usr/bin/env python3
"""
File: rover_main.py

Description: This script serves as the main control module for a rover system. 
It utilizes the Robot Operating System (ROS) client library (rclpy) to interface 
with the rover's hardware components. The program instantiates the MissionControl class 
responsible for managing various missions that the rover can execute.

Author: Ryan Barry
Date Created: August 26, 2023
"""

import rclpy
from missions.MissionControl import MissionControl

def main():
    rclpy.init()
    mission_control = MissionControl()
    print("mother fucker")
    while rclpy.ok():
        # print("Here")
        mission_control.exec()
        # rclpy.spin(mission_control.controller) # what is controller?

    rclpy.shutdown()


if __name__ == "__main__":
    try:
        main()
    except Exception as E:
        print(f"main failed argument: {E.args}")
        rclpy.shutdown()
