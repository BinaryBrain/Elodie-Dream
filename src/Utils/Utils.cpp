#include <string>
#include "Utils.h"

using std::string;

Utils::Utils() {}

char* Utils::toCharArray(string s) {
    char c [s.length()];
    for(unsigned int i(0); i< s.length(); i++) c[i] = s.at(i);
    return c;
}
