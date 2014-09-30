#include "Utils.h"

Utils::Utils() {

}

std::string Utils::itos(int number) {
    std::stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
}

std::string Utils::toStringWithLength(int number, unsigned int length) {
    std::string output = "";
    std::stringstream ss;
    ss << number;

    output = ss.str();
    while(output.length() < length) {
        output = "0"+output;
    }

    return output;
}

bool Utils::fileExists(const std::string& name) {
  std::ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}
