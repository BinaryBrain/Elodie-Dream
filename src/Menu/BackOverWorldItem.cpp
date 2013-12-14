#include "BackOverWorldItem.h"

BackOverWorldItem::BackOverWorldItem(std::string label): MenuItem(label) {
    //ctor
}

BackOverWorldItem::~BackOverWorldItem() {
    if(text) {
        delete text;
        text = NULL;
    }
}

std::pair<GameState, MenuComponent*> BackOverWorldItem::execute() {
    std::pair<GameState, MenuComponent*> p = std::make_pair(GameState::LOAD, this); // todo
    return p;
}
