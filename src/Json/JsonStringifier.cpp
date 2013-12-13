#include "JsonStringifier.h"


JsonStringifier::JsonStringifier() {
    const char buff[] = "{}";
    if(values.Parse<0>(buff).HasParseError() == true){
        std::cerr << "Parse error when initializing document in JsonStringifier" << std::endl;
    }
}

JsonStringifier::~JsonStringifier() {

}

void JsonStringifier::add(std::string key, int i) {
    values.AddMember(key.c_str(), i, values.GetAllocator());
}

void JsonStringifier::add(std::string key, std::string s) {
    values.AddMember(key.c_str(), s.c_str(), values.GetAllocator());
}

void JsonStringifier::add(std::string key, std::vector<int> v) {
    /*rapidjson::Value a;	// This time we uses non-const reference.
    for (unsigned int i(0); i <v.size(); ++i){
        a.PushBack(i, values.GetAllocator());	// May look a bit strange, allocator is needed for potentially realloc. We normally uses the document's.
    }
    values.AddMember(key.c_str(), a, values.GetAllocator());*/
}

void JsonStringifier::add(std::string key, std::vector<std::vector<int> > v) {

}

std::string JsonStringifier::getStringifiedDoc() {
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    values.Accept(writer);

    return strbuf.GetString();
}
