#ifndef DATE_H
#define DATE_H

#include <time.h>
#include "Utils.h"

class Date {
public:
    Date();
    ~Date();

    std::string getSec();
    std::string getMin();
    std::string getHour();
    std::string getDay();
    std::string getMonth();
    std::string getYear();
    void refreshTime();

private:
    struct tm* now;

    std::string onTwoDigits(int a);
};

#endif