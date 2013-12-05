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

    stringifier.setInt((int)state, "gamestate");
    std::string s = stringifier.getStringifiedDoc();

    FileHandler fh;
    fh.writeContent(path, s);
}

void SaveHandler::encrypt(std::string p) {

}

void SaveHandler::decrpyt(std::string c) {

}


