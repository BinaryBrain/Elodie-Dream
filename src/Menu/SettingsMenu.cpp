#include <vector>
#include "SettingsMenu.h"

SettingsMenu::SettingsMenu() {
    opened = false;
}

SettingsMenu::~SettingsMenu() {
    //dtor
}

void SettingsMenu::open() {
    if(!opened) {
        opened = true;
    }
}

void SettingsMenu::close() {
    if(opened) {
        opened = false;
    }
}

void SettingsMenu::changeState() {
    opened = !opened;
}

bool SettingsMenu::isOpened() {
    return opened;
}
