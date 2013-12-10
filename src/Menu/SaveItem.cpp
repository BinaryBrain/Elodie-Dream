#include "SaveItem.h"

SaveItem::SaveItem(std::string label): MenuItem(label) {

}

SaveItem::~SaveItem() {
    //dtor
}

std::pair<GameState, MenuComponent*> SaveItem::execute() {
    std::pair<GameState, MenuComponent*> p = std::make_pair(GameState::SAVE, this);
    return p;
}
