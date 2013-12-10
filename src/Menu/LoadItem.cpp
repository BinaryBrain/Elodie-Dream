#include "LoadItem.h"

LoadItem::LoadItem(std::string label): MenuItem(label) {

}

LoadItem::~LoadItem() {
    //dtor
}

std::pair<GameState, MenuComponent*> LoadItem::execute() {
    std::pair<GameState, MenuComponent*> p = std::make_pair(GameState::LOAD, this);
    return p;
}
