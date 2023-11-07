"""
File: ArmRobot.py

Description:This module defines the ArmRobot class, which represents an arm robot with multiple joints. 
It provides functionality to add links to the arm, move individual joints, update the Denavit-Hartenberg 
(DH) table, and perform forward and inverse kinematics calculations.


Author: Ryan Barry
Date Created: October 5, 2023
"""

from hardware.subsystems.arm.ArmRobotKinematics import PRISMATIC, REVOLUTE, ArmRobotKinematics
from hardware.subsystems.cameras.ArmCamera import ArmCamera

class ArmRobot(ArmRobotKinematics):
    def __init__(self):
        super().__init__()
        '''
        Additional initialization code specific to the arm robot:
        This is where you will define the configuration of your robot with the addLink method

        Example Usage:
            # Add a link called link0 with a revolute joint and length 1 (m) and a parallel z axis
            self.link0 = self.addLink(joint_type=REVOLUTE, length=1, alpha=0)
            # Add a prismatic joint with an initial extended length of 1 (m) and a z axis rotated 90 degrees
            self.link1 = self.addLink(joint_type=PRISMATIC, length=1, alpha=math.rad(90))
        '''
        self.camera = ArmCamera()
         
    def inverse_kinematics(self, target_position, target_orientation):
        # Override the generic inverse kinematics method
        # Implement the specific inverse kinematics calculations for the arm robot
        pass
