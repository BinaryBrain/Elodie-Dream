#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <sstream>
#include <string>

class Utils {

    public:
        Utils();
        static char* toCharArray(std::string s);
        static std::string itos(int number);

};

#endif // UTILS_H_INCLUDED
