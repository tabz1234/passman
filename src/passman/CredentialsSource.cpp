#include "CredentialsSource.hpp"

#include <chrono>
#include <sstream>

#include "../passman/err_msg.hpp"
#include "../passman/fs/is_empty.hpp"
#include "../passman/println.hpp"

#include "../util/ExitCode.hpp"
#include "../util/fcheck.hpp"

#include "../sqlite/StaticData.hpp"
#include "../sqlite/error/to_str.hpp"

using namespace std::string_literals;

Passman::CredentialsSource::CredentialsSource(const std::string_view dbpath) noexcept : db_{dbpath}
{
    fcheck(!FS::is_empty(dbpath), [&ldb = db_] {
        println("Creating credentials database ...");
        auto&& create_errc = ldb.execute("CREATE TABLE CREDENTIALS( "
                                         "LOGIN TEXT PRIMARY KEY NOT NULL, "
                                         "PASSWORD TEXT NOT NULL, "
                                         "CREATED UNSIGNED BIG INT NOT NULL, "
                                         "LAST_ACCESS UNSIGNED BIG INT);");
        println("Result of creation : ", SQLite::Error::to_str(create_errc));
    });
}

std::vector<std::tuple<std::string, std::string, unsigned long, unsigned long>> Passman::CredentialsSource::get() noexcept
{
    const auto&& [raw_data_vec, errc] = db_.select<SQLite::StaticData, 4>("SELECT * FROM CREDENTIALS");

    fcheck(errc == SQLite::Error::OK, [lerrc = errc] {
        err_msg("There is error while loading credentials from database : ", SQLite::Error::to_str(lerrc));
        println("Exiting ...");
        std::exit(exit_failure);
    });

    std::vector<std::tuple<std::string, std::string, unsigned long, unsigned long>> ret;
    ret.reserve(raw_data_vec.size());

    for (const auto& raw_data : raw_data_vec) {
        ret.emplace_back(raw_data.values_.at(0).value_or("NULL"),
                         raw_data.values_.at(1).value_or("NULL"),
                         std::stoul(raw_data.values_.at(2).value_or("0")),
                         std::stoul(raw_data.values_.at(3).value_or("0")));
    }
    return ret;
}
std::tuple<std::string, unsigned long, unsigned long> Passman::CredentialsSource::get(const std::string_view login) noexcept
{
    std::stringstream ss;
    ss << "SELECT * FROM CREDENTIALS WHERE LOGIN = '" << login << "'";

    const auto&& [raw_data, errc] = db_.select_one<SQLite::StaticData, 4>(ss.str());
    if (!raw_data.has_value()) {
        if (errc != SQLite::Error::OK) {
            err_msg("There was error while getting record with login \"", login, "\" from database :", SQLite::Error::to_str(errc));
        }
        else {
            err_msg("There is no record with login \"", login, "\" in database");
        }

        println("Exiting ...");
        std::exit(exit_failure);
    }

    return {raw_data.value().values_.at(1).value_or("NULL"),
            std::stoul(raw_data.value().values_.at(2).value_or("0")),
            std::stoul(raw_data.value().values_.at(3).value_or("0"))};
}
void Passman::CredentialsSource::add(const std::string_view login, const std::string_view password) noexcept
{
    const auto cur_time = std::chrono::system_clock::now();
    const auto cur_time_unix = cur_time.time_since_epoch().count();

    std::stringstream ss;
    ss << "INSERT INTO CREDENTIALS VALUES ('" << login << "','" << password << "'," << std::to_string(cur_time_unix) << ",NULL);";

    const auto errc = db_.execute(ss.str());

    fcheck(errc == SQLite::Error::OK, [&] {
        err_msg("Failed to insert record with login '", login, "', password '", password, "' into database :", SQLite::Error::to_str(errc));
        println("Exiting ...");
        std::exit(exit_failure);
    });
}
void Passman::CredentialsSource::add(const std::string_view login) noexcept
{
    add(login, "UNIMPL_");
}
