#include "LuaConfigFile.hpp"
#include "PassmanDB.hpp"
#include "PassmanFatalError.hpp"
#include "Password.hpp"
#include "SQliteDB.hpp"
#include "TerminalColor.hpp"
#include "getHomePath.hpp"

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <optional>
#include <stdexcept>

int
main(int argc, char** argv)
{
    bool using_config = true;
    int random_ascii_lenght = 30;

    const auto home_path = get_home_path();

    auto appdata_dir = home_path / ".local" / "share" / "passman";

    const auto load_config = [&]() -> void {
        LuaConfigFile cfg(home_path / ".config" / "passman" / "passman_conf.lua");

        appdata_dir = cfg.get_string("AppDataDir");
        random_ascii_lenght = cfg.get_number("RandomAsciiLenght");
    };

    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "get") == 0) {
            if (using_config) [[likely]]
                load_config();

            if (i + 1 == argc) [[unlikely]]
                throw PassmanFatalError("After get you must specify password id ");
            else {
                const std::string pass_id = argv[i + 1];

                PassmanDB db(appdata_dir / "passman.db");
                const auto password = db.get(pass_id);

                std::cout << '\n' << FGColor{ 100, 255, 100 } << "Pass :" << password.str_ << '\n';
            }

            i = i + 1; // shift to end of command sequence
        } else if (std::strcmp(argv[i], "gen") == 0) {
            if (using_config) [[likely]]
                load_config();

            if (i + 1 == argc) [[unlikely]]
                throw std::runtime_error("After gen you must specify password id ");
            else {
                const std::string pass_id = argv[i + 1];

                if (i + 2 != argc) {
                    random_ascii_lenght = std::stoi(argv[i + 2]);
                }

                const Password pass(pass_id, random_ascii_lenght);

                std::cout << '\n' << pass.str_ << '\n';

                PassmanDB db(appdata_dir / "passman.db");
                db.add(pass);
            }

            i = i + 2; // shift to end of command sequence
        } else if (std::strcmp(argv[i], "status") == 0) {
            if (using_config) [[likely]]
                load_config();

        } else if (std::strcmp(argv[i], "--no-config") == 0) {
            using_config = false;
        } else if (std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0) {
            const std::string help_message = "HELP_MSG\n";
            std::cout << help_message << '\n';
        } else
            std::cout << "Unrecognized command line option :" + std::string(argv[i]) + " ,type \"passman --help\"\n";
    }

    return 0;
}
