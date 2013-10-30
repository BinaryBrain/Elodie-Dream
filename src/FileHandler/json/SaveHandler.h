#ifndef SAVEHANDLER_H
#define SAVEHANDLER_H

#include <string>

class SaveHandler {

    public:
        SaveHandler(std::string path);
        void save();
        virtual ~SaveHandler();
    private:
        std::string m_path;
};

#endif // SAVEHANDLER_H
