#include "SaveItem.h"

SaveItem::SaveItem(std::string label, std::string date): MenuItem(label) {
    this->date = date;
    isSaveRelateditem = true;
}

SaveItem::~SaveItem() {
    //dtor
}

std::pair<GameState, std::string> SaveItem::execute() {
    std::pair<GameState, std::string> p = std::make_pair(GameState::SAVE, text->getString());
    return p;
}
