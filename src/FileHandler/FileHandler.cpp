#include <iostream>
#include <fstream>
#include <streambuf>

#include "FileHandler.h"

FileHandler::FileHandler()
{

}

FileHandler::~FileHandler()
{

}

std::string FileHandler::getContent(const std::string& path)
{
    std::ifstream stream(path.c_str());

    // Do NOT remove parentheses. (most vexing parse)
    std::string str((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());

    stream.close();
    return str;
}

bool FileHandler::writeContent(const std::string& path, const std::string& toWrite)
{
    std::ofstream stream(path.c_str());
    if (stream)
    {
        stream << toWrite << std::endl;
        stream.close();
        return true;
    }
    else
    {
        std::cerr << "Error: could not write to " << path << "." << std::endl;
        return false;
    }
}

bool FileHandler::deleteFile(const std::string& path)
{
    if (std::remove(path.c_str()) != 0 )
    {
        std::cerr << "Error: could not delete " << path << "." << std::endl;
        return false;
    }
    return true;
}

bool FileHandler::fileExists(const std::string& path)
{
    std::ifstream f((path).c_str());
    if (f.good())
    {
        f.close();
        return true;
    }
    else
    {
        f.close();
        return false;
    }
}

bool FileHandler::createFileIfNotExisting(const std::string& path, const std::string& content)
{
    if (!fileExists(path))
    {
        if (FILE* f = fopen(path.c_str(), "w"))
        {
            fputs(content.c_str(), f);
            fclose(f);
            return true;
        }
        else
        {
            std::cerr << "Error: could not create " << path << "." << std::endl;
            return false;
        }
    }
    return true;
}

bool FileHandler::createDirIfNotExisting(const std::string& path)
{
    struct stat info;

    if (stat(path.c_str(), &info) == 0 && S_ISDIR(info.st_mode))
    {
        // The directory already exists, so nothing to do
    }
    else
    {
        int mkdirRes = 0;
#ifdef _WIN32
        mkdirRes = mkdir(path.c_str());
#else
        mkdirRes = mkdir(path.c_str(), 0777);
#endif
        if (mkdirRes == -1)    // Creates the directory
        {
            std::cerr << "Error: can't create " << path << std::endl;
            return false;
        }
    }
    return true;
}
