#pragma once

#include "msg.hpp"

namespace Passman {
    template <typename... Args>
    void err_msg(Args... args) noexcept
    {
        constexpr std::string_view err_prefix = "_ERR_ :";
        println(err_prefix, args...);
    }
} // namespace Passman
