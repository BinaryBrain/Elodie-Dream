#include "EnglishItem.h"

EnglishItem::EnglishItem(std::string label): MenuItem(label) {
    //ctor
}

EnglishItem::~EnglishItem() {
    //dtor
}

std::pair<GameState, std::string> EnglishItem::execute() {
    std::pair<GameState, std::string> p = std::make_pair(GameState::INMENU, text->getString());
    return p;
}
