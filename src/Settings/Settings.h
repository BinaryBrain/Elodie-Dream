#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>

#include "../Game/GameView.h"

class Settings {
public:
    Settings();
    virtual ~Settings();

    void open();
    void close();

    void changeState();
    bool isOpened();

    void draw(GameView* view);

private:
    bool opened = false;
    sf::Font* font;
};

#endif // SETTINGS_H
