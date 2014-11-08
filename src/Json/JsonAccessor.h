#ifndef JSONACCESSOR_H
#define JSONACCESSOR_H

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output<w>
#include "rapidjson/stringbuffer.h"

#include "../Utils/Utils.h"
#include "../Include/EntityInfo.h"

class JsonAccessor {
public:
    JsonAccessor();
    virtual ~JsonAccessor();
    std::string getString(const std::string& key);
    int getInt(const std::string& key);
    double getDouble(const std::string& key);
    std::vector<int>* getIntVector(const std::string& key);
    std::vector< std::vector<int>* >* getInt2DVector(const std::string& key);
    EntityInfo* getEntityInfo();
    bool load(const std::string& pathToFile);
    bool canTakeElementFrom(const std::string& key);
    bool close();
    bool createJsonIfNotExisting(const std::string& file);

private:
    rapidjson::Document values;
    rapidjson::Value& getAskedObject(std::string key);
    FILE* pFile;
    std::string pathToFile;
    bool loaded = false;
};

#endif // JSONACCESSOR_H
