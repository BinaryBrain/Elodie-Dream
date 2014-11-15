#include "Utils.h"

Utils::Utils()
{

}

std::string Utils::itos(int number)
{
    std::stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
}

int Utils::stoi(std::string s)
{
    int ret;
    std::istringstream(s) >> ret;
    return ret;
}

std::string Utils::toStringWithLength(int number, unsigned int length)
{
    std::string output = "";
    std::stringstream ss;
    ss << number;

    output = ss.str();
    while(output.length() < length)
    {
        output = "0"+output;
    }

    return output;
}

std::pair<std::string, std::string> Utils::splitString(const std::string& original, const std::string& separator)
{
    size_t pos = original.find(separator);
    std::string wanted = original.substr(0, pos);
    std::string newString = original.substr(pos+1);

    return std::make_pair(wanted, newString);
}
