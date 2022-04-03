#pragma once

#include <utility>
#include <vector>

#include "../Settings.hpp"
#include "function/OverloadingSet.hpp"

namespace Passman::CmdLine {
    std::pair<std::vector<Function::OverloadingSet>, std::vector<int>>
    parse_arguments(const int argc,
                    const char** const argv,
                    Settings& app_settings) noexcept; // return : function maped to its argv position, or in
                                                      // ohter words : "0" argument position
} // namespace Passman::CmdLine
