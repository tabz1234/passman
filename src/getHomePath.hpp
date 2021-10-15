#ifndef GETHOMEPATH_HPP
#define GETHOMEPATH_HPP

#include <cstdlib>
#include <filesystem>
#include <optional>

static std::optional<std::filesystem::path>
get_home_path() noexcept
{
    const char* homepath = std::getenv("HOME");

    if (homepath == nullptr) [[unlikely]]
        return std::nullopt;
    else
        return homepath;
}

#endif
