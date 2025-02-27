#include "VOSS/utils/Pose.hpp"
#include "robot/basics.hpp"

namespace robot::drive {
    // utilities
    bool mirrored = false; // false = red
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
    // and we're back to the OU days :(
    void face(double angle, double speed = 100) {
        auto ang = mirrored ? 180 - angle : angle;
        chassis.turn(ang, speed);
    }
    void swing(double angle, bool reversed = false) {
        auto ang = mirrored ? 180 - angle : angle;
        drive::chassis.turn(
            ang,
            drive::swing_ctr,
            100.0,
            reversed ? voss
            ::Flags::REVERSE : voss::Flags::NONE
        );
    }
    void go(double distance, float speed = 100) {
        chassis.move(distance, speed, distance < 0 ? voss::Flags::REVERSE : voss::Flags::NONE);
    }
    /**
     * @warning NOT TESTED. Heavily test this before using it.
     * Moves the robot in an arc.
     * @param left_speed The speed of the left side of the robot.
     * @param right_speed The speed of the right side of the robot.
     * @param delay How long to wait, in milliseconds, before ending the movement.
     */
    void arc(double left_speed, double right_speed, double delay) {
        chassis.tank(mirrored ? right_speed : left_speed, mirrored ? left_speed : right_speed);
        pros::delay(delay);
        chassis.tank(0, 0);
    }
}


















































/*
// Robot pose; allows for aggregate initialization such as Rose x = {.x = 5};
struct Rose { // robot pose
    std::optional<double> x = std::nullopt;
    std::optional<double> y = std::nullopt;
    std::optional<double> theta = std::nullopt;
};
// Builder-based notation to configure drivetrain movements
class RobotConfig {
    public:
    voss::Flags flags = voss::Flags::NONE;
    float speed = 100.;
    voss::AngularDirection direction = voss::AngularDirection::AUTO;
    bool use_boomerang = false;
    bool auto_y_reverse = true;
    bool turn = false;
    RobotConfig() {};
};
class DriveConfigBuilder {
    private:
    RobotConfig config;
    public:
    DriveConfigBuilder() { config = RobotConfig();};

    void add_flags(voss::Flags flags) { config.flags = config.flags | flags; }
    void add_speed(float speed) { config.speed = speed; }
    void add_auto_y_reverse(bool state) { config.auto_y_reverse = state; }
    void add_use_boomerang(bool state) { config.use_boomerang = state; }

    RobotConfig build() {return config;};
};
class TurnConfigBuilder {
    private:
    RobotConfig config;
    public:
    TurnConfigBuilder() { config = RobotConfig(); config.turn = true; };

    void add_flags(voss::Flags flags) { config.flags = config.flags | flags; }
    void add_speed(float speed) { config.speed = speed; }
    void add_direction(voss::AngularDirection direction) { config.direction = direction; }

    RobotConfig build() {return config;}
};


namespace robot::drive {
    // utilities
    bool mirrored = false; // false = red
    void set_mirroring(bool state) {
        mirrored = state;
    }
    void set_position(voss::Pose position) {
        odom->set_pose(position); // ADD MIRRORING DHRKGJLHKLWEHKLAS
    };
    void init() {
        odom->begin_localization();
        set_mirroring(false);
    }
    // main movement function
    void move(Rose point, RobotConfig config) {
        Rose position = point; // ADD MIRRORING SHRGKDJKLHsFGHSDJFL
        / *
        SITUATIONS:
        - turn is true OR only ti is set
        - only y is set
        - otherwise: just regular
        * /
        // turns
        if (config.turn && position.x.has_value() && position.y.has_value()) {
            chassis.turn_to(voss::Point{position.x.value(), position.y.value()}, config.speed, config.flags, config.direction);
            return;
        }
        else if (position.theta.has_value() && !position.x.has_value() && !position.y.has_value()) {
            chassis.turn(position.theta.value(), config.speed, config.flags, config.direction);
            return;
        }
        std::shared_ptr<voss::controller::AbstractController> controller = pid;
        if (config.use_boomerang) {controller = boomerang;}
        // going forward
        if (position.y.has_value() && !position.x.has_value() && !position.theta.has_value()) {
            voss::Flags flags = config.flags;
            if (config.auto_y_reverse && position.y.value() < 0) {
                flags = flags | voss::Flags::REVERSE;
            }
            chassis.move(position.y.value(), controller, config.speed, flags);
            return;
        }
        // substitution
        voss::Pose pose = voss::Pose{
            position.x.value_or(odom->get_x()),
            position.y.value_or(odom->get_y()),
            position.theta.value_or(odom->get_orientation_deg())
        };
        if (config.flags & voss::Flags::RELATIVE) {
            pose = voss::Pose{
                position.x.value_or(0),
                position.y.value_or(0),
                position.theta.value_or(0)
            };
        };
        // FINAL MOVEMENT: move to point/pose
        voss::Pose target = pose;
        if (position.x.has_value() && position.y.has_value() && !position.theta.has_value()) {
            target.theta = std::nullopt;
        }
        chassis.move(target, controller, config.speed, config.flags);
    }
}
*/
