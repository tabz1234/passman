#pragma once

#include <string_view>

namespace Passman::FS {
    std::string_view get_home_path() noexcept;
}
