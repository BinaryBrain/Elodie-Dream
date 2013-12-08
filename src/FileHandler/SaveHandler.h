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
#include "../Json/JsonAccessor.h"
#include "FileHandler.h"

class SaveHandler {
public:
    static SaveHandler* getInstance();

    void setPath(std::string path);
    JsonStringifier* getStringifier();

    void save();
    std::string load();

    void clearStringifier();

private:
    SaveHandler();
    virtual ~SaveHandler();

    static SaveHandler* shInstance;
    SaveHandler& operator= (SaveHandler const&); // Makes operator= private

    std::string path;
    JsonStringifier* stringifier;
    JsonAccessor* accessor;

    std::vector<int> encrypt(std::string p, std::string key);
    std::string decrypt(std::vector<int> tmp, std::string key);
};

#endif // SAVEHANDLER_H
