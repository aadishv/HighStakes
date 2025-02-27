#include "VOSS/utils/Pose.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/motors.h"
#include "robot/config.hpp"

#include "VOSS/controller/PIDController.hpp"
#include "VOSS/exit_conditions/ExitConditions.hpp"
#include "VOSS/controller/SwingController.hpp"
#include "VOSS/controller/SwingControllerBuilder.hpp"
#include <optional>

#if BUILDING_BACKUP_ODOM
#include "VOSS/localizer/IMELocalizerBuilder.hpp"
#else
#include "VOSS/localizer/TrackingWheelLocalizerBuilder.hpp"
#endif

#include "VOSS/controller/PIDControllerBuilder.hpp"
#include "VOSS/controller/BoomerangControllerBuilder.hpp"

#include "VOSS/chassis/DiffChassis.hpp"

#include "pros/adi.hpp"

#include "pros/misc.hpp"
#include <string>
// warns compiler in case building for babybot
#if BUILDING_BABYBOT
#warning "Building for babybot, not main bot"
#endif
// declares EVERYTHING
namespace robot::drive {
    // odometry - configured for BABYBOT
    #if !BUILDING_BACKUP_ODOM
    // based on a conversation with Rocky from BLRS (PROS/VOSS team)
    auto _odom = voss::localizer::TrackingWheelLocalizerBuilder::new_builder()
                .with_right_rotation(PARALLEL_ROTATION)
                .with_middle_rotation(MIDDLE_ROTATION)
                .with_imu(IMU_PORT)
                .with_left_right_tpi(-BASE_TPI)
                .with_middle_tpi(BASE_TPI)
                .with_middle_dist(MIDDLE_DISTANCE)
                .build();
    #else
    // backup odom using IME's
    auto odom = voss::localizer::IMELocalizerBuilder::new_builder()
                .with_left_motors(LEFT_MOTORS)
                .with_right_motors(RIGHT_MOTORS)
                .with_track_width(BACKUP_TRACK_WIDTH)
                .with_left_right_tpi(BACKUP_BASE_TPI)
                .with_imu(IMU_PORT)
                .build();
    #endif
    // controllers
    auto pid = voss::controller::PIDControllerBuilder::new_builder(odom)
            .with_linear_constants(LINEAR_KP, LINEAR_KD, LINEAR_KI)
            .with_angular_constants(250, 0.05, 2435)
            .with_min_error(PID_MIN_ERROR)
            .with_min_vel_for_thru(PID_MIN_VEL_FOR_THRU)
            .build();
    auto swing_ctr = voss::controller::SwingControllerBuilder::new_builder(odom)
        .with_angular_constants(250, 0.05, 2435)
        .build();
    auto boomerang = voss::controller::BoomerangControllerBuilder::new_builder(odom)
            .with_linear_constants(20, 0.02, 169)
            .with_angular_constants(250, 0.05, 2435)
            .with_lead_pct(0.5)
            .with_min_vel_for_thru(70)
            .with_min_error(5)
            .build();
    // controllers
    auto ec = voss::controller::ExitConditions::new_conditions()
            .add_settle(EC_SETTLE_1, EC_SETTLE_2, EC_SETTLE_3)
            .add_tolerance(EC_TOLERANCE_1, EC_TOLERANCE_2, EC_TOLERANCE_3)
            .add_timeout(EC_TIMEOUT)
            .add_thru_smoothness(EC_THRU_SMOOTHNESS)
            .build();
    // chassis
    auto chassis = voss::chassis::DiffChassis(
        LEFT_MOTORS,
        RIGHT_MOTORS,
        pid,
        ec,
        8,
        pros::motor_brake_mode_e::E_MOTOR_BRAKE_BRAKE
    );
}
namespace robot::subsys {
    pros::MotorGroup intake_motor(INTAKE_MOTORS, pros::MotorGears::blue, pros::MotorUnits::deg);
    pros::Motor wsm_motor(WSM_MOTOR, pros::MotorGears::green, pros::MotorUnits::deg);
    pros::adi::Pneumatics mogo(MOGO_MECH_PORT, false, false);
    pros::adi::Pneumatics intake_raise(INTAKE_RAISE_PORT, false, false);
    pros::adi::Pneumatics doinker(DOINKER_PORT, false, false);
    pros::adi::Pneumatics endgame_raise(ENDGAME_RAISE_PORT, false, false);
}

namespace robot {
    pros::Controller controller(pros::E_CONTROLLER_MASTER);

    void log(std::string message, std::string end = "\n") {
        if (!pros::competition::is_connected()) {
            std::cout << message << end;
        }
    }
    void log_pose(std::string end = "\n") {
        if (!pros::competition::is_connected()) {
            auto x = std::to_string(drive::odom->get_x());
            auto y = std::to_string(drive::odom->get_y());
            auto heading = std::to_string(drive::odom->get_orientation_deg());
            std::string tmp = "{" + x + ", " + y + ", " + heading + "}";
            std::cout << tmp << end;
        }
    }
    void rumble(const char* pattern) {
        if (!pros::competition::is_connected()) {
            controller.rumble(pattern);
        }
    }

}
