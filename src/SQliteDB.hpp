#ifndef SQLITEDB_HPP
#define SQLITEDB_HPP

extern "C"
{
#include "sqlite3.h"
}

#include <filesystem>

class SQliteDB
{
  protected:
    sqlite3* pdb_;
    const std::filesystem::path dbpath_;

    SQliteDB(const std::filesystem::path& dbpath) noexcept;

    ~SQliteDB();
};

#endif
