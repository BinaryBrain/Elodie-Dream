#include <iostream>
#include <fstream>
#include <streambuf>

#include "FileHandler.h"

FileHandler::FileHandler() {

}

FileHandler::~FileHandler() {

}

std::string FileHandler::getContent(std::string path) {
    std::ifstream stream(path.c_str());

    // Do NOT remove parentheses. (most vexing parse)
    std::string str((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());
    return str;
}

void FileHandler::writeContent(std::string path, std::string toWrite) {
    std::ofstream stream(path.c_str());
    if(stream) stream << toWrite << std::endl;
    else std::cerr << "An unexpected error occured. Is the file available ?" << std::endl;
}
