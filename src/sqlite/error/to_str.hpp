#pragma once

#include <string>

#include "Code.hpp"

namespace SQLite {
    namespace Error {
        std::string to_str(const Code errc) noexcept;
    } // namespace Error
} // namespace SQLite
