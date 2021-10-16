#include "LuaConfigFile.hpp"
#include "SQliteDB.hpp"
#include "getHomePath.hpp"

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <functional>
#include <iostream>
#include <optional>
#include <random>
#include <stdexcept>
#include <unordered_set>

std::string
generate_password(const std::string& id, const int random_ascii_lenght);

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

            std::string password;

            if (using_config) [[likely]]
                load_config();

            if (++i == argc)
                throw std::runtime_error(
                  "After gen you must specify password id ");
            else {
                const std::string key_id = argv[i];

                if (++i != argc)
                    random_ascii_lenght = std::stod(argv[i]);

                password = generate_password(key_id, random_ascii_lenght);
                std::cout << '\n' << password << '\n';
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

std::string
generate_password(const std::string& id, const int random_ascii_lenght)
{

    constexpr auto latin_litera_count = 26;
    constexpr auto arabic_digits_count = 10;

    std::array<char, latin_litera_count * 2 + arabic_digits_count> symbols_map;

    size_t arr_i = 0;

    for (char i = 'A'; i <= 'Z'; i++, arr_i++)
        symbols_map[arr_i] = i;

    for (char i = 'a'; i <= 'z'; i++, arr_i++)
        symbols_map[arr_i] = i;

    for (char i = '0'; i <= '9'; i++, arr_i++)
        symbols_map[arr_i] = i;

    const std::default_random_engine eng;
    const std::uniform_int_distribution<uint> distr(0, symbols_map.size());
    auto get_rand = std::bind(distr, eng);

    std::string res;

    res += '_';
    res += id;
    res += '_';

    for (int i = 0; i < random_ascii_lenght; i++)
        res += symbols_map[get_rand()];

    res += '_';
    res += id;
    res += '_';

    return res;
}

