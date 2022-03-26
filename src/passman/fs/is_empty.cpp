#include "is_empty.hpp"

#include <filesystem>

bool Passman::FS::is_empty(const std::string_view path) noexcept
{
    std::error_code errc;
    return std::filesystem::is_empty(path, errc);
}
