#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output<w>
#include <string>
#include <iostream>

#include "../Utils/Utils.h"

using std::string;

class JsonParser {
public:
    JsonParser();
    static string encode(rapidjson::Document &doc);
    static rapidjson::Document* decode(string s, rapidjson::Document* document, bool isFile);
    ~JsonParser();

private:
};

#endif // JSONHANDLER_H
