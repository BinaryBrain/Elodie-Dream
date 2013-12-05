#include "SaveHandler.h"

SaveHandler::SaveHandler() {

}

SaveHandler::~SaveHandler() {

}

void SaveHandler::setPath(std::string path) {
    this->path = path;
}

void SaveHandler::save() {
    JsonStringifier stringifier;
    GameState state = Game::getInstance()->getState();
    std::cout << (int)state << std::endl;

    stringifier.setInt((int)state, "gamestate");
    std::string s = stringifier.getStringifiedDoc();
    std::cout << "stringified: " << s << std::endl;

    FileHandler fh;
    fh.writeContent(path, s);
}

void SaveHandler::encrypt(std::string p) {

}

void SaveHandler::decrpyt(std::string c) {

}


