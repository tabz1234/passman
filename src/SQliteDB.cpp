#include "SQliteDB.hpp"
#include "createFile.hpp"

#include <filesystem>
#include <iostream>
#include <stdexcept>

int
sql_callback(void* pvoid_ret, int rows, char** ppvalues, char** ppkeys)
{
    *((std::unique_ptr<const sqlite_return>*)pvoid_ret) =
      std::make_unique<const sqlite_return>(rows, ppvalues, ppkeys);

    return 0;
}
sqlite_return
SQliteDB::execute(const std::string& sql_statement) noexcept
{
    std::unique_ptr<const sqlite_return> ret;

    char* dumb;
    int rc =
      sqlite3_exec(pdb_, sql_statement.c_str(), sql_callback, &ret, &dumb);

    if (!ret) {
        return { rc };
    }

    return *ret;
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
