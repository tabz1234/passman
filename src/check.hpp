#pragma once

#include <cstdlib>
#include <stdexcept>
#include <string_view>

template <typename ExceptionT = std::runtime_error>
auto check(const bool expr, std::string_view msg) {
    if (!expr) [[unlikely]] {
        throw ExceptionT{msg.data()};
    }
}
