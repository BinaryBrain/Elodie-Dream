#ifndef JSONACCESSOR_H
#define JSONACCESSOR_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "../Json/JsonParser.h"
#include "../Utils/Utils.h"
#include "../Include/EntityInfo.h"

using std::string;

class JsonAccessor {
public:
    JsonAccessor();
    virtual ~JsonAccessor();
    string getString(string key);
    int getInt(string key);
    std::vector<int>* getIntVector(string key);
    std::vector< std::vector<int>* >* getInt2DVector(string key);
    EntityInfo* getEntityInfo();
    bool load(string file);
    bool close();
protected:
private:
    rapidjson::Document values;
    rapidjson::Value& getAskedObject(string key);
    FILE * pFile;
    std::string pathToFile;
    bool loaded = false;
};

#endif // JSONACCESSOR_H
