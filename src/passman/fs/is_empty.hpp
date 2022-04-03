#pragma once

#include <filesystem>

namespace Passman::FS {
    bool is_empty(const std::string_view path) noexcept;
}
