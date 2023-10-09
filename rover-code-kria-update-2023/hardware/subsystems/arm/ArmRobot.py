"""
File: ArmRobot.py

Description:This module defines the ArmRobot class, which represents an arm robot with multiple joints. 
It provides functionality to add links to the arm, move individual joints, update the Denavit-Hartenberg 
(DH) table, and perform forward and inverse kinematics calculations.


Author: Ryan Barry
Date Created: August 11, 2023
"""
import math
import sys

sys.path.append("../..")
from ArmRobotKinematics import PRISMATIC, REVOLUTE, ArmRobotKinematics
from Gripper import Gripper
from RoverPinout import *
from subsystems.cameras.ArmCamera import ArmCamera

BASE_LENGTH = 0
SHOULDER_LENGTH = 1
ELBOW_LENGTH = 1
ELBOW_LENGTH = 1
WRIST_TWIST_LENGTH = 0
WRIST_TWIST_ALPHA = math.rad(90)
WRIST_LENGTH = 1


class ArmRobot(ArmRobotKinematics):
    def __init__(self):
        super().__init__(self)
        # Additional initialization code specific to the arm robot
        self.camera = ArmCamera()

        self.base = self.addLink(joint_type=REVOLUTE, length=BASE_LENGTH)
        self.shoulder = self.addLink(joint_type=REVOLUTE, length=SHOULDER_LENGTH)
        self.elbow = self.addLink(joint_type=REVOLUTE, length=ELBOW_LENGTH)
        self.wrist_twist = self.addLink(
            joint_type=REVOLUTE, length=WRIST_TWIST_LENGTH, alpha=WRIST_TWIST_ALPHA
        )
        self.wrist_raise = self.addLink(joint_type=REVOLUTE, length=WRIST_LENGTH)

        self.gripper = Gripper()

    def inverse_kinematics(self, target_position, target_orientation):
        # Override the generic inverse kinematics method
        # Implement the specific inverse kinematics calculations for the arm robot
        pass
