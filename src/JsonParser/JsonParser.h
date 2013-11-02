#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output<w>
#include <string>

class JsonHandler
{
    public:
        JsonHandler();
        static std::string encode(rapidjson::Document &doc);
        static rapidjson::Document decode(std::string s, bool isFile);
        ~JsonHandler();

    private:
};

#endif // JSONHANDLER_H
