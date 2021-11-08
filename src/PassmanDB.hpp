#ifndef PASSMANDB_HPP
#define PASSMANDB_HPP

#include "Password.hpp"
#include "SQliteDB.hpp"

#include <filesystem>
#include <string>
#include <vector>

class PassmanDB final
{
    SQliteDB db_;

  public:
    PassmanDB(const std::filesystem::path& db_path);

    Password get(const std::string& password_id);
    std::vector<Password> get();

    void remove(const std::string& password_id);

    void add(const Password& password);
};

#endif
