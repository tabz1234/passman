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
        throw std::runtime_error(
          "Error : environment variable \"HOME\" is not " //@TODO
          "set, run : \"export HOME=/home/YOUR_USER\"");
    else
        return homepath;
}

#endif
