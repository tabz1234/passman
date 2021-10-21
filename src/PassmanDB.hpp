#ifndef PASSMANDB_HPP
#define PASSMANDB_HPP

#include "Password.hpp"
#include "SQliteDB.hpp"

#include <filesystem>
#include <string>
#include <vector>

class PassmanDB
{
    SQliteDB db_;

  public:
    PassmanDB(const std::filesystem::path& db_path) noexcept;

    Password get(const std::string& password) noexcept;
    std::vector<Password> get() noexcept;

    void add(const Password& password) noexcept;
};

#endif
