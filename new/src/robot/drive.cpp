#include "VOSS/utils/Pose.hpp"
#include "robot/basics.hpp"

namespace robot::drive {
    bool mirrored = false;
    void set_mirroring(bool state) {
        mirrored = state;
    }
    void init() {
        odom->begin_localization();
        set_mirroring(false);
    }
    void set_position(voss::Pose position) {
        odom->set_pose({-position.x, position.y, position.theta});
    }
    double mirrored_angle(double angle) { return mirrored ? 180 - angle : angle; }
    void face(double angle, double speed = 100) {
        chassis.turn(mirrored_angle(angle), speed);
    }
    void swing(double angle, bool reversed = false) {
        drive::chassis.turn(
            mirrored_angle(angle),
            drive::swing_ctr,
            100.0,
            reversed ? voss::Flags::REVERSE : voss::Flags::NONE
        );
    }
    void go(double distance, float speed = 100) {
        chassis.move(distance, speed, distance < 0 ? voss::Flags::REVERSE : voss::Flags::NONE);
    }
    void arc(double left_speed, double right_speed, double delay) {
        chassis.tank(mirrored ? right_speed : left_speed, mirrored ? left_speed : right_speed);
        pros::delay(delay);
        chassis.tank(0, 0);
    }
}
