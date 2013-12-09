#include "LoadItem.h"

LoadItem::LoadItem(std::string label, std::string date): MenuItem(label) {
    this->date = date;
    isSaveRelateditem = true;
}

LoadItem::~LoadItem() {
    //dtor
}

std::pair<GameState, std::string> LoadItem::execute() {
    std::pair<GameState, std::string> p = std::make_pair(GameState::LOAD, text->getString());
    return p;
}
