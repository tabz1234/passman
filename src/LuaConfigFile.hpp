#ifndef LUACONFIGFILE_HPP
#define LUACONFIGFILE_HPP

extern "C"
{
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include <filesystem>
#include <memory>
#include <string>

class LuaConfigFile final
{
    std::unique_ptr<lua_State, void (*)(lua_State*)> plua_state_;

    const std::filesystem::path filepath_;

  public:
    LuaConfigFile(const std::filesystem::path& filepath);

    std::string get_string(const std::string& lua_var_name);
    double get_number(const std::string& lua_var_name);
    bool get_bool(const std::string& lua_var_name);
};

#endif
