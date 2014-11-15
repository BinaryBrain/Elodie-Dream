#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#ifdef _WIN32
#include <direct.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>

/**
* The class handling files.
*/
class FileHandler
{
public:
    /**
    * \brief The constructor of FileHandler.
    */
    FileHandler();
    /**
    * \brief The destructor of FileHandler.
    */
    virtual ~FileHandler();

    /**
    * \brief Gets the contents of a file.
    * \param path The path to the file.
    * \return A string, the content of the file.
    */
    static std::string getContent(const std::string& path);
    /**
    * \brief Writes a string to a file.
    * \param path The path to the file.
    * \param toWrite The string to write.
    */
    static bool writeContent(const std::string &path, const std::string& toWrite);
    /**
    * \brief Deletes a file.
    * \param path The path to the file.
    */
    static bool deleteFile(const std::string& path);
    /**
    * \brief Checks if a file exists.
    * \param path The path to the file.
    * \return A bool, whether the file exists.
    */
    static bool fileExists(const std::string& path);
    /**
    * \brief Creates a file if it does not exist.
    * \param path The path to the file.
    * \return A bool, whether the file could be created.
    */
    static bool createFileIfNotExisting(const std::string& path, const std::string& content = "");
    /**
    * \brief Creates a directory if it does not exist.
    * \param path The path to the directory.
    * \return A bool, whether the directory could be created.
    */
    static bool createDirIfNotExisting(const std::string& path);

private:

};

#endif // FILEHANDLER_H
