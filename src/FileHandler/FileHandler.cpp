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

    stream.close();
    return str;
}

void FileHandler::writeContent(std::string path, std::string toWrite) {
    std::ofstream stream(path.c_str());
    if(stream) {
        stream << toWrite << std::endl;
        stream.close();
    }
    else {
        std::cerr << "An unexpected error occurred. Can't write content to " << path << "." << std::endl;
    }
}
