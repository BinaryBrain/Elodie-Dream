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
    static int stoi(std::string s);
    static std::string toStringWithLength(int number, unsigned int length);
    static std::pair<std::string, std::string> splitString(const std::string& original, const std::string& separator);
    static bool fileExists(const std::string& name);
};

#endif // UTILS_H_INCLUDED
