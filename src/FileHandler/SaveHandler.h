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
#include "FileHandler.h"

class SaveHandler {
public:

    SaveHandler();
    virtual ~SaveHandler();

    void setPath(std::string path);

    void save();
    void load();

private:
    std::string path;

    rapidjson::Document createDocument();
    void encrypt(std::string p);
    void decrpyt(std::string c);
};

#endif // SAVEHANDLER_H
