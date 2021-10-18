#include "SQliteDB.hpp"
#include "createFile.hpp"

#include <filesystem>
#include <iostream>
#include <stdexcept>

sqlite_return*
SQliteDB::execute(const std::string& sql_statement) noexcept
{
    sqlite_return* ret = (sqlite_return*)malloc(sizeof(sqlite_return));

    int rc = sqlite3_exec(pdb_, sql_statement.c_str(), sql_callback, ret, nullptr);
    if (rc)
        throw std::runtime_error("sqlite3_exec() returned true");

    return ret;
}
SQliteDB::SQliteDB(const std::filesystem::path& dbpath) noexcept
  : dbpath_{ dbpath }
{

    if (!std::filesystem::exists(dbpath_)) [[unlikely]]
        std::filesystem::create_directories(dbpath_.parent_path());

    if (sqlite3_open(dbpath_.c_str(), &pdb_)) [[unlikely]]
        throw std::runtime_error("sqlite3_open() returned true");
}

SQliteDB::~SQliteDB()
{
    sqlite3_close(pdb_);
}
