#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output
#include <iostream>

#include "JsonHandler.h"

using namespace std;


JsonHandler::JsonHandler() {}

std::string encode(rapidjson::Document &doc) {
    //todo
    return "tout doux";
}

rapidjson::Document decode(std::string s) {
    const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
	printf("Original JSON:\n %s\n", json);

	rapidjson::Document document;	// Default template parameter uses UTF8 and MemoryPoolAllocator.

    // "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
    if (document.Parse<0>(json).HasParseError()) cout << "Parse error" << endl;

    // In-situ parsing, decode strings directly in the source string. Source must be string.
    char buffer[sizeof(json)];
    memcpy(buffer, json, sizeof(json));
    if (document.ParseInsitu<0>(buffer).HasParseError()) cout << "Parse error" << endl;

    return document;
}

JsonHandler::~JsonHandler() {}
