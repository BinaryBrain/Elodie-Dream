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
    *
    * \param[in] file name The name of the file.
    * \return A string, the content of the file.
    */
    static std::string getContent(std::string filename);
protected:
private:

};

#endif // FILEHANDLER_H
