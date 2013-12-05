#ifndef SAVEHANDLER_H
#define SAVEHANDLER_H

#include <fstream>
#include <cstdio>
#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output
#include "../env.h"

#include "../Json/JsonParser.h"
#include "../Json/JsonStringifier.h"
#include "../Game/Game.h"
#include "FileHandler.h"

class SaveHandler {
public:

    SaveHandler();
    virtual ~SaveHandler();

    void setPath(std::string path);

    void addSave();
    void applySaves();
    void load();

private:
    std::string path;

    std::vector<int> encrypt(std::string p, std::string key);
    std::string decrypt(std::vector<int> tmp, std::string key);
};

#endif // SAVEHANDLER_H
