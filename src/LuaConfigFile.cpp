#include "LuaConfigFile.hpp"
#include "createFile.hpp"
#include "getHomePath.hpp"

#include <fstream>

LuaConfigFile::LuaConfigFile(const std::filesystem::path& filepath) noexcept
  : filepath_{ filepath }
  , plua_state_{ luaL_newstate() }
{

    luaL_openlibs(plua_state_);

    if (!std::filesystem::exists(filepath_)) [[unlikely]] {
        createFile(filepath_);

        std::ofstream ofs(filepath_.c_str(), std::ios::out | std::ios::app);
        ofs << "AppDataDir = \"" + get_home_path().string() + "/.local" +
                 "/passman" + "\"\n";
        ofs << "RandomAsciiLenght = 30";
    }

    luaL_dofile(plua_state_, filepath.c_str());
}

LuaConfigFile::~LuaConfigFile()
{
    lua_close(plua_state_);
}

std::string
LuaConfigFile::get_string(const std::string& lua_var_name) noexcept
{
    if (!lua_getglobal(plua_state_, lua_var_name.c_str())) [[unlikely]]
        throw std::runtime_error("lua_getglobal fail :" + lua_var_name);

    if (!lua_isstring(plua_state_, -1)) [[unlikely]]
        throw std::runtime_error(lua_var_name + " : you wanted it as string");

    return lua_tostring(plua_state_, -1);
}

double
LuaConfigFile::get_number(const std::string& lua_var_name) noexcept
{
    if (!lua_getglobal(plua_state_, lua_var_name.c_str())) [[unlikely]]
        throw std::runtime_error("lua_getglobal fail :" + lua_var_name);

    if (!lua_isnumber(plua_state_, -1)) [[unlikely]]
        throw std::runtime_error(lua_var_name + " : you wanted it as number");

    return lua_tonumber(plua_state_, -1);
}

bool
LuaConfigFile::get_bool(const std::string& lua_var_name) noexcept
{
    if (!lua_getglobal(plua_state_, lua_var_name.c_str())) [[unlikely]]
        throw std::runtime_error("lua_getglobal fail :" + lua_var_name);

    if (!lua_isboolean(plua_state_, -1)) [[unlikely]]
        throw std::runtime_error(lua_var_name + " : you wanted it as boolean");

    return lua_toboolean(plua_state_, -1);
}
