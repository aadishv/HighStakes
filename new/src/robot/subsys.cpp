#include "pros/motors.h"
#include "robot/basics.hpp"

namespace robot::subsys {
    int intake_state = 0;
    int wsm_state = 0;
    void intake(float speed) {
        intake_motor.move(127 * speed);
        if (speed > 0)
            intake_state = 1;
        else if (speed < 0)
            intake_state = -1;
        else
            intake_state = 0;
    }
    void intake(Direction direction) {
        auto speed = static_cast<float>(direction);
        intake(speed);
    }
    void wsm(float speed) {
        wsm_motor.move(127 * speed);
        if (speed > 0)
            wsm_state = 1;
        else if (speed < 0)
            wsm_state = -1;
        else
            wsm_state = 0;
    }
    void init() {
        intake(0);
        wsm_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        doinker.retract();
        endgame_raise.retract();
        intake_raise.retract();
    }
}
