#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <ctime>
#include <optional>
#include <string>

#include "CalendarTime.hpp"

struct Password final
{
    std::string id_;

    std::string str_;

    CalendarTime created_;
    std::optional<CalendarTime> last_acces_;
};

#endif

