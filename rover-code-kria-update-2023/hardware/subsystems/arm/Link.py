"""
File: Link.py

Description: This module defines the Link class which represents a single link in an arm robot.  
It contains the joint type, length, angle and methods to move the joint.

Author: Ryan Barry 
Date Created: October 6, 2023
"""
PRISMATIC = 0
REVOLUTE = 1


class Link:
    def __init__(self, joint_type, length, alpha=0):
        self.joint_type = joint_type
        self.theta = 0
        self.a = 0
        self.d = 0
        # rotate around the x1 axis an angle alpha to make z1 parallel to z2
        self.alpha = alpha
        if self.joint_type == PRISMATIC:
            self.d = length
        elif self.joint_type == REVOLUTE:
            self.a = length
        else:
            print(f"Invalid joint type at joint {i}")

    def moveJoint(self, joint_value):
        if self.joint_type == REVOLUTE:
            self.theta = joint_value
        elif self.joint_type == PRISMATIC:
            self.d = joint_value
        else:
            print(f"Invalid joint type at joint {joint}")
            return None
