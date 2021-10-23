#include "LuaConfigFile.hpp"
#include "PassmanDB.hpp"
#include "Password.hpp"
#include "SQliteDB.hpp"
#include "TerminalUtils.hpp"
#include "getHomePath.hpp"

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <optional>
#include <stdexcept>

using namespace std::string_literals;

constexpr int STRCMP_EQUAL = 0;

constexpr auto help_message = "HELP";

int
main(int argc, char** argv)
{
    bool using_config = true;
    int random_ascii_lenght = 30;

    bool quiet = false;

    const auto home_path = get_home_path();

    auto appdata_dir = home_path / ".local" / "share" / "passman";

    const auto load_config = [&]() -> void {
        LuaConfigFile cfg(home_path / ".config" / "passman" /
                          "passman_conf.lua");

        appdata_dir = cfg.get_string("AppDataDir");
        random_ascii_lenght = cfg.get_number("RandomAsciiLenght");
    };

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') { // options sequences
            if (argv[i][1] == '\0') [[unlikely]] {
                ColorfulText<FG{ 255, 0, 0 }>(
                  "Unrecognized command line option :"s + argv[i] +
                  " ,type \"passman --help\"\n");
            } else if (argv[i][1] == '-') { // long options

                if (std::strcmp(argv[i] + 2, "no-config") == STRCMP_EQUAL) {
                    using_config = false;
                } else if (std::strcmp(argv[i] + 2, "lenght=") ==
                           STRCMP_EQUAL) {

                } else if (std::strcmp(argv[i] + 2, "quiet") == STRCMP_EQUAL) {
                    quiet = true;
                } else if (std::strcmp(argv[i] + 2, "help") == STRCMP_EQUAL) {
                    std::cout << help_message;
                } else {
                    ColorfulText<FG{ 255, 0, 0 }>(
                      "Unrecognized option :" + std::string(argv[i]) +
                      " ,type \"passman --help\"\n");
                }
            } else { // short options

                int short_options_iterator = 1;
                do {
                    if (argv[i][short_options_iterator] == 'l') {

                    } else if (argv[i][short_options_iterator] == 'q') {
                        quiet = true;
                    } else if (argv[i][short_options_iterator] == 'h') {
                        std::cout << help_message;
                    } else {
                        ColorfulText<FG{ 255, 0, 0 }>(
                          "Unrecognized option :"s +
                          argv[i][short_options_iterator] +
                          " ,type \"passman --help\"\n");
                    }
                    short_options_iterator++;
                } while (argv[i][short_options_iterator] != '\0');
            }
        } else { // command sequences
            if (std::strcmp(argv[i], "get") == STRCMP_EQUAL) {

                if (using_config) [[likely]]
                    load_config();

                if (i + 1 == argc) [[unlikely]] {
                    ColorfulText<FG{ 255, 0, 0 }>(
                      "After get you must specify password id ");
                } else {
                    const std::string pass_id = argv[i + 1];

                    PassmanDB db(appdata_dir / "passman.db");
                    const auto password = db.get(pass_id);

                    std::cout << '\n' << "Pass :" << password.str_ << '\n';
                }

                i = i + 1; // shift to end of command sequence
            } else if (std::strcmp(argv[i], "add") == STRCMP_EQUAL) {

                if (using_config) [[likely]]
                    load_config();

                if (i + 1 == argc) [[unlikely]] {
                    ColorfulText<FG{ 255, 0, 0 }>(
                      "After add you must specify password id ");
                } else {

                    if (i + 2 == argc) {
                        ColorfulText<FG{ 255, 0, 0 }>(
                          "You must specify password string after id ");
                        break;
                    }

                    const std::string pass_id = argv[i + 1];
                    const std::string pass_str = argv[i + 2];

                    const Password pass(pass_id, pass_str);

                    std::cout << '\n' << "ADD " << pass.str_ << '\n';

                    PassmanDB db(appdata_dir / "passman.db");
                    db.add(pass);
                }

                i = i + 2; // shift to end of command sequence
            } else if (std::strcmp(argv[i], "gen") == STRCMP_EQUAL) {

                if (using_config) [[likely]]
                    load_config();

                if (i + 1 == argc) [[unlikely]] {
                    ColorfulText<FG{ 255, 0, 0 }>(
                      "After gen you must specify password id ");
                } else {
                    const std::string pass_id = argv[i + 1];

                    if (i + 2 != argc) {
                        random_ascii_lenght = std::atoi(argv[i + 2]);
                    }

                    const Password pass(pass_id, random_ascii_lenght);

                    std::cout << '\n' << pass.str_ << '\n';

                    PassmanDB db(appdata_dir / "passman.db");
                    db.add(pass);
                }

                i = i + 2; // shift to end of command sequence
            } else if (std::strcmp(argv[i], "status") == STRCMP_EQUAL) {
            } else if (std::strcmp(argv[i], "rm") == STRCMP_EQUAL) {
            } else {
                ColorfulText<FG{ 255, 0, 0 }>(
                  "Unrecognized command sequence argument:" +
                  std::string(argv[i]) + " ,type \"passman --help\"\n");
            }
        }
    }

    return EXIT_SUCCESS;
}
