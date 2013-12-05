#include "JsonStringifier.h"


JsonStringifier::JsonStringifier() {

}

JsonStringifier::~JsonStringifier() {

}

void JsonStringifier::setInt(int i, std::string key) {
    values.AddMember(key.c_str(), i, values.GetAllocator());
}

void JsonStringifier::setString(std::string s, std::string key) {
    values.AddMember(key.c_str(), s.c_str(), values.GetAllocator());
}

void JsonStringifier::setIntVector(std::vector<int> v, std::string key) {

}

void JsonStringifier::setInt2DVector(std::vector<std::vector<int> > v, std::string key) {

}

std::string JsonStringifier::getStringifiedDoc() {
    rapidjson::GenericStringBuffer< rapidjson::UTF8<> > buffer;
    rapidjson::Writer< rapidjson::GenericStringBuffer< rapidjson::UTF8<> > > writer(buffer);
    values.Accept(writer);

    return buffer.GetString();
}

