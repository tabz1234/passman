#ifndef GENERATERANDOMPASSWORD_HPP
#define GENERATERANDOMPASSWORD_HPP

#include <array>
#include <random>
#include <string>

static std::string
generateRandomPassword(const std::string& password_id, const int max_lenght)
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

    std::default_random_engine eng(std::random_device{}());
    std::uniform_int_distribution<size_t> distr(0, symbols_map.size() - 1);

    std::string ret;

    ret += "_" + password_id + "_";

    const int random_part_len = max_lenght - 4 - password_id.size();

    for (int i = 0; i < random_part_len; i++) {
        ret += symbols_map[distr(eng)];
    }

    ret += "_" + password_id + "_";

    return ret;
}

#endif
