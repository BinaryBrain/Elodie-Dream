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
    std::cout << "Added: " << i << std::endl;
    values.AddMember(key.c_str(), i, values.GetAllocator());
}

void JsonStringifier::add(std::string key, std::string s) {
    values.AddMember(key.c_str(), s.c_str(), values.GetAllocator());
}

void JsonStringifier::add(std::string key, std::vector<int> v) {

}

void JsonStringifier::add(std::string key, std::vector<std::vector<int> > v) {

}

std::string JsonStringifier::getStringifiedDoc() {
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    values.Accept(writer);

    return strbuf.GetString();
}

