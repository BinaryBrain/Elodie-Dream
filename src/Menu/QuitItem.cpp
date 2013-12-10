#include "QuitItem.h"

QuitItem::QuitItem(std::string label): MenuItem(label) {
    //ctor
}

QuitItem::~QuitItem() {
    //dtor
}

std::pair<GameState, MenuComponent*> QuitItem::execute() {
    std::pair<GameState, MenuComponent*> p = std::make_pair(GameState::EXIT, this);
    return p;
}
