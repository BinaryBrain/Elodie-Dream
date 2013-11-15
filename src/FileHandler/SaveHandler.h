#ifndef SAVEHANDLER_H
#define SAVEHANDLER_H

#include <string>
/**
* Not implemented yet.
* Can save json in a file.
*/
class SaveHandler {

    public:
        /**
        * \brief The constructor of SaveHandler. Sets the path of the file.
        *
        * \param[in] path The path to the file.
        */
        SaveHandler(std::string path);
        /**
        * \brief Can save something in a file (not yet implemented).
        */
        void save();
        /**
        * \brief The destructor of SaveHandler.
        */
        virtual ~SaveHandler();
    private:
        std::string m_path;
};

#endif // SAVEHANDLER_H
