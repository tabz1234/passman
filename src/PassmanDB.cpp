#include "PassmanDB.hpp"
#include "SQliteDB.hpp"
#include "TerminalColor.hpp"
#include "createFile.hpp"
#include "sqlite_return.hpp"

#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>

PassmanDB::PassmanDB(const std::filesystem::path& db_path) noexcept
  : db_{ db_path }
{
    if (std::filesystem::file_size(db_path) == 0)
        db_.execute("CREATE TABLE PASSWORD( "
                    "ID VARCHAR PRIMARY KEY NOT NULL, "
                    "STR VARCHAR NOT NULL, "
                    "LAST_ACCES BIGINT, "
                    "CREATED BIGINT);");
}

Password
PassmanDB::get(const std::string& pass_id) noexcept
{
    const auto sql_data =
      db_.execute("SELECT * from PASSWORD where ID = '" + pass_id + "'");
    if (sql_data.rc_) {
        std::cout << FGColor{ 255, 0, 0 } << "cant get password with id :\""
                  << pass_id << "\"\n\n"
                  << FGColor{ 255, 255, 255 };
    }

    const Password temp(
      sql_data.ppvalues_[1],
      (sql_data.ppvalues_[2] == 0)
        ? unixtime_t{}
        : unixtime_t{ std::chrono::seconds(std::atoll(sql_data.ppvalues_[2])) },
      unixtime_t{ std::chrono::seconds(std::atoll(sql_data.ppvalues_[3])) });

    return temp;
}
std::vector<Password>
PassmanDB::get() noexcept
{}

void
PassmanDB::add(const Password& password) noexcept
{

    const auto sys_clock_time = std::chrono::system_clock::now();
    const auto since_epoch =
      std::to_string(sys_clock_time.time_since_epoch().count());

    const auto sql_data = db_.execute("INSERT INTO PASSWORD (ID,STR,CREATED) "
                                      "VALUES ('" +
                                      password.id_ + "','" + password.str_ +
                                      "'," + since_epoch + ");");

    if (sql_data.rc_) {
        std::cout << FGColor{ 255, 0, 0 }
                  << "cant add to database password with id :\"" << password.id_
                  << "\"\n\n"
                  << FGColor{ 255, 255, 255 };
    }
}
