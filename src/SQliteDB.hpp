#ifndef SQLITEDB_HPP
#define SQLITEDB_HPP

extern "C"
{
#include "sqlite3.h"
}

#include "sqlite_return.hpp"

#include <filesystem>

class SQliteDB
{
    sqlite3* pdb_;
    const std::filesystem::path dbpath_;

  public:
    sqlite_return execute(const std::string& sql_statement) noexcept;

    SQliteDB(const std::filesystem::path& dbpath) noexcept;

    SQliteDB(const SQliteDB&) = delete;
    SQliteDB& operator=(const SQliteDB&) = delete;

    ~SQliteDB();
};

#endif
