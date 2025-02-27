#include "pros/motors.h"
#include "robot/basics.hpp"

namespace robot::subsys {
    Direction intake_state;

    void intake(Direction direction, float speed = 1) {
        intake_motor.move(speed * static_cast<int32_t>(static_cast<int32_t>(direction) * 1)); // doesn't work at 100% speed
        intake_state = direction;
    }
    void wsm(Direction direction, float speed = 1) {
        wsm_motor.move(speed * static_cast<int32_t>(static_cast<int32_t>(direction) * 1));
    }
    void init() {
        intake(Direction::STOP);
        wsm_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        doinker.retract();
        endgame_raise.retract();
        intake_raise.retract();
    }
}
