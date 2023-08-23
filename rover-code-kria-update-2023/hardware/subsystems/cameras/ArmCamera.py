"""
File: ArmCamera.py

Description: This file contains attributes for the rover's hand camera on the arm
Any peripheral related to this camera (servos etc) should be instantiated here.

Author: Ryan Barry
Date Created: August 23, 2023
"""
import sys
sys.path.append("../..")
from sensors.Camera import Camera
from RoverPinout import ARM_CAMERA_INDEX

class ArmCamera(Camera):
    def __init__(self, name="arm_camera", camera_index=ARM_CAMERA_INDEX):
        super().__init__(self, name, camera_index)

    def rotate(self):
        pass