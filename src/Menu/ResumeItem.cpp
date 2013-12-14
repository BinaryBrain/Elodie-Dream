#include "ResumeItem.h"

ResumeItem::ResumeItem(std::string label): MenuItem(label) {
    //ctor
}

ResumeItem::~ResumeItem() {
    if(text) {
        delete text;
        text = NULL;
    }
}

std::pair<GameState, MenuComponent*> ResumeItem::execute() {
    std::pair<GameState, MenuComponent*> p = std::make_pair(GameState::LOAD, this); // todo
    return p;
}
