#include "main.h"

#include "autons.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "robot/config.hpp"

using namespace robot;
using namespace robot::drive;

/**
 * Blocking init code
 */
void initialize() {
    robot::drive::init();
    robot::subsys::init();
    // if using intake v3 api
    //intv2::init({{0, intv2::RingColor::RED}, {37, intv2::RingColor::NONE}});
    bool show_selector = pros::competition::is_connected() || !BUILDING_ODOM_LOGGING;
    robot::selector::init(autons::game_autons, autons::auton_skills, autons::default_auton, show_selector);
    if (!show_selector) {
        pros::lcd::initialize();
    }
}
/**
 * auton
 */
void autonomous() {
    robot::selector::run_auton();
}

/**
 * driver control
 */
void opcontrol() {
    robot::subsys::init();
    robot::log("opcontrol");
    int frame = 0;
    int time_state = 0;
    auto initial_time = pros::millis();
    while (true) {
        // chassis controls
        chassis.arcade(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
                       controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        // intake controls
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
            if (subsys::intake_state == Direction::FORWARD) {
                subsys::intake(Direction::STOP);
            }
            else {
                subsys::intake(Direction::FORWARD);
            }
        }
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
            if (subsys::intake_state == Direction::REVERSE) {
                subsys::intake(Direction::STOP);
            }
            else {
                subsys::intake(Direction::REVERSE);
            }
        }
        // endgame controls
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            subsys::wsm(Direction::REVERSE);
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            subsys::wsm(Direction::FORWARD);
        }
        else {
            subsys::wsm(Direction::STOP);
        }
        // mogo mech controls
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
            subsys::mogo.extend();
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
            subsys::mogo.retract();
        // endgame controls
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
            subsys::endgame_raise.extend();
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
            subsys::endgame_raise.retract();
        // doinker controls
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
            subsys::doinker.extend();
        else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
            subsys::doinker.retract();
        // dv utils
        frame = frame % 10;
        if (!pros::competition::is_connected()) {
            if (!frame) {
                robot::log_pose();
            }
            #if BUILDING_ODOM_LOGGING
            voss::Pose p = odom->get_pose();
            pros::lcd::clear_line(1);
            pros::lcd::clear_line(2);
            pros::lcd::clear_line(3);
            pros::lcd::print(1, std::to_string(p.x).c_str());
            pros::lcd::print(2, std::to_string(p.y).c_str());
            pros::lcd::print(3, "%lf", odom->get_orientation_deg());
            pros::lcd::print(4, "%s", (odom == nullptr) ? "true" : "false");
            #endif
            if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
                robot::selector::run_auton();
            }
            if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
                robot::drive::odom->set_pose({0,0,0});
            }
        }
        if (pros::competition::is_connected()) {
            auto time_remaining = 105*1000 - (pros::millis() - initial_time);
            if (time_remaining <= 5000 && frame < 1) {
                subsys::endgame_raise.extend();
            }
            if (time_remaining <= 2000 && frame < 2) {
                subsys::mogo.extend();
                subsys::doinker.retract();
            }
        }
        frame += 1;
        pros::delay(20);
    }
}
