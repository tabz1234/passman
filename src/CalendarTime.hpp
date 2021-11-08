#ifndef CALENDARTIME_HPP
#define CALENDARTIME_HPP

#include <ctime>

class CalendarTime
{
    std::time_t unixtime_;

    std::tm* pcalendar_time_;

  public:
    CalendarTime(const std::time_t unixtime);

    int day();
    int month();
    int year();

    int second();
    int minute();
    int hour();
};

#endif
