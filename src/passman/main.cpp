#include "../util/ExitCode.hpp"
#include "../util/fcheck.hpp"

#include "../passman/Settings.hpp"
#include "../passman/cmdline/parse_arguments.hpp"
#include "../passman/err_msg.hpp"
#include "../passman/fs/cd_to_appdata_dir.hpp"
#include "../passman/fs/is_empty.hpp"
#include "../passman/fs/touch_appdata_dir.hpp"
#include "../passman/msg.hpp"

#include "../sqlite/DataBase.hpp"
#include "../sqlite/StaticData.hpp"
#include "../sqlite/error/to_str.hpp"

using namespace Passman;

int main(const int argc, const char** const argv) noexcept
{
    Settings app_settings;
    auto&& [functions, offsets] = CmdLine::parse_arguments(argc, argv, app_settings);

    FS::touch_appdata_dir(app_settings.AppDataDir_);
    FS::cd_to_appdata_dir(app_settings.AppDataDir_);

    constexpr std::string_view credentials_db_fname = "passman_credentials.db";
    SQLite::DataBase db{credentials_db_fname};

    fcheck(!FS::is_empty(credentials_db_fname), [&ldb = db] {
        println("Creating new credentials database ...");
        auto&& create_errc = ldb.execute("CREATE TABLE CREDENTIALS( "
                                         "LOGIN TEXT PRIMARY KEY NOT NULL, "
                                         "PASSWORD TEXT NOT NULL, "
                                         "CREATED INTEGER NOT NULL, "
                                         "LAST_ACCESS INTEGER) STRICT;");
        println("Result of creation : ", SQLite::Error::to_str(create_errc));
    });

    for (const auto& fun : functions) {
        switch (fun) {
        case CmdLine::Function::get_0arg: {
            break;
        }
        case CmdLine::Function::get_1arg: {
            break;
        }
        }
    }

#if 0

    auto&& a = db.execute("INSERT INTO CREDENTIALS "
                          "VALUES ('"
                          "BLOB_VAL_1"
                          "',"
                          "'NULL ))))))))'"
                          ","
                          "12343"
                          ",NULL"
                          ");");
    println("Insert result :", SQLite::Error::to_str(a));
    const auto errc = db.execute(""
                                 "SELECT * from CREDENTIALS"
                                 ";");
    err_msg(SQLite::Error::to_str(errc));

    auto&& [vec, errcode] = db.select<SQLite::StaticData<4>>("SELECT * from CREDENTIALS;");
    err_msg(SQLite::Error::to_str(errcode));

    for (const auto& data : vec) {
        println(" +++++ NODE START +++++");

        for (int i = 0; i < data.keys_.size(); ++i) {
            println("Key :", data.keys_[i]);
            println("Value :", data.values_[i].value_or("NULL VALUE"));
        }
        println(" ----- NODE FINISH -----");
    }

    auto&& [vec2, errcode2] = db.select<SQLite::StaticData<4>>("SELECT * from CREDENTIALS;");
    err_msg(SQLite::Error::to_str(errcode2));

    for (const auto& data : vec2) {
        println(" +++++ NODE START +++++");

        for (int i = 0; i < data.keys_.size(); ++i) {
            println("Key :", data.keys_[i]);
            println("Value :", data.values_[i].value_or("NULL VALUE"));
        }
        println(" ----- NODE FINISH -----");
    }

#endif
    return exit_success;
}
