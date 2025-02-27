#pragma once

#include "config.hpp"
#include "pros/abstract_motor.hpp"

#if BUILDING_BACKUP_ODOM
#include "VOSS/localizer/IMELocalizer.hpp"
#else
#include "VOSS/localizer/TrackingWheelLocalizer.hpp"
#endif

#include "VOSS/controller/PIDController.hpp"
#include "VOSS/controller/BoomerangController.hpp"
#include "VOSS/controller/SwingController.hpp"
#include "VOSS/exit_conditions/ExitConditions.hpp"
#include "VOSS/chassis/DiffChassis.hpp"

#include "pros/adi.hpp"

#include "pros/misc.hpp"
#include <string>

namespace robot::drive {
    #if BUILDING_BACKUP_ODOM
    extern std::shared_ptr<voss::localizer::IMELocalizer> odom;
    #else
    extern std::shared_ptr<voss::localizer::TrackingWheelLocalizer> odom;
    #endif
    extern std::shared_ptr<voss::controller::PIDController> pid;
    extern std::shared_ptr<voss::controller::BoomerangController> boomerang;
    extern std::shared_ptr<voss::controller::ExitConditions> ec;
    extern std::shared_ptr<voss::controller::SwingController> swing_ctr;
    extern voss::chassis::DiffChassis chassis;
}
namespace robot::subsys {
    extern pros::MotorGroup intake_motor;
    extern pros::Motor wsm_motor;

    extern pros::adi::Pneumatics mogo;
    extern pros::adi::Pneumatics intake_raise;
    extern pros::adi::Pneumatics doinker;
    extern pros::adi::Pneumatics endgame_raise;
}

namespace robot {
    void rumble(const char* sequence);
    void log(std::string message, std::string end = "\n");
    void log_pose(std::string end = "\n");

    enum class Direction {
        FORWARD = 1,
        REVERSE = -1,
        STOP = 0
    };

    extern pros::Controller controller;
}
