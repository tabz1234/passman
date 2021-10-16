#ifndef GETHOMEPATH_HPP
#define GETHOMEPATH_HPP

#include <cstdlib>
#include <filesystem>
#include <optional>
#include <stdexcept>

static std::filesystem::path
get_home_path() noexcept
{
    const char* homepath = std::getenv("HOME");

    if (homepath == nullptr) [[unlikely]]
        throw std::runtime_error("Error : environment variable \"HOME\" is not "
                                 "set, run : \"export HOME=/home/YOUR_USER\"");
    else
        return homepath;
}

#endif
