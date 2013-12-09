#include "SaveItem.h"

SaveItem::SaveItem(std::string label, std::string date): MenuItem(label) {
    this->date = date;
    isSaveItem = true;
}

SaveItem::~SaveItem() {
    //dtor
}

std::pair<GameState, std::string> SaveItem::execute() {
    std::pair<GameState, std::string> p = std::make_pair(GameState::SAVE, text->getString());
    return p;
}

std::string SaveItem::getDate() {
    return date;
}
