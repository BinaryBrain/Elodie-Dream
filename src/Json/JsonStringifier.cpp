#include "JsonStringifier.h"


JsonStringifier::JsonStringifier() {
    reset();
}

JsonStringifier::~JsonStringifier() {

}

void JsonStringifier::add(std::string key, int i) {
    doc.AddMember(key.c_str(), i, doc.GetAllocator());
}

void JsonStringifier::add(std::string key, double d) {
    doc.AddMember(key.c_str(), d, doc.GetAllocator());
}

void JsonStringifier::add(std::string key, std::string s) {
    doc.AddMember(key.c_str(), s.c_str(), doc.GetAllocator());
}

void JsonStringifier::add(std::string key, std::vector<int> v) {
    rapidjson::Value arr;
    arr.SetArray();

    for (size_t i = 0; i < v.size(); ++i) {
        arr.PushBack(i, doc.GetAllocator());
    }
    doc.AddMember(key.c_str(), arr, doc.GetAllocator());
}

void JsonStringifier::add(std::string key, std::vector< std::vector<int> > v2d) {
    rapidjson::Value arr;
    rapidjson::Value arr2;

    arr.SetArray();

    for (size_t i = 0; i < v2d.size(); ++i) {
        arr2.SetArray();

        for (size_t j = 0; j < v2d[i].size(); ++j) {
            arr2.PushBack(v2d[i][j], doc.GetAllocator());
        }
        arr.PushBack(arr2, doc.GetAllocator());
    }
    doc.AddMember(key.c_str(), arr, doc.GetAllocator());
}

std::string JsonStringifier::getStringifiedDoc() {
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    doc.Accept(writer);

    return strbuf.GetString();
}

bool JsonStringifier::reset() {
    doc.SetObject();
    const char buff[] = "{}";
    if (doc.Parse<0>(buff).HasParseError()) {
        std::cerr << "Parse error when initializing document in JsonStringifier" << std::endl;
        return false;
    }
    return true;
}
