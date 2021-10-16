#include "LuaConfigFile.hpp"
#include "PassmanDB.hpp"
#include "Password.hpp"
#include "SQliteDB.hpp"
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

    const std::filesystem::path home_path = get_home_path();

    std::filesystem::path appdata_dir =
      home_path / ".local" / "share" / "passman";

    int random_ascii_lenght = 30;

    const auto load_config =
      [&home_path, &appdata_dir, &random_ascii_lenght]() -> void {
        LuaConfigFile cfg(home_path / ".config" / "passman" /
                          "passman_conf.lua");

        appdata_dir = cfg.get_string("AppDataDir");
        random_ascii_lenght = cfg.get_number("RandomAsciiLenght");
    };

    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "get") == 0) {
            if (using_config) [[likely]]
                load_config();

        } else if (std::strcmp(argv[i], "gen") == 0) {
            if (using_config) [[likely]]
                load_config();

            if (++i == argc)
                throw std::runtime_error(
                  "After gen you must specify password id ");
            else {
                const std::string pass_id = argv[i];

                if (++i != argc)
                    random_ascii_lenght = std::stod(argv[i]);

                Password pass({ pass_id, random_ascii_lenght });

                std::cout << '\n' << pass.str() << '\n';

                PassmanDB(appdata_dir / "passman.db");
            }

        } else if (std::strcmp(argv[i], "status") == 0) {
            if (using_config) [[likely]]
                load_config();

            std::exit(EXIT_SUCCESS);
        } else if (std::strcmp(argv[i], "--no-config") == 0) {
            using_config = false;
        } else if (std::strcmp(argv[i], "-h") == 0 ||
                   std::strcmp(argv[i], "--help") == 0) {
            const std::string help_message = "HELP_MSG\n";
            std::cout << help_message << '\n';
            std::exit(EXIT_SUCCESS);
        } else
            std::cout << "Unrecognized command line option :" +
                           std::string(argv[i]) + " ,type \"passman --help\"\n";
    }

    return 0;
}
