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

    // todo fin why there should be another string each time, not the same one which switches values
    std::string keyState = "gamestate";
    GameState state = Game::getInstance()->getState();
    stringifier.setInt(keyState, (int)state);

    std::string test = "test";
    std::string vie = "la vie!";
    stringifier.setString(test, vie);

    std::string toWrite(stringifier.getStringifiedDoc());
    FileHandler fh;
    std::cout << "Saved string: " << toWrite << std::endl;
    fh.writeContent(path, toWrite);
}

void SaveHandler::encrypt(std::string p) {

}

void SaveHandler::decrpyt(std::string c) {

}


