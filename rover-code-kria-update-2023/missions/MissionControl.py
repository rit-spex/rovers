#!/usr/bin/env python3
"""
File: mission_control.py
Description: This script serves as the main control module for a rover system.
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
#Access locally store rclpy file 
sys.path.append("..")
from hardware.Rover import Rover
from testing.Test import TestingEnvironment


class MissionControl:
    """manages missions that the rover can execute.
            
        Contains:
            - methods for executing the mission control logic
            - methods for switching between missions
            - a Rover object used to interface with the rover's hardware components
    """
    def __init__(self):
        # initialize all missions with their respective classes
        self.rover = Rover()
        self.testing_environment = TestingEnvironment(self.rover)
        self.autonomous_navigation = AutonomousNavigationMission(self.rover)
        self.equipment_servicing = EquipmentServicingMission(self.rover)
        self.extreme_retrieval_delivery = ExtremeRetrievalDeliveryMission(self.rover)
        self.science_mission = ScienceMission(self.rover)

    
    def exec(self):
        """Executes the mission control logic.

        This method is called in the main loop of the rover's main control script.
        """
        
        # Run testing environment if Rover in TEST_MODE
        # Use TEST_MODE for hardware bringup
        if self.rover.status.operating_mode == TEST_MODE:
            self.testing_environment.run()
        
        else:  # all missions are empty
            mission = self.rover.get_mission()
            if mission == AUTONOMOUS:
                self.autonomous_navigation.run()
            if mission == EQUIPMENT_SERVICING:
                self.equipment_servicing.run()
            if mission == EXTREME_RETRIEVAL_DELIVERY:
                self.extreme_retrieval_delivery.run()
            if mission == SCIENCE:
                self.science_mission.run()
