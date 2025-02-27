
#include "pros/rtos.hpp"
#include "robot/basics.hpp"
#include "robot/robot.hpp"

using namespace robot;
using namespace robot::drive;
using namespace robot::subsys;
using namespace voss;
/*
 * NR = no rush (left quadrant from red's perspective)
 * RS = rush side (right quadrant from red's perspectve)
 * TODO: Add auton descriptions
*/
namespace autons::blocks {
    /**
     * Reusable in game autons for the following:
     * 1. Get mogo
     * 2. Score preload
     * 3. Score stack next to NR square
    */
    void game_get_mogo(bool mirror=false) {
        bool old_mirror = mirrored;
        if (mirror) { set_mirroring(!old_mirror); } // because it was coded from the perspective of RS...
        /**
        * Get mogo
        */
        mogo.extend();
        go(-16);
        //go(-3, 30);
        swing(-120, true);
        go(-12, 20);
        mogo.retract();
        pros::delay(500);
        auton::checkpoint("Grabbed mogo");

        set_mirroring(old_mirror);
    }
}
namespace autons::shared {
    /**
     * @brief An auton whose only goal is to gain the Autonomous Win Point (AWP).
     *
     * @note This auton was designed with intake raise and odom.
     *
     * @details
     * Starting position: NR starting position
     * 1. Aligns with alliance wall stake & scores preload
     * 2. Gets mogo
     * 3. Get NR square rings
     * 4. Touch ladder
    //  */
    void awp() {
        auton::start({0,0,180}); // UTB mirrored ? 0 : 180 ; please test auto mirroring
        /**
         * Align with alliance wall stake & score preload
         */
        go(-16);
        face(90);
        go(-9);
        go(-2);
        go(1.75);
        intake(Direction::FORWARD);
        pros::delay(550);
        /**
         * Get mogo
         */
        go(10);
        face(-49);
        mogo.extend();
        go(-27);
        intake(Direction::STOP);
        go(-10, 30);
        mogo.retract();
        pros::delay(800);

        auton::checkpoint("Got mogo");
        /**
         * Get NR square ring
         */
        face(139);
        intake(Direction::FORWARD);
        go(17.5);
        pros::delay(400);
        /**
         * Get ring from stack next to square
         */
        swing(-32, true);
        go(20);
        pros::delay(400);

        auton::checkpoint("Got da goods");
        /**
         * Touch ladder
         */
        go(-25);
        go(-5, 60);

        auton::checkpoint("Touched ladder");
        auton::end();
    }
    void autonomous_skills() {
        auton::start({0, 0, 90});

        intake(Direction::FORWARD);
        pros::delay(1000);
        go(15);
        face(0);
        mogo.extend();
        intake(Direction::STOP);
        go(-20, 20);
        mogo.retract();
        pros::delay(500);

        face(105);
        intake(Direction::FORWARD);
        go(25);
        face(175);
        go(20);

        face(-90);
        go(27);
        pros::delay(1000);

        go(-12);
        face(180);

        go(12);
        face(90);
        go(40);

        pros::delay(1000);
        go(-45);
        face(45);
        go(-20);
        mogo.extend();
        pros::delay(1000);

        go(20);

        auton::end();
    }
    void null_auton() {
        //go(-24);
        auton::start({29.25,0,270});
        go(-24);
        auton::end();
    }
}
namespace autons::nr {
    /**
     * 1. Use reusable block to get mogo, score 2
     * 2. Score & disrupt NR square
     * 3. Score ring from stack next to square
     * 4. Touch ladder
     */
    void awp_pos() {
        auton::start({-24, 0, 270});
        /**
         * Use reusable block to get mogo, score 2
         */
        blocks::game_get_mogo();

        /*
         * Score & disrupt NR square
         */
        // first
        face(135);
        intake(Direction::FORWARD);
        go(15.75, 50);
        pros::delay(300);
        // second
        swing(155, true);
        go(5, 35);
        auton::checkpoint("Scored 1st NR square ring");
        /**
         * Score rings from stack next to square
         */
        pros::delay(1500);
        drive::chassis.turn(
            mirrored ? 180 - (0) : 0,
            drive::swing_ctr,
            100.0,
            voss::Flags::NONE, // or voss::Flags::REVERSE
            mirrored ? voss::AngularDirection::CLOCKWISE : voss::AngularDirection::COUNTERCLOCKWISE
        );
        go(7);
        auton::checkpoint("Scored rings from stack next to square");
        /**
         * Touch ladder
         */
        go(-7);
        pros::delay(1000);
        // run for loop 
        face(210);
        face(150);
        face(210);
        face(150);

        auton::checkpoint("Touched ladder");
        auton::end();
    }
}
namespace autons::rs {
    /**
     * 1. Use reusable block to get mogo
     * 2. Score preload + other ring
     * 3. Touch ladder using endgame
    */
    void awp_pos() {
        auton::start({24, 0, 270});
        /**
         * Get mogo
         */
        blocks::game_get_mogo(true);
        /*
         * Score preload + other ring
         */
        face(-3);
        intake(Direction::FORWARD);
        go(12);
        go(3,50);
        auton::checkpoint("Scored preload + ring");
        /**
         * Touch ladder
         */
        pros::delay(3000);
        intake(Direction::STOP);
        face(0);
        go(-20, 80);
        face(150);
        go(12, 20);
        face(180, 20);
        auton::checkpoint("Touched ladder");
        auton::end();
    }
}
namespace autons {
    std::map<std::string, VoidFn> game_autons = {
        {"1-NIL", shared::null_auton},
        {"2-NR AWP POS", nr::awp_pos},
        {"3-RS AWP POS", rs::awp_pos},
        {"4-AWP BETA", shared::awp}
    };
    int default_auton = 2;
    VoidFn auton_skills = autons::shared::autonomous_skills;
}
