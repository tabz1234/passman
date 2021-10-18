#include "PassmanDB.hpp"
#include "sqlite_return.h"

#include <chrono>
#include <filesystem>
#include <iostream>

PassmanDB::PassmanDB(const std::filesystem::path& db_path) noexcept
  : sqlite_db_{ db_path }
{
    if (std::filesystem::file_size(db_path) == 0)
        sqlite_db_.execute("CREATE TABLE PASSWORD( "
                           "ID VARCHAR(65535) PRIMARY KEY NOT NULL, "
                           "STR VARCHAR(65535) NOT NULL, "
                           "LAST_ACCES BIGINT(255), "
                           "CREATED BIGINT(255));");
}

void
PassmanDB::get(const std::string& pass_id) noexcept
{
    auto sql_table_info = sqlite_db_.execute("SELECT * from PASSWORD where ID = '" + pass_id + "'");

    for (int i = 0; i < sql_table_info->rows_count_; i++) {
        std::cout << sql_table_info->ppkeys_[i] << " = " << sql_table_info->ppvalues_[i] << '\n';
    }

    delete_sqlite_return(sql_table_info);
}
std::vector<Password>
PassmanDB::get() noexcept
{}

void
PassmanDB::add(const Password& password) noexcept
{

    const auto p1 = std::chrono::system_clock::now();
    const auto since_epoch = std::to_string(p1.time_since_epoch().count());

    sqlite_db_.execute("INSERT INTO PASSWORD (ID,STR,CREATED) "
                       "VALUES ('" +
                       password.info_.id_ + "','" + password.str_ + "'," + since_epoch + ");"

    );
}
