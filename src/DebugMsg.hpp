#pragma once

#include <experimental/source_location>
#include <iostream>
#include <string_view>

#include "ConstexprDebug.hpp"

static auto inline debugMsg(const bool expr,
                            const std::string_view msg,
                            const std::experimental::source_location location =
                                std::experimental::source_location::current()) {

    if (!expr) [[unlikely]] {
        if constexpr (DEBUG) {
            std::cout << "[" << location.file_name() << "](" << location.line() << ":"
                      << location.column() << ") `" << location.function_name() << "`: " << msg
                      << '\n';
        }
    }
}
