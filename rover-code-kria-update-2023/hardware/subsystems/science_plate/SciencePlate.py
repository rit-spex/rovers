#!/usr/bin/env python3
"""
File: SciencePlate.py

Description:

Author: Ryan Barry
Date Created:
"""
import sys

sys.path.append("../..")

from Backpack import Backpack
from DNADetector import DNADetector
from HeatBlock import HeatBlock
from LipidDetector import LipidDetector
from sensors.Fluorometer import Fluorometer
from sensors.Humidity import Humidity
from subsystems.cameras.ScienceCamera import ScienceCamera


class SciencePlate:
    def __init__(self):
        self.camera = ScienceCamera()
        self.fluorometer = Fluorometer()
        self.humidity_sensor = Humidity()
        self.heat_block = HeatBlock()
        self.backpack = Backpack()
        self.lipid_detector = LipidDetector()
        self.dna_detector = DNADetector()
