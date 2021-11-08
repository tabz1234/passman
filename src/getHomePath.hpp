#ifndef GETHOMEPATH_HPP
#define GETHOMEPATH_HPP

#include "TerminalUtils.hpp"

#include <cstdlib>
#include <filesystem>
#include <optional>
#include <stdexcept>

static std::filesystem::path
get_home_path()
{
    const char* homepath = std::getenv("HOME");

    if (homepath == nullptr) [[unlikely]]
        throw std::runtime_error("homepath == nullptr");
    else
        return homepath;
}

#endif
