#pragma once

#include <string_view>

#include "../util/TerminalPrinter.hpp"
#include "../util/newl.hpp"

namespace Passman {
    template <typename... Args>
    void println(Args... args) noexcept
    {
        constexpr std::string_view msg_init = "====| ";
        constexpr char msg_fini = newl;

        tprinter.queue(msg_init, args..., msg_fini);
    }
} // namespace Passman
