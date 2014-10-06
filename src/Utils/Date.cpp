#include "Date.h"

Date::Date() {
    time_t t = time(0);
    now = localtime(&t);
}

Date::~Date() {

}

std::string Date::getSec() {
    return Utils::itos(now->tm_sec);
}

std::string Date::getMin() {
    return Utils::itos(now->tm_min);
}

std::string Date::getHour() {
    return Utils::itos(now->tm_hour);
}

std::string Date::getDay() {
    return Utils::itos(now->tm_mday);
}

std::string Date::getMonth() {
    return Utils::itos(now->tm_mon + 1);
}

std::string Date::getYear() {
    return Utils::itos(now->tm_year + 1900);
}
