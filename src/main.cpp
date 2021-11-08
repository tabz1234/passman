#include "LuaConfigFile.hpp"
#include "PassmanDB.hpp"
#include "Password.hpp"
#include "SQliteDB.hpp"
#include "TerminalUtils.hpp"
#include "generateRandomPassword.hpp"
#include "getHomePath.hpp"
#include "readFile.hpp"

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <optional>
#include <stdexcept>

using namespace std::string_literals;

constexpr int STRCMP_EQUAL = 0;

int
main(int argc, char** argv)
{
    bool using_config = true;
    int password_len = 30;

    bool quiet = false;

    std::filesystem::path home_path;
    std::filesystem::path appdata_dir;

    try {
        home_path = get_home_path();
    } catch (const std::runtime_error&) {
        printColorfulText<FG_RED>(
          "Failed to initialize home path, aborting. Is $HOME set? ");
    }

    appdata_dir = home_path / ".local" / "share" / "passman";
    const auto load_config = [&]() -> void {
        LuaConfigFile cfg(home_path / ".config" / "passman" /
                          "passman_conf.lua");

        appdata_dir = cfg.get_string("AppDataDir");
        password_len = cfg.get_number("PasswordLenght");
        quiet = cfg.get_bool("Quiet");
    };

    const auto help_message = readFile("/usr/lib/passman/help_message.txt");

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') { // options sequences

            if (argv[i][1] == '\0') [[unlikely]] {
                printColorfulText<FG_RED>(
                  "Unrecognized command line option :"s + argv[i] +
                  " ,type \"passman --help\"\n");

            } else if (argv[i][1] == '-') { // long options

                if (std::strcmp(argv[i] + 2, "no-config") == STRCMP_EQUAL) {
                    using_config = false;
                } else if (std::string(argv[i] + 2).starts_with("lenght=")) {

                } else if (std::strcmp(argv[i] + 2, "quiet") == STRCMP_EQUAL) {
                    quiet = true;
                } else if (std::strcmp(argv[i] + 2, "help") == STRCMP_EQUAL) {
                    for (const auto& it : help_message)
                        std::cout << it;
                } else {
                    printColorfulText<FG_RED>(
                      "Unrecognized long option :" + std::string(argv[i]) +
                      " ,type \"passman --help\"\n");
                }
            } else { // short options

                int short_options_iterator = 1;
                do {
                    if (argv[i][short_options_iterator] == 'l') {

                    } else if (argv[i][short_options_iterator] == 'q') {
                        quiet = true;
                    } else if (argv[i][short_options_iterator] == 'h') {
                        for (const auto& it : help_message)
                            std::cout << it;
                    } else {
                        printColorfulText<FG_RED>(
                          "Unrecognized short option :"s +
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
                    PassmanDB db(appdata_dir / "passman.db");

                    const auto data = db.get();

                    for (const auto& iter : data) {
                        std::cout << iter.id_ << " : " << iter.str_ << '\n';
                    }

                    break;
                } else {
                    const std::string pass_id = argv[i + 1];

                    PassmanDB db(appdata_dir / "passman.db");
                    const auto password = db.get(pass_id);

                    std::cout << '\n' << "Pass :" << password.str_ << '\n';

                    i = i + 1; // shit to end of command sequence
                }
            } else if (std::strcmp(argv[i], "add") == STRCMP_EQUAL) {

                if (using_config) [[likely]]
                    load_config();

                if (i + 1 == argc) [[unlikely]] {
                    printColorfulText<FG_RED>(
                      "After add you must specify password id \n");
                    break;
                } else {

                    if (i + 2 == argc) {
                        printColorfulText<FG_RED>(
                          "You must specify password string after id \n");
                        break;
                    }

                    const std::string pass_id = argv[i + 1];
                    const std::string pass_str = argv[i + 2];

                    const Password pass{ .id_ = pass_id,
                                         .str_ = pass_str,
                                         .created_ = std::time(0) };

                    std::cout << '\n' << "ADD " << pass.str_ << '\n';

                    PassmanDB db(appdata_dir / "passman.db");
                    db.add(pass);

                    i = i + 2; // shift to end of command sequence
                }

            } else if (std::strcmp(argv[i], "gen") == STRCMP_EQUAL) {

                if (using_config) [[likely]]
                    load_config();

                if (i + 1 == argc) [[unlikely]] {
                    printColorfulText<FG_RED>(
                      "After gen you must specify password id \n");
                    break;
                } else {
                    const std::string pass_id = argv[i + 1];

                    const Password pass{ .id_ = pass_id,
                                         .str_ = generateRandomPassword(
                                           pass_id, password_len),
                                         .created_ = std::time(0) };

                    std::cout << '\n' << pass.str_ << '\n';

                    PassmanDB db(appdata_dir / "passman.db");

                    db.add(pass);

                    i = i + 1; // shift to end of command sequence
                }

            } else if (std::strcmp(argv[i], "purge") == STRCMP_EQUAL) {
                std::filesystem::remove_all(appdata_dir);
            } else if (std::strcmp(argv[i], "rm") == STRCMP_EQUAL) {
                if (using_config) [[likely]]
                    load_config();

                if (i + 1 == argc) [[unlikely]] {
                    printColorfulText<FG_RED>(
                      "After rm you must specify password id \n");
                    break;
                } else {
                    const std::string pass_id = argv[i + 1];

                    PassmanDB db(appdata_dir / "passman.db");
                    db.remove(pass_id);
                    i = i + 1; // shift to end of command sequence
                }
            } else {
                printColorfulText<FG_RED>(
                  "Unrecognized command sequence argument:"s + argv[i] +
                  " ,type \"passman --help\"\n");
            }
        }
    }

    return EXIT_SUCCESS;
}
