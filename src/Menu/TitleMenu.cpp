#include "TitleMenu.h"

TitleMenu::TitleMenu(std::string label, GameState state): Menu(label, state) {

}

TitleMenu::~TitleMenu() {

}

void TitleMenu::toLevelMenu() {
    index = 0;
    for (size_t i = 0; i < items.size(); ++i) {
        std::string itemLabel = items[i]->getLabel();
        if (itemLabel == MENU_RESUME_LABEL || itemLabel == MENU_LEAVELEVEL_LABEL || itemLabel == MENU_STATS_LABEL) {
            items[i]->setVisibility(true);
        }
    }
    prepareVisibles();
}

void TitleMenu::toNormalMenu() {
    index = 0;
    for (size_t i = 0; i < items.size(); ++i) {
        std::string itemLabel = items[i]->getLabel();
        if (itemLabel == MENU_RESUME_LABEL || itemLabel == MENU_LEAVELEVEL_LABEL) {
            items[i]->setVisibility(false);
        } else if (itemLabel == MENU_STATS_LABEL) {
            items[i]->setVisibility(true);
        }
    }
    prepareVisibles();
}

void TitleMenu::toTitleMenu() {
    index = 0;
    for (size_t i = 0; i < items.size(); ++i) {
        std::string itemLabel = items[i]->getLabel();
        if (itemLabel == MENU_RESUME_LABEL || itemLabel == MENU_LEAVELEVEL_LABEL || itemLabel == MENU_STATS_LABEL) {
            items[i]->setVisibility(false);
        }
    }
    prepareVisibles();
}
