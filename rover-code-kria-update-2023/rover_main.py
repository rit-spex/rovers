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


def main(args=None):
    # Initialize the ROS client library
    rclpy.init(args=args)

    # Create an instance of the MissionControl class
    mission_control = MissionControl()

    # loop until ROS shutdown
    while rclpy.ok():
        mission_control.exec()                          # Execute the mission control logic
        rclpy.spin_once(mission_control.controller)     # Spin the controller node
        # TODO figure out what spin means   
        #link for spin once -> https://docs.ros2.org/foxy/api/rclpy/api/init_shutdown.html#rclpy.spin_once

    # Shutdown the ROS client library
    rclpy.shutdown()


if __name__ == "__main__":
    try:
        main()
    except Exception as E:
        print(E.args)
        rclpy.shutdown()
