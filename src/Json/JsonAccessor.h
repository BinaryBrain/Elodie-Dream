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
#include "FileHandler.h"

class JsonAccessor
{
public:
    JsonAccessor();
    ~JsonAccessor();
    std::string getString(const std::string& key);
    int getInt(const std::string& key);
    double getDouble(const std::string& key);
    std::vector<int> getIntVector(const std::string& key);
    std::vector< std::vector<int> > getInt2DVector(const std::string& key);
    std::map<std::string, int> getMap(const std::string& key, const std::vector<std::string>& keys);
    std::vector< std::map<std::string, int> > getVectMaps(const std::string& key, const std::vector<std::string>& keys);
    EntityInfo* getEntityInfo();

    std::string getStringWithDefault(const std::string& key, const std::string& defaultValue);
    int getIntWithDefault(const std::string& key, int defaultValue);

    bool loadJsonFrom(const std::string& pathToFile);
    bool setJson(const std::string& json);
    bool canTakeElementFrom(const std::string& key);
    std::string getCurrentJson();
    void reset();

private:
    rapidjson::Document doc;
    std::string pathToFile;
    char* buffer = NULL;
};

#endif // JSONACCESSOR_H
