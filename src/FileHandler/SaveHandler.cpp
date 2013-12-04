#include "SaveHandler.h"

SaveHandler::SaveHandler(std::string path) {
    this->path = path;
}

SaveHandler::~SaveHandler() {

}


void SaveHandler::save() {
    GameState state = Game::getInstance()->getState();
    std::string s = "result of JsonpParser.encode()";
    std::cout << "Actually used so no error >:3" << (int)state <<s << std::endl;
}

void SaveHandler::encrypt(std::string p) {

}

void SaveHandler::decrpyt(std::string c) {

}


