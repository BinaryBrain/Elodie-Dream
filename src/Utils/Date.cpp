#include "Date.h"

Date::Date()
{
    refreshTime();
}

Date::~Date()
{

}

std::string Date::getSec()
{
    return onTwoDigits(now->tm_sec);
}

std::string Date::getMin()
{
    return onTwoDigits(now->tm_min);
}

std::string Date::getHour()
{
    return onTwoDigits(now->tm_hour);
}

std::string Date::getDay()
{
    return onTwoDigits(now->tm_mday);
}

std::string Date::getMonth()
{
    return onTwoDigits(now->tm_mon + 1);
}

std::string Date::getYear()
{
    return onTwoDigits(now->tm_year + 1900);
}

std::string Date::getHMS(std::string separator)
{
    return getHour() + separator + getMin() + separator + getSec();
}

std::string Date::getDMY(std::string separator)
{
    return getDay() + separator + getMonth() + separator + getYear();
}

void Date::refreshTime()
{
    time_t t = time(0);
    now = localtime(&t);
}

std::string Date::onTwoDigits(int a)
{
    std::string s = Utils::itos(a);
    return a < 10 ? "0" + s : s;
}
