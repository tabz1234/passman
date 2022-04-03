#include "../util/ExitCode.hpp"

#include "../passman/CredentialsSource.hpp"
#include "../passman/Settings.hpp"
#include "../passman/cmdline/parse_arguments.hpp"
#include "../passman/err_msg.hpp"
#include "../passman/fs/cd_to_appdata_dir.hpp"
#include "../passman/fs/touch_appdata_dir.hpp"
#include "../passman/println.hpp"

#include "../sqlite/DataBase.hpp"
#include "../sqlite/StaticData.hpp"
#include "../sqlite/error/to_str.hpp"

using namespace Passman;

int main(const int argc, const char** const argv) noexcept
{
    Settings app_settings;
    const auto&& [functions, offsets] = CmdLine::parse_arguments(argc, argv, app_settings);

    FS::touch_appdata_dir(app_settings.AppDataDir_);
    FS::cd_to_appdata_dir(app_settings.AppDataDir_);

    constexpr std::string_view credentials_db_fname = "credentials.db";
    CredentialsSource credentials_source(credentials_db_fname);

    for (int i = 0; i < functions.size(); ++i) {
        switch (functions.at(i)) {
        case CmdLine::Function::get_0arg: {
            auto&& credentials_vec = credentials_source.get();

            for (auto&& credentials : credentials_vec) {
                println(" -- RECORD START --");
                println("Login : ", std::get<0>(credentials));
                println("Password : ", std::get<1>(credentials));
                println("Created : ", std::to_string(std::get<2>(credentials)));
                println("Last Acces : ", std::to_string(std::get<3>(credentials)));
                println(" -- RECORD END --");
                println("");
            }
            break;
        }
        case CmdLine::Function::get_1arg: {
            std::string_view login = argv[offsets.at(i) + 1];
            auto&& credentials = credentials_source.get(login);

            println("Login : ", login);
            println("Password : ", std::get<0>(credentials));
            println("Created : ", std::to_string(std::get<1>(credentials)));
            println("Last Acces : ", std::to_string(std::get<2>(credentials)));

            break;
        }
        case CmdLine::Function::add_1arg: {
            std::string_view login = argv[offsets.at(i) + 1];

            credentials_source.add(login);
            println("Succsessfuly added new record with login '", login, "' and auto-generated password");
            break;
        }
        case CmdLine::Function::add_2arg: {
            std::string_view login = argv[offsets.at(i) + 1];
            std::string_view password = argv[offsets.at(i) + 2];

            credentials_source.add(login, password);
            println("Succsessfuly added new record with login '", login, "' and password '", password, "'");
            break;
        }
        }
    }

#if 0

#endif
    return exit_success;
}
