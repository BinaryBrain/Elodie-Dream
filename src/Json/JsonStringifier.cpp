#include "JsonStringifier.h"

JsonStringifier::JsonStringifier() {
    //ctor
}

JsonStringifier::~JsonStringifier() {
    //dtor
}

void JsonStringifier::setInt(int i, std::string key) {

}

void JsonStringifier::setString(std::string s, std::string key) {

}

void JsonStringifier::setIntVector(std::vector<int> v, std::string key) {

}

void JsonStringifier::setInt2DVector(std::vector<std::vector<int> > v, std::string key) {

}

rapidjson::Document* JsonStringifier::getDocument() {
    return &values;
}

