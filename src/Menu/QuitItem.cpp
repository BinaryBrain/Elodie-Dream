#include "QuitItem.h"

QuitItem::QuitItem(std::string label): MenuItem(label) {
    //ctor
}

QuitItem::~QuitItem() {
    //dtor
}

GameState QuitItem::execute() {
    return GameState::EXIT;
}
