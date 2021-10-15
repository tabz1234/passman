#ifndef SQLITEDB_HPP
#define SQLITEDB_HPP

#include <filesystem>

extern "C"
{
#include "sqlite3.h"
}

class SQliteDB
{
    sqlite3* pdb_;

    const std::filesystem::path dbpath_;

  public:
    SQliteDB(const std::filesystem::path& dbpath) noexcept;

    void execute(const std::string& sql_statement) noexcept;

    ~SQliteDB();
};

#endif
