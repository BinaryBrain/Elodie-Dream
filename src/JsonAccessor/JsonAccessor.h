#ifndef JSONACCESSOR_H
#define JSONACCESSOR_H

#include <string>
#include <iostream>
#include <vector>

#include "../JsonParser/JsonParser.h"
#include "../Utils/Utils.h"

using std::string;

class JsonAccessor
{
    public:
        JsonAccessor();
        virtual ~JsonAccessor();
        string getString(string key);
        int getInt(string key);
        std::vector<int>* getIntVector(string key);
        bool load(string file);
    protected:
    private:
        rapidjson::Document values;
        bool loaded = false;
};

#endif // JSONACCESSOR_H
