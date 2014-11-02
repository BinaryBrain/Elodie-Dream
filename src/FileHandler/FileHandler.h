#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

/**
* The class handling files.
* Doesn't do much yet.
*/
class FileHandler {
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
    static std::string getContent(std::string path);
    /**
    * \brief Writes a string to a file.
    * \param path The path to the file.
    * \param toWrite The string to write.
    */
    static void writeContent(std::string path, std::string toWrite);
    /**
    * \brief Deletes a file.
    * \param path The path to the file.
    */
    static void deleteFile(std::string path);
    /**
    * \brief Checks if a file exists.
    * \param path A string, the path to the file.
    * \return A bool, whether the file exists.
    */
    static bool fileExists(const std::string& path);

private:

};

#endif // FILEHANDLER_H
