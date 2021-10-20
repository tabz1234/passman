#include "SQliteDB.hpp"
#include "createFile.hpp"
#include "sqlite_return.h"

#include <filesystem>
#include <iostream>
#include <stdexcept>

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
