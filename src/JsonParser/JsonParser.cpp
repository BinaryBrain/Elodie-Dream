#include "JsonParser.h"

using std::string;
using std::cerr;
using std::endl;

JsonParser::JsonParser() {}

string JsonParser::encode(rapidjson::Document &doc)
{
    //todo
    return "tout doux";
}

// FIXME address of local variable 'document' returned
rapidjson::Document* JsonParser::decode(string s, rapidjson::Document* document, bool isFile) {
    // Default template parameter uses UTF8 and MemoryPoolAllocator.
    if(isFile)
    {
        FILE* pFile = fopen (s.c_str(), "r");
        rapidjson::FileStream is(pFile);
        if(document->ParseStream<0>(is).HasParseError())
        {
            cerr << "Parse Error" << endl;
        }
    }
    else
    {
        char json[s.length()];
        for(unsigned int i(0); i< s.length(); i++)
        {
            json[i] = s.at(i);
        }
        printf("Original JSON:\n %s\n", json);

        // "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
        if (document->Parse<0>(json).HasParseError())
        {
            cerr << "Parse error" << endl;
        }
        // In-situ parsing, decode strings directly in the source string. Source must be string.
        char buffer[sizeof(json)];
        memcpy(buffer, json, sizeof(json));
        if (document->ParseInsitu<0>(buffer).HasParseError())
        {
            cerr << "Parse error" << endl;
        }
    }

    return document;
}

JsonParser::~JsonParser() {}
