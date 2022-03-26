#pragma once

#include <string>

#include "fs/get_home_path.hpp"

using namespace std::string_literals;

namespace Passman {
    struct Settings final {
        bool interactive_ = false;
        bool quiet_ = false;
        const bool use_encryption_ = false; //@TODO

        std::string_view home_path_ = FS::get_home_path();
        std::string AppDataDir_ = home_path_.data() + "/.local/share/passman"s;
    };
} // namespace Passman
