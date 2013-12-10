#include "NewGameItem.h"

NewGameItem::NewGameItem(std::string label): MenuItem(label) {
    //ctor
}

NewGameItem::~NewGameItem() {
    //dtor
}

std::pair<GameState, std::string> NewGameItem::execute() {
    std::pair<GameState, std::string> p = std::make_pair(GameState::INOVERWORLD, label);
    return p;
}
