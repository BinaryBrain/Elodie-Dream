#include "NewGameItem.h"

NewGameItem::NewGameItem(std::string label): MenuItem(label) {
    //ctor
}

NewGameItem::~NewGameItem() {
    //dtor
}

GameState NewGameItem::execute() {
    return GameState::INOVERWORLD;
}
