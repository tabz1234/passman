#ifndef SQLITEDB_HPP
#define SQLITEDB_HPP

extern "C"
{
#include "sqlite3.h"
}

#include "sqlite_return.hpp"

#include <filesystem>
#include <memory>
#include <vector>

class SQliteDB final
{
    std::unique_ptr<sqlite3, void (*)(sqlite3*)> pdb_;
    const std::filesystem::path dbpath_;

  public:
    SQliteDB(const std::filesystem::path& dbpath);

    std::vector<sqlite_return> execute(const std::string& sql_statement);
};

#endif
