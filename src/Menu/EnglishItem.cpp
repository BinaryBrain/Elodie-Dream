#include "EnglishItem.h"

EnglishItem::EnglishItem(std::string label): MenuItem(label) {
    //ctor
}

EnglishItem::~EnglishItem() {
    //dtor
}

std::pair<GameState, MenuComponent*> EnglishItem::execute() {
    std::pair<GameState, MenuComponent*> p = std::make_pair(GameState::INMENU, this);
    return p;
}
