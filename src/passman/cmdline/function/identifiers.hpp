#pragma once

#include <array>
#include <string_view>

namespace Passman::CmdLine::Function {
    static std::array<std::string_view, 2> identifiers = {"add", "get"};
}
