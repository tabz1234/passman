#include "PassmanDB.hpp"
#include "CalendarTime.hpp"
#include "SQliteDB.hpp"
#include "TerminalUtils.hpp"
#include "createFile.hpp"
#include "sqlite_return.hpp"

#include <chrono>
#include <cstring>
#include <filesystem>
#include <memory>
#include <stdexcept>

PassmanDB::PassmanDB(const std::filesystem::path& db_path)
  : db_{ db_path }
{
    if (std::filesystem::file_size(db_path) == 0) [[unlikely]] {
        const auto sql_data = db_.execute("CREATE TABLE PASSWORD( "
                                          "ID VARCHAR PRIMARY KEY NOT NULL, "
                                          "STR VARCHAR NOT NULL, "
                                          "CREATED BIGINT NOT NULL, "
                                          "LAST_ACCES BIGINT);");
    }
}

Password
PassmanDB::get(const std::string& password_id)
{
    try {
        const auto sql_data = db_.execute(

          "SELECT * from PASSWORD where ID = '" + password_id + "'");

        if (sql_data.size() == 0)
            throw std::exception{};

        return Password{ .id_ = sql_data[0].ppvalues_[0],
                         .str_ = sql_data[0].ppvalues_[1],
                         .created_ = std::atol(sql_data[0].ppvalues_[2]),
                         .last_acces_ =
                           std::atol(sql_data[0].ppvalues_[3] == nullptr
                                       ? "0"
                                       : sql_data[0].ppvalues_[3]) };

    } catch (const std::exception& exception) {
        printColorfulText<FG{ 255, 0, 0 }>(
          "Cant get password with id :" + password_id + "\n");
        throw;
    }
}
std::vector<Password>
PassmanDB::get()
{
    try {

        const auto sql_data = db_.execute("SELECT * from PASSWORD;");

        std::vector<Password> passwords;
        passwords.reserve(sql_data.size());

        for (const auto& cur : sql_data) {
            passwords.push_back({
              cur.ppvalues_[0],
              cur.ppvalues_[1],
              std::atol(cur.ppvalues_[2]),
              std::atol(cur.ppvalues_[3] == nullptr ? "0" : cur.ppvalues_[3]),
            });
        }

        return passwords;
    } catch (const std::exception& exception) {
        printColorfulText<FG{ 255, 0, 0 }>("Cant get passwords(all) \n");
        throw;
    }
}

void
PassmanDB::remove(const std::string& pass_id)
{
    const auto sql_data =
      db_.execute("DELETE from PASSWORD where ID = '" + pass_id + "';");
}

void
PassmanDB::add(const Password& password)
{
    const auto since_epoch = std::to_string(
      std::chrono::system_clock::now().time_since_epoch().count());

    const auto sql_data = db_.execute("INSERT INTO PASSWORD "
                                      "VALUES ('" +
                                      password.id_ + "','" + password.str_ +
                                      "'," + since_epoch + ",NULL" + ");");
}
