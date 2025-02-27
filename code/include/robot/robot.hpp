#pragma once

#include <map>
#include "systems.hpp"

using VoidFn = void(*)();

namespace robot::selector {
    void init(std::map<std::string, VoidFn> game_autons, VoidFn skills_auton, int default_auton, bool show_graphics = true);

    void run_auton();
}

namespace robot::auton {
    void start(voss::Pose starting_pose);
    void checkpoint(std::optional<std::string> point = std::nullopt);
    void end();
}
