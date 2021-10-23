#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <chrono>
#include <ctime>
#include <optional>
#include <string>

using unixtime_t = std::chrono::time_point<std::chrono::system_clock>;
using CalendarTime = time_t;

struct Password
{
    std::string id_;
    std::string str_;

    CalendarTime created_;
    std::optional<CalendarTime> last_acces_;

    Password(const std::string& id, const int random_ascii_lenght) noexcept;
    Password(const std::string& str,
             const unixtime_t last_acces,
             const unixtime_t created) noexcept;
    Password(const std::string& id, const std::string& str) noexcept;
};

#endif

