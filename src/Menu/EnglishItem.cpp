#include "EnglishItem.h"

EnglishItem::EnglishItem(std::string label): MenuItem(label) {
    //ctor
}

EnglishItem::~EnglishItem() {
    //dtor
}

GameState EnglishItem::execute() {
    return GameState::INMENU;
}
