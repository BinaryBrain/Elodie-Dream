#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "../Game/GameView.h"

class Menu {
public:
    Menu();
    virtual ~Menu();

    void open();
    void close();
    void changeState();

    void draw(GameView* view);
    bool isOpened();

private:
    bool opened = false;
    sf::Font* font;
};

#endif // MENU_H
