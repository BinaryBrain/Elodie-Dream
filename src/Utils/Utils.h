#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
/**
* A class with many useful functions.
*/
class Utils
{
public:
    /**
    * \brief The default constructor of Utils.
    */
    Utils();
    /**
    * \brief Converts a string to a char array.
    * \param s The string to convert in char array.
    * \return The char array wanted.
    */
    static char* toCharArray(std::string s);
    /**
    * \brief Converts an int to a string.
    * \param number The int to convert.
    * \return The string wanted.
    */
    static std::string itos(int number);
    /**
    * \brief Converts a string to an int.
    * \param number The string to convert.
    * \return The int wanted.
    */
    static int stoi(std::string s);
    /**
    * \brief Converts an int to a string of a certain length. Adds '0's at the left of the string while the string is smaller than length.
    * \param number The number to convert.
    * \param length The length of the resulting string.
    * \return The wanted string.
    */
    static std::string toStringWithLength(int number, unsigned int length);
    /**
    * \brief Separates a string into two substrings at the first position of the separator.
    * \param original The original string to split.
    * \param separator The separator used to split the string.
    * \return A pair of string, the part before the separator and the part after.
    */
    static std::pair<std::string, std::string> splitString(const std::string& original, const std::string& separator);
};

#endif // UTILS_H_INCLUDED
