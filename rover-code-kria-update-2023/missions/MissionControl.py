#!/usr/bin/env python3
"""
File: mission_control.py

Description: This script serves as the main control module for a rover system. 
It utilizes the Robot Operating System (ROS) client library (rclpy) to interface 
with the rover's hardware components. The program defines a MissionControl class 
responsible for managing various missions that the rover can execute. Each mission 
is represented by a separate class: AutonomousNavigationMission, 
EquipmentServicingMission, ExtremeRetrievalDeliveryMission, and ScienceMission.

Author: Ryan Barry
Date Created: July 16, 2023
"""

import sys

import rclpy
from AutonomousNavigation import AutonomousNavigationMission
from EquipmentServicing import EquipmentServicingMission
from ExtremeRetrievalDelivery import ExtremeRetrievalDeliveryMission
from hardware.RoverConstants import (
    AUTONOMOUS,
    EQUIPMENT_SERVICING,
    EXTREME_RETRIEVAL_DELIVERY,
    SCIENCE,
    TEST_MODE,
)
from ScienceMission import ScienceMission

sys.path.append("..")
from hardware.Rover import Rover
from testing.Test import TestingEnvironment


class MissionControl:
    def __init__(self):
        self.rover = Rover()
        # Implement the testing environment for rover upbringing and subsystem testing
        self.testing_environment = TestingEnvironment(self.rover)
        self.autonomous_navigation = AutonomousNavigationMission(self.rover)
        self.equipment_servicing = EquipmentServicingMission(self.rover)
        self.extreme_retrieval_delivery = ExtremeRetrievalDeliveryMission(self.rover)
        self.science_mission = ScienceMission(self.rover)

    def exec(self):  # Method for executing the mission control logic

        # Run testing environment if Rover in TEST_MODE
        # Use TEST_MODE for hardware bringup
        if self.rover.status.operating_mode == TEST_MODE:
            self.testing_environment.run()

        else:
            mission = self.rover.get_mission()
            if mission == AUTONOMOUS:
                self.autonomous_navigation.run()
            if mission == EQUIPMENT_SERVICING:
                self.equipment_servicing.run()
            if mission == EXTREME_RETRIEVAL_DELIVERY:
                self.extreme_retrieval_delivery.run()
            if mission == SCIENCE:
                self.science_mission.run()
