# CONNECTION STATUS CONSTANTS
CONNECTED = True
NOT_CONNECTED = False

# WAYPOINT STATUS CONSTANTS
WAYPOINT_INACTIVE = 100
WAYPOINT_ACTIVE = 101
WAYPOINT_COMPLETE = 102

# MISSION CONSTANTS
EXTREME_RETRIEVAL_DELIVERY = 200
SCIENCE = 201
AUTONOMOUS = 202
EQUIPMENT_SERVICING = 203
missions = [EXTREME_RETRIEVAL_DELIVERY, SCIENCE, AUTONOMOUS, EQUIPMENT_SERVICING]

# OPERATING MODE CONSTANTS
AUTONOMOUS_MODE = 300
DRIVER_CONTROL_MODE = 301
TEST_MODE = 302

# SCIENCE CONSTANTS
LIPID_DETECTED = 400
LIPID_NOT_DETECTED = 401
DNA_DETECTED = 402
DNA_NOT_DETECTED = 403

# LED STATUS CONSTANTS
OFF = 500
ON = 501
BLUE = 502
RED = 503
GREEN = 504

# ERROR CONSTANTS
MISSION_FAILURE = 600

# DRIVE BASE ATTRIBUTES
WHEEL_RADIUS = 8 * 0.0254  # (m)
BASE_WIDTH = [0.75, 0.75, 0.75, 0.75, 0.75, 0.75]  # (m)
GAMMA = [0, 0, 0, 0, 0, 0]
ALPHA = [0, 0, 0, 0, 0, 0]
BETA = [0, 0, 0, 0, 0, 0]
WHEEL_NAMES = [
    "front_left_wheel",
    "middle_left_wheel",
    "back_left_wheel",
    "front_right_wheel",
    "middle_right_wheel",
    "back_right_wheel",
]
KP = [1.0, 1.0, 1.0, 1.0, 1.0, 1.0]
KI = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
KD = [0.1, 0.1, 0.1, 0.1, 0.1, 0.1]
