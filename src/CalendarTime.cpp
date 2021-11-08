#include "CalendarTime.hpp"

CalendarTime::CalendarTime(const time_t unixtime)
{
    unixtime_ = time(0);
    unixtime_ = unixtime;

    pcalendar_time_ = std::localtime(&unixtime_);
}

int
CalendarTime::day()
{
    return pcalendar_time_->tm_mday;
}
int
CalendarTime::month()
{
    return pcalendar_time_->tm_mon + 1;
}
int
CalendarTime::year()
{
    return pcalendar_time_->tm_year - 100;
}
int
CalendarTime::second()
{
    return pcalendar_time_->tm_sec;
}
int
CalendarTime::minute()
{
    return pcalendar_time_->tm_min;
}
int
CalendarTime::hour()
{
    return pcalendar_time_->tm_hour;
}
