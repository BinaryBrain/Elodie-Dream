#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "../Game/GameView.h"

class SettingsMenu : public Menu {
public:
    SettingsMenu();
    virtual ~SettingsMenu();

    void open();
    void close();

    void changeState();
    bool isOpened();

private:
    bool opened = false;
};

#endif // SETTINGS_H
