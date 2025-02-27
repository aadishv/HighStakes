#include "robot/systems.hpp"

#include "VOSS/selector/Selector.hpp"
#include <map>
#include <string>

using VoidFn = void(*)();

namespace robot::selector {
    const char* game_auton_names[11];
    std::map<std::string, VoidFn> _game_autons;
    VoidFn skills;
    int selected_auton;
    bool showing_graphics;

    void update_names() {
        int i = 0;
        for (auto it = _game_autons.begin(); it != _game_autons.end(); ++it) {
            game_auton_names[i] = (it->first).c_str();
            i++;
        }
        game_auton_names[i] = "";
    }

    void init(std::map<std::string, VoidFn> game_autons, VoidFn skills_auton, int default_auton, bool show_graphics = true) {
        selected_auton = default_auton;
        _game_autons = game_autons;
        skills = skills_auton;
        showing_graphics = show_graphics;
        // auton selector setup
        update_names();
        const char** game_auton_names_ptr = game_auton_names;
        // start VOSS selector
        if (showing_graphics) {
            voss::selector::init(default_auton, game_auton_names_ptr);
        }
    }

    void run_auton() {
        // get the selected auton index
        update_names();
        if (showing_graphics) {
            selected_auton = voss::selector::get_auton(); // index + 1; neg if blue
        }
        if (selected_auton < 0) {
            robot::drive::set_mirroring(true);
            selected_auton *= -1;
        }
        // run the auton if its skills
        if (selected_auton == 0) {
            skills();
            return;
        }
        // run game auton
        auto name = game_auton_names[selected_auton-1];
        void(*fn)() = _game_autons.at(name);
        fn();
    }
}


namespace robot::auton {
    int _checkpoint = 0;
    int start_time;
    void start(voss::Pose starting_pose) {
        voss::Pose adjusted_pose = drive::mirrored ? voss::Pose{starting_pose.x, starting_pose.y, 180.0 - starting_pose.theta.value()} : starting_pose;
        drive::odom->set_pose(starting_pose);
        start_time = pros::millis();
    }
    void checkpoint(std::optional<std::string> point = std::nullopt) {
        std::string msg = "Checkpoint " + std::to_string(_checkpoint);
        if (point.has_value()) {
            msg += ", " + point.value() + ", ";
        }
        msg += " at " + std::to_string((pros::millis()-start_time)) + " ms";
        robot::log(msg);
        _checkpoint++;
    }
    void end() {
        robot::log("Auton ended after " + std::to_string((pros::millis()-start_time)) + " ms");
    }
}
