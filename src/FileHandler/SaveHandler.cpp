#include "SaveHandler.h"

SaveHandler::SaveHandler() {

}

SaveHandler::~SaveHandler() {

}

void SaveHandler::setPath(std::string path) {
    this->path = path;
}

void SaveHandler::save() {

    rapidjson::Document doc = createDocument();
    std::string s = JsonParser::encode(doc);

    FileHandler fh;
    fh.writeContent(path, s);
}

rapidjson::Document SaveHandler::createDocument() {
    GameState state = Game::getInstance()->getState();

    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Value v;
    v.AddMember("int", (int)state, doc.GetAllocator());

    return doc;
}

void SaveHandler::encrypt(std::string p) {

}

void SaveHandler::decrpyt(std::string c) {

}


