#include "SQliteDB.hpp"
#include "createFile.hpp"

#include <filesystem>
#include <stdexcept>
#include <vector>

inline static int
sql_callback(void* pvoid_ret, int cols, char** ppvalues, char** ppkeys)
{
    reinterpret_cast<std::vector<sqlite_return>*>(pvoid_ret)->emplace_back(
      cols, ppvalues, ppkeys);

    return 0;
}
std::vector<sqlite_return>
SQliteDB::execute(const std::string& sql_statement)
{
    std::vector<sqlite_return> ret;
    ret.reserve(20);

    const int rc = sqlite3_exec(
      pdb_.get(), sql_statement.c_str(), sql_callback, &ret, nullptr);

    if (rc) [[unlikely]]
        throw std::runtime_error("sqlite exec returned true");

    return ret;
}
SQliteDB::SQliteDB(const std::filesystem::path& dbpath)
  : dbpath_{ dbpath }
  , pdb_{ nullptr, nullptr }
{

    if (!std::filesystem::exists(dbpath_)) [[unlikely]]
        createFile(dbpath_);

    sqlite3* raw_psqlobj;
    if (sqlite3_open(dbpath_.c_str(), &raw_psqlobj)) [[unlikely]]
        throw std::runtime_error("sqlite3_open() returned true");

    pdb_ = std::unique_ptr<sqlite3, void (*)(sqlite3*)>(
      raw_psqlobj, [](sqlite3* psqlobj) { sqlite3_close(psqlobj); });
}
