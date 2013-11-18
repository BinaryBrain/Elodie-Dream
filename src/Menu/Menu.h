#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

#include "../Game/GameView.h"

class Menu {
public:
    Menu();
    virtual ~Menu();

    void loadGame();
    void draw(GameView* view);

private:
    sf::Font* font;
};

#endif // MENU_H
