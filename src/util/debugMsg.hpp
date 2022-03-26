#pragma once

#include <experimental/source_location>
#include <iostream>
#include <string_view>

#include "DebugVariable.hpp"

static auto debugMsg(const std::string_view msg,
                     const std::experimental::source_location location =
                         std::experimental::source_location::current()) noexcept
{
    if (DEBUG) {
        std::cout << "[" << location.file_name() << "](" << location.line() << ":"
                  << location.column() << ") `" << location.function_name() << "`: " << msg << '\n';
    }
}
