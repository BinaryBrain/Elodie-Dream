#include "SaveItem.h"

SaveItem::SaveItem(std::string label): MenuItem(label) {

}

SaveItem::~SaveItem() {
    //dtor
}

std::pair<GameState, std::string> SaveItem::execute() {
    std::pair<GameState, std::string> p = std::make_pair(GameState::SAVE, text->getString());
    return p;
}
