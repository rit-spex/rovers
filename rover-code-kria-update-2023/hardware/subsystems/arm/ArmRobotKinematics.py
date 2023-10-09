"""
File: ArmRobotKinematics.py

This module defines the ArmRobot class, which represents an arm robot with multiple joints.
It provides functionality to add links to the arm, move individual joints, update the
Denavit-Hartenberg (DH) table, and perform forward kinematics to compute the end-effector
position and orientation.

Author: Ryan Barry
Date created: June, 26 2023
"""

import numpy as np  # Importing the NumPy library for mathematical operations
from Link import PRISMATIC, REVOLUTE, Link


class ArmRobotKinematics:
    def __init__(self):
        # self.num_joints = 0  # Initialize the number of joints to 0
        self.links = []
        self.__theta = []  # Private list to store joint angles
        self.__d = []  # Private list to store d parameters
        self.__a = []  # Private list to store a parameters
        self.__alpha = []  # Private list to store alpha parameters
        self.dhTable = None  # Initialize DH table as None

    # Add a link to the arm
    # Parameters:
    #   joint_type:
    #       - REVOLUTE
    #       - PRISMATIC
    #   length (meters)
    #   alpha (radians)
    #       - rotate around the x1 axis an angle alpha to make z1 parallel to z2
    def addLink(self, joint_type, length, alpha):
        self.links.append(Link(joint_type=joint_type, length=length, alpha=alpha))
        self.updateDHTable()
        return self.links[len(self.links) - 1]

    def updateDHTable(self):
        if self.dhTable is None:
            self.__theta = [0] * len(self.links)  # Initialize theta as a list of zeros
            self.__d = [0] * len(self.links)  # Initialize d as a list of zeros
            self.__a = [0] * len(self.links)  # Initialize a as a list of zeros
            self.__alpha = [0] * len(self.links)  # Initialize alpha as a list of zeros

            for i, link in enumerate(self.links):
                self.__theta[i] = link.theta
                self.__a[i] = link.a
                self.__d[i] = link.d
                self.__alpha[i] = link.alpha

        theta = np.array(self.__theta)
        d = np.array(self.__d)
        a = np.array(self.__a)
        alpha = np.array(self.__alpha)

        # Create the DH table using NumPy
        self.dhTable = np.column_stack((theta, d, a, alpha))

        # Compute the forward kinematics based on the updated DH Table and return the transformation matrix
        return self.forward_kinematics()

    def forward_kinematics(self):
        self.__A = []  # Initialize A matrices as empty list
        self.__T = np.identity(4)  # Initialize the transformation matrix as an identity matrix

        for i, link in enumerate(self.links):
            theta = self.__theta[i]  # Get the joint angle
            d = self.__d[i]  # Get the d parameter
            a = self.__a[i]  # Get the a parameter
            alpha = self.__alpha[i]  # Get the alpha parameter

            ct = np.cos(theta)  # Compute the cosine of theta
            st = np.sin(theta)  # Compute the sine of theta
            ca = np.cos(alpha)  # Compute the cosine of alpha
            sa = np.sin(alpha)  # Compute the sine of alpha

            if link.joint_type == REVOLUTE:  # Check if the joint type is revolute
                self.__A.append(
                    np.array(
                        [
                            [ct, -st * ca, st * sa, a * ct],  # Create the transformation matrix A
                            [st, ct * ca, -ct * sa, a * st],
                            [0, sa, ca, d],
                            [0, 0, 0, 1],
                        ]
                    )
                )

            elif link.joint_type == PRISMATIC:  # Check if the joint type is prismatic
                self.__A.append(
                    np.array(
                        [
                            [ct, -st * ca, st * sa, ct * d],  # Create the transformation matrix A
                            [st, ct * ca, -ct * sa, st * d],
                            [0, sa, ca, a],
                            [0, 0, 0, 1],
                        ]
                    )
                )
            else:
                print(f"Invalid joint type at joint {i}")
                return None

            self.__T = np.dot(self.__T, self.__A[i])  # Multiply the transformation matrix T by A

        return self.__T  # Return the final transformation matrix

    def inverse_kinematics(self, target_position, target_orientation):
        pass
