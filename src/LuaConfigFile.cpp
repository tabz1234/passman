#include "LuaConfigFile.hpp"
#include "createFile.hpp"
#include "readFile.hpp"

#include <fstream>

LuaConfigFile::LuaConfigFile(const std::filesystem::path& filepath)
  : filepath_{ filepath }
  , plua_state_{ std::unique_ptr<lua_State, void (*)(lua_State*)>(
      luaL_newstate(),
      [](lua_State* raw_pluastate) { lua_close(raw_pluastate); }) }
{

    luaL_openlibs(plua_state_.get());

    if (!std::filesystem::exists(filepath_)) [[unlikely]] {
        createFile(filepath_);

        std::ofstream outfile(filepath_);

        const auto file_content = readFile("/usr/lib/passman/passman_conf.lua");
        outfile.write(file_content.data(), file_content.size());
    }

    luaL_dofile(plua_state_.get(), filepath.c_str());
}

std::string
LuaConfigFile::get_string(const std::string& lua_var_name)
{
    if (!lua_getglobal(plua_state_.get(), lua_var_name.c_str())) [[unlikely]]
        throw std::runtime_error("lua_getglobal fail :" + lua_var_name);

    if (!lua_isstring(plua_state_.get(), -1)) [[unlikely]]
        throw std::runtime_error(lua_var_name + " : you wanted it as string");

    return lua_tostring(plua_state_.get(), -1);
}

double
LuaConfigFile::get_number(const std::string& lua_var_name)
{
    if (!lua_getglobal(plua_state_.get(), lua_var_name.c_str())) [[unlikely]]
        throw std::runtime_error("lua_getglobal fail :" + lua_var_name);

    if (!lua_isnumber(plua_state_.get(), -1)) [[unlikely]]
        throw std::runtime_error(lua_var_name + " : you wanted it as number");

    return lua_tonumber(plua_state_.get(), -1);
}

bool
LuaConfigFile::get_bool(const std::string& lua_var_name)
{
    if (!lua_getglobal(plua_state_.get(), lua_var_name.c_str())) [[unlikely]]
        throw std::runtime_error("lua_getglobal fail :" + lua_var_name);

    if (!lua_isboolean(plua_state_.get(), -1)) [[unlikely]]
        throw std::runtime_error(lua_var_name + " : you wanted it as boolean");

    return lua_toboolean(plua_state_.get(), -1);
}
