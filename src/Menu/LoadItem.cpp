#include "LoadItem.h"

LoadItem::LoadItem(std::string label): MenuItem(label) {
    //ctor
}

LoadItem::~LoadItem() {
    //dtor
}

std::pair<GameState, std::string> LoadItem::execute() {
    std::pair<GameState, std::string> p = std::make_pair(GameState::LOAD, text->getString());
    return p;
}
