#include "SaveHandler.h"

SaveHandler::SaveHandler() {

}

SaveHandler::~SaveHandler() {

}

void SaveHandler::setPath(std::string path) {
    this->path = path;
}

void SaveHandler::save() {
    std::string key("");
    std::string value("");
    JsonStringifier stringifier;

    key = "gamestate";
    GameState state = Game::getInstance()->getState();
    stringifier.setInt(key, (int)state);

    key = "test";
    value = "la vie!";
    stringifier.setString(key, value);

    std::string toWrite(stringifier.getStringifiedDoc());
    FileHandler fh;
    std::cout << toWrite << std::endl;
    fh.writeContent(path, toWrite);
}

void SaveHandler::encrypt(std::string p) {

}

void SaveHandler::decrpyt(std::string c) {

}


