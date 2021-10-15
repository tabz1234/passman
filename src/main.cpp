#include "LuaConfigFile.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <optional>
#include <stdexcept>

std::optional<std::filesystem::path>
get_home_path() noexcept;

int
main(int argc, char** argv)
{
    const auto homepath = get_home_path();
    if (!homepath.has_value()) [[unlikely]]
        throw std::runtime_error("Error : environment variable \"HOME\" is not "
                                 "set, run : \"export HOME=/home/YOUR_USER\"");

    const auto config_file_path =
      homepath.value() / ".config" / "passman" / "passman_conf.lua";

    LuaConfigFile cfg(config_file_path);

    const auto appdata = cfg.get_string("AppDataDir");
    std::cout << appdata << '\n';

    const auto num_a = cfg.get_number("A");
    std::cout << num_a << '\n';

    const auto DEBUG = cfg.get_bool("DEBUG");
    std::cout << DEBUG << '\n';

    return 0;
}

std::optional<std::filesystem::path>
get_home_path() noexcept
{
    const char* homepath = std::getenv("HOME");

    if (homepath == nullptr) [[unlikely]]
        return std::nullopt;
    else
        return homepath;
}

