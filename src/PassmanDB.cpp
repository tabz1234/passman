#include "PassmanDB.hpp"
#include "SQliteDB.hpp"
#include "TerminalColor.hpp"
#include "createFile.hpp"
#include "sqlite_return.h"

#include <chrono>
#include <filesystem>
#include <iostream>
#include <stdexcept>

PassmanDB::PassmanDB(const std::filesystem::path& db_path) noexcept
  : SQliteDB{ db_path }
{
    if (std::filesystem::file_size(db_path) == 0)
        sqlite3_exec(pdb_,
                     "CREATE TABLE PASSWORD( "
                     "ID VARCHAR(65535) PRIMARY KEY NOT NULL, "
                     "STR VARCHAR(65535) NOT NULL, "
                     "LAST_ACCES BIGINT(255), "
                     "CREATED BIGINT(255));",
                     nullptr,
                     nullptr,
                     nullptr);
}

Password
PassmanDB::get(const std::string& pass_id) noexcept
{
    sqlite_return ret;

    const int rc =
      sqlite3_exec(pdb_, ("SELECT * from PASSWORD where ID = '" + pass_id + "'").c_str(), sql_callback, &ret, nullptr);
    if (rc) {
        std::cout << FGColor{ 255, 0, 0 } << "cant get password with id :\"" << pass_id << "\"\n\n" << FGColor{ 255, 255, 255 };
    }

    const Password temp(ret.ppvalues_[1],
                        (ret.ppvalues_[2] == 0) ? unixtime_t{} : unixtime_t{ std::chrono::seconds(std::atoll(ret.ppvalues_[2])) },
                        unixtime_t{ std::chrono::seconds(std::atoll(ret.ppvalues_[3])) });

    delete_sqlite_return(&ret);

    return temp;
}
std::vector<Password>
PassmanDB::get() noexcept
{}

void
PassmanDB::add(const Password& password) noexcept
{

    const auto sys_clock_time = std::chrono::system_clock::now();
    const auto since_epoch = std::to_string(sys_clock_time.time_since_epoch().count());

    const int rc = sqlite3_exec(pdb_,
                                ("INSERT INTO PASSWORD (ID,STR,CREATED) "
                                 "VALUES ('" +
                                 password.id_ + "','" + password.str_ + "'," + since_epoch + ");")
                                  .c_str(),
                                sql_callback,
                                nullptr,
                                nullptr);
    if (rc) {
        std::cout << FGColor{ 255, 0, 0 } << "cant add to database password with id :\"" << password.id_ << "\"\n\n"
                  << FGColor{ 255, 255, 255 };
    }
}
