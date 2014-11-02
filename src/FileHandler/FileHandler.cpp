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
        std::cerr << "An error occurred: could not write to " << path << "." << std::endl;
    }
}

void FileHandler::deleteFile(std::string path) {
    if (remove(path.c_str()) != 0 ) {
        std::cerr << "An error occurred: could not delete " << path << "." << std::endl;
    }
}

bool FileHandler::fileExists(const std::string& path) {
  std::ifstream f(path.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}
