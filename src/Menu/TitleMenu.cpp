#include "TitleMenu.h"

TitleMenu::TitleMenu(std::string label, GameState state): Menu(label, state) {

}

TitleMenu::~TitleMenu() {

}

void TitleMenu::toLevelMenu() {
    index = 0;
    for (std::size_t i = 0; i < items.size(); ++i) {
        std::string itemLabel = items[i]->getLabel();
        if (itemLabel == "Resume" || itemLabel == "Leave level" || itemLabel == "Stats") {
            items[i]->setVisibility(true);
        }
    }
    prepareVisibles();
}

void TitleMenu::toNormalMenu() {
    index = 0;
    for (std::size_t i = 0; i < items.size(); ++i) {
        std::string itemLabel = items[i]->getLabel();
        if (itemLabel == "Resume" || itemLabel == "Leave level") {
            items[i]->setVisibility(false);
        } else if (itemLabel == "Stats") {
            items[i]->setVisibility(true);
        }
    }
    prepareVisibles();
}

void TitleMenu::toTitleMenu() {
    index = 0;
    for (std::size_t i = 0; i < items.size(); ++i) {
        std::string itemLabel = items[i]->getLabel();
        if (itemLabel == "Resume" || itemLabel == "Leave level" || itemLabel == "Stats") {
            items[i]->setVisibility(false);
        }
    }
    prepareVisibles();
}
