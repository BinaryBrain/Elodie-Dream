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
#include "FileHandler.h"

class SaveHandler {
public:
    static SaveHandler* getInstance();

    void setPath(std::string path);

    void save();
    void load();

private:
    SaveHandler();
    virtual ~SaveHandler();

    static SaveHandler* shInstance;
    SaveHandler& operator= (SaveHandler const&); // Makes operator= private

    std::string path;

    std::vector<int> encrypt(std::string p, std::string key);
    std::string decrypt(std::vector<int> tmp, std::string key);
};

#endif // SAVEHANDLER_H
