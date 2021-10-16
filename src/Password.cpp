#include "Password.hpp"

#include <array>
#include <functional>
#include <random>

Password::Password(const PasswordInfo& info) noexcept
  : info_{ info }
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

    str_ += '_';
    str_ += info_.id_;
    str_ += '_';

    for (int i = 0; i < info_.random_ascii_lenght_; i++)
        str_ += symbols_map[get_rand()];

    str_ += '_';
    str_ += info_.id_;
    str_ += '_';
}

std::string
Password::str() noexcept
{
    return str_;
}
