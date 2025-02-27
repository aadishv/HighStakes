#pragma once

#include "basics.hpp"

namespace robot::drive {
    extern bool mirrored; // false = red
    void init();

    void face(double angle, double speed = 100);
    void go(double distance, float speed = 100);
    void swing(double angle, bool reversed = false);

    void set_mirroring(bool state);
    double mirrored_angle(double angle);
    void set_position(voss::Pose position);
}

namespace robot::subsys {
    void init();

    extern Direction intake_state;

    void intake(float speed);
    void wsm(float speed);
    void intake(Direction direction);
}
