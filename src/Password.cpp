#include "Password.hpp"

#include <array>
#include <random>

Password::Password(const std::string& str,
                   const unixtime_t last_acces,
                   const unixtime_t created) noexcept
  : str_{ str }
  , created_{ std::chrono::system_clock::to_time_t(created) }
  , last_acces_{ std::chrono::system_clock::to_time_t(last_acces) }
{}
Password::Password(const std::string& id, const std::string& str) noexcept

  : id_{ id }
  , str_{ str }
  , created_{ std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now()) }
  , last_acces_{ std::nullopt }
{}
Password::Password(const std::string& id,
                   const int random_ascii_lenght) noexcept
  : id_{ id }
  , created_{ std::chrono::system_clock::to_time_t(
      std::chrono::system_clock::now()) }
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

    str_ += "_" + id_ + "_";

    for (int i = 0; i < random_ascii_lenght; i++) {
        str_ += symbols_map[distr(eng)];
    }

    str_ += "_" + id_ + "_";
}
