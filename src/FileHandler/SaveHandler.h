#ifndef SAVEHANDLER_H
#define SAVEHANDLER_H

#include <fstream>
#include <cstdio>
#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output
#include "../env.h"

#include "../Json/JsonParser.h"
#include "../Game/Game.h"

class SaveHandler {
public:

    SaveHandler(std::string path);
    virtual ~SaveHandler();

    void save();

private:
    std::string path;

    void encrypt(std::string p);
    void decrpyt(std::string c);
};

#endif // SAVEHANDLER_H
