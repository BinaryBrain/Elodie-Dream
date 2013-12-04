#ifndef SAVEHANDLER_H
#define SAVEHANDLER_H

#include <fstream>
#include <cstdio>
#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output
#include "../env.h"

#include "SaveHandler.h"
#include "../Game/Game.h"
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
    * \brief The destructor of SaveHandler.
    */
    virtual ~SaveHandler();

    void save();

private:
    std::string path;
};

#endif // SAVEHANDLER_H
