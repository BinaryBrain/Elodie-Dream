#include "TitleMenu.h"

TitleMenu::TitleMenu(std::string label, GameState state): Menu(label, state) {

}

TitleMenu::~TitleMenu() {

}

void TitleMenu::toLevelMenu() {
    index = 0;
    for (std::size_t i = 0; i < items.size(); ++i) {
        if (items[i]->getLabel() == "Resume" || items[i]->getLabel() == "Leave level") {
            items[i]->setVisibility(true);
        }
    }
    prepareVisibles();
}

void TitleMenu::toNormalMenu() {
    index = 0;
    for (std::size_t i = 0; i < items.size(); ++i) {
        if (items[i]->getLabel() == "Resume" || items[i]->getLabel() == "Leave level") {
            items[i]->setVisibility(false);
        }
    }
    prepareVisibles();
}
