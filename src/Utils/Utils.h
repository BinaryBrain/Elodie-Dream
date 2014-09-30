#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

class Utils {
public:
    Utils();
    static char* toCharArray(std::string s);
    static std::string itos(int number);
    static std::string toStringWithLength(int number, unsigned int length);
    static bool fileExists(const std::string& name);
};

#endif // UTILS_H_INCLUDED
