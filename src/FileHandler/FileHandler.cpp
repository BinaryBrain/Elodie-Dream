#include <iostream>
#include <fstream>
#include <streambuf>

#include "FileHandler.h"

FileHandler::FileHandler() {

}

FileHandler::~FileHandler() {

}

std::string FileHandler::getContent(const std::string& path) {
    std::ifstream stream(path.c_str());

    // Do NOT remove parentheses. (most vexing parse)
    std::string str((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());

    stream.close();
    return str;
}

bool FileHandler::writeContent(const std::string& path, const std::string& toWrite) {
    std::ofstream stream(path.c_str());
    if(stream) {
        stream << toWrite << std::endl;
        stream.close();
        return true;
    }
    else {
        std::cerr << "An error occurred: could not write to " << path << "." << std::endl;
        return false;
    }
}

bool FileHandler::deleteFile(const std::string& path) {
    if (remove(path.c_str()) != 0 ) {
        std::cerr << "An error occurred: could not delete " << path << "." << std::endl;
        return false;
    }
    return true;
}

bool FileHandler::fileExists(const std::string& path) {
  std::ifstream f((path).c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}

bool FileHandler::createDirIfNotExisting(const std::string& path) {
    if (CreateDirectory(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
        return true;
    } else {
        std::cerr << "Could not create save folder." << std::endl;
        return false;
    }
}
