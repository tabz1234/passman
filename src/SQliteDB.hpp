#ifndef SQLITEDB_HPP
#define SQLITEDB_HPP

extern "C"
{
#include "sqlite3.h"
}

#include "sqlite_return.h"

#include <filesystem>
#include <unordered_map>

class SQliteDB
{
    sqlite3* pdb_;
    const std::filesystem::path dbpath_;

  public:
    SQliteDB(const std::filesystem::path& dbpath) noexcept;

    sqlite_return* execute(const std::string& sql_statement) noexcept;

    ~SQliteDB();
};

#endif
