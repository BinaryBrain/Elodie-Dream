#include "SaveItem.h"

SaveItem::SaveItem(std::string label): MenuItem(label) {
    //ctor
}

SaveItem::~SaveItem() {
    //dtor
}

GameState SaveItem::execute() {
    return GameState::INMENU;
}
