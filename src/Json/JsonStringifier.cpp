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
    rapidjson::Value arr;
    arr.SetArray();

    for (std::size_t i = 0; i < v.size(); ++i) {
        arr.PushBack(i, values.GetAllocator());
    }
    values.AddMember(key.c_str(), arr, values.GetAllocator());
}

void JsonStringifier::add(std::string key, std::vector< std::vector<int> > v2d) {
    rapidjson::Value arr;
    rapidjson::Value arr2;

    arr2.SetArray();

    for (std::size_t i = 0; i < v2d.size(); ++i) {
        arr2.SetArray();

        for (std::size_t j = 0; v2d[i].size(); ++j) {
            arr2.PushBack(i, values.GetAllocator());
        }
        arr.PushBack(arr2, values.GetAllocator());
    }
    values.AddMember(key.c_str(), arr, values.GetAllocator());
}

std::string JsonStringifier::getStringifiedDoc() {
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    values.Accept(writer);

    return strbuf.GetString();
}
