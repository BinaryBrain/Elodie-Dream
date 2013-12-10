#include "NewGameItem.h"

NewGameItem::NewGameItem(std::string label): MenuItem(label) {
    //ctor
}

NewGameItem::~NewGameItem() {
    //dtor
}

std::pair<GameState, MenuComponent*> NewGameItem::execute() {
    std::pair<GameState, MenuComponent*> p = std::make_pair(GameState::INOVERWORLD, this);
    return p;
}
