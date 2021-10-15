#include "SQliteDB.hpp"

#include <stdexcept>

static int
sql_callback(void* NotUsed, int argc, char** argv, char** azColName)
{}

void
SQliteDB::execute(const std::string& sql_statement) noexcept
{
    if (sqlite3_exec(pdb_, sql_statement.c_str(), nullptr, nullptr, nullptr))
        throw std::runtime_error("sqlite3_exec() returned true");
}
SQliteDB::SQliteDB(const std::filesystem::path& dbpath) noexcept
  : dbpath_{ dbpath }
{
    if (sqlite3_open(dbpath_.c_str(), &pdb_))
        throw std::runtime_error("sqlite3_open() returned true");
}

SQliteDB::~SQliteDB()
{
    sqlite3_close(pdb_);
}
