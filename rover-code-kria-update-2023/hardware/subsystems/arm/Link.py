"""
File: Link.py

Description: This module defines the Link class which represents a single link in an arm robot.  
It contains the joint type, length, angle and methods to move the joint.

Author: Ryan Barry 
Date Created: October 6, 2023
"""
import numpy as np

PRISMATIC = 0
REVOLUTE = 1

class Link:
    def __init__(self, joint_type, length, theta_fix=0, a=0, alpha_fix=0):
        self.joint_type = joint_type
        # Rotate about the z_n axis an angle theta_n+1 to make x_n parallel to x_n+1
        self.theta_fix = theta_fix
        self.theta = self.theta_fix
        # Translate along the z_n axis a distance d_n+1 to make x_n and x_n+1 collinear
        self.d = length
        # Translate along the (already rotated) x_n axis at a distance of a_n+1 to 
        # bring the origins of x_n and x_n+1 together
        self.a = a
        # otate the z_n axis about the x_n+1 axis an angle of alpha_n+1 to align the 
        # z_n axis with the z_n+1 axis
        self.alpha_fix = alpha_fix
        self.alpha = alpha_fix
        
            
        
    def moveJoint(self, joint_value):
        if self.joint_type == REVOLUTE:
            self.theta = self.theta_fix + joint_value
        elif self.joint_type == PRISMATIC:
            self.d = length + joint_value
        else:
            print(f"Invalid joint type at joint {joint}")
            return None
        
        
    def transform_matrix(self):
        ct = np.cos(self.theta)  # Compute the cosine of theta
        st = np.sin(self.theta)  # Compute the sine of theta
        ca = np.cos(self.alpha)  # Compute the cosine of alpha
        sa = np.sin(self.alpha)  # Compute the sine of alpha
        a = self.a
        d = self.d
        
        return np.array(
                            [
                                [ct, -st * ca, st * sa, a * ct],  # Create the transformation matrix A
                                [st, ct * ca, -ct * sa, a * st],
                                [0, sa, ca, d],
                                [0, 0, 0, 1]
                            ]
                        )
