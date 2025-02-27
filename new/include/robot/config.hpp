#pragma once
/*
 * NOTE: All of the below boolean macros should be set to false when building
 * in a competition ready mode. (That is, we are building for the main bot
 * without odometry logging or the backup odometry).
 * Most of the derivative actions from these bools already are gated behind
 * competition checks, but it is still good practice to set them to false.
*/
// whether build for main bot or baby (testing) bot
#define BUILDING_BABYBOT false
#if BUILDING_BABYBOT
#warning "WARNING: Building for babybot. This code version SHOULD NOT be used in competition."
#endif
// defines whether or not we should run odometry logging on the brain if not
// connected to competition. if defined, will disable auton selector when not
// connected to competition. no matter what, we log odom on terminal when not
// connected regardless of this flag
#define BUILDING_ODOM_LOGGING false
// defines whether to build using regular (tracking wheel) odometry or our
// backup (IME) odom
#define BUILDING_BACKUP_ODOM true
// main statement
#if !BUILDING_BABYBOT // MAIN BOT CONFIG
// motors
#define LEFT_MOTORS {-11, -12, -13}
#define RIGHT_MOTORS {18, 19, 20}
#define INTAKE_MOTORS {-1, 2}
#define WSM_MOTOR 3
// pneumatics
#define MOGO_MECH_PORT 'A'
#define ENDGAME_RAISE_PORT 'B'
#define DOINKER_PORT 'C'
#define INTAKE_RAISE_PORT 'D'
// odom
#define MIDDLE_ROTATION 0
#define PARALLEL_ROTATION 0
#define IMU_PORT 15

#define MIDDLE_DISTANCE 3.5 // still set to babybot

#define BASE_TPI 36000/(2.75*M_PI)

#define BACKUP_TRACK_WIDTH 10.5
#define BACKUP_BASE_TPI (300/(3.25*M_PI))*48/36
// PID constants
#define LINEAR_KP 20
#define LINEAR_KD 0.02
#define LINEAR_KI 169

#define ANGULAR_KP 225
#define ANGULAR_KD 0.025
#define ANGULAR_KI 2435

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
#define EC_TIMEOUT 2000
#define EC_THRU_SMOOTHNESS 4
#else // includes the babybot config
#include "babybot_config.hpp"
#endif // BUILDING_BABYBOT
