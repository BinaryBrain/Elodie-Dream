#include "NewGameItem.h"

NewGameItem::NewGameItem(std::string label): MenuItem(label) {
    //ctor
}

NewGameItem::~NewGameItem() {
    if(text) {
        delete text;
        text = NULL;
    }
}

std::pair<GameState, MenuComponent*> NewGameItem::execute() {
    std::pair<GameState, MenuComponent*> p = std::make_pair(GameState::NEWGAME, this);
    return p;
}
