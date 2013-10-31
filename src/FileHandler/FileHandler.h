#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler {

    public:
        FileHandler();
        virtual ~FileHandler();

        static std::string getContent(std::string filename);
    protected:
    private:

};

#endif // FILEHANDLER_H
