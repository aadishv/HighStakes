#pragma once
// motors
#define LEFT_MOTORS { 9 } // babybot
#define RIGHT_MOTORS { -2 } // bbybot
#define INTAKE_MOTORS { 0 } 
// pneumatics
#define MOGO_MECH_PORT 'A'
#define INTAKE_RAISE_PORT 'A'
#define ENDGAME_RAISE_PORT 'A'
// odom
#define MIDDLE_ROTATION 1 
#define PARALLEL_ROTATION 10
#define IMU_PORT 21

#define MIDDLE_DISTANCE 4

#define BASE_TPI 36000/(2.75*M_PI)

#define BACKUP_TRACK_WIDTH  11.5
#define BACKUP_BASE_TPI 900/(4.00*M_PI)
// PID constants
#define LINEAR_KP 20
#define LINEAR_KD 0.001
#define LINEAR_KI 185

#define ANGULAR_KP -35
#define ANGULAR_KD -0.07
#define ANGULAR_KI -500

#define PID_MIN_ERROR 5
#define PID_MIN_VEL_FOR_THRU 70
#define BOOMERANG_LEAD_PCT 0.5
// exit conditions
#define EC_SETTLE_1 400
#define EC_SETTLE_2 0.5
#define EC_SETTLE_3 400
#define EC_TOLERANCE_1 1.0
#define EC_TOLERANCE_2 2.0
#define EC_TOLERANCE_3 200
#define EC_TIMEOUT 22500
#define EC_THRU_SMOOTHNESS 4