#ifndef PASSMANDB_HPP
#define PASSMANDB_HPP

#include "Password.hpp"
#include "SQliteDB.hpp"

#include <filesystem>
#include <string>

class PassmanDB
{
    SQliteDB sqlite_db_;

  public:
    PassmanDB(const std::filesystem::path& db_path) noexcept;

    std::string get(const Password& password) noexcept;

    void add(const Password& password) noexcept;
};

#endif
