#include <iostream>
#include <fstream>
#include <streambuf>

#include "FileHandler.h"

FileHandler::FileHandler() {

}

FileHandler::~FileHandler() {

}

std::string FileHandler::getContent(std::string filename) {
    std::ifstream stream(filename.c_str());

    // Do NOT remove parentheses. (most vexing parse)
    std::string str((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());
    return str;
}

void FileHandler::writeContent(std::string filename, std::string toWrite) {
    //todo
}
