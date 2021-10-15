#ifndef LUACONFIGFILE_HPP
#define LUACONFIGFILE_HPP

#include <filesystem>
#include <string>

extern "C"
{
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

class LuaConfigFile
{
    lua_State* plua_state_;

    const std::filesystem::path filepath_;

    void create_config_file() noexcept;

  public:
    LuaConfigFile(const std::filesystem::path& filepath) noexcept;

    std::string get_string(const std::string& lua_var_name) noexcept;
    double get_number(const std::string& lua_var_name) noexcept;
    bool get_bool(const std::string& lua_var_name) noexcept;

    ~LuaConfigFile();
};

#endif
