#include "QuitItem.h"

QuitItem::QuitItem(std::string label): MenuItem(label) {
    //ctor
}

QuitItem::~QuitItem() {
    //dtor
}

std::pair<GameState, std::string> QuitItem::execute() {
    std::pair<GameState, std::string> p = std::make_pair(GameState::EXIT, text->getString());
    return p;
}
